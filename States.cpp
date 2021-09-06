//
// Created by Adam Torres on 5/30/21.
//

#include "States.h"

States::States()
{
    states.insert(std::make_pair(ObjectState::HIDDEN, false));
    states.insert(std::make_pair(ObjectState::HIGHLIGHTED, false));
    states.insert(std::make_pair(ObjectState::ENABLED, false));
    states.insert(std::make_pair(ObjectState::LASTSTATE, false));
}