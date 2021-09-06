//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_MENUBAR_H
#define FINAL_PROJECT_MENUBAR_H
#include <SFML/graphics.hpp>
#include "Menu.h"
#include "EventHandler.h"
#include "Observer_Interface.h"

class MenuBar : public sf::Drawable, public EventHandler,  public Gen_Subject
{
public:

    void init(std::vector<std::vector<std::string>> menuMap, const int windowWidth);

    //From sf::Drawable
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    //EventHandler
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update() {};

private:
    std::vector<Menu> topMenus; //Vector container holding all of the menu bars across the top
    sf::RectangleShape bannerBar; //The bar that runs the length of the screen across the top of the application
    Menu* activeMenu; //Pointer to "active" menu used for selection and drawing in eventHandler
    bool isEnabled; //boolean value to set behavior of topMenu during active/inactive status in draw and eventHandler

    //Helper Functions

    void SetBanner(const int windowWidth); //Builds bar that runs the length of the screen across the top of application
    void SetMenus(std::vector<std::vector<std::string>>& menuMap); //Sets Menus based on incoming 2D vector
    void CheckActiveMenu(sf::RenderWindow& window);  //Changes activeMenu* if menu is activated but mouse cursor moves to different top menu
    void HighlightSelection(sf::RenderWindow& window); //Highlights particular elements based on
    void ResetBannerHighlights(); //Sets all banner Menus to original color
};


#endif //FINAL_PROJECT_MENUBAR_H
