#include <iostream>
//#include "mainwindow.h"
//#include "boardtile.h"
#include "gamecontroller.h"

using namespace std;

int main()
{

    GameController gameController;
    gameController.startGame(30,16);

    return 0;
}
