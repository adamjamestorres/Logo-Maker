//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_TEXTINPUT_H
#define FINAL_PROJECT_TEXTINPUT_H
#include "History.h"
#include "TextCursor.h"
#include "KeywordCompare.h"
#include <iostream>
#include <sstream>
#include <list>

class TextInput : public GUI_Component {
public:
    //All of the constructor functionality has been rolled in to one constructor with default values
    TextInput(std::string labelText = "Default Label", float rows = 1, float charactersWide = 40);
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update();
    void takeSnapshot();
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot);
    void setLabel(std::string labelText);
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition();
    std::string getTextString();
    void setTextString(std::string);

private:
    void AssignComponentID();
    void LoadFontFromFile(); //I store my fonts in a different position, but I did find your preferred font online
    void InitializeInputField(float rows, float charactersWide);
    void InitializeTextProperties();
    void InitializeLabel(std::string);
    void AssignCursorPosition(); //Added setCurrentRow functionality inside AssignCursor position as well as another if check
    bool LeftClickedInsideTextBox(sf::Event& event, sf::RenderWindow& window);
    bool IsNotEnabled();
    void ProcessEnteredText(sf::Event& event); //Made most all of the functionality changes within this function
    bool isUndoInput(sf::Event& event);  //Added findLastSpaceItr functionality within here
    bool willOverflow(sf::Text);

    //These are all new functions
    void AssignCursorPosition(sf::Vector2f); //overloaded cursor position function
    void setCurrentRow();
    void setSpaceItr(); //These two functions, setSpaceItr and findLastSpaceItr have almost the same function
    void findLastSpaceItr(); //We could use findLastSpaceItr everywhere setSpaceItr is, but it is much less effecient
    void moveToNextRow();


    std::list<sf::Text> textList;
    KeywordCompare keywordCompare;
    TextCursor textCursor;
    std::string componentID;
    sf::RectangleShape inputField;
    sf::Font font;
    sf::Text templateText;
    sf::Text label;

    //New data members
    std::list<sf::Text>::iterator spaceItr = textList.begin();
    const int maxRows;
    int currentRow;
};


#endif //FINAL_PROJECT_TEXTINPUT_H
