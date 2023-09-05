#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "./../headers/Platform.hpp"


using namespace std;

#ifndef Def_Platform
#define Def_Platform

void Platform::startThePlatform()
{

    ThePlatform += "\\";
    for (size_t i = 1; i < (W_WIDTH - 1); i++)
    {
        ThePlatform += "-";
    }
    ThePlatform += "/\n";

    ThePlatform += "|\\";
    for (size_t i = 1; i < (W_WIDTH - 3); i++)
    {
        ThePlatform += "-";
    }
    ThePlatform += "/|\n";

    for (size_t i = 1; i < (W_HEIGHT - 3); i++)
    {
        ThePlatform += "||";
        for (size_t z = 1; z < (W_WIDTH - 3); z++)
        {
            ThePlatform += " ";
        }
        ThePlatform += "||\n";
    }

    ThePlatform += "|/";
    for (size_t i = 1; i < (W_WIDTH - 3); i++)
    {
        ThePlatform += "-";
    }
    ThePlatform += "\\|\n";

    ThePlatform += "/";
    for (size_t i = 1; i < (W_WIDTH - 1); i++)
    {
        ThePlatform += "-";
    }
    ThePlatform += "\\";
}

int Platform::getThePosition(int x, int y)
{
    return y * (Platform::W_WIDTH + 1) + x;
}

void Platform::showThePlatform()
{
    cout << ThePlatform << endl;
}


#endif