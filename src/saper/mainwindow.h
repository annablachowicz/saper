#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "board.h"

class MainWindow
{
public:
    MainWindow();

    void showWindow();
    sf::RenderWindow* getWindow();

private:
//    Board *board;
    sf::RenderWindow *gameWindow;

};

#endif // MAINWINDOW_H
