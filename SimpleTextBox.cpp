//
// Created by Adam Torres on 5/30/21.
//

#include "SimpleTextBox.h"

SimpleTextBox::SimpleTextBox()
{
    AssignComponentID();
    InitializeValues();
}

void SimpleTextBox::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(inputField);
    window.draw(text);
    window.draw(textCursor);
    window.draw(label);
}

void SimpleTextBox::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    if (LeftClickedInsideTextBox(event, window))
    {
        return;
    }
    if (IsNotEnabled())
    {
        return;
    }
    ProcessEnteredText(event);
}

void SimpleTextBox::update()
{
    textCursor.update();
}

void SimpleTextBox::takeSnapshot()
{
    std::string temp = text.getString();
    std::shared_ptr<SimpleTextBoxSnapshot> snapPtr = std::make_shared<SimpleTextBoxSnapshot>(componentID, temp);
    History::pushHistory(snapPtr);
}

void SimpleTextBox::applySnapshot(const std::shared_ptr<SnapShot> snapshot)
{
    this->text.setString(std::static_pointer_cast<SimpleTextBoxSnapshot>(snapshot)->getTextString());
    AssignCursorPosition();
}

void SimpleTextBox::setTextString(std::string str)
{
    text.setString(str);
    AssignCursorPosition();
}

void SimpleTextBox::setSize(int charactersWide, int rows)
{
    inputField.setSize(sf::Vector2f(charactersWide * 6.f, rows * 22.f + 13.f));
}

void SimpleTextBox::setPosition(sf::Vector2f pos)
{
    inputField.setPosition(pos);
    text.setPosition(inputField.getPosition().x + 5, inputField.getPosition().y + 2);
    AssignCursorPosition();
}

void SimpleTextBox::AssignComponentID()
{
    std::ostringstream getAddress;
    getAddress << this;
    componentID = getAddress.str();
    History::addComponent(componentID, this);
}

void SimpleTextBox::InitializeValues()
{
    inputField.setFillColor(sf::Color::Transparent);
    inputField.setOutlineColor(sf::Color::White);
    inputField.setOutlineThickness(2.f);
    inputField.setSize({ 2.f,2.f });

    font.loadFromFile("../Fonts/OpenSans-Bold.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20u);
    text.setPosition(inputField.getPosition().x + 5, inputField.getPosition().y + 2);

    textCursor.setsize(20u);
}

bool SimpleTextBox::isUndoInput(sf::Event& event)
{
    if (event.text.unicode == 26) {
        return true;
    }
    else
    {
        return false;
    }
}

bool SimpleTextBox::willOverflow()
{
    float diff = textCursor.GetPosition().x - (inputField.getGlobalBounds().left + inputField.getGlobalBounds().width);
    if (std::abs(diff) < 20.f)
    {
        return true;
    }

    return false;
}

void SimpleTextBox::ProcessEnteredText(sf::Event& event)
{
    if (event.type == sf::Event::TextEntered)
    {
        if (isUndoInput(event)) { return; }

        if (event.text.unicode == 13)
        {
            if (std::string(text.getString()).empty()) { return; }
            return;
        }

        if (event.text.unicode == 8) // if backspace key is pressed
        {
            std::string temp = text.getString();
            if (temp.empty()) { return; }

            takeSnapshot();
            temp.resize(temp.size() - 1); //delete last element
            text.setString(temp); //seet string
        }
        else
        {
            if(willOverflow()) {return;}

            sf::String temp = text.getString();
            takeSnapshot();
            temp += event.text.unicode;
            text.setString(temp);
        }

        AssignCursorPosition();
    }
}

bool SimpleTextBox::LeftClickedInsideTextBox(sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            if (inputField.getGlobalBounds().contains(mousePos))
            {
                textCursor.SetEnabled();
                EnableState(ObjectState::ENABLED);
                return true;
            }

            textCursor.SetDisabled();
            this->DisableState(ObjectState::ENABLED);
        }
    }
    return false;
}

bool SimpleTextBox::IsNotEnabled()
{
    return !this->CheckStateStatus(ObjectState::ENABLED);
}

void SimpleTextBox::AssignCursorPosition()
{
    if (std::string(text.getString()).empty())
    {
        textCursor.SetPosition(sf::Vector2f(inputField.getPosition().x + 5.f, inputField.getPosition().y + 2.f));
    }
    else
    {
        textCursor.SetPosition(sf::Vector2f(inputField.getPosition().x + text.getGlobalBounds().width + 8.f, inputField.getPosition().y));
    }
}