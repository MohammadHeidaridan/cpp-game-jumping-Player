#ifndef Def_theFigure_h
#define Def_theFigure_h

class theFigure
{
public:
    static const char figure = '*';
    static int score;
    void static setTheFigurePosition(Platform &MyPlatform);
    void static getScore(Platform &MyPlatform);
};

#endif