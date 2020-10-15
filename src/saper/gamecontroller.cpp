#include "gamecontroller.h"

GameController::GameController()
{
    gameWindow = new sf::RenderWindow (sf::VideoMode(800, 600), "Minesweeper");
    database = new Database();
//    User user({1, "ewewe", 23, 32});
//    database->addUser(user);
//    database->getBestScore();
    gameBoard = nullptr;

    gameGenerated = false;
    gameOver = false;
}

void GameController::startGame(int boardWidth, int boardHeight)
{
    gameBoard = new Board(boardWidth, boardHeight, 160, 120);

    while (gameWindow->isOpen())
    {
        sf::Event event;
        while (gameWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow->close();

            if(event.type == sf::Event::KeyPressed)
            {
                if(!gameOver)
                {
                    if(event.key.code == sf::Keyboard::Left)
                    {
                        gameBoard->moveSelector(left);
                        reloadDisplay();
                    }
                    else if(event.key.code == sf::Keyboard::Right)
                    {
                        gameBoard->moveSelector(right);
                        reloadDisplay();
                    }
                    else if(event.key.code == sf::Keyboard::Up)
                    {
                        gameBoard->moveSelector(up);
                        reloadDisplay();
                    }
                    else if(event.key.code == sf::Keyboard::Down)
                    {
                        gameBoard->moveSelector(down);
                        reloadDisplay();
                    }
                    else if(event.key.code == sf::Keyboard::Space) // explore
                    {
                        if(gameBoard->explore()) // ok
                        {
                            reloadDisplay();
                        }
                        else // przegrana
                        {
                            gameOver = true;
                            reloadDisplay();
//                            endGame();
                        }
                    }
                    else if(event.key.code == sf::Keyboard::X)  // flag
                    {
                        gameBoard->flag();
                        reloadDisplay();
                    }
                }
            }
        }


        if(!gameGenerated)
        {
            gameBoard->generateGameBoard();
            reloadDisplay();
            gameGenerated = true;
        }

    }
}

void GameController::reloadDisplay()
{
    gameWindow->clear(sf::Color(170, 0, 0));
    gameBoard->draw(*gameWindow);
    gameWindow->display();
}

void GameController::endGame()
{
    // TODO
    gameWindow->clear();
    gameBoard->draw(*gameWindow);
    gameWindow->display();

}
