#ifndef Def_Columns_h
#define Def_Columns_h

class Columns
{
public:
    static const int availableForColumns = 113; // 116 (empty positions) - 2 (2 because we use center of floor of column to set column's position)
    static const char column = '#';
    void processThePlatform(Platform &MyPlatform);

private:

    // One level columns
    //
    // ###
    int OL_Columns = 0;
    vector<int> OL_ColumnsPositions;

    // Two level columns
    //
    // ###
    // ###
    int TwL_Columns = 0;
    vector<int> TwL_ColumnsPositions;

    // Theee level columns
    //
    // ###
    // ###
    // ###
    int ThL_Columns = 0;
    vector<int> ThL_ColumnsPositions;
    
    // Column Types
    enum columnType
    {
        OL,
        TwL,
        ThL
    };
    static const int MaximumNumberOfColumns= 38; // 116 (empty positions) / 3 = 38.66 => 38

    void setColumns();
    void setAndcreateColumnPositions(Platform &MyPlatform);
    void createColumn(enum columnType columnType, int center, Platform &MyPlatform);
};

#endif