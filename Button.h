//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_BUTTON_H
#define FINAL_PROJECT_BUTTON_H
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
    sf::Text text;
    sf::RectangleShape rect;

    Button();
    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    sf::FloatRect getGlobalBounds() { return rect.getGlobalBounds(); }

private:
    sf::Font font;
};
#endif //FINAL_PROJECT_BUTTON_H
