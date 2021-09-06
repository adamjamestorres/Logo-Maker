//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_HISTORY_H
#define FINAL_PROJECT_HISTORY_H
#include "GUI_Component.h"
#include <stack>
#include <iostream>
#include <sstream>

class History
{
private:
    static std::stack<std::shared_ptr<SnapShot>> stack;
    static std::map<std::string, GUI_Component*> components;

public:
    static void pushHistory(std::shared_ptr<SnapShot> snapshot);
    static std::shared_ptr<SnapShot> topHistory();
    static void popHistory();
    static void addEventHandler(sf::RenderWindow& window, sf::Event event);
    static void addComponent(std::string componentID, GUI_Component* component);
    static void Undo();

private:
    static void CleanUpStack();
};


#endif //FINAL_PROJECT_HISTORY_H
