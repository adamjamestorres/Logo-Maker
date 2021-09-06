//
// Created by Adam Torres on 5/30/21.
//

#include "OpenProjectWindow.h"

OpenProjectWindow::OpenProjectWindow(ProjectEditor& editorRef)
        :editorRef(editorRef)
{
    loadWindow.create(sf::VideoMode(500, 400), "Load Project Window", sf::Style::Default);

    openButton.text.setString("OPEN");
    closeButton.text.setString("CLOSE");

    openButton.setPosition({ 200.f, 300.f });
    closeButton.setPosition({ 350.f, 300.f });

    fileTree.setPosition({ 10.f, 10.f });

    fileTree.push("nullptr", ImageEnum::folder, "Main");
    fileTree.push("Main", ImageEnum::file, "Project1.save");
}

void OpenProjectWindow::Update()
{
    sf::Event event;

    while (loadWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            loadWindow.close();

        fileTree.addEventHandler(loadWindow, event);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(loadWindow);
            sf::Vector2f mousePos = loadWindow.mapPixelToCoords(pixelPos);

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (openButton.getGlobalBounds().contains(mousePos))
                {
                    editorRef.LoadProject();
                    loadWindow.close();
                }

                if (closeButton.getGlobalBounds().contains(mousePos))
                {
                    loadWindow.close();
                }
            }
        }

    }

    fileTree.update();

    loadWindow.clear(sf::Color::Black);

    loadWindow.draw(openButton);
    loadWindow.draw(closeButton);
    loadWindow.draw(fileTree);

    loadWindow.display();
}