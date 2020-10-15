#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow()
{
//    board = new Board(20, 20);
    gameWindow = new sf::RenderWindow (sf::VideoMode(800, 600), "Minesweeper");
}

void MainWindow::showWindow()
{
    while (gameWindow->isOpen())
    {
        sf::Event event;
        while (gameWindow->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                gameWindow->close();
        }

        gameWindow->clear();


        //    window.draw(shape);
        gameWindow->display();

    }

    std::cout<<"okno"<<std::endl;
}

sf::RenderWindow *MainWindow::getWindow()
{
    return gameWindow;
}

