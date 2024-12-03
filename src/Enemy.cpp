#include <iostream>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;
#include "include\Enemy.h"
#include <cstdlib>

//Basic Enemy
//constructor
Enemy::Enemy(sf::Texture* tex, float speed, sf::Vector2u windowSize)
{
    type = 0;
    if(speed<1.0f){
        speed=1.0f;
    }
    enemySprite.setTexture(*tex);
    enemySprite.setScale(0.1f, 0.1f);
    float randomX = static_cast<float>(rand() % static_cast<int>(windowSize.x - (enemySprite.getGlobalBounds().width)));
    enemySprite.setPosition(randomX, -50.0f); // Staggered positions
}

void Enemy::setPosition(float x, float y) 
{
    enemySprite.setPosition(x, y);
}

void Enemy::update() 
{
    enemySprite.move(0, 0.7f);
}

bool Enemy::isOffScreen(float windowHeight) const {
    return enemySprite.getPosition().y > windowHeight;
}


void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemySprite);
}


//Enemy2
Enemy2::Enemy2(sf::Texture* tex, float speed, sf::Vector2u windowSize): Enemy(tex, speed, windowSize) 
{
    type = 1;
    enemySprite.setScale(0.2f, 0.2f);
    float randomX = static_cast<float>(rand() % static_cast<int>(windowSize.x - (enemySprite.getGlobalBounds().width)));
    enemySprite.setPosition(randomX, -50.0f); // Staggered positions
}

//Enemy3
Enemy3::Enemy3(sf::Texture* tex, float speed, sf::Vector2u windowSize): Enemy(tex, speed, windowSize) 
{
    type = 2;
    diagonalSpeedX = (rand() % 2 == 0) ? 2.0f : -2.0f; // Randomly move left or right
    enemySprite.setScale(0.08f, 0.08f); // Slightly smaller size
    float randomX = static_cast<float>(rand() % static_cast<int>(windowSize.x - enemySprite.getGlobalBounds().width));
    enemySprite.setPosition(randomX, -50.0f); // Start position
}

void Enemy3::update()
{
    enemySprite.move(0, 0.7f);

    // Reverse direction if hitting screen edges
    if (enemySprite.getPosition().x <= 0 || 
        enemySprite.getPosition().x + enemySprite.getGlobalBounds().width >= 800) { // Assuming 800 is window width
        diagonalSpeedX = -diagonalSpeedX; // Change direction
    }
}
