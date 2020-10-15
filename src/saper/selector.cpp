#include "selector.h"

Selector::Selector(int _offsetX, int _offsetY, int _maxX, int _maxY)
{
    tileX = 0;
    tileY = 0;

    maxX = _maxX;
    maxY = _maxY;

    offsetX = _offsetX;
    offsetY = _offsetY;

    selectorRect.setPosition(sf::Vector2f(offsetX, offsetY));
    selectorRect.setSize(sf::Vector2f(16, 16));
    selectorRect.setFillColor(sf::Color::Transparent);
    selectorRect.setOutlineThickness(3);
    selectorRect.setOutlineColor(sf::Color(250, 150, 100));
}

int Selector::getTileX() const
{
    return tileX;
}

void Selector::setTileX(int _tileX)
{
    tileX = _tileX;
}

int Selector::getTileY() const
{
    return tileY;
}

void Selector::setTileY(int _tileY)
{
    tileY = _tileY;
}

void Selector::drawSelector(sf::RenderWindow &window)
{
    selectorRect.setPosition(sf::Vector2f(tileX*16+offsetX, tileY*16+offsetY));
    window.draw(selectorRect);
}

void Selector::move(int direction)
{
    switch(direction)
    {
    case left:
        if(tileX == 0) break;
        else
        {
          tileX-=1;
        } break;
    case right:
        if(tileX == maxX-1) break;
        else
        {
          tileX+=1;
        } break;
    case up:
        if(tileY == 0) break;
        else
        {
          tileY-=1;
        } break;
    case down:
        if(tileY == maxY-1) break;
        else
        {
          tileY+=1;
        } break;
    }

}

