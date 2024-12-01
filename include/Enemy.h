#pragma once

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include <cstdlib>
class Enemy 
{
private:
    sf::Texture enemyTexture;

public:
    sf::Sprite enemySprite;
    float speed;
    int type;
    
    Enemy()=default;
    Enemy(sf::Texture* tex, float speed, sf::Vector2u windowSize);
    void setPosition(float x, float y);
    virtual void update();
    bool isOffScreen(float windowHeight) const;
    void draw(sf::RenderWindow& window);
    virtual ~Enemy() = default;
    
};

//change here name of classes
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
        void update() override; /////// Override update method to include diagonal movement//chanmg here
};
