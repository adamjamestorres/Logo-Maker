//
// Created by Adam Torres on 5/30/21.
//

#include "HueSelector.h"
HueSelector::HueSelector()
{
    border.setFillColor(sf::Color::White);
    border.setSize({ 180.f,30.f });
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(1.0f);
}

void HueSelector::buildVertexArray()
{
    vertexArray.resize(180u * 2u);
    vertexArray.setPrimitiveType(sf::Lines);
    int lineCount;

    pos.x += 1.f;

    for (size_t i = 0; i < vertexArray.getVertexCount(); ++i)
    {
        lineCount = (i + 1) / 2;

        std::array<int, 3> Hue_RGB = findRGB(lineCount * 2);

        vertexArray[i].color = sf::Color(Hue_RGB[0], Hue_RGB[1], Hue_RGB[2]);
        vertexArray[i].position = sf::Vector2f(pos.x + lineCount, pos.y);

        ++i;

        vertexArray[i].position = sf::Vector2f(pos.x + lineCount - 1.f, pos.y + 30.f);
        vertexArray[i].color = sf::Color(Hue_RGB[0], Hue_RGB[1], Hue_RGB[2]);
    }
}

float HueSelector::getSelectedHue(sf::Vector2f mousePos)
{
    //multiplied by two to get [0,360] range
    return 2.f * (mousePos.x - border.getGlobalBounds().left - 1.f);
}

void HueSelector::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(border);
    window.draw(vertexArray);
}

std::array<int, 3> HueSelector::findRGB(float H, float S, float V)
{
    float h_i = int(H / 60.f);
    float f = H / 60.f - h_i;
    float p = V * (1 - S);
    float q = V * (1 - S * f);
    float t = V * (1 - S * (1 - f));

    float r = 0.f, g = 0.f, b = 0.f;

    if (h_i == 1) { r = q; g = V; b = p; }
    else if (h_i == 2) { r = p; g = V; b = t; }
    else if (h_i == 3) { r = p; g = q; b = V; }
    else if (h_i == 4) { r = t; g = p; b = V; }
    else if (h_i == 5) { r = V; g = p; b = q; }
    else { r = V; g = t; b = p; }

    int R = r * 255.f;
    int G = g * 255.f;
    int B = b * 255.f;

    std::array<int, 3> answer = { R, G, B };

    return answer;
}
