#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <iostream>
#include <memory>
#include <ctime>
#include <string>

#include "board.h"
#include "database.h"

class GameController
{
public:
    GameController();
    ~GameController();

    void startGame(int boardWidth, int boardHeight);

private:
    Database *database;
    Board *gameBoard;
    sf::RenderWindow *gameWindow;
    UserData user;
//    int bestTime = 0;

    bool welcomeScreen;
    bool gameGenerated;
    bool gameOver;

    sf::Text welcomeText;
    sf::String nameInput;
    sf::Text nameText;
    sf::RectangleShape nameTextField;
    sf::Font font;

    sf::Text gameOverText;
    sf::Text gameOverText2;

    void reloadDisplay();
    void endGame();
    void showWelcomeScreen();
    void showGameOverScreen();
    void gameFinished();

    bool loser;

    clock_t beginTimer;
    clock_t endTimer;
    int gameTime = 0;
};

#endif // GAMECONTROLLER_H
