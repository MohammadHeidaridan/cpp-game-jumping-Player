#include "./../headers/Animation.hpp"
#include "./../headers/Platform.hpp"
#include <windows.h>
#include <thread>

using namespace std;

#ifndef Def_Animation
#define Def_Animation

inline void Animation::typeInConsoleByPosition(Platform &MyPlatform, int x, int y, char chr)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    // for hiding cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);

    COORD position = {static_cast<short>(x), static_cast<short>(y)};
    SetConsoleCursorPosition(console, position);
    cout << chr;
    MyPlatform.ThePlatform[Platform::getThePosition(x, y)] = chr;
}

inline void Animation::typeInConsoleByPosition(Platform &MyPlatform, int x, int y, string str)
{
    size_t counter = 0;
    for (char chr : str)
    {
        Animation::typeInConsoleByPosition(MyPlatform, x + counter, y, chr);
        counter++;
    }
}

void Animation::animateForOneCell(char AnimatedChar, Platform &MyPlatform, int fromX, int fromY, int toX, int toY, int sleep)
{
    // sleep for animation stuff
    this_thread::sleep_for(chrono::milliseconds(sleep));

    // change character position
    Animation::typeInConsoleByPosition(MyPlatform, fromX, fromY, ' ');
    Animation::typeInConsoleByPosition(MyPlatform, toX, toY, AnimatedChar);
}

void Animation::animateForLongMove(char AnimatedChar, Platform &MyPlatform, int fromX, int fromY, int toX, int toY, int sleep)
{
    // vertical movement
    if (fromX == toX && fromY != toY)
    {
        int diff = fromY - toY;

        if (diff > 0)
        {
            // movement to the up
            for (unsigned int Y = 1; Y <= diff; Y++)
            {
                Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX, fromY, toX, fromY - 1, sleep);
                fromY = fromY - 1;
            }
        }
        else
        {
            // movement to the down
            for (unsigned int Y = 1; Y <= -(diff); Y++)
            {
                Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX, fromY, toX, fromY + 1, sleep);
                fromY = fromY + 1;
            }
        }
    }

    // horizontal movement
    else if (fromX != toX && fromY == toY)
    {
        int diff = fromX - toX;

        if (diff > 0)
        {
            // movement to the left
            for (unsigned int X = 1; X <= diff; X++)
            {
                Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX, fromY, fromX - 1, toY, sleep);
                fromX = fromX - 1;
            }
        }
        else
        {
            // movement to the rught
            for (unsigned int X = 1; X <= -(diff); X++)
            {
                Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX, fromY, fromX + 1, toY, sleep);
                fromX = fromX + 1;
            }
        }
    }

    // diagonal movement
    else if (fromX != toX && fromY != toY)
    {
        /*
            twelve state of diagonal movement

            diff > 0
             (1) x       x (2)
                  \     /
                   --@--
                  /     \
             (3) x       x  (4)

            diff < 0
               (5) x   x (6)
                    \ /
                     |
                     @
                     |
                    / \
               (7) x   x (8)

            diff = 0
               (9) x   x (10)
                    \ /
                     @
                    / \
             (11) x    x (12)
        */

        /*--------------------------------------------------------------*\
       |*         in all parts diffX and diffY must be positive!         *|
        \* -------------------------------------------------------------*/

        if (fromX > toX && fromY > toY)
        {
            int diffX = fromX - toX;
            int diffY = fromY - toY;
            int diff = diffX - diffY;

            //(1)
            if (diff > 0)
            {
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX - diff, fromY, sleep);

                for (size_t M = 1; M <= diffY; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX - diff - M + 1, fromY - M + 1, fromX - diff - M, fromY - M, sleep);
                }
            }

            //(5)
            else if (diff < 0)
            {
                // because diff < 0 we do fromY + diff which equals to fromY - (-diff)
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX, fromY + diff, sleep);

                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX - M + 1, fromY + diff - M + 1, fromX - M, fromY + diff - M, sleep);
                }
            }

            //(9)
            else
            {
                // there is no difference between useing diffX or diffY
                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX - M + 1, fromY - M + 1, fromX - M, fromY - M, sleep);
                }
            }
        }
        else if (fromX < toX && fromY > toY)
        {
            int diffX = toX - fromX;
            int diffY = fromY - toY;
            int diff = diffX - diffY;

            //(2)
            if (diff > 0)
            {
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX + diff, fromY, sleep);

                for (size_t M = 1; M <= diffY; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX + diff + M - 1, fromY - M + 1, fromX + diff + M, fromY - M, sleep);
                }
            }

            //(6)
            else if (diff < 0)
            {
                // because diff < 0 we do fromY + diff which equals to fromY - (-diff)
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX, fromY + diff, sleep);

                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX + M - 1, fromY + diff - M + 1, fromX + M, fromY + diff - M, sleep);
                }
            }

            //(10)
            else
            {
                // there is no difference between useing diffX or diffY
                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX + M - 1, fromY - M + 1, fromX + M, fromY - M, sleep);
                }
            }
        }
        else if (fromX > toX && fromY < toY)
        {
            int diffX = fromX - toX;
            int diffY = toY - fromY;
            int diff = diffX - diffY;

            //(3)
            if (diff > 0)
            {
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX - diff, fromY, sleep);

                for (size_t M = 1; M <= diffY; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX - diff - M + 1, fromY + M - 1, fromX - diff - M, fromY + M, sleep);
                }
            }

            //(7)
            else if (diff < 0)
            {
                // because diff < 0 we do fromY - diff which equals to fromY + (-diff)
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX, fromY - diff, sleep);

                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX - M + 1, fromY - diff + M - 1, fromX - M, fromY - diff + M, sleep);
                }
            }

            //(11)
            else
            {
                // there is no difference between useing diffX or diffY
                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX - M + 1, fromY + M - 1, fromX - M, fromY + M, sleep);
                }
            }
        }
        else if (fromX < toX && fromY < toY)
        {
            int diffX = toX - fromX;
            int diffY = toY - fromY;
            int diff = diffX - diffY;

            //(4)
            if (diff > 0)
            {
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX + diff, fromY, sleep);

                for (size_t M = 1; M <= diffY; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX + diff + M - 1, fromY + M - 1, fromX + diff + M, fromY + M, sleep);
                }
            }

            //(8)
            else if (diff < 0)
            {
                // because diff < 0 we do fromY + diff which equals to fromY - (-diff)
                Animation::animateForLongMove(AnimatedChar, MyPlatform, fromX, fromY, fromX, fromY - diff, sleep);

                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX + M - 1, fromY - diff + M - 1, fromX + M, fromY - diff + M, sleep);
                }
            }

            //(12)
            else
            {
                // there is no difference between useing diffX or diffY
                for (size_t M = 1; M <= diffX; M++)
                {
                    Animation::animateForOneCell(AnimatedChar, MyPlatform, fromX + M - 1, fromY + M - 1, fromX + M, fromY + M, sleep);
                }
            }
        }
    }
}

void Animation::animateForOneCell(Platform &MyPlatform, int toX, int toY, int sleep)
{
    Animation::animateForOneCell(Player::player, MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1], toX, toY, sleep);
    Player::setPlayerPosition(toX, toY);
}

void Animation::animateForLongMove(Platform &MyPlatform, int toX, int toY, int sleep)
{
    Animation::animateForLongMove(Player::player, MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1], toX, toY, sleep);
    Player::setPlayerPosition(toX, toY);
}

#endif
