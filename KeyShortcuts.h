//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_KEYSHORTCUTS_H
#define FINAL_PROJECT_KEYSHORTCUTS_H
#include <SFML/Graphics.hpp>
#include <iostream>

class KeyShortcuts
{
public:

    static bool isUndo()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
            return true;

        return false;
    }
};



#endif //FINAL_PROJECT_KEYSHORTCUTS_H
