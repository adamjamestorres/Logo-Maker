//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_FONTSELECTOR_H
#define FINAL_PROJECT_FONTSELECTOR_H
#include "DropdownMenu.h"
#include "History.h"
#include <SFML/Graphics.hpp>


class FontSelector : public GUI_Component
{
public:
    FontSelector(sf::Font& fontRef, sf::Vector2f pos);

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update();
    void takeSnapshot();
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot);

    Label& getLabel() { return label; }

private:
    void setFont(std::string);

    sf::Font& fontRef;
    std::string currentFont;
    DropdownMenu ddMenu;
    Label label;
};


#endif //FINAL_PROJECT_FONTSELECTOR_H
