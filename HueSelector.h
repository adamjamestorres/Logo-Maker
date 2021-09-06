//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_HUESELECTOR_H
#define FINAL_PROJECT_HUESELECTOR_H
#include <SFML/Graphics.hpp>
#include "EventHandler.h"
#include <array>

class HueSelector : public sf::Drawable
{
public:
    HueSelector();

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void buildVertexArray();
    void setPosition(sf::Vector2f pos) { this->pos = pos; border.setPosition(pos); }
    float getSelectedHue(sf::Vector2f mousePos);
    sf::FloatRect getGlobalBounds() { return border.getGlobalBounds(); }

private:
    std::array<int, 3> findRGB(float Hue, float Saturation = 1.0f, float V = 1.0f);

    sf::VertexArray vertexArray;
    sf::RectangleShape border;
    sf::Vector2f pos;

};

#endif //FINAL_PROJECT_HUESELECTOR_H
