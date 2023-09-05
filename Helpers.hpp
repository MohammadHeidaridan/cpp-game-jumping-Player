#include <cstdlib>
#include <iostream>

#ifndef Def_Helpers
#define Def_Helpers

int getRandomNumber(int from, int to)
{
    return from + rand() % (to - from + 1);
}

template <typename T>
void print(const T& value) {
    std::cout << value << std::endl;
}

#endif