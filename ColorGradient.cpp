//
// Created by Adam Torres on 5/30/21.
//

#include "ColorGradient.h"

ColorGradient::ColorGradient(float h,sf::Vector2f pos)
        : vertexArray(sf::Points, 255u*255u), pos(pos), chosenHue(h)
{
    pos.x += 1.f;
    pos.y -= 1.f;

    backdrop.setPosition(pos);
    backdrop.setSize({255.f,255.f});
    backdrop.setFillColor(sf::Color::White);
    backdrop.setOutlineColor(sf::Color::White);
    backdrop.setOutlineThickness(1.0f);

    // builds color gradient with a different color value for each pixel
    double v = 1;
    double s = 1;

    float xPos = pos.x - 1.0f;
    float yPos = pos.y + 1.0f;

    double increment = 1.0 / 255.f;

    for (int i = 0; i < 255; ++i)
    {
        v = 1;
        s -= increment;

        for (int j = 0; j < 255; ++j)
        {
            v -= increment;
            std::array<int, 3> rgb_array;
            rgb_array = findRGB(h, s, v);
            vertexArray[(255 * i) + j].position = sf::Vector2f(xPos + 255 - i, yPos + j);
            vertexArray[(255 * i) + j].color = sf::Color(rgb_array[0], rgb_array[1], rgb_array[2]);
        }
    }
}

void ColorGradient::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(backdrop);
    window.draw(vertexArray);
}

sf::Color ColorGradient::getChosenColor(sf::Vector2f mousePos)
{
    float saturation = ((mousePos.x - backdrop.getGlobalBounds().left))/255.f;
    float value = (255-(mousePos.y- backdrop.getGlobalBounds().top))/255.f;

    std::array<int,3> colorArr = findRGB(chosenHue, saturation, value);

    return sf::Color(colorArr[0], colorArr[1], colorArr[2]);
}

std::array<int, 3> ColorGradient::findRGB(float H, float S, float V)
{
    //Implementation of provided german HSV to RGB formulas
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

    //Values are solved in scaled of [0,1], need to multiply by 255
    // for conversion for sf::color spectrum in range of [0,255]
    int R = r * 255;
    int G = g * 255;
    int B = b * 255;

    std::array<int, 3> answer = { R, G, B };

    return answer;
}
