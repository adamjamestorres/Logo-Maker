//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_INPUTBOX_H
#define FINAL_PROJECT_INPUTBOX_H
#include <memory>
#include "Item.h"
#include "TextCursor.h"

class InputBox
{
public:
    InputBox(sf::Vector2f pos = { 0.f,0.f }, unsigned int charSize = 15u);

    void InsertSelection(std::shared_ptr<Item> selectionPtr);
    void DisplaySearchText(std::string searchString);
    void setText(sf::String str);
    void setPosition(sf::Vector2f pos);
    void resize(unsigned int newSize);
    void Update();

    sf::RectangleShape* GetRectPtr()  { return &rect; }
    sf::Text* GetTextPtr() { return &text; }

public:
    sf::RectangleShape rect;
    sf::Text text;
    TextCursor textCursor;

private:
    void LoadFont();
    void InitializeBoundingBox(unsigned int charSize, sf::Vector2f& pos); //Initializes rect bounding box
    void InitializeText(unsigned int charSize);							  //Initializes text based on characterSize
    void InitializeCursor(unsigned int charSize);
    void CenterText(); //Repositions text to center after each operation
    sf::Font font;
};



#endif //FINAL_PROJECT_INPUTBOX_H
