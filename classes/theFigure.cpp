#include "./../headers/theFigure.hpp"
#include "./../headers/Animation.hpp"

using namespace std;

#ifndef Def_theFigure
#define Def_theFigure

int theFigure::score = 0;

void theFigure::setTheFigurePosition(Platform &MyPlatform)
{
    // FPH = figure position horizontally
    // FPV = figure position vertically
    int FPH, FPV;

    while (true)
    {
        // add to (3 - 1) because of three start character of the row
        // and - 1 because indexes of platform vector starts from zero
        FPH = getRandomNumber(1, Columns::availableForColumns) + 2;
        FPV = 26;

        if (MyPlatform.ThePlatform[Platform::getThePosition(FPH, FPV)] == Player::player)
            continue;

        for (int Y = 0; Y <= 2; Y++)
        {
            if (MyPlatform.ThePlatform[Platform::getThePosition(FPH, 26 - Y)] == Columns::column)
            {
                FPV = 26 - Y - 1;
                if (MyPlatform.ThePlatform[Platform::getThePosition(FPH, FPV)] == Player::player)
                    goto setTheFigurePositionContinue;
            }
        }

        break;
    setTheFigurePositionContinue:;
    }

    Animation::typeInConsoleByPosition(MyPlatform, FPH, FPV, theFigure::figure);
}

void theFigure::getScore(Platform &MyPlatform)
{
    theFigure::score += 1;
    theFigure::setTheFigurePosition(MyPlatform);
    Animation::typeInConsoleByPosition(MyPlatform, 18, 4, to_string(theFigure::score));
}

#endif