#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Bullet.h"
#include <iostream>

Bullet::Bullet()
{
    if (!loadTexture("assets\\bullet.png"))
    { 
        std::cerr << "Error loading bullet texture!" << std::endl;
    }
}

Bullet::Bullet(float x, float y)
{
    if (!bulletTexture.loadFromFile("assets\\bullet.png"))
    {
        std::cerr << "Error loading bullet texture!" << std::endl;
    }
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setPosition(x, y); // Set the position
}

bool Bullet::loadTexture(const std::string &filepath)
{
    if (!bulletTexture.loadFromFile(filepath))
    {
        return false;
    }
    bulletSprite.setTexture(bulletTexture);
    return true;
}

void Bullet::setPosition(float x, float y)
{
    bulletSprite.setPosition(x, y);
}

void Bullet::update()
{
    bulletSprite.move(0, -5); // Move the bullet upwards
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(bulletSprite);
}
bool Bullet::isOffScreen(int windowHeight) const
{
    return bulletSprite.getPosition().y < 0 || bulletSprite.getPosition().y > windowHeight;
}
float Bullet::getWidth() const
{
    return bulletSprite.getGlobalBounds().width;
}
