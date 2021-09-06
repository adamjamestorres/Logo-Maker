//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_FILEITEM_H
#define FINAL_PROJECT_FILEITEM_H
#include "GUI_Component.h"
#include "Item.h"
#include "Image.h"

class FileItem : public Item
{
public:
    //Constructor taking in requisite parameters for icon, text string, charactersize, and initial position
    FileItem(ImageEnum image, std::string text, unsigned int size, sf::Vector2f position);

    //Draws rect background, text, and icon to screen
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;

    //Sets position of the item data such as rect background, text and icon
    //It then calls leftAlignText to place in proper position
    void setPosition(sf::Vector2f pos);

    //Getter Functions
    sf::FloatRect getGlobalBounds() const { return rect.getGlobalBounds(); }
    sf::Vector2f getSize() const { return rect.getSize(); }
    sf::Vector2f getPosition() const { return rect.getPosition(); }

private:
    Image icon; //Icon which loads in file or folder based on enumeration

    //Helper Functions
    //Sets rect preferences for this Directory Use case
    void SetItemPreferences();
    //Aligns text to the left of the bounding rect, to the right of the icon
    void LeftAlignText();
};
#endif //FINAL_PROJECT_FILEITEM_H
