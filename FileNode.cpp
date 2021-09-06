//
// Created by Adam Torres on 5/30/21.
//

#include "FileNode.h"

void FileNode::toggleChildren()
{
    if (isActive) {

        isActive = false; //If active, sets to inactive

        for (auto itr : getChildren())
        {
            resetChildren(itr); //Recursively sets child nodes of deactivated node to inactive
        }
    }
    else { isActive = true; } //if inactive, sets to active
}

void FileNode::resetChildren(std::shared_ptr<FileNode>& nodePtr)
{
    nodePtr->isActive = false;

    for (auto itr : nodePtr->getChildren())
    {
        itr->resetChildren(itr); //recursively sets child nodes to inactive
    }
}

void FileNode::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    data.draw(window, states); //Draws data structures to screen

    if (isActive) {
        for (auto itr : children)
        {
            itr->draw(window, states); //Recursively calls draw call for all active child nodes
        }
    }

}

void FileNode::addEventHandler(sf::RenderWindow& window, sf::Event event)
{

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            if (this->data.rect.getGlobalBounds().contains(mousePos)) //Checks if node is clicked on
            {
                this->toggleChildren(); //Activates or inactivates child node
                needsUpdate = true; //Sets boolean flag to signal need for repositioning
                data.rect.setFillColor(sf::Color::Yellow); //Highlights current node
            }
            else
            {
                data.rect.setFillColor(sf::Color::Transparent); //Resets color of current node
            }
        }
    }
}