//
// Created by Adam Torres on 5/30/21.
//

#include "TopMenu.h"

TopMenu::TopMenu(sf::RenderWindow& windowRef, ProjectEditor& projectEditorRef)
        : windowRef(windowRef), projectEditorRef(projectEditorRef), loadWindow(nullptr), exportFlag(false)
{
    initMenuBar();
    attachObservers();
}

void TopMenu::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(menuBar);
}

void TopMenu::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    exportImage();
    menuBar.addEventHandler(window, event);
}

void TopMenu::update()
{
    if (loadWindow) { loadWindow->Update(); }
}

void TopMenu::ObserverUpdate(std::string str)
{
    //Evaluates the str to determine the correct behavior to choose

    if (str == "Quit")
    {
        windowRef.close();
    }
    if (str == "New Project")
    {
        projectEditorRef.Reset();
    }
    if (str == "Save Project")
    {
        projectEditorRef.SaveProject();
    }
    if (str == "Open Project")
    {
        loadWindow = std::make_unique<OpenProjectWindow>(projectEditorRef);
    }
    if (str == "Close Project")
    {
        projectEditorRef.Reset();
    }
    if (str == "Undo")
    {
        History::Undo();
    }
    if (str == "Redo")
    {
        //To be implemented
        std::cout << "Redo Action\n";
    }
    if (str == "Export Image")
    {
        //Sets export flag to true
        //Boolean flag is used to avoid picking up artifact from displayed topMenu bar
        exportFlag = true;
    }

}

void TopMenu::initMenuBar()
{
    std::vector<std::vector<std::string>> menuMap = { {"File", "New Project", "Open Project", "Save Project", "Close Project", "Quit"},
                                                      {"Edit", "Undo"/*, "Redo"*/},
                                                      {"Render", "Export Image"} };
    menuBar.init(menuMap, float(WINDOW_WIDTH));
}

void TopMenu::attachObservers()
{
    menuBar.Attach(this); //Adds observer to menuBar for callback functionality
}

void TopMenu::exportImage()
{
    if (exportFlag == false) { return; }

    sf::Texture texture; //Builds screenshot from windowReference
    texture.create(windowRef.getSize().x, windowRef.getSize().y);
    texture.update(windowRef);

    sf::Image image1 = texture.copyToImage(); //Creates image of appropriate size
    sf::Image image2;
    image2.create(WINDOW_WIDTH, 265u);

    //Copies pixel by pixel from image1 screenshot to image2 utilizing sf::intrect
    image2.copy(image1, 0u, 0u, sf::IntRect(0u, 35u, WINDOW_WIDTH, 265u));
    image2.saveToFile("export.png"); //Saves exported image to determined file name

    exportFlag = false; //Returns exportflag to false status after export is complete

}