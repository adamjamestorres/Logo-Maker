//
// Created by Adam Torres on 5/30/21.
//

#include "MenuBar.h"

void MenuBar::init(std::vector<std::vector<std::string>> menuMap, const int windowWidth)
{
    SetBanner(windowWidth);
    SetMenus(menuMap);
}

void MenuBar::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(bannerBar); //Draws simple gray strip behind menuButtons

    for (auto& itr : topMenus) //Draws all menus across the top
    {
        itr.draw(window, states);
    }

    if (activeMenu != nullptr) //If active, draws the border and text of menu item from active list
    {
        for (auto& itr : activeMenu->GetItemList().GetItems())
        {
            window.draw(itr->rect);
            window.draw(itr->text);
        }
    }
}

void MenuBar::addEventHandler(sf::RenderWindow& window, sf::Event event)
{
    if (event.type == sf::Event::MouseMoved)
    {
        CheckActiveMenu(window);
        HighlightSelection(window);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

            if (isEnabled) //Checks if item in menuList is clicked
            {
                for (auto& itr : activeMenu->GetItemList().GetItems())
                {
                    if (itr->rect.getGlobalBounds().contains(mousePos))
                    {
                        //Calls the registered observer which in this case
                        //is the topMenu class, it passes along the string to be handled by
                        //the top menu
                        Notify(itr->text.getString());

                        activeMenu = nullptr;
                        isEnabled = false;
                    }
                }
            }

            for (auto& itr : topMenus) //Checks if a topMenu is clicked
            {
                if (itr.GetBannerItem()->rect.getGlobalBounds().contains(mousePos))
                {
                    activeMenu = &itr;
                    isEnabled = true;

                    ResetBannerHighlights();
                    activeMenu->GetBannerItem()->setColor(sf::Color(219, 223, 0, 202));

                    return;
                }
            }

            //Resets menu bar to inactive status
            activeMenu = nullptr;
            isEnabled = false;

        }
    }
}

void MenuBar::SetBanner(const int windowWidth)
{
    //Sets gray bar across top of application
    bannerBar.setSize({ static_cast<float> (windowWidth), 35.f });
    bannerBar.setFillColor(sf::Color(109, 150, 173, 255));
}

void MenuBar::SetMenus(std::vector<std::vector<std::string>>& menuMap)
{
    //Initial position for first menu placed in upper left corner at pos = 0,0
    //position is updated after each element is placed in topMenu vector to ready position for next element
    sf::Vector2f pos = { 0.f,0.f };

    for (auto& itr : menuMap)
    {
        Menu tempMenu(itr, pos); //Creates temporary Menu to push back on to data structure
        topMenus.push_back(tempMenu);

        //Updates position for next menu based on width of current element
        pos.x += topMenus.back().GetBannerItem()->rect.getGlobalBounds().width;
    }
}

void MenuBar::CheckActiveMenu(sf::RenderWindow& window)
{
    if (isEnabled == false) { return; }

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    for (auto& itr : topMenus) //Checks if mouse moves to another menu category while MenuBar is active
    {
        if (itr.GetBannerItem()->rect.getGlobalBounds().contains(mousePos))
        {
            activeMenu = &itr;
            break;
        }
    }
}

void MenuBar::HighlightSelection(sf::RenderWindow& window)
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    sf::Color highlightColor = sf::Color(219, 223, 0, 202);

    for (auto& itr : topMenus) //Highlights menu banner
    {
        if (itr.GetBannerItem()->rect.getGlobalBounds().contains(mousePos))
        {
            itr.GetBannerItem()->rect.setFillColor(highlightColor);
        }
        else
        {
            itr.GetBannerItem()->rect.setFillColor(sf::Color::Transparent);
        }
    }

    if (isEnabled == false || activeMenu == nullptr) { return; } //returns if menu is inactive

    for (auto& itr : activeMenu->GetItemList().GetItems()) //Highlights list item
    {
        if (itr->rect.getGlobalBounds().contains(mousePos))
        {
            itr->rect.setFillColor(highlightColor); //If item rectangle is hovered over (contains mousePos) then set color to yellow
            continue;
        }

        itr->rect.setFillColor(sf::Color::Black);
    }

    activeMenu->GetBannerItem()->setColor(highlightColor); //Highlights active banner
}

void MenuBar::ResetBannerHighlights()
{
    //Resets all banners to original color
    for (auto& itr : topMenus) { itr.GetBannerItem()->rect.setFillColor(sf::Color::Transparent); }
}
