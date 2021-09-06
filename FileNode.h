//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_FILENODE_H
#define FINAL_PROJECT_FILENODE_H
#include "FileItem.h"

class FileNode : public GUI_Component
{
private:
    FileItem data; //Entities drawn to screen holding text data
    bool& needsUpdate; //Boolean flag reference signalling filetree for reposition
    std::vector<std::shared_ptr<FileNode>> children; //Child nodes of current node

    void toggleChildren(); //If children are active, makes inactive as well as reverse
    void resetChildren(std::shared_ptr<FileNode>& nodePtr); //Recursively inactivates child nodes of node who is inactivated

public:
    //Constructor taking in the data for whether the image is a file or folder, the text string, the size of the letters,
    // as well as the initial position of the node, and a reference to the needsUpdate flag, this information is then immediately
    // passed to the FileItem "data" constructor and the reference to the needsUpdate flag is stored locally
    FileNode(ImageEnum icon, std::string text, unsigned int size, sf::Vector2f position, bool& needsUpdate)
            : data(icon, text, size, position), needsUpdate(needsUpdate) {}

    bool isActive = false; //boolean flag relaying whether the children of this particular node are active, default is set to false

    //draws the data to the screen and recursively calls the draw function for active child nodes
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    //Checks whether the fileNode has been clicked, if yes, activates the child nodes and highlights clicked node
    void addEventHandler(sf::RenderWindow& window, sf::Event event);

    //Getter and Setter Functions
    void reposition(sf::Vector2f pos) { data.setPosition(pos); }
    std::vector<std::shared_ptr<FileNode>>& getChildren() { return children; }

    void setData(const FileItem& data) { this->data = data; }
    FileItem& getData() { return data; }
    sf::FloatRect getGlobalBounds() { return data.getGlobalBounds(); }



    //Not used in this instance of GUI_Component
    void takeSnapshot() {};
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot) {};
    void update() {};
};

#endif //FINAL_PROJECT_FILENODE_H
