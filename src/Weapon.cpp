#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Weapon.h"

void Weapon::fire(float x, float y)
{
    bullets.emplace_back(x, y); // Add a new bullet at the specified position
}

void Weapon::update(float windowHeight)
{
    for (size_t i = 0; i < bullets.size(); ++i)
    {
        bullets[i].update();
        if (bullets[i].isOffScreen(windowHeight))
        {
            bullets.erase(bullets.begin() + i); // Remove bullet if it's off-screen
            --i;                                // Adjust index after removal
        }
    }
}

void Weapon::draw(sf::RenderWindow &window)
{
    for (auto &bullet : bullets)
    {
        bullet.draw(window);
    }
}

std::vector<Bullet> &Weapon::getBullets()
{
    return bullets;
}
