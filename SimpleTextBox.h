//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_SIMPLETEXTBOX_H
#define FINAL_PROJECT_SIMPLETEXTBOX_H
#include "History.h"
#include "TextCursor.h"

class SimpleTextBox : public GUI_Component
{

public:
    SimpleTextBox();

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update();
    void takeSnapshot();
    void applySnapshot(const std::shared_ptr<SnapShot> snapshot);

    void setTextString(std::string str);
    void setSize(int charactersWide, int rows);
    std::string getTextString() { return text.getString(); }
    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() { return inputField.getPosition(); }
    Label& getLabel() { return label; }

private:
    void AssignComponentID();
    void InitializeValues();
    bool isUndoInput(sf::Event& event);
    bool willOverflow();
    void ProcessEnteredText(sf::Event& event);
    bool LeftClickedInsideTextBox(sf::Event& event, sf::RenderWindow& window);
    void AssignCursorPosition();
    bool IsNotEnabled();

    Label label;
    std::string componentID;
    sf::Font font;
    sf::Text text;
    sf::RectangleShape inputField;
    TextCursor textCursor;
    std::string textString;
};



#endif //FINAL_PROJECT_SIMPLETEXTBOX_H
