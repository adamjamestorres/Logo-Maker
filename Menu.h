//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_MENU_H
#define FINAL_PROJECT_MENU_H
#include "ItemList.h"


class Menu : public sf::Drawable
{
public:
    Menu(std::vector<std::string> menuList, sf::Vector2f pos);
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    //Getter Functions

    std::shared_ptr<Item> GetBannerItem() { return bannerItem; }
    ItemList GetItemList() const& { return itemList; }

private:
    std::shared_ptr<Item> bannerItem; //Holds banner item at top of menu
    ItemList itemList; //Holds items kept in list underneath banner menu
};


#endif //FINAL_PROJECT_MENU_H
