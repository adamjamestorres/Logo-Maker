//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_TEXTCURSOR_H
#define FINAL_PROJECT_TEXTCURSOR_H
#include <SFML/Graphics.hpp>
#include <iostream>


class TextCursor : public sf::Drawable
{
public:
    TextCursor();

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void update();

    void SetPosition(sf::Vector2f pos) { cursor.setPosition(pos.x-3, pos.y); }
    sf::Vector2f GetPosition() { return cursor.getPosition(); }

    void SetEnabled() { isEnabled = true; }
    void SetDisabled() { isEnabled = false; }

    void setsize(unsigned int charSize) { cursor.setCharacterSize(charSize); }

private:
    sf::Font font;
    sf::Text cursor;
    sf::Clock clock;
    float deltaTime;
    bool isEnabled = false;
};


#endif //FINAL_PROJECT_TEXTCURSOR_H
