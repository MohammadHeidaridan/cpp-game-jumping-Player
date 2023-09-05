#include <string>
#include "./Platform.hpp"

#ifndef Def_Menu_h
#define Def_Menu_h

class Menu
{
public:
    static const std::string scoreMenu;
    static void showMenuInPlatform(Platform MyPlatform);
};

#endif