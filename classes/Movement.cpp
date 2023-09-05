#include "./../headers/Movement.hpp"
#include "./../headers/Player.hpp"
#include "./../headers/Columns.hpp"
#include "./../headers/theFigure.hpp"
#include "./../headers/Animation.hpp"

#ifndef Def_Movement
#define Def_Movement

// true mean right
// false mean left
bool Movement::PlayerDirection = true;

inline void Movement::keyEvents(Platform &MyPlatform, KEY_EVENT_RECORD keyEvent)
{
    char nextCharacter;
    char belowChar;

    switch (keyEvent.wVirtualKeyCode)
    {
    case VK_LEFT:

        // turn left
        Movement::PlayerDirection = false;

        nextCharacter = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] - 1, Player::PlayerPosition[1])];

        if (nextCharacter == Columns::column || nextCharacter == '|')
            break;

        if (nextCharacter == theFigure::figure)
            theFigure::getScore(MyPlatform);

        Animation::animateForOneCell(MyPlatform, Player::PlayerPosition[0] - 1, Player::PlayerPosition[1], 15);

        /* for falling */
        // check if player is on the floor
        if (Player::PlayerPosition[1] == 26)
            break;

        belowChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)];
        if (belowChar == Columns::column || belowChar == '-')
            break;

        for (size_t Y = 2; Y <= 4; Y++)
        {
            char belowCharacter = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + Y)];

            if (belowCharacter == Columns::column || belowCharacter == '-')
            {
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + Y - 2, 15);

                if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);

                break;
            }
        }

        break;
    case VK_RIGHT:

        // turn right
        Movement::PlayerDirection = true;

        nextCharacter = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] + 1, Player::PlayerPosition[1])];

        if (nextCharacter == Columns::column || nextCharacter == '|')
            break;

        if (nextCharacter == theFigure::figure)
            theFigure::getScore(MyPlatform);

        Animation::animateForOneCell(MyPlatform, Player::PlayerPosition[0] + 1, Player::PlayerPosition[1], 15);

        /* for falling */
        // check if player is on the floor
        if (Player::PlayerPosition[1] == 26)
            break;

        belowChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)];
        if (belowChar == Columns::column || belowChar == '-')
            break;

        for (size_t Y = 2; Y <= 4; Y++)
        {
            char belowCharacter = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + Y)];

            if (belowCharacter == Columns::column || belowCharacter == '-')
            {
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + Y - 2, 15);
                if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);

                break;
            }
        }

        break;
    case VK_SPACE:

        /*
            every jump add 3 to y and x
            then subtract 3 from y and add 3 to x again

              a jump
                 @
                @ @
               @   @
              @     @
         */

        // right
        if (Movement::PlayerDirection)
        {
            /* first stage of jump */
            /* if player cannot move forward and @| or @# */
            char nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] + 1, Player::PlayerPosition[1])];
            if (nextChar == Columns::column || nextChar == '|')
            {
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] - 3, 15);

                nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] + 1, Player::PlayerPosition[1])];

                if (nextChar == '|')
                {
                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 3, 15);
                    goto EndOfJump;
                }

                if (nextChar == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] + 1, Player::PlayerPosition[1], 15);

                for (size_t Y = 1; Y <= (26 - Player::PlayerPosition[1] + 1); Y++)
                {
                    if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + Y)] != Columns::column)
                        continue;

                    // for falling
                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + Y - 2, 15);

                    if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                        theFigure::getScore(MyPlatform);

                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);

                    break;
                }

                goto EndOfJump;
            }

            /* if player hit platform wall or columns */
            // M = 1 means @| or @#
            for (size_t M = 2; M <= 4; M++)
            {
                char nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] + M, Player::PlayerPosition[1] - M + 2)];

                if (nextChar != Columns::column && nextChar != '|')
                    continue;

                /* the hit moment */
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] + M - 1, Player::PlayerPosition[1] - M + 1, 15);

                /* fall after hit */
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + M - 2, 15);
                if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);

                goto EndOfJump;
            }

            /* first level jump of player without hit anything */
            Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] + 3, Player::PlayerPosition[1] - 3, 15);

            /*##################################################################################*/

            // scound stage of jump
            // use 26 because maximum available height for player is 26
            int DiffPositionY = (26 - Player::PlayerPosition[1]);

            /* secound stage of jump with hit something */
            // start from 2 because in previous stage we use 4
            for (size_t M = 2; M <= DiffPositionY; M++)
            {
                char nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] + M, Player::PlayerPosition[1] + M)];

                /* check for hit */
                if (nextChar != Columns::column && nextChar != '|')
                    continue;

                /* the hit moment */
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] + M - 2, Player::PlayerPosition[1] + M - 2, 15);
                if (nextChar == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] + 1, Player::PlayerPosition[1] + 1, 15);

                /* fall after hit */
                /* calculte floor position */
                for (size_t Y = 1; Y <= (26 - Player::PlayerPosition[1] + 1); Y++)
                {
                    char belowChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + Y)];
                    if (belowChar != Columns::column && belowChar != '-')
                        continue;

                    // put Y = 1 because if we start from 2 its make bug
                    // and break when Y = 1 because its makes player go -1 and then came back
                    if (Y == 1 && (belowChar == Columns::column || belowChar == '-'))
                        break;

                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + Y - 2, 15);
                    if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                        theFigure::getScore(MyPlatform);

                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);
                    break;
                }

                goto EndOfJump;
            }

            /* secound level jump of player without hit anything */
            /* and does not land in a column */
            if (DiffPositionY)
            {
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] + DiffPositionY - 1, Player::PlayerPosition[1] + DiffPositionY - 1, 15);
                if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] + 1, Player::PlayerPosition[1] + 1)] == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForOneCell(MyPlatform, Player::PlayerPosition[0] + 1, Player::PlayerPosition[1] + 1, 15);
            }
        }
        // left
        else
        {
            /* first stage of jump */
            /* if player cannot move forward and @| or @# */
            char nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] - 1, Player::PlayerPosition[1])];
            if (nextChar == Columns::column || nextChar == '|')
            {
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] - 3, 15);

                nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] - 1, Player::PlayerPosition[1])];

                if (nextChar == '|')
                {
                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 3, 15);
                    goto EndOfJump;
                }

                if (nextChar == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] - 1, Player::PlayerPosition[1], 15);

                for (size_t Y = 1; Y <= (26 - Player::PlayerPosition[1] + 1); Y++)
                {
                    if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + Y)] != Columns::column)
                        continue;

                    // for falling
                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + Y - 2, 15);

                    if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                        theFigure::getScore(MyPlatform);

                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);
                    break;
                }

                goto EndOfJump;
            }

            /* if player hit platform wall or columns*/
            // M = 1 means @| or @#
            for (size_t M = 2; M <= 4; M++)
            {
                char nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] - M, Player::PlayerPosition[1] - M + 2)];

                if (nextChar != Columns::column && nextChar != '|')
                    continue;

                /* the hit moment */
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] - M + 1, Player::PlayerPosition[1] - M + 1, 15);

                /* fall after hit */
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + M - 2, 15);
                if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);

                goto EndOfJump;
            }

            /* first level jump of player without hit anything */
            Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] - 3, Player::PlayerPosition[1] - 3, 15);

            /*##################################################################################*/

            // scound stage of jump
            // use 26 because maximum available height for player is 26
            int DiffPositionY = (26 - Player::PlayerPosition[1]);

            /* secound stage of jump with hit something */
            // start from 2 because in previous stage we use 4
            for (size_t M = 2; M <= DiffPositionY; M++)
            {
                char nextChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] - M, Player::PlayerPosition[1] + M)];

                /* check for hit */
                if (nextChar != Columns::column && nextChar != '|')
                    continue;

                /* the hit moment */
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] - M + 2, Player::PlayerPosition[1] + M - 2, 15);
                if (nextChar == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] - 1, Player::PlayerPosition[1] + 1, 15);

                /* fall after hit */
                /* calculte floor position */
                for (size_t Y = 1; Y <= (26 - Player::PlayerPosition[1] + 1); Y++)
                {
                    char belowChar = MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + Y)];
                    if (belowChar != Columns::column && belowChar != '-')
                        continue;

                    // put Y = 1 because if we start from 2 its make bug
                    // and break when Y = 1 because its makes player go -1 and then came back
                    if (Y == 1 && (belowChar == Columns::column || belowChar == '-'))
                        break;

                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + Y - 2, 15);
                    if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0], Player::PlayerPosition[1] + 1)] == theFigure::figure)
                        theFigure::getScore(MyPlatform);

                    Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0], Player::PlayerPosition[1] + 1, 15);
                    break;
                }

                goto EndOfJump;
            }

            /* secound level jump of player without hit anything */
            /* and does not land in a column */
            if (DiffPositionY)
            {
                Animation::animateForLongMove(MyPlatform, Player::PlayerPosition[0] - DiffPositionY + 1, Player::PlayerPosition[1] + DiffPositionY - 1, 15);
                if (MyPlatform.ThePlatform[Platform::getThePosition(Player::PlayerPosition[0] - 1, Player::PlayerPosition[1] + 1)] == theFigure::figure)
                    theFigure::getScore(MyPlatform);

                Animation::animateForOneCell(MyPlatform, Player::PlayerPosition[0] - 1, Player::PlayerPosition[1] + 1, 15);
            }
        }

    EndOfJump:;
        break;
    }
}

inline void Movement::runTheGame(Platform &MyPlatform)
{
    HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(input, ENABLE_EXTENDED_FLAGS);
    INPUT_RECORD inputEvent;
    DWORD numEventsRead;
    while (true)
    {
        ReadConsoleInput(input, &inputEvent, 1, &numEventsRead);

        if (numEventsRead <= 0 || inputEvent.EventType != KEY_EVENT || !inputEvent.Event.KeyEvent.bKeyDown)
            continue;

        Movement::keyEvents(MyPlatform, inputEvent.Event.KeyEvent);
    };
}

#endif