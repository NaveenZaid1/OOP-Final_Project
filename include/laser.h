#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

class Laser
{
private:
    sf::Sprite laserSprite;
    float speed;

public:
    // Default constructor
    Laser();

    // Parameterized constructor
    Laser(float x, float y, sf::Texture *laserTexture);

    void update();
    void draw(sf::RenderWindow &window);

    float getWidth() const;
    float getHeight() const;
    sf::FloatRect getBounds() const;
};

#endif