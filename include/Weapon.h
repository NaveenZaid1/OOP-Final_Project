#ifndef WEAPON_H
#define WEAPON_H

#include "include\Bullet.h"
#include "include\laser.h"
#include <vector>

enum class WeaponType
{
    BULLET,
    LASER
};

class Weapon
{
private:
    sf::Texture laserTexture;
    WeaponType currentWeaponType;

public:
    std::vector<Bullet> bullets;
    std::vector<Laser> lasers;

    Weapon(); // Constructor to load laser texture
    void switchWeaponType(WeaponType type);
    WeaponType getCurrentWeaponType() const;

    void fire(float x, float y);
    void update(float windowHeight);
    void draw(sf::RenderWindow &window);
};

#endif
