//
// Created by Adam Torres on 5/30/21.
//

#include "ColorPicker.h"

ColorPicker::ColorPicker(sf::Color& colorRef, std::string str, sf::Vector2f pos)
        :colorRef(colorRef), colorGradient(nullptr)
{
    AssignComponentID();

    isActive = false;

    displaySquare.setFillColor(colorRef);
    displaySquare.setOutlineThickness(2u);
    displaySquare.setOutlineColor(sf::Color::White);
    displaySquare.setPosition(pos);
    displaySquare.setSize({ 25.f,25.f });

    hueSelector.setPosition({ displaySquare.getPosition().x-1.f, displaySquare.getPosition().y + 27.f });
    hueSelector.buildVertexArray();

    label.setString(str);
    label.setCharacterSize(15u);
    label.setPosition(displaySquare.getPosition().x - label.getGlobalBounds().width - 10.f,displaySquare.getPosition().y);
}

void ColorPicker::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(label);
    window.draw(displaySquare);

    if (isActive == false) { return; }

    window.draw(hueSelector);
    window.draw(*colorGradient);
}

void ColorPicker::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            if (displaySquare.getGlobalBounds().contains(mousePos))
            {
                isActive = true;
                colorGradient = std::make_shared<ColorGradient>
                        (241.f, sf::Vector2f(displaySquare.getPosition().x -2 , displaySquare.getPosition().y + 60.f));
                return;
            }

            if (isActive && hueSelector.getGlobalBounds().contains(mousePos))
            {
                float hue = hueSelector.getSelectedHue(mousePos);
                colorGradient = std::make_shared<ColorGradient>
                        (hue, sf::Vector2f(displaySquare.getPosition().x - 2, displaySquare.getPosition().y + 60.f));
                isActive = true;
                return;
            }

            if(isActive && colorGradient->getGlobalBounds().contains(mousePos))
            {
                takeSnapshot(); //Take Snapshot right before change is made

                sf::Color selectedColor = colorGradient->getChosenColor(mousePos);
                displaySquare.setFillColor(selectedColor);
                colorRef = selectedColor;

                isActive = true;
                return;
            }

            isActive = false;
        }
    }
}

void ColorPicker::takeSnapshot()
{
    sf::Color colorCopy = displaySquare.getFillColor();
    std::shared_ptr<ColorPickerSnapshot> snapPtr = std::make_shared<ColorPickerSnapshot>(componentID, colorCopy);
    History::pushHistory(snapPtr);
}

void ColorPicker::applySnapshot(const std::shared_ptr<SnapShot> snapshot)
{
    sf::Color colorCopy = std::static_pointer_cast<ColorPickerSnapshot>(snapshot)->getColor();
    displaySquare.setFillColor(colorCopy);
    colorRef = colorCopy;
}

void ColorPicker::AssignComponentID()
{
    std::ostringstream getAddress;
    getAddress << this;
    componentID = getAddress.str();
    History::addComponent(componentID, this);
}