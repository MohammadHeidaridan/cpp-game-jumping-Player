#include "./../headers/Player.hpp"
#include "./../headers/Platform.hpp"
#include "./../headers/Animation.hpp"

#ifndef Def_Player
#define Def_Player

// start positoin 0 => X , 1 => Y
int Player::PlayerPosition[2] = {59, 15};

void Player::startThePlayer(Platform &MyPlatform)
{
    Animation::typeInConsoleByPosition(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1], Player::player);
}

void Player::animateTheStartPlayer(Platform &MyPlatform)
{
    // finding the floor position
    int floorYPosition = 26;
    for (int Y = 2; Y >= 0; Y--)
    {
        if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], 26 - Y)] == '#')
        {
            floorYPosition = 26 - Y - 1;
            break;
        }
    }

    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], floorYPosition, 50);
}

void Player::setPlayerPosition(int X, int Y)
{
    Player::PlayerPosition[0] = X;
    Player::PlayerPosition[1] = Y;
}

#endif