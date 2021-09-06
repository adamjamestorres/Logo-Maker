//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_PROJECTEDITOR_H
#define FINAL_PROJECT_PROJECTEDITOR_H
#include "ProjectImage.h"
#include "EventHandler.h"
#include "TextInput.h"
#include "DropdownMenu.h"
#include "MenuBar.h"
#include "KeyShortcuts.h"
#include "FileTree.h"
#include "Slider.h"
#include "ColorPicker.h"
#include "HueSelector.h"
#include "Constants.h"
#include "SimpleTextBox.h"
#include "FontSelector.h"
#include <fstream>

class ProjectEditor : public sf::Drawable, public EventHandler
{
public:
    ProjectEditor(ProjectImage& textRef);

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update();

    void Reset();
    void SaveProject();
    void LoadProject();

private:

    ProjectImage& textRef;
    SimpleTextBox textBox;
    sf::RectangleShape background;
    std::vector<std::shared_ptr<Slider>> sliders;
    std::vector<std::shared_ptr<ColorPicker>> colorPickers;
    FontSelector fontSelector;
};

#endif //FINAL_PROJECT_PROJECTEDITOR_H
