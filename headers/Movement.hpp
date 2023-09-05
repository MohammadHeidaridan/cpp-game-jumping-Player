#include "./Platform.hpp"
#include <Windows.h>

#ifndef Def_Movement_h
#define Def_Movement_h

class Movement
{
private:
    static bool PlayerDirection;
    inline void static keyEvents(Platform &MyPlatform, KEY_EVENT_RECORD keyEvent);

public:
    inline void static runTheGame(Platform &MyPlatform);
};

#endif