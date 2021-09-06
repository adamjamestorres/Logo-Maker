//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_IMAGE_H
#define FINAL_PROJECT_IMAGE_H
#include <SFML/Graphics.hpp>

enum class ImageEnum { file = 1, folder };


class Image : public sf::Sprite //Image inherits from sprite therefore has drawable interface
{
public:
    //Public constructor for image which takes in the enum for
    //Which icon to show as well as the character size
    Image(ImageEnum image, unsigned int size);
private:
    sf::Texture texture; //Texture which loads the image to bind to the sprite
};


#endif //FINAL_PROJECT_IMAGE_H
