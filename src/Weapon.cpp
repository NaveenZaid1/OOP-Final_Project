#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Weapon.h"
#include <algorithm>
#include <iostream>

Weapon::Weapon() : currentWeaponType(WeaponType::BULLET) //first bullet by default
{
    // Load laser texture
    if (!laserTexture.loadFromFile("assets\\laser.png")) 
    {
        std::cerr << "Failed to load laser texture!" << std::endl;
    }
}

void Weapon::switchWeaponType(WeaponType type)
{
    currentWeaponType = type;
}

WeaponType Weapon::getCurrentWeaponType() const
{
    return currentWeaponType;
}

void Weapon::fire(float x, float y)
{
    switch (currentWeaponType)
    {
    case WeaponType::BULLET:
        bullets.emplace_back(x, y);
        break;
    case WeaponType::LASER:
        lasers.emplace_back(x, y, &laserTexture);
        break;
    }
}

void Weapon::update(float windowHeight)
{
    // Update and remove bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                       [windowHeight](const Bullet &bullet)
                       {
                           return bullet.getBounds().top + bullet.getHeight() < 0;
                       }),
        bullets.end());

    for (auto &bullet : bullets)
    {
        bullet.update();
    }

    // Update and remove lasers
    lasers.erase(
        std::remove_if(lasers.begin(), lasers.end(),
                       [windowHeight](const Laser &laser)
                       {
                           return laser.getBounds().top + laser.getHeight() < 0;
                       }),
        lasers.end());

    for (auto &laser : lasers)
    {
        laser.update();
    }
}

void Weapon::draw(sf::RenderWindow &window)
{
    // Draw bullets
    for (auto &bullet : bullets)
    {
        bullet.draw(window);
    }

    // Draw lasers
    for (auto &laser : lasers)
    {
        laser.draw(window);
    }
}
