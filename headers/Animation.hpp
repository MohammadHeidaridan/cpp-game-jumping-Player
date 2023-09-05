#ifndef Def_Animation_h
#define Def_Animation_h

class Platform;

class Animation
{
public:
    void inline static typeInConsoleByPosition(Platform &MyPlatform, int x, int y, char chr);
    void inline static typeInConsoleByPosition(Platform &MyPlatform,int x, int y, std::string str);

    void static animateForOneCell(char AnimatedChar, Platform &MyPlatform, int fromX, int fromY, int toX, int toY, int sleep = 10);
    void static animateForLongMove(char AnimatedChar, Platform &MyPlatform, int fromX, int fromY, int toX, int toY, int sleep = 10);

    // for player movement
    void static animateForOneCell(Platform &MyPlatform, int toX, int toY, int sleep = 10);
    void static animateForLongMove(Platform &MyPlatform, int toX, int toY, int sleep = 10);
};

#endif
