#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::Sprite bulletSprite;
    sf::Texture bulletTexture;

public:
    Bullet();
    Bullet(float x, float y);
    bool loadTexture(const std::string &filepath);
    void setPosition(float x, float y);
    void update();                       // Moves the bullet
    void draw(sf::RenderWindow &window); // Draws the bullet
    bool isOffScreen(int windowHeight) const;

    float getWidth() const; // Get bullet width for positioning
};

#endif
