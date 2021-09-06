//
// Created by Adam Torres on 5/30/21.
//

#include "FontSelector.h"

FontSelector::FontSelector(sf::Font& fontRef, sf::Vector2f pos)
        : ddMenu({"Calibri", "OpenSans-Bold"}, pos), fontRef(fontRef)
{
    fontRef.loadFromFile("OpenSans-Bold.ttf");
    currentFont = "OpenSans-Bold";

    label.setString("Font Select: ");
    label.setPosition(pos.x - label.getGlobalBounds().width - 6.f, pos.y);
}

void FontSelector::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(ddMenu);
    window.draw(label);
}

void FontSelector::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    ddMenu.addEventHandler(window, event);
}

void FontSelector::update()
{
    setFont(ddMenu.getSelection());
}

void FontSelector::takeSnapshot()
{

}

void FontSelector::applySnapshot(const std::shared_ptr<SnapShot> snapshot)
{
}

void FontSelector::setFont(std::string str)
{
    if (str == currentFont) { return; }

    if (str == "Calibri")
    {
        fontRef.loadFromFile("calibri.ttf");
        currentFont = "Calibri";
    }
    else if (str == "OpenSans-Bold")
    {
        fontRef.loadFromFile("OpenSans-Bold.ttf");
        currentFont = "OpenSans-Bold";
    }
}
