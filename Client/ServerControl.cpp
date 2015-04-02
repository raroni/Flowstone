#include <assert.h>
#include "SysTime/SysTime.h"
#include "SysThread.h"
#include "Server/Game.h"
#include "ServerControlQueue.h"
#include "ServerControl.h"

namespace ServerControl {
  enum State {
    Ready,
    Starting,
    Running,
    Terminating,
    Completed
  };

  State state = Ready;
  ServerControlQueue queue;
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
    Server::Game::initialize();
    state = Running;
    unlock();

    Server::Game::run();

    lock();
    Server::Game::terminate();
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
    Server::Game::requestTermination();
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
    ServerControlCommand command = queue.getNext();
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
