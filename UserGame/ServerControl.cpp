#include <assert.h>
#include "SysTime/SysTime.h"
#include "SysThread.h"
#include "ServerGame/ServerGame.h"
#include "ServerControl.h"

namespace ServerControl {
  enum State {
    Ready,
    Starting,
    Running,
    Terminating,
    Completed
  };

  enum Command {
    Start,
    Stop
  };

  class CommandQueue {
    const static uint8_t max = 8;
    uint8_t head = 0;
    uint8_t tail = 0;
    uint8_t count = 0;
    Command list[max];
  public:
    Command getNext() const {
      return list[tail];
    }
    void next() {
      assert(count != 0);
      count--;
      tail = (tail+1) % 8;
    }
    void push(Command command) {
      assert(count != max);
      list[head] = command;
      count++;
      head = (head+1) % max;
    }
    uint16_t getCount() const {
      return count;
    }
  };

  State state = Ready;
  CommandQueue queue;
  SysThread::Mutex mutex;
  SysThread::Thread thread;

  void lock() {
    SysThread::lock(&mutex);
  }

  void unlock() {
    SysThread::unlock(&mutex);
  }

  void* run(void *data) {
    lock();
    ServerGame::initialize();
    state = Running;
    unlock();

    ServerGame::run();

    lock();
    ServerGame::terminate();
    state = Completed;
    unlock();

    return NULL;
  }

  void requestInit() {
    queue.push(Start);
  }

  void requestTermination() {
    queue.push(Stop);
  }

  bool tryServerInitialization() {
    bool result;
    lock();
    if(state == Ready) {
      state = Starting;
      SysThread::init(&thread, run);
      result = true;
    } else {
      result = false;
    }
    unlock();
    return result;
  }

  void requestServerTermination() {
    state = Terminating;
    ServerGame::requestTermination();
  }

  bool tryServerTerminationRequest() {
    bool result;
    lock();
    if(state == Running) {
      requestServerTermination();
      result = true;
    } else {
      result = false;
    }
    unlock();
    return result;
  }

  bool runNextCommand() {
    Command command = queue.getNext();
    bool success;

    switch(command) {
      case Start: {
        success = tryServerInitialization();
        break;
      }
      case Stop: {
        success = tryServerTerminationRequest();
        break;
      }
    }

    if(success) {
      queue.next();
    }

    return success;
  }

  void runCommands() {
    while(queue.getCount() != 0) {
      if(!runNextCommand()) {
        return;
      }
    }
  }

  void checkCompleted() {
    lock();
    if(state == Completed) {
      SysThread::join(&thread);
      state = Ready;
    }
    unlock();
  }

  void update() {
    runCommands();
    checkCompleted();
  }

  void initialize() {
    SysThread::initMutex(&mutex);
  }

  void terminate() {
    sync();
    SysThread::destroyMutex(&mutex);
  }

  void sync() {
    while(1) {
      update();
      lock();
      bool synced = (
        queue.getCount() == 0 &&
        (state == Ready || state == Running)
      );
      unlock();
      if(synced) {
        return;
      }
      SysTime::sleep(1000);
    }
  }
}
