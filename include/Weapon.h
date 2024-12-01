#ifndef WEAPON_H
#define WEAPON_H

#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Bullet.h"
#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\laser.h"
#include <vector>

class Weapon
{
public:
    std::vector<Bullet> bullets;
    void fire(float x, float y);
    void update(float windowHeight);
    void draw(sf::RenderWindow &window);
    
};

#endif
