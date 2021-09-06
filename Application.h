//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_APPLICATION_H
#define FINAL_PROJECT_APPLICATION_H
#include "ProjectEditor.h"
#include "Constants.h"
#include "TopMenu.h"

class Application
{
public:
    Application();

    void Run();

private:
    void HandleEvents(); //SFML Event Loop
    void Update(); //SFML Update Loop
    void Render(); //SFML Render Loop

private:
    sf::RenderWindow window; //SFML Renderwindow
    TopMenu topMenu;		 //TopMenu along top of screen
    ProjectImage imageText;		//Displayed ProjectImage
    ProjectEditor projectEditor; //User Defined Editor for ProjectImage
};

#endif //FINAL_PROJECT_APPLICATION_H
