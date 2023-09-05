#include <string>
#ifndef Def_Platform_h
#define Def_Platform_h

class Platform
{
public:
    static const int W_HEIGHT = 29;
    static const int W_WIDTH = 119;
    std::string ThePlatform;
    void startThePlatform();
    void showThePlatform();
    int static getThePosition(int x , int y);
};

#endif