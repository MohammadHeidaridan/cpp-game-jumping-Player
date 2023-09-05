#include <ctime>
#include "./Helpers.hpp"
#include "./classes/Player.cpp"
#include "./classes/Platform.cpp"
#include "./classes/Columns.cpp"
#include "./classes/theFigure.cpp"
#include "./classes/Animation.cpp"
#include "./classes/Movement.cpp"
#include "./classes/Menu.cpp"

int main()
{
    // seed the rand
    srand(time(0));

    // create platform
    Platform MyPlatform;
    MyPlatform.startThePlatform();

    // set columns 
    Columns Columns;
    Columns.processThePlatform(MyPlatform);

    // show the platform
    MyPlatform.showThePlatform();

    // show menus
    Menu::showMenuInPlatform(MyPlatform);

    // set figure and player position
    Player::startThePlayer(MyPlatform);
    
    // palyer droping animation
    Player::animateTheStartPlayer(MyPlatform);
    theFigure::setTheFigurePosition(MyPlatform);

    // start the game
    Movement::runTheGame(MyPlatform);

    return 0;
}