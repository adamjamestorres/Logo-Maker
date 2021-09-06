//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_SLIDER_H
#define FINAL_PROJECT_SLIDER_H
#include "History.h"
#include <sstream>
#include <iostream>
#include "Label.h"

class Slider : public GUI_Component
{


public:
    Slider(float& propRef, std::string labelText = "", sf::Vector2f pos = { 0.f,0.f }, float minValue = 0.f, float maxValue = 10.f);

    //GUI_Component Required Methods
    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update() {};
    void takeSnapshot();
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot);
    //Added Methods
    void updateCurrentValue();
    void setValue();

private:
    void AssignComponentID();

private:
    std::string componentID;

    float& propRef;
    float minValue;
    float maxValue;
    bool isActive;

    sf::RectangleShape sliderBar;
    sf::CircleShape knob;
    Label numDisplay;
    Label labelDisplay;
};


#endif //FINAL_PROJECT_SLIDER_H
