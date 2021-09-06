//
// Created by Adam Torres on 5/30/21.
//

#include "Image.h"

Image::Image(ImageEnum image, unsigned int size)
{
    //Builds multiplier by dividing the desired character size by the default size
    float sizeMultiplier = float(size) / 20.f;

    //Loads correct .png file to sf::Texture based on image enum
    if (image == ImageEnum::file)
    {
        texture.loadFromFile("file.png");
        this->setScale(sf::Vector2f(0.04 * sizeMultiplier, 0.04 * sizeMultiplier)); //sets scale for image
    }
    else if (image == ImageEnum::folder)
    {
        texture.loadFromFile("folder.png");
        this->setScale(sf::Vector2f(.02f * sizeMultiplier, .02f * sizeMultiplier)); //sets scale for image
    }

    this->setTexture(texture); //Binds chosen texture to the sprite
}