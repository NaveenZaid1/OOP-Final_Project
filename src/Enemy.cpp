#include <iostream>
#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
using namespace std;
#include "Enemy.h"
#include <cstdlib>

//Basic Enemy
//constructor
Enemy::Enemy(sf::Texture* tex, float speed, sf::Vector2u windowSize)
{
    HPMax = 3;
    HP = HPMax;
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
    enemySprite.move(0, 1.0f);
}

bool Enemy::isOffScreen(float windowHeight) const {
    return enemySprite.getPosition().y > windowHeight;
}


void Enemy::draw(sf::RenderWindow& window) {
    window.draw(enemySprite);
}


//EnemySmall
EnemySmall::EnemySmall(sf::Texture* tex, float speed, sf::Vector2u windowSize): Enemy(tex, speed, windowSize) 
{
    HPMax = 3;
    HP = HPMax;

    enemySprite.setScale(0.2f, 0.2f);
    float randomX = static_cast<float>(rand() % static_cast<int>(windowSize.x - (enemySprite.getGlobalBounds().width)));
    enemySprite.setPosition(randomX, -50.0f); // Staggered positions
}

//EnemyDiagonal
EnemyDiagonal::EnemyDiagonal(sf::Texture* tex, float speed, sf::Vector2u windowSize): Enemy(tex, speed, windowSize) 
{
    HPMax = 2;
    HP = HPMax;

    diagonalSpeedX = (rand() % 2 == 0) ? 2.0f : -2.0f; // Randomly move left or right
    enemySprite.setScale(0.08f, 0.08f); // Slightly smaller size
    float randomX = static_cast<float>(rand() % static_cast<int>(windowSize.x - enemySprite.getGlobalBounds().width));
    enemySprite.setPosition(randomX, -50.0f); // Start position
}

void EnemyDiagonal::update()
{
    enemySprite.move(0, 1.0f); // Move diagonally

    // Reverse direction if hitting screen edges
    if (enemySprite.getPosition().x <= 0 || 
        enemySprite.getPosition().x + enemySprite.getGlobalBounds().width >= 800) { // Assuming 800 is window width
        diagonalSpeedX = -diagonalSpeedX; // Change direction
    }
}