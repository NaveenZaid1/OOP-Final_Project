#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Bullet.h"
#include <iostream>

Bullet::Bullet(float x, float y) : speed(5.0f)
{
    bulletShape.setRadius(10.0f);
    bulletShape.setFillColor(sf::Color::Red);

    // Center the bullet at the given x and y coordinates
    bulletShape.setPosition(x - bulletShape.getRadius(), y);
}

void Bullet::update()
{
    // Move the bullet upwards
    bulletShape.move(0, -speed);
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(bulletShape);
}

float Bullet::getWidth() const
{
    return bulletShape.getRadius() * 2.0f;
}

float Bullet::getHeight() const
{
    return bulletShape.getRadius() * 2.0f;
}

sf::FloatRect Bullet::getBounds() const
{
    return bulletShape.getGlobalBounds();
}
