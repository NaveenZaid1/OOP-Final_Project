#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::CircleShape bulletShape;
    float speed;

public:
    Bullet(float x, float y);
    Bullet(); 

    void update();
    void draw(sf::RenderWindow &window);

    float getWidth() const;
    float getHeight() const;
    sf::FloatRect getBounds() const;

};
#endif
