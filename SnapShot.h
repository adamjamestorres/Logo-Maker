//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_SNAPSHOT_H
#define FINAL_PROJECT_SNAPSHOT_H


#include <list>

class SnapShot {
public:
    SnapShot(std::string component_ID) : component_ID(component_ID) {}
    std::string component_ID;
};

class TextBoxSnapShot : public SnapShot
{
public:
    TextBoxSnapShot(std::string component_ID, std::list<sf::Text> textList) : textList(textList), SnapShot(component_ID) {};
    std::list<sf::Text> GetTextList() { return textList; };

private:
    std::list<sf::Text> textList;
};

class SimpleTextBoxSnapshot : public SnapShot
{
public:
    SimpleTextBoxSnapshot(std::string component_ID, std::string textString) : textString(textString), SnapShot(component_ID) {};
    std::string getTextString() { return textString; }
private:
    std::string textString;
};

class DropDownSnapShot : public SnapShot
{
public:
    DropDownSnapShot(std::string component_ID, sf::String storedString) : SnapShot(component_ID), storedString(storedString) {}
    sf::String GetString() { return storedString; }
private:
    sf::String storedString;
};

class SliderSnapshot : public SnapShot
{
public:
    SliderSnapshot(std::string component_ID, float knobPosition) : SnapShot(component_ID), knobPosition(knobPosition) {}
    float GetKnobPosition() { return knobPosition; }
private:
    float knobPosition;
};

class ColorPickerSnapshot : public SnapShot
{
public:
    ColorPickerSnapshot(std::string componentID, sf::Color color) : SnapShot(componentID), color(color) {}
    sf::Color getColor() { return color; }
private:
    sf::Color color;
};

class SnapshotInterface
{
public:
    //this function will capture a snapshot of the object's current state
    virtual void takeSnapshot() = 0;
    //this function will apply a snapshot to an object reverting back to previous recorded state
    virtual void applySnapshot(const std::shared_ptr<SnapShot> snapshot) = 0;

};


#endif //FINAL_PROJECT_SNAPSHOT_H
