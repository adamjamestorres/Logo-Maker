//
// Created by Adam Torres on 5/30/21.
//

#include "Application.h"

Application::Application()
        : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), //WINDOW HEIGHT/WIDTH defined in Constants.h
                 "Image Modifier Application"),
          projectEditor(imageText),
          topMenu(window,projectEditor) {}


void Application::Run()
{
    while (window.isOpen())
    {
        HandleEvents();
        Update();
        Render();
    }
}

void Application::HandleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        topMenu.addEventHandler(window, event);
        projectEditor.addEventHandler(window, event);
        History::addEventHandler(window, event);
    }
}

void Application::Update()
{
    topMenu.update();
    projectEditor.update();
    imageText.update();
}

void Application::Render()
{
    window.clear(sf::Color::Black);

    window.draw(imageText);
    window.draw(projectEditor);
    window.draw(topMenu);

    window.display();
}