//
// Created by Adam Torres on 5/30/21.
//

#include "History.h"

std::map<std::string, GUI_Component*> History::components;
std::stack<std::shared_ptr<SnapShot>> History::stack;

void History::pushHistory(std::shared_ptr<SnapShot> snapshot)
{
    stack.push(snapshot);
    CleanUpStack();
}

std::shared_ptr<SnapShot> History::topHistory()
{
    return stack.top();
}

void History::popHistory()
{
    stack.pop();
}

void History::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    //Using CTRL+Z for UNDO functionality here
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.control && event.key.code == sf::Keyboard::Z)
        {
            Undo();
        }
    }
}

void History::addComponent(std::string componentID, GUI_Component* component)
{
    components.insert(std::make_pair(componentID, component));
}

void History::Undo()
{
    if (stack.empty()) { return; }
    GUI_Component* component = components[stack.top()->component_ID];
    component->applySnapshot(stack.top());
    stack.pop();
}

void History::CleanUpStack()
{
    if (stack.size() <= 10) //Can set max # of undo elements here
        return;

    //Initialize utilityStack
    std::stack<std::shared_ptr<SnapShot>> utilityStack;

    //Loads stack in to utility stack with oldest object on top
    while (!stack.empty())
    {
        utilityStack.push(stack.top());
        stack.pop();
    }

    //oldest object is removed
    utilityStack.pop();

    //Stack is reverted to LIFO behavior in original stack
    while (!utilityStack.empty())
    {
        stack.push(utilityStack.top());
        utilityStack.pop();
    }


}
