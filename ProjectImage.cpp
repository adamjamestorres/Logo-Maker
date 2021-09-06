//
// Created by Adam Torres on 5/30/21.
//

#include "ProjectImage.h"

ProjectImage::ProjectImage()
{
    SetImageProperties();

    str = "Default Text";

    font.loadFromFile("OpenSans-Bold.ttf");

    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(30);
    text.setPosition({iProps.xPos,iProps.yPos});
    text.setFillColor(sf::Color::Blue);

    background.setSize({ float(WINDOW_WIDTH), 270.f});
    background.setFillColor(sf::Color::White);
    background.setPosition({ 0.f,30.f });
}

void ProjectImage::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(background);
    window.draw(text);
}

void ProjectImage::update()
{
    text.setFont(iProps.textFont);
    text.setFillColor(iProps.textColor);

    text.setPosition({ iProps.xPos,iProps.yPos });
    text.setRotation(iProps.rotation);
    text.setCharacterSize((int)iProps.charSize);
    text.setString(sf::String(iProps.textString));
    background.setFillColor(iProps.backColor);
}

void ProjectImage::SetImageProperties()
{
    iProps.xPos = 200.f;
    iProps.yPos = 200.f;
    iProps.charSize = 20.f;
    iProps.rotation = 0.f;

    iProps.textColor = sf::Color::Blue;
    iProps.textString = "";
}

void ProjectImage::InitializeValues()
{

}