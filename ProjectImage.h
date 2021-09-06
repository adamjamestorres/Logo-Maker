//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_PROJECTIMAGE_H
#define FINAL_PROJECT_PROJECTIMAGE_H

#include "SFML/Graphics.hpp"
#include "ImageProperties.h"
#include "Constants.h"

class ProjectImage : public sf::Drawable
{
public:
    //Assets
    std::string str;
    sf::RectangleShape background;
    sf::Text text;
    sf::Font font;

    ImageProperties iProps;

    ProjectImage();

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void update();

private:
    void SetImageProperties();
    void InitializeValues();

};


#endif //FINAL_PROJECT_PROJECTIMAGE_H
