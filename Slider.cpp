//
// Created by Adam Torres on 5/30/21.
//

#include "Slider.h"

Slider::Slider(float& propRef, std::string labelText, sf::Vector2f pos, float minValue, float maxValue)
        :propRef(propRef)
{
    AssignComponentID();

    this->minValue = minValue;
    this->maxValue = maxValue;
    isActive = false;

    sliderBar.setFillColor(sf::Color::White);
    sliderBar.setSize({ 250.f,2.f });
    sliderBar.setPosition(pos);

    knob.setFillColor(sf::Color::White);
    knob.setRadius(10.f);
    knob.setOrigin(10.f, 10.f);

    float initialOffset = (sliderBar.getGlobalBounds().width/ (maxValue - minValue)) * propRef;
    knob.setPosition(pos.x + initialOffset, pos.y + sliderBar.getGlobalBounds().height/2);

    numDisplay.setOrigin(0.f, float(numDisplay.getCharacterSize()/2.f));
    numDisplay.setPosition(sliderBar.getPosition().x + sliderBar.getGlobalBounds().width + 15.f, sliderBar.getPosition().y);
    numDisplay.setString(std::to_string((int)propRef));

    labelDisplay.setOrigin(0.f, float(labelDisplay.getCharacterSize() / 2.f));
    labelDisplay.setString(labelText);
    labelDisplay.setPosition(pos.x - labelDisplay.getGlobalBounds().width - 10.f, pos.y);

    updateCurrentValue();
}

void Slider::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(sliderBar);
    window.draw(knob);
    window.draw(numDisplay);
    window.draw(labelDisplay);
}

void Slider::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    if (isActive && event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            isActive = false;
        }
    }

    if (isActive && event.type == sf::Event::MouseMoved)
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

        float X_max = sliderBar.getPosition().x + sliderBar.getGlobalBounds().width;
        float X_min = sliderBar.getPosition().x;

        //Clamps knob between max and min value
        if (mousePos.x > X_max)
        {
            knob.setPosition(X_max, knob.getPosition().y);
        }
        else if (mousePos.x < X_min)
        {
            knob.setPosition(X_min, knob.getPosition().y);
        }
        else
        {
            knob.setPosition(mousePos.x, knob.getPosition().y);
        }

        updateCurrentValue();
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            if (knob.getGlobalBounds().contains(mousePos))
            {
                isActive = true;
                takeSnapshot();
            }
        }
    }
}

void Slider::updateCurrentValue()
{
    float normalizedValue = (knob.getPosition().x - sliderBar.getPosition().x) / sliderBar.getGlobalBounds().width;

    propRef = normalizedValue * maxValue;

    numDisplay.setString(std::to_string((int)propRef));
}

void Slider::setValue()
{
    float knobXpos = sliderBar.getPosition().x + ((propRef / maxValue) * sliderBar.getGlobalBounds().width);
    knob.setPosition(knobXpos, knob.getPosition().y);
    numDisplay.setString(std::to_string((int)propRef));
}

void Slider::AssignComponentID()
{
    std::ostringstream getAddress;
    getAddress << this;
    componentID = getAddress.str();
    History::addComponent(componentID, this);
}

void Slider::takeSnapshot()
{
    float XposCopy = knob.getPosition().x;
    std::shared_ptr<SliderSnapshot> snapPtr = std::make_shared<SliderSnapshot>(componentID, XposCopy);
    History::pushHistory(snapPtr);
}

void Slider::applySnapshot(const std::shared_ptr<SnapShot> snapshot)
{
    float reverted_Xpos = std::static_pointer_cast<SliderSnapshot>(snapshot)->GetKnobPosition();
    knob.setPosition(reverted_Xpos, knob.getPosition().y);
    updateCurrentValue();
}
