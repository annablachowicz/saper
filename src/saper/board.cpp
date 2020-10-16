#include "board.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>


Board::Board(int width, int height, int _offsetX, int _offsetY)
{
    boardHeight = height;
    boardWidth = width;
    offsetX = _offsetX;
    offsetY = _offsetY;

    flaggedOk = 0;
    explored = 0;

    gameOn = true;

    selector = new Selector(offsetX, offsetY, width, height);

    tileBoard = std::vector<std::vector<BoardTile*>>(width, std::vector<BoardTile*>(height));

    int tileOffsetX = offsetX;
    int tileOffsetY = offsetY;

    for(int x = 0; x < tileBoard.size(); x++)
    {
        for(int y = 0; y < tileBoard[x].size(); y++)
        {
            tileBoard[x][y] = new BoardTile(tileOffsetX, tileOffsetY);
            tileOffsetY += 16;
        }
        tileOffsetX += 16;
        tileOffsetY = offsetY;
    }

}

void Board::draw(sf::RenderWindow &window)
{
    for(int x = 0; x < tileBoard.size(); x++)
    {
        for(int y = 0; y < tileBoard[x].size(); y++)
        {
            tileBoard[x][y]->draw(window);
        }
    }

    selector->drawSelector(window);

}

void Board::generateGameBoard()
{
    generateMines();
    generateNumbers();
}

void Board::moveSelector(int direction)
{
    selector->move(direction);
}

bool Board::explore()
{
    switch(tileBoard[selector->getTileX()][selector->getTileY()]->explore())
    {
    case emptyRevealed:
        explored++;
        revealEmptyNeighbors(selector->getTileX(), selector->getTileY());
        break;
    case numberRevealed:
        break;
    case blowup: blowUp();
        gameOn = false;
        break;
    }

    return gameOn;
}

void Board::flag()
{
    tileBoard[selector->getTileX()][selector->getTileY()]->flag();
    if(tileBoard[selector->getTileX()][selector->getTileY()]->getHasMine()&&
            tileBoard[selector->getTileX()][selector->getTileY()]->getFlagged())
    {
        flaggedOk += 1;
    }
    else if(tileBoard[selector->getTileX()][selector->getTileY()]->getHasMine()&&
            !tileBoard[selector->getTileX()][selector->getTileY()]->getFlagged())
    {
        flaggedOk -= 1;
    }
}

void Board::blowUp()
{
    for(int x = 0; x < tileBoard.size(); x++)
    {
        for(int y = 0; y < tileBoard[x].size(); y++)
        {
            tileBoard[x][y]->revealTexture();
        }
    }
}

bool Board::finishGame()
{
    if(explored + flaggedOk == 480) return true;
    return false;
}

int Board::calculateScore()
{
    return flaggedOk + explored;
}

void Board::generateMines()
{
    // losowanie położenia min
    // 99 min dla planszy 30 x 16
    srand (time(NULL));

    int mineX = rand() % boardWidth;
    int mineY = rand() % boardHeight;

    for(int i = 0; i < 99; i++)
    {
        while(tileBoard[mineX][mineY]->getHasMine())  // jeśli jest mina to losowanie od nowa
        {
            mineX = rand() % boardWidth;
            mineY = rand() % boardHeight;
        }

        tileBoard[mineX][mineY]->setHasMine(true);
    }

}

void Board::generateNumbers()
{
    int hintNumber = 0;

    for(int x = 0; x < boardWidth; x++)
    {
        for(int y = 0; y < boardHeight; y++)
        {
            if(!tileBoard[x][y]->getHasMine())  // nie ma miny => liczymy dookoła
            {
                if(x == 0)  // krawędź
                {
                    if(y == 0)
                    {
                        for(int i = x; i <= x+1; i++)
                        {
                            for(int j = y; j <= y+1; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                    else if(y == boardHeight-1)
                    {
                        for(int i = x; i <= x+1; i++)
                        {
                            for(int j = y-1; j <= y; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                    else
                    {
                        for(int i = x; i <= x+1; i++)
                        {
                            for(int j = y-1; j <= y + 1; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                }
                else if(x == boardWidth-1)  // krawędź
                {
                    if(y == 0)
                    {
                        for(int i = x-1; i <= x; i++)
                        {
                            for(int j = y; j <= y+1; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                    else if(y == boardHeight-1)
                    {
                        for(int i = x-1; i <= x; i++)
                        {
                            for(int j = y-1; j <= y; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                    else
                    {
                        for(int i = x-1; i <= x; i++)
                        {
                            for(int j = y-1; j <= y+1; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                }

                else
                {
                    if(y == 0)
                    {
                        for(int i = x-1; i <= x; i++)
                        {
                            for(int j = y; j <= y+1; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                    else if(y == boardHeight-1)
                    {
                        for(int i = x-1; i <= x; i++)
                        {
                            for(int j = y-1; j <= y; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }

                    else
                    {
                        for(int i = x-1; i <= x+1; i++)
                        {
                            for(int j = y-1; j <= y+1; j++)
                            {
                                if(tileBoard[i][j]->getHasMine())
                                {
                                    hintNumber++;
                                }
                            }
                        }
                    }
                }

                tileBoard[x][y]->setHintNumber(hintNumber);
                hintNumber = 0;

            }
        }
    }
}

void Board::revealEmptyNeighbors(int x, int y)
{
    if(x == 0)  // krawędź
    {
        if(y == 0)
        {
            for(int i = x; i <= x+1; i++)
            {
                for(int j = y; j <= y+1; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }

                    }
                }
            }
        }
        else if(y == boardHeight-1)
        {
            for(int i = x; i <= x+1; i++)
            {
                for(int j = y-1; j <= y; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for(int i = x; i <= x+1; i++)
            {
                for(int j = y-1; j <= y + 1; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }
    }
    else if(x == boardWidth-1)  // krawędź
    {
        if(y == 0)
        {
            for(int i = x-1; i <= x; i++)
            {
                for(int j = y; j <= y+1; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }
        else if(y == boardHeight-1)
        {
            for(int i = x-1; i <= x; i++)
            {
                for(int j = y-1; j <= y; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for(int i = x-1; i <= x; i++)
            {
                for(int j = y-1; j <= y+1; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }
    }

    else
    {
        if(y == 0)
        {
            for(int i = x-1; i <= x; i++)
            {
                for(int j = y; j <= y+1; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }
        else if(y == boardHeight-1)
        {
            for(int i = x-1; i <= x; i++)
            {
                for(int j = y-1; j <= y; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }

        else
        {
            for(int i = x-1; i <= x+1; i++)
            {
                for(int j = y-1; j <= y+1; j++)
                {
                    if(x!=i || j != y)
                    {
                        if(!tileBoard[i][j]->getRevealed()) // zakryte
                        {
                            tileBoard[i][j]->revealTexture();
                            explored++;

                            if(tileBoard[i][j]->getHintNumber()==0)
                            {
                                revealEmptyNeighbors(i, j);
                            }
                        }
                    }
                }
            }
        }
    }

}

