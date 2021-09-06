//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_DROPDOWNMENU_H
#define FINAL_PROJECT_DROPDOWNMENU_H
#include "History.h"
#include "ItemList.h"
#include "InputBox.h"
#include "TextCursor.h"
#include <sstream>

class DropdownMenu : public GUI_Component
{
public://Functions inherited from GUI_Component
    DropdownMenu(std::vector<std::string> strVec, sf::Vector2f pos = { 0.f,0.f }, unsigned int charSize = 20u);
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update();
    void takeSnapshot();
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot);

public: //Public functions added to class
    void setPosition(sf::Vector2f pos);
    void resize(unsigned int newSize);
    std::string getSelection() { return inputBox.text.getString(); }

private:
    bool isEnabled;             //Boolean isActive check value for input and display
    ItemList itemList;          //List of all items in provided std::string list
    InputBox inputBox;          //Display of chosen item from std::string list or entered searchText
    std::string searchString;   //searchText to be compared to items held in itemList
    std::string componentID;    //ID for GUI_Component-Dropdown menu to be used as lookup for History class

    void AssignComponentID();  //Simply assigns ID based on string representation of *this objects place in memory
    void HighlightSelection(sf::RenderWindow& window); //Sets highlight if mousepos is correct, sets no color otherwise
    void PositionMatchList();                          //Compares ItemList->Item->strings to searchstring, if beginning characters match, it positions accordingly
    void DisplayMatches(sf::RenderTarget& window) const; //Displays only items matching to searchstring

    void Enable() { isEnabled = true; }
    void Disable() { isEnabled = false; }
    bool IsEnabled() const { return isEnabled; }



};

#endif //FINAL_PROJECT_DROPDOWNMENU_H
