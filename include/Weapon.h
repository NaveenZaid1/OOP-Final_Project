#ifndef WEAPON_H
#define WEAPON_H

#include "Bullet.h"
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
