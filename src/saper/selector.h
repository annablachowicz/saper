#ifndef SELECTOR_H
#define SELECTOR_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>

enum keys
{
    left = 0,
    right,
    up,
    down
};

class Selector
{
public:
    Selector(int _offsetX, int _offsetY, int _maxX, int _maxY);

    int getTileX() const;
    void setTileX(int _tileX);

    int getTileY() const;
    void setTileY(int _tileY);

    void drawSelector(sf::RenderWindow &window);
    void move(int direction);

private:
    int tileX, tileY;
    int maxX, maxY;
    int offsetX, offsetY;

    sf::RectangleShape selectorRect;
};

#endif // SELECTOR_H
