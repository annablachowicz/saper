#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <memory>

#include "board.h"
#include "database.h"
#include "mainwindow.h"

class GameController
{
public:
    GameController();

    void startGame(int boardWidth, int boardHeight);

private:
    Database *database;
    Board *gameBoard;
    sf::RenderWindow *gameWindow;

    bool gameGenerated;
    bool gameOver;

    void reloadDisplay();
    void endGame();
};

#endif // GAMECONTROLLER_H
