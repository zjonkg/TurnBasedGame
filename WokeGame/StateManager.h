#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <stack>
#include <memory>
#include "State.h"
#include <iostream>

class StateManager {
public:
    void pushState(std::shared_ptr<State> state);
    void popState();
    State* getCurrentState();
    State* getPreviousState();
    bool hasStateChanged() ;
    void setStateChanged(bool stateChanged);

    void printStates() const;

private:
    bool stateChanged;
    State* m_currentState;
    State* m_previousState;
    std::stack<std::shared_ptr<State>> states;
};

#endif // STATEMANAGER_H
