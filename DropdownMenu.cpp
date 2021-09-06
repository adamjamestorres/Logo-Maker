//
// Created by Adam Torres on 5/30/21.
//

#include "DropdownMenu.h"

DropdownMenu::DropdownMenu(std::vector<std::string> strVec, sf::Vector2f pos, unsigned int charSize)
        : inputBox(pos, charSize), isEnabled(false), searchString("")
{
    AssignComponentID();
    itemList.GenerateItems(strVec, 20u, inputBox.GetRectPtr());
}

void DropdownMenu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(inputBox.rect);
    window.draw(inputBox.text);

    if (IsEnabled())
    {
        DisplayMatches(window);
        window.draw(inputBox.textCursor);
    }
}

void DropdownMenu::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        HighlightSelection(window);
    }


    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            if (IsEnabled())
            {

                bool itemSelected = false;

                for (auto itr : itemList.GetItems())
                {
                    if (itr->rect.getGlobalBounds().contains(mousePos))
                    {
                        takeSnapshot();
                        inputBox.InsertSelection(itr);
                        searchString = inputBox.GetTextPtr()->getString();
                        itemSelected = true;
                        break;
                    }

                }

                //clears input in box if a listed option is not selected
                if (itemSelected == false)
                {
                    searchString.clear();
                    inputBox.DisplaySearchText(searchString);
                }
            }

            if (inputBox.GetRectPtr()->getGlobalBounds().contains(mousePos))
            {
                Enable();
                PositionMatchList();
                return;
            }

            Disable();
        }
    }
    if (IsEnabled() == false) { return; }

    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode == 26) { return; } //Ignore input if == to Ctrl+Z

        if (!searchString.empty() && event.text.unicode == 8)
        {

            searchString.pop_back();
            takeSnapshot();
            inputBox.DisplaySearchText(searchString);
            PositionMatchList();
            return;
        }
        else if(event.text.unicode == 8)
        {
            //Avoiding pushing null character on to searchString
            //if string is empty as well as avoiding popback
            return;
        }

        searchString.push_back(event.text.unicode);
        takeSnapshot();
        inputBox.DisplaySearchText(searchString);
        PositionMatchList();
    }
}

void DropdownMenu::update()
{
    inputBox.Update();
}

void DropdownMenu::takeSnapshot()
{
    sf::String stringCopy = inputBox.GetTextPtr()->getString();
    std::shared_ptr<DropDownSnapShot> snapPtr = std::make_shared<DropDownSnapShot>(componentID, stringCopy);
    History::pushHistory(snapPtr);
}

void DropdownMenu::applySnapshot(const std::shared_ptr<SnapShot> snapshot)
{
    //Applies stored data string to both displayed and search string to revert to previous
    //data point

    this->inputBox.setText(std::static_pointer_cast<DropDownSnapShot>(snapshot)->GetString());
    searchString = inputBox.GetTextPtr()->getString();
    PositionMatchList();
}

void DropdownMenu::setPosition(sf::Vector2f pos)
{
    inputBox.setPosition(pos);
    itemList.setPosition(inputBox.GetRectPtr());
}

void DropdownMenu::resize(unsigned int newSize)
{
    inputBox.resize(newSize);
    itemList.resize(inputBox.GetRectPtr(), newSize);
}

void DropdownMenu::AssignComponentID()
{
    std::ostringstream getAddress;
    getAddress << this;
    componentID = getAddress.str();
    History::addComponent(componentID, this);
}

void DropdownMenu::HighlightSelection(sf::RenderWindow& window)
{
    if (isEnabled == false) { return; }

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    for (auto item : itemList.GetItems())
    {
        if (item->rect.getGlobalBounds().contains(mousePos))
        {
            item->rect.setFillColor(sf::Color::Yellow); //If item rectangle is hovered over (contains mousePos) then set color to yellow
            continue;
        }

        item->rect.setFillColor(sf::Color::Black);
    }
}

void DropdownMenu::PositionMatchList()
{
    float count = 1.0f;

    for (auto& item : itemList.GetItems())
    {
        std::string itemString = item->text.getString();

        if (searchString.empty() || itemString.substr(0, searchString.size()) == searchString)
        {
            itemList.setMatchesPosition(item, count++, inputBox.GetRectPtr());
            continue;
        }
        itemList.hideNonMatched(item);
    }
}

void DropdownMenu::DisplayMatches(sf::RenderTarget& window) const
{
    float count = 1.0f;

    for (auto& item : itemList.GetItems())
    {
        std::string itemString = item->text.getString();

        if (searchString.empty() || itemString.substr(0, searchString.size()) == searchString)
        {
            window.draw(item->rect);
            window.draw(item->text);
            continue;
        }
    }
}
