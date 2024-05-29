#include "StateManager.h"



void StateManager::pushState(std::shared_ptr<State> state) {
    states.push(state);
    stateChanged = true;
}

void StateManager::printStates() const {
    std::stack<std::shared_ptr<State>> tempStates = states;
    std::vector<std::string> stateNames;

    while (!tempStates.empty()) {
        stateNames.push_back(tempStates.top()->getStateName());
        tempStates.pop();
    }

    std::cout << "Current States in Stack (top to bottom):\n";
    for (auto it = stateNames.rbegin(); it != stateNames.rend(); ++it) {
        std::cout << *it << std::endl;
    }
}

void StateManager::popState() {
    if (!states.empty()) {
        states.pop();
    }
}

State* StateManager::getCurrentState() {
    if (!states.empty()) {
        return states.top().get();
    }
    return nullptr;
}

State* StateManager::getPreviousState() {
    return m_previousState;
}

bool StateManager::hasStateChanged() 
{
    return stateChanged;
}

void StateManager::setStateChanged(bool stateChanged)
{
    stateChanged = stateChanged;
}


