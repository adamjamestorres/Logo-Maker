//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_EVENTHANDLER_H
#define FINAL_PROJECT_EVENTHANDLER_H
class EventHandler
{
public:
    virtual void addEventHandler(sf::RenderWindow& window, sf::Event event) = 0;
    virtual void update() = 0;
};
#endif //FINAL_PROJECT_EVENTHANDLER_H
