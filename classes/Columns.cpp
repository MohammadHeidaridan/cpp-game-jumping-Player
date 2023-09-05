#include "./../headers/Columns.hpp"

#ifndef Def_Columns
#define Def_Columns

void Columns::setColumns()
{
    int theNumberOfColumns = getRandomNumber(0, MaximumNumberOfColumns);

    // ###
    OL_Columns = getRandomNumber(0, theNumberOfColumns);

    // remining columns
    theNumberOfColumns = theNumberOfColumns - OL_Columns;

    if (OL_Columns)
    {
        // number of two level columns according to OL_Columns or theNumberOfColumns
        // each one level column can support two , two level column
        TwL_Columns = getRandomNumber(0, (theNumberOfColumns - (OL_Columns * 2)) >= 0 ? OL_Columns * 2 : theNumberOfColumns);
        theNumberOfColumns = theNumberOfColumns - TwL_Columns;

        if (TwL_Columns)
        {
            // number of three level columns according to TwL_Columns or theNumberOfColumns
            // each two level column can support two , three level column
            ThL_Columns = getRandomNumber(0, (theNumberOfColumns - (TwL_Columns * 2)) >= 0 ? TwL_Columns * 2 : theNumberOfColumns);
        }
    }
}

void Columns::setAndcreateColumnPositions(Platform &MyPlatform)
{
    // set three level columns positions
    while (ThL_Columns)
    {
        int The_ThL_position = getRandomNumber(1, availableForColumns);

        for (int Position : ThL_ColumnsPositions)
        {
            if (The_ThL_position == Position || The_ThL_position == Position + 1 || The_ThL_position == Position - 1 || The_ThL_position == Position + 2 || The_ThL_position == Position - 2)
                goto ThL_Loop_Continue;
        }

        ThL_ColumnsPositions.push_back(The_ThL_position);
        ThL_Columns--;
        this->createColumn(columnType::ThL, The_ThL_position, MyPlatform);

    // for the continuing twi loops
    ThL_Loop_Continue:;
    }

    // set two level columns positions
    while (TwL_Columns)
    {
        int The_TwL_position = getRandomNumber(1, availableForColumns);

        for (int Position : ThL_ColumnsPositions)
        {
            if (The_TwL_position == Position || The_TwL_position == Position + 1 || The_TwL_position == Position - 1 || The_TwL_position == Position + 2 || The_TwL_position == Position - 2)
                goto TwL_Loop_Continue;
        }

        for (int Position : TwL_ColumnsPositions)
        {
            if (The_TwL_position == Position || The_TwL_position == Position + 1 || The_TwL_position == Position - 1 || The_TwL_position == Position + 2 || The_TwL_position == Position - 2)
                goto TwL_Loop_Continue;
        }

        TwL_ColumnsPositions.push_back(The_TwL_position);
        TwL_Columns--;
        this->createColumn(columnType::TwL, The_TwL_position, MyPlatform);

    // for the continuing twi loops
    TwL_Loop_Continue:;
    }

    // set one level columns positions
    while (OL_Columns)
    {
        int The_OL_position = getRandomNumber(1, availableForColumns);

        for (int Position : ThL_ColumnsPositions)
        {
            if (The_OL_position == Position || The_OL_position == Position + 1 || The_OL_position == Position - 1 || The_OL_position == Position + 2 || The_OL_position == Position - 2)
                goto OL_Loop_Continue;
        }

        for (int Position : TwL_ColumnsPositions)
        {
            if (The_OL_position == Position || The_OL_position == Position + 1 || The_OL_position == Position - 1 || The_OL_position == Position + 2 || The_OL_position == Position - 2)
                goto OL_Loop_Continue;
        }

        for (int Position : OL_ColumnsPositions)
        {
            if (The_OL_position == Position || The_OL_position == Position + 1 || The_OL_position == Position - 1 || The_OL_position == Position + 2 || The_OL_position == Position - 2)
                goto OL_Loop_Continue;
        }

        OL_ColumnsPositions.push_back(The_OL_position);
        OL_Columns--;
        this->createColumn(columnType::OL, The_OL_position, MyPlatform);

    // for the continuing twi loops
    OL_Loop_Continue:;
    }
}

void Columns::createColumn(enum columnType columnType, int center, Platform &MyPlatform)
{
    // The horizontol center of floor level of column
    // add to (3 - 1) because of three start character of the row
    // and - 1 because indexes of platform vector starts from zero
    center = center + 2;

    // All columns have base floor!
    // first floor
    int yIntox = 26 * (Platform::W_WIDTH + 1);
    MyPlatform.ThePlatform[yIntox + center + 1] = Columns::column;
    MyPlatform.ThePlatform[yIntox + center] = Columns::column;
    MyPlatform.ThePlatform[yIntox + center - 1] = Columns::column;

    switch (columnType)
    {
    case columnType::TwL:
        // scound floor
        yIntox = 25 * (Platform::W_WIDTH + 1);
        MyPlatform.ThePlatform[yIntox + center + 1] = Columns::column;
        MyPlatform.ThePlatform[yIntox + center] = Columns::column;
        MyPlatform.ThePlatform[yIntox + center - 1] = Columns::column;
        break;
    case columnType::ThL:
        // scound floor
        yIntox = 25 * (Platform::W_WIDTH + 1);
        MyPlatform.ThePlatform[yIntox + center + 1] = Columns::column;
        MyPlatform.ThePlatform[yIntox + center] = Columns::column;
        MyPlatform.ThePlatform[yIntox + center - 1] = Columns::column;
        // third floor
        yIntox = 24 * (Platform::W_WIDTH + 1);
        MyPlatform.ThePlatform[yIntox + center + 1] = Columns::column;
        MyPlatform.ThePlatform[yIntox + center] = Columns::column;
        MyPlatform.ThePlatform[yIntox + center - 1] = Columns::column;
        break;
    }
}

void Columns::processThePlatform(Platform &MyPlatform)
{
    this->setColumns();
    this->setAndcreateColumnPositions(MyPlatform);
}

#endif