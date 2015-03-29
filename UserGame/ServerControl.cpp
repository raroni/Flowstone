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

  void runCommandsBlocking() {
    while(queue.getCount() != 0) {
      if(!runNextCommand()) {
        SysTime::sleep(1000);
      }
    }
  }

  void runCommandsNonBlocking() {
    while(queue.getCount() != 0) {
      if(!runNextCommand()) {
        return;
      }
    }
  }

  void joinThread() {
    SysThread::join(&thread);
    state = Ready;
  }

  void checkCompleted() {
    lock();
    if(state == Completed) {
      joinThread();
    }
    unlock();
  }

  void update() {
    runCommandsNonBlocking();
    checkCompleted();
  }

  void initialize() {
    SysThread::initMutex(&mutex);
  }

  State getState() {
    lock();
    State copy = state;
    unlock();
    return copy;
  }

  void waitForCompleted() {
    while(1) {
      if(getState() == Completed) {
        return;
      }
      SysTime::sleep(1000);
    }
  }

  void sync() {
    runCommandsBlocking();
    // todo: ensure we arrive at either
    // ready or running
    // that all commands are executed does
    // not mean all work has been done
  }

  void terminate() {
    runCommandsBlocking();

    State stateCopy = getState();
    assert(stateCopy != Starting || stateCopy != Running);
    if(stateCopy == Terminating) {
      waitForCompleted();
      joinThread();
    }
    else if(stateCopy == Completed) {
      joinThread();
    }

    SysThread::destroyMutex(&mutex);
  }
}
