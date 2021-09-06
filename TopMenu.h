//
// Created by Adam Torres on 5/30/21.
//

#ifndef FINAL_PROJECT_TOPMENU_H
#define FINAL_PROJECT_TOPMENU_H
#include "MenuBar.h"
#include "GUI_Component.h"
#include "ProjectEditor.h"
#include "Constants.h"
#include "OpenProjectWindow.h"

class TopMenu : public sf::Drawable, public EventHandler, public I_Observer {
public:
    TopMenu(sf::RenderWindow& windowRef, ProjectEditor& projectEditorRef);

    void draw(sf::RenderTarget& window, sf::RenderStates states) const;
    void addEventHandler(sf::RenderWindow& window, sf::Event event);
    void update();

    void ObserverUpdate(std::string str);

private:

    void initMenuBar();
    void attachObservers();
    void exportImage();

    MenuBar menuBar;
    sf::RenderWindow& windowRef;
    ProjectEditor& projectEditorRef;
    std::unique_ptr<OpenProjectWindow> loadWindow;
    bool exportFlag;

};


#endif //FINAL_PROJECT_TOPMENU_H
