#ifndef ACTIONS_NODE_INTERFACE_H
#define ACTIONS_NODE_INTERFACE_H

namespace Actions {
  struct NodeInterface {
    typedef void (*StartFunction)(const void *config, void *state);
    typedef uint8_t (*CalcLengthFunction)(const void *args);
    typedef void (*ConfigureFunction)(const void *args, void *config);

    StartFunction start;
    CalcLengthFunction calcConfigLength;
    CalcLengthFunction calcStateLength;
    ConfigureFunction configure;
  };
}

#endif
