//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_STATES_H
#define FINAL_PROJECT_STATES_H
#include <map>

enum class ObjectState
{
    HIDDEN = 0, HIGHLIGHTED, ENABLED, LASTSTATE
};

class States
{
public:
    States();
    bool CheckStateStatus(ObjectState objectState) { return  states[objectState]; }
    void EnableState(ObjectState objectState) { states[objectState] = true; }
    void DisableState(ObjectState objectState) { states[objectState] = false; }

private:
    std::map<ObjectState, bool> states;
};

#endif //FINAL_PROJECT_STATES_H
