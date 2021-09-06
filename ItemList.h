//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_ITEMLIST_H
#define FINAL_PROJECT_ITEMLIST_H
#include "Item.h"
#include <memory>

class ItemList
{
public:
    void GenerateItems(std::vector<std::string> names, unsigned int charSize, sf::RectangleShape* inputBox);
    void setPosition(sf::RectangleShape* inputBox);
    void setMatchesPosition(std::shared_ptr<Item> matchItem, float count, sf::RectangleShape* inputBox);
    void hideNonMatched(std::shared_ptr<Item> hideItem);
    void resize(sf::RectangleShape* inputBox, unsigned int newSize);

    std::vector<std::shared_ptr<Item>> GetItems() const& { return items; }

private:
    std::vector<std::shared_ptr<Item>> items;
};

#endif //FINAL_PROJECT_ITEMLIST_H
