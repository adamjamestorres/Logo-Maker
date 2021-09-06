//
// Created by Adam Torres on 5/30/21.
//

#include "Menu.h"

Menu::Menu(std::vector<std::string> menuList,sf::Vector2f pos)
{
    //Initialize bannerItem shared pointer
    bannerItem = std::make_shared<Item>(menuList[0], 20u, pos);
    bannerItem->setBoundarySize({ bannerItem->text.getGlobalBounds().width + 20.f, bannerItem->text.getGlobalBounds().height + 20.f });
    bannerItem->setColor(sf::Color::Transparent);
    bannerItem->rect.setOutlineThickness(0.f);
    bannerItem->rect.setOutlineColor(sf::Color::Transparent);

    menuList.erase(menuList.begin()); //Eliminates first element from vector

    //Pushes remainder on to the item list
    itemList.GenerateItems(menuList, 20u, &bannerItem->rect);
    itemList.setPosition(&bannerItem->rect);
}

void Menu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(bannerItem->rect);
    window.draw(bannerItem->text);
}