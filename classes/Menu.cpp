#include "./../headers/Menu.hpp"

#ifndef Def_Menu
#define Def_Menu

const std::string Menu::scoreMenu = "Your Score : 0";

void Menu::showMenuInPlatform(Platform MyPlatform)
{
    // score menu
    Animation::typeInConsoleByPosition(MyPlatform, 5, 4, Menu::scoreMenu);
}

#endif