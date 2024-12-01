// #ifndef ENEMY_H
// #define ENEMY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <cstdlib>
class Enemy {
public:
    sf::Texture enemyTexture;
    sf::Sprite enemySprite;
    int HP;
    int HPMax;
    float speed;
    
    Enemy()=default;
    Enemy(sf::Texture* tex, float speed, sf::Vector2u windowSize);
    void setPosition(float x, float y);
    virtual void update();
    bool isOffScreen(float windowHeight) const;
    void draw(sf::RenderWindow& window);
    virtual ~Enemy() = default;
    
};


class Enemy2: public Enemy
{
    public:
        Enemy2(sf::Texture* tex, float speed, sf::Vector2u windowSize);
};


class Enemy3 : public Enemy 
{
    public:
        float diagonalSpeedX; // Speed in the horizontal direction

        Enemy3(sf::Texture* tex, float speed, sf::Vector2u windowSize);
        void update() override; // Override update method to include diagonal movement
};


// #endif
