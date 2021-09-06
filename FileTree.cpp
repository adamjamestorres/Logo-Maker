//
// Created by Adam Torres on 5/30/21.
//

#include "FileTree.h"
//Private

//Private push function that recursively searches for root node with matching string to parent node.
//If found, the "insertPtr" node is placed in to the child vector of the parent node "root"
void FileTree::push(std::shared_ptr<FileNode>& root, std::shared_ptr<FileNode>& insertPtr, std::string parent)
{
    if (parent == "nullptr") { root = insertPtr; return; } //Checks if initial node

    if (parent == std::string(root->getData().text.getString())) //Checks provided string against root nodes string
    {
        root->getChildren().push_back(insertPtr);
        return;
    }

    for (auto& itr : root->getChildren()) //recursively calls child nodes in DFS fashion
    {
        push(itr, insertPtr, parent);
    }
}

//Recursively adds eventhandler to current node and any active children in DFS fashion
void FileTree::traverse(std::shared_ptr<FileNode>& nodePtr, sf::RenderWindow& window, sf::Event event)
{
    nodePtr->addEventHandler(window, event); //Adds eventhandler to current node

    if (nodePtr->isActive)
    {
        for (auto& itr : nodePtr->getChildren())
        {
            traverse(itr, window, event); //If active, calls each child node recursively to add eventhandler
        }
    }
}

void FileTree::positionBranches(std::shared_ptr<FileNode> currentNode, sf::Vector2f& pos, float offset)
{
    currentNode->reposition({ pos.x + offset, pos.y }); //Positions current node

    pos = { pos.x, pos.y + currentNode->getData().rect.getGlobalBounds().height }; //updates position to ready pos for next node

    if (currentNode->isActive)
    {
        //"offset" is temporary variable whereas "pos" is carried through the recursion by reference
        //because we are going to continually increase the .y position of pos based on the number of active nodes,
        //but the offset is only going to get bigger if we go deeper in to a child tree. If we come back out of that child branch
        //to continue placing position of nodes, then the offset will again be what it was for other child nodes at that level of the tree.

        offset += 20.0f;

        for (auto itr : currentNode->getChildren())
        {
            positionBranches(itr, pos, offset); //If active, recursively calls child nodes in DFS fashion
        }
    }
}

//Helper function to activate root node to reposition branches whenever a node is added to the tree
void FileTree::initializeBranchPositions()
{
    root->isActive = true; //Activates root node
    sf::Vector2f tempPosition = initPosition; //Initializes temporary position that can be updated recursively
    positionBranches(root, tempPosition, 0.f);  //in this positionBranches function
    root->isActive = false; //Deactivates root node
}

void FileTree::setPosition(sf::Vector2f pos)
{
    initPosition = pos;
}

void FileTree::push(std::string parent, ImageEnum image, std::string itemText, unsigned int size)
{
    std::shared_ptr<FileNode> rootPtr = root; // New pointer to original root node which can be updated recursively
    std::shared_ptr<FileNode> insertPtr = std::make_shared<FileNode>(image, itemText, size, initPosition, needsUpdate); //Node to insert

    push(root, insertPtr, parent); //private push, adds node to provided parent node

    initializeBranchPositions(); //Helper function to reposition brances
}

void FileTree::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    root->draw(window, states); //draws root node
}

void FileTree::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    traverse(root, window, event); //Adds event handler to each fileNode
}

void FileTree::update()
{
    if (needsUpdate == false) { return; } //Boolean flag checking if change within tree has been made

    sf::Vector2f tempPos = initPosition;  //Initialize temporary position variable which can be updated recursively
    positionBranches(root, tempPos, 0.f); //Updates recursively the position of each visible node
    needsUpdate = false; //Update has been made, so flag is reset
}