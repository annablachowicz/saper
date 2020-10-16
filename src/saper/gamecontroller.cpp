#include "gamecontroller.h"
//#include <SFML/Graphics/Font.hpp>


GameController::GameController()
{
    gameWindow = new sf::RenderWindow (sf::VideoMode(800, 600), "Minesweeper");
    database = new Database();

    if (!font.loadFromFile("../source/fonts/arial.ttf")) {}

    gameBoard = nullptr;
    welcomeText.setString("WPROWADZ IMIE");
    welcomeText.setCharacterSize(26);
    welcomeText.setFont(font);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setPosition(280, 140);

    nameText.setString("");
    nameText.setCharacterSize(24);
    nameText.setFont(font);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(330, 220);

    nameTextField.setSize(sf::Vector2f(140, 70));
    nameTextField.setFillColor(sf::Color(168, 250, 145));
    nameTextField.setPosition(320, 200);

    gameGenerated = false;
    gameOver = false;
    loser = false;
    welcomeScreen = true;
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

            if(welcomeScreen)
            {
                if (event.type == sf::Event::TextEntered)
                {
                    nameInput += event.text.unicode;
                    nameText.setString(nameInput);
                }
                if(event.type == sf::Event::KeyPressed)
                {
                    if(event.key.code == sf::Keyboard::Return)
                    {
                        welcomeScreen = false;
                        user.setName(nameInput);
                        beginTimer = clock();
                    }
                    //                    if(event.key.code == sf::Keyboard::BackSpace)
                    //                    {
                    //                        nameInput.erase(nameInput.toAnsiString().length()-1);
                    //                        nameText.setString(nameInput);
                    //                    }
                }

            }


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
                            reloadDisplay();
                            loser = true;
                            gameFinished();
                            //                            endGame();
                        }
                        if(gameBoard->finishGame()) // wygrana
                        {
                            gameFinished();
                        }
                    }
                    else if(event.key.code == sf::Keyboard::X)  // flag
                    {
                        gameBoard->flag();
                        reloadDisplay();

                        if(gameBoard->finishGame()) // wygrana
                        {
                            gameFinished();
                        }
                    }
                }
            }
        }

        if(welcomeScreen)
        {
            showWelcomeScreen();
        }


        if(!gameGenerated && !welcomeScreen)
        {
            gameBoard->generateGameBoard();
            reloadDisplay();
            gameGenerated = true;
        }

        if(gameOver)
        {
            showGameOverScreen();
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

void GameController::showWelcomeScreen()
{
    gameWindow->clear(sf::Color(5, 48, 11));
    gameWindow->draw(nameTextField);
    if(nameInput.toAnsiString().length() > 0)
    {
        gameWindow->draw(nameText);
    }
    gameWindow->draw(welcomeText);

    gameWindow->display();
}

void GameController::showGameOverScreen()
{
    gameWindow->clear(sf::Color(80, 80, 255));
    gameBoard->draw(*gameWindow);

    gameOverText.setCharacterSize(24);
    gameOverText.setFont(font);
    gameOverText.setFillColor(sf::Color(0,0,0));
    gameOverText.setPosition(180, 50);
    if(loser)
    {
        gameOverText.setString(sf::String("PRZEGRALES :( Twoj wynik: " + std::to_string(gameTime)));
    }
    else
    {
        gameOverText.setString(sf::String("WYGRALES! Twoj wynik: " + std::to_string(gameTime)));

    }

    gameOverText2.setCharacterSize(24);
    gameOverText2.setFont(font);
    gameOverText2.setFillColor(sf::Color(0,0,0));
    gameOverText2.setPosition(180, 80);
    if(noWinner)
    {
        gameOverText2.setString(sf::String("Najlepszy wynik (przegral): " + std::to_string(ss.get())));
    }
    else
    {
        gameOverText2.setString(sf::String("Najlepszy wynik (wygral): " + std::to_string(ss.get())));
    }

    gameWindow->draw(gameOverText);
    gameWindow->draw(gameOverText2);

    gameWindow->display();
}

void GameController::gameFinished()
{
    endTimer = clock();

    if(loser) user.setSuccess(0);
    else user.setSuccess(1);

    gameTime = int(endTimer - beginTimer);

    user.setTime(gameTime);
    database->addUser(user);
    database->getBestUser();
    if(noWinner) database->getBestLoser();

    gameOver = true;

    ss >> bestTime;
       std::cout<< "best time "/* << ss.get() << " "*/ << bestTime << std::endl;

    //   std::cout<<bestScore<<std::endl;
}


