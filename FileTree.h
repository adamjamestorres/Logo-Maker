//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_FILETREE_H
#define FINAL_PROJECT_FILETREE_H
#include "FileNode.h"

class FileTree : public GUI_Component
{
private:
    sf::Vector2f initPosition; //initialPosition, optionally modified w/in constructor
    std::shared_ptr<FileNode> root = nullptr; //Initialized root node, first node added shall have parent "nullptr"
    bool needsUpdate = false; //boolean flag used to reposition the nodes of the tree only if change has been made

    //Using DFS, recursively looks through tree to find root node matching parent string, if found adds
    //the insert node to the child vector of the root node
    void push(std::shared_ptr<FileNode>& root, std::shared_ptr<FileNode>& insertPtr, std::string parent);
    //Moves along the tree in a DFS fashion adding eventHandler to each node and any active child nodes
    void traverse(std::shared_ptr<FileNode>& root, sf::RenderWindow& window, sf::Event event);
    //Recursively positions each viewed node in the tree by updating the pos sf::vector2f after each
    //positioning of a node
    void positionBranches(std::shared_ptr<FileNode> currentNode, sf::Vector2f& pos, float offset);
    //Helper function to activate tree after a node is added in order to facilitate
    //repositioning, after repositioning is complete, root node is again deactivated
    void initializeBranchPositions();

public:
    //Constructor, takes in optional sf::vector2f for position
    FileTree(sf::Vector2f pos = { 0.f,0.f }) : initPosition(pos) {}

    //Adds element to the tree with provided parameters
    void push(std::string parent, ImageEnum image, std::string itemText, unsigned int size = 20u);
    //Draws the root node
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    //Used to move through the tree and addEventHandler to each FileNode
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    //Updates the position of each node recursively if a change is made to the tree
    void update();

    void setPosition(sf::Vector2f pos);

    //Not currently used for this GUI Component
    void takeSnapshot() {};
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot) {};
};
#endif //FINAL_PROJECT_FILETREE_H
