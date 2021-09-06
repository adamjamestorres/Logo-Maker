//
// Created by Adam Torres on 5/30/21.
//

#include "ProjectEditor.h"

ProjectEditor::ProjectEditor(ProjectImage& textRef)
        : textRef(textRef), fontSelector(textRef.iProps.textFont, sf::Vector2f(150.f, 400.f))
{
    textBox.setPosition(sf::Vector2f(50.f, IMAGE_HEIGHT + 40.f));
    textBox.setSize(50, 1);
    textBox.getLabel().setString("Text: ");
    textBox.getLabel().setPosition(textBox.getPosition().x, textBox.getPosition().y - textBox.getLabel().getGlobalBounds().height - 20.f);
    textBox.getLabel().setCharacterSize(25);

    background.setSize({ float(WINDOW_WIDTH), float(WINDOW_HEIGHT) - IMAGE_HEIGHT});
    background.setPosition(0.f, IMAGE_HEIGHT);
    background.setFillColor(sf::Color::Black);

    std::shared_ptr<Slider> Xpos_Slider = std::make_shared<Slider>(textRef.iProps.xPos, "X-Position: ", sf::Vector2f{600.f, 410.f}, 0.f, 700.f);
    sliders.push_back(Xpos_Slider);

    std::shared_ptr<Slider> Ypos_Slider = std::make_shared<Slider>(textRef.iProps.yPos, "Y-Position: ", sf::Vector2f(600.f, 460.f), 30.f, 300.f);
    sliders.push_back(Ypos_Slider);

    std::shared_ptr<Slider> Rotation_Slider = std::make_shared<Slider>(textRef.iProps.rotation, "Rotation: ", sf::Vector2f(600.f, 510.f), 0.f, 360.f);
    sliders.push_back(Rotation_Slider);

    std::shared_ptr<Slider> CharSize_Slider = std::make_shared<Slider>(textRef.iProps.charSize, "Char Size: ", sf::Vector2f(600.f, 560.f), 0.f, 80.f);
    sliders.push_back(CharSize_Slider);

    std::shared_ptr<ColorPicker> textColor = std::make_shared<ColorPicker>(textRef.iProps.textColor, "Text Color: ", sf::Vector2f(500.f, 325.f));
    colorPickers.push_back(textColor);

    std::shared_ptr<ColorPicker> backColor = std::make_shared<ColorPicker>(textRef.iProps.backColor, "Background Color: ", sf::Vector2f(750.f, 325.f));
    colorPickers.push_back(backColor);

    Reset();
}

void ProjectEditor::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(background);
    window.draw(textBox);
    window.draw(fontSelector);
    for (auto& itr : sliders) { window.draw(*itr); }
    for (auto& itr : colorPickers) { window.draw(*itr); }
}

void ProjectEditor::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    for (auto& itr : sliders) { itr->addEventHandler(window, event); }
    for (auto& itr : colorPickers) { itr->addEventHandler(window, event); }
    textBox.addEventHandler(window, event);
    fontSelector.addEventHandler(window, event);
}

void ProjectEditor::update()
{
    textBox.update();
    textRef.iProps.textString = textBox.getTextString();
    fontSelector.update();
}

void ProjectEditor::Reset()
{
    textRef.iProps.textColor = sf::Color::Blue;
    textRef.iProps.backColor = sf::Color::White;
    textRef.iProps.textString = "";
    textBox.setTextString("");

    colorPickers[0]->setColor(sf::Color::Blue);
    colorPickers[1]->setColor(sf::Color::White);

    textRef.iProps.xPos = 500.f;
    textRef.iProps.yPos = 150.f;
    textRef.iProps.rotation = 0.f;
    textRef.iProps.charSize = 20.f;

    for (auto itr : sliders)
    {
        itr->setValue();
    }

}

void ProjectEditor::SaveProject()
{
    std::ofstream fout;

    fout.open("new.save", std::ios::binary);

    fout << textRef.iProps.xPos << '\n';
    fout << textRef.iProps.yPos << '\n';
    fout << textRef.iProps.charSize << '\n';
    fout << textRef.iProps.rotation << '\n';
    fout << reinterpret_cast<const char*>(textRef.iProps.textString.c_str()) << '\n';

    fout.close();
}

void ProjectEditor::LoadProject()
{
    std::ifstream fin;

    fin.open("new.save");

    fin >> textRef.iProps.xPos;
    fin >> textRef.iProps.yPos;
    fin >> textRef.iProps.charSize;
    fin >> textRef.iProps.rotation;
    fin >> textRef.iProps.textString;

    fin.close();

    textBox.setTextString(textRef.iProps.textString);

    for (auto& itr : sliders)
    {
        itr->setValue();
    }
}
