#ifndef BOARD_H
#define BOARD_H

#include "boardtile.h"
#include "selector.h"
#include "userdata.h"

#include "vector"
#include <memory>


class Board
{
public:
    Board(int width, int height, int _offsetX, int _offsetY);
    ~Board();

    void draw(sf::RenderWindow &window);
    void generateGameBoard();
    void moveSelector(int direction);

    bool explore();
    void flag();
    void blowUp();

    bool finishGame();
    int calculateScore();

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

    int flaggedOk, explored;

};

#endif // BOARD_H
