#pragma once
#include <SFML/Graphics.hpp>
#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Weapon.h"

class Laser : public Weapon
{
public:
    Laser(const sf::Texture &texture, const sf::Vector2f &startPosition);
    void update(float deltaTime);           // Update the laser's movement
    void draw(sf::RenderWindow &window);    // Draw laser sprite
    bool isOutOfBounds(float screenHeight); // Check if laser is out of screen bounds

    // You can add additional functionality like changing the laser's color, speed, etc.

private:
    sf::Sprite laserSprite; // Laser sprite
    float speed;            // Speed of the laser
};