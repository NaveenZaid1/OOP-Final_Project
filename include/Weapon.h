#ifndef WEAPON_H
#define WEAPON_H

#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Bullet.h"
#include <vector>

class Weapon
{
private:
    std::vector<Bullet> bullets; // Stores active bullets

public:
    void fire(float x, float y);         // Create a new bullet
    void update(float windowHeight);     // Update bullet positions and remove off-screen bullets
    void draw(sf::RenderWindow &window); // Render bullets
    std::vector<Bullet> &getBullets();   // Access the bullet list
};

#endif
