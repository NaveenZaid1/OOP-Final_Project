#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Weapon.h"

void Weapon::fire(float x, float y)
{
    // Create a new bullet at the specified position
    bullets.emplace_back(x, y);
}


void Weapon::update(float windowHeight)
{
    // Remove bullets that have gone off the screen
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                       [windowHeight](const Bullet &bullet)
                       {
                           return bullet.getBounds().top + bullet.getHeight() < 0;
                       }),
        bullets.end());

    // Update remaining bullets
    for (auto &bullet : bullets)
    {
        bullet.update();
    }
}

void Weapon::draw(sf::RenderWindow &window)
{
    // Draw all bullets
    for (auto &bullet : bullets)
    {
        bullet.draw(window);
    }
}