#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\laser.h"
#include <iostream>

// Default constructor
Laser::Laser() : speed(5.0f)
{
    // Initialize with default values if needed
}

Laser::Laser(float x, float y, sf::Texture *laserTexture) : speed(5.0f)
{
    // Check if texture is valid
    if (laserTexture)
    {
        // Set the laser sprite with the provided texture
        laserSprite.setTexture(*laserTexture);

        // Scale the laser sprite (adjust as needed)
        laserSprite.setScale(0.5f, 0.5f);

        // Center the laser at the given x and y coordinates
        laserSprite.setPosition(x - laserSprite.getGlobalBounds().width / 2, y);
    }
    else
    {
        std::cerr << "Invalid laser texture!" << std::endl;
    }
}

void Laser::update()
{
    // Move the laser upwards
    laserSprite.move(0, -speed);
}

void Laser::draw(sf::RenderWindow &window)
{
    window.draw(laserSprite);
}

float Laser::getWidth() const
{
    return laserSprite.getGlobalBounds().width;
}

float Laser::getHeight() const
{
    return laserSprite.getGlobalBounds().height;
}

sf::FloatRect Laser::getBounds() const
{
    return laserSprite.getGlobalBounds();
}