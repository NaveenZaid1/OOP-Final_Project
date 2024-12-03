#ifndef PLAYER_H
#define PLAYER_H

#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Weapon.h"
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

public:
    Weapon weapon;
    int HP = 3; // Added HP tracking
    bool loadTexture(const std::string &filepath);
    void setPosition(float x, float y);
    void scale(float scaleX, float scaleY);
    void update();
    void draw(sf::RenderWindow &window);

    void stayWithinBounds();
    void fire();
    void updateBullets(float windowHeight);

    sf::Vector2f getPosition() const;
    float getWidth() const;
    sf::FloatRect GetGlobalBounds() const;

    // Getter for HP
    int getHP() const { return HP; }

    // Setter for HP 
    void setHP(int hp) { HP = hp; }
    // sf::FloatRect GetGlobalBounds() const;
    
};

#endif
