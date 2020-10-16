#include "boardtile.h"
#include <iostream>

BoardTile::BoardTile(int _x, int _y)
{
    x = _x;
    y = _y;

    currentX = 0;
    currentY = 0;

    revealed = false;
    flagged = false;

    try
    {
        texture.loadFromFile("../source/img/saper2.png");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what();
    }

    textureRec = sf::IntRect(153, 52, 16, 16);

    sprite.setTexture(texture);
    sprite.setTextureRect(textureRec);
    sprite.setPosition(sf::Vector2f(x, y));

    hasMine = false;
    blownUp = false;
}

void BoardTile::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

bool BoardTile::getHasMine() const
{
    return this->hasMine;
}

void BoardTile::setHasMine(const bool &_hasMine)
{
    hasMine = _hasMine;
}

int BoardTile::getHintNumber() const
{
    return hintNumber;
}

void BoardTile::setHintNumber(const int &_hintNumber)
{
    hintNumber = _hintNumber;
}

int BoardTile::explore()
{
    if(hasMine)
    {
        textureRec = sf::IntRect(425, 148, 16, 16);
        sprite.setTextureRect(textureRec);
        blownUp = true;
//        std::cout << "blowup" << std::endl;
        return blowup;
    }
    if(hintNumber == 0)
    {
        revealTexture();
//        std::cout << "emptyRevealed" << std::endl;
        return emptyRevealed;
    }
    else
    {
        revealTexture();
//        std::cout << "numberRevealed" << std::endl;
        return numberRevealed;
    }
}

void BoardTile::flag()
{
    flagged = !flagged;

    if(flagged)
    {
        textureRec = sf::IntRect(329, 148, 16, 16);
    }
    else
    {
        textureRec = sf::IntRect(153, 52, 16, 16);
    }

    sprite.setTextureRect(textureRec);

}

void BoardTile::setTextureRec(sf::IntRect _textureRect)
{
    textureRec = _textureRect;
}

bool BoardTile::getFlagged() const
{
    return flagged;
}

bool BoardTile::getRevealed() const
{
    return revealed;
}

void BoardTile::revealTexture()
{
    if(hasMine && !blownUp && !flagged)
    {
        textureRec = sf::IntRect(153, 68, 16, 16);
    }
    if(flagged && !hasMine) // źle zaznaczona
    {
        textureRec = sf::IntRect(409, 148, 16, 16);
    }
    else if (!hasMine && !flagged)
    {
        switch (hintNumber) {
        case 0: textureRec = sf::IntRect(41, 196, 16, 16);
            break;
        case 1: textureRec = sf::IntRect(249, 292, 16, 16);
            break;
        case 2: textureRec = sf::IntRect(265, 276, 16, 16);
            break;
        case 3: textureRec = sf::IntRect(233, 292, 16, 16);
            break;
        case 4: textureRec = sf::IntRect(281, 132, 16, 16);
            break;
        case 5: textureRec = sf::IntRect(314, 132, 16, 16);
            break;
        case 6: textureRec = sf::IntRect(233, 276, 16, 16);
            break;
        case 7: textureRec = sf::IntRect(281, 292, 16, 16);
            break;
        case 8: textureRec = sf::IntRect(297, 292, 16, 16);
            break;

        }
    }

    sprite.setTextureRect(textureRec);

    revealed = true;
}
