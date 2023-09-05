#ifndef Def_Player_h
#define Def_Player_h

class Platform;

class Player
{
public:
    // 0 => X , 1 => Y
    static int PlayerPosition[2] ;
    const static char player = '@';
    void static startThePlayer(Platform &MyPlatform);
    void static animateTheStartPlayer(Platform &MyPlatform);
    void static setPlayerPosition(int X, int Y);
};

#endif