//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_COLORPICKER_H
#define FINAL_PROJECT_COLORPICKER_H
#include "History.h"
#include "ColorGradient.h"
#include "ImageProperties.h"
#include "HueSelector.h"
#include "Label.h"

class ColorPicker : public GUI_Component
{
public:
    ColorPicker(sf::Color& colorRef, std::string str, sf::Vector2f pos);

    //GUI_Component Methods
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update() {};
    void takeSnapshot();
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot);

    void setColor(sf::Color color) { displaySquare.setFillColor(color); }

private:
    void AssignComponentID();
    std::string componentID;

    sf::Color& colorRef;
    std::shared_ptr<ColorGradient> colorGradient;
    sf::RectangleShape displaySquare;
    HueSelector hueSelector;
    Label label;
    bool isActive;
};


#endif //FINAL_PROJECT_COLORPICKER_H
