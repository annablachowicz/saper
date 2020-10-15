#ifndef BOARD_H
#define BOARD_H

#include "boardtile.h"
#include "selector.h"
#include "userdata.h"

#include "vector"


class Board
{
public:
    Board(int width, int height, int _offsetX, int _offsetY);

    void draw(sf::RenderWindow &window);
    void generateGameBoard();
    void moveSelector(int direction);

    bool explore();
    void flag();
    void blowUp();

private:

    Selector *selector;
    UserData user;

    int boardWidth;
    int boardHeight;

    int offsetX;
    int offsetY;

    bool gameOn;

    std::vector<std::vector<BoardTile*>> tileBoard;

    void generateMines();
    void generateNumbers();
    void revealEmptyNeighbors(int x, int y);

};

#endif // BOARD_H
