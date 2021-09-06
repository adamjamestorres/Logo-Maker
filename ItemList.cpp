//
// Created by Adam Torres on 5/30/21.
//

#include "ItemList.h"

void ItemList::GenerateItems(std::vector<std::string> names, unsigned int charSize, sf::RectangleShape* inputBoxBounds)
{
    //Makes ptr to temporary time before pushing on to item vector
    float count = 1.0f;

    for (auto& itr : names)
    {
        std::shared_ptr<Item> temp = std::make_shared<Item>(itr, charSize);
        temp->setPosition({ inputBoxBounds->getPosition().x, inputBoxBounds->getPosition().y + inputBoxBounds->getGlobalBounds().height * count++ });
        items.push_back(temp);
    }
}

void ItemList::setPosition(sf::RectangleShape* inputBoxBounds)
{
    float count = 1.0f;
    sf::Vector2f pos = inputBoxBounds->getPosition();
    pos.y += inputBoxBounds->getGlobalBounds().height;

    for (auto itr : items)
    {
        itr->setPosition(pos);
        pos.y += itr->rect.getGlobalBounds().height; //Updates position and prepares for next element
    }
}

void ItemList::setMatchesPosition(std::shared_ptr<Item> matchItem, float count, sf::RectangleShape* inputBoxBounds)
{
    matchItem->setPosition({ inputBoxBounds->getPosition().x, inputBoxBounds->getPosition().y +
                                                              inputBoxBounds->getGlobalBounds().height * count });
}

void ItemList::hideNonMatched(std::shared_ptr<Item> hideItem)
{
    //Moves item off rendertarget, hiding it from accidental input
    hideItem->setPosition({ -100.f,-100.f });
}

void ItemList::resize(sf::RectangleShape* inputBox, unsigned int newSize)
{
    for (auto itr : items)
    {
        itr->resize(newSize);
    }

    setPosition(inputBox);
}
