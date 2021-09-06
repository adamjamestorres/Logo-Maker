//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_GUI_COMPONENT_H
#define FINAL_PROJECT_GUI_COMPONENT_H
#include <SFML/Graphics.hpp>
#include "States.h"
#include "SnapShot.h"
#include "EventHandler.h"
#include "Label.h"

class GUI_Component : public EventHandler, public States, public SnapshotInterface, public sf::Drawable, public sf::Transformable
{
public:
    //From sf::Drawable
    virtual void draw(sf::RenderTarget& window, sf::RenderStates states) const = 0;

    //EventHandler
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event) = 0;
    virtual void update() = 0;

    //Snapshot Interface
    virtual void takeSnapshot() = 0;
    virtual void applySnapshot(const std::shared_ptr<SnapShot> snapshot) = 0;
};

#endif //FINAL_PROJECT_GUI_COMPONENT_H
