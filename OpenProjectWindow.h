//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_OPENPROJECTWINDOW_H
#define FINAL_PROJECT_OPENPROJECTWINDOW_H
#include "ProjectEditor.h"
#include "Button.h"


class OpenProjectWindow
{
public:
    OpenProjectWindow(ProjectEditor& editorRef);

    void Update();

private:

    sf::RenderWindow loadWindow;
    ProjectEditor& editorRef;
    FileTree fileTree;
    Button closeButton;
    Button openButton;
};


#endif //FINAL_PROJECT_OPENPROJECTWINDOW_H
