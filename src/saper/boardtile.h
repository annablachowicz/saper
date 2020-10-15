#ifndef BOARDTILE_H
#define BOARDTILE_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>

enum exploreResult
{
    emptyRevealed = 0,
    numberRevealed,
    blowup
};

class BoardTile
{
public:
    BoardTile(int _x, int _y);
    void draw(sf::RenderWindow &window);
    void revealTexture();

    bool getHasMine() const;
    void setHasMine(const bool &_hasMine);

    int getHintNumber() const;
    void setHintNumber(const int &_hintNumber);

    int explore();
    void flag();

    bool getRevealed() const;

private:
    void setTextureRec(sf::IntRect _textureRect);

    sf::Sprite sprite;
    sf::IntRect textureRec;
    int x, y;
    sf::Texture texture;

    int currentX, currentY; // indeksy zaznaczonego pola
    bool hasMine;
    bool blownUp;
    bool revealed;
    bool flagged;
    int hintNumber;

};

#endif // BOARDTILE_H
