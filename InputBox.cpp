//
// Created by Adam Torres on 5/30/21.
//

#include "InputBox.h"

InputBox::InputBox(sf::Vector2f pos, unsigned int charSize)
{
    LoadFont();
    InitializeBoundingBox(charSize, pos);
    InitializeText(charSize);
    InitializeCursor(charSize);
    CenterText();
}

void InputBox::InsertSelection(std::shared_ptr<Item> selectionPtr)
{
    text.setString(selectionPtr->text.getString());
    CenterText();
}

void InputBox::DisplaySearchText(std::string searchString)
{
    text.setString(searchString);
    CenterText();
}

void InputBox::setText(sf::String str)
{
    text.setString(str);
    CenterText();
}

void InputBox::setPosition(sf::Vector2f pos)
{
    rect.setPosition(pos);
    CenterText();
}

void InputBox::resize(unsigned int newSize)
{
    rect.setSize({ float(newSize) * 10.f, float(newSize) + 10.f });
    text.setCharacterSize(newSize);
    textCursor.setsize(newSize);
    CenterText();
}

void InputBox::Update()
{
    textCursor.update();
}

//Helper Functions
void InputBox::LoadFont()
{
    if (!font.loadFromFile("../Fonts/OpenSans-Bold.ttf"))
    {
        std::cout << "Error, failed to load fonts in Item \n";
    }
}

void InputBox::CenterText()
{
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect rectBounds = rect.getGlobalBounds();

    text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
    text.setPosition(rectBounds.left + (rectBounds.width / 2.f),
                     rectBounds.top + (rectBounds.height / 3.f));

    textCursor.SetPosition({ text.getPosition().x + textBounds.width / 2.0f, rectBounds.top + (rectBounds.height/10.0f) });
}

void InputBox::InitializeBoundingBox(unsigned int charSize, sf::Vector2f& pos)
{
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(2.0f);
    rect.setSize({ float(charSize) * 10.f, float(charSize) + 10.f });
    rect.setOutlineColor(sf::Color::White);
    rect.setPosition(pos);
}

void InputBox::InitializeText(unsigned int charSize)
{
    text.setFont(font);
    text.setString("");
    text.setCharacterSize(charSize);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);
}

void InputBox::InitializeCursor(unsigned int charSize)
{
    textCursor.SetEnabled();
    textCursor.setsize(charSize);
}
