#include <SFML/Graphics.hpp>
#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Player.h"
#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Bullet.h" // Include Bullet header
#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\Enemy.h"
#include "C:\Users\User\Documents\Sem 5\OOP\project\OOP Project\OOP-Final_Project\include\laser.h"
#include <iostream>
#include <vector> // To store bullets in a vector

enum class GameState
{
    MENU,
    GAME
};



int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "GAME SCREEN");

    sf::Font font;
    if (!font.loadFromFile("SFML\\Fonts\\VGA New.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets\\background.png"))
    {
        std::cerr << "Error loading background image!" << std::endl;
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    sf::Texture gameBackgroundTexture;
    if (!gameBackgroundTexture.loadFromFile("assets\\game_background.png"))
    {
        std::cerr << "Error loading game background image!" << std::endl;
        return -1;
    }
    sf::Sprite gameBackground(gameBackgroundTexture);

    sf::Vector2u textureSize = gameBackgroundTexture.getSize(); // Aligning the game background with window size
    sf::Vector2u windowSize = window.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    gameBackground.setScale(scaleX, scaleY);

    sf::Text message("SPACESHOOTERS", font, 90);
    message.setFillColor(sf::Color(255, 165, 0));
    message.setPosition(79, 230);

    sf::RectangleShape startButton(sf::Vector2f(200, 70));
    startButton.setFillColor(sf::Color(135, 206, 235)); // Sky blue
    startButton.setPosition(300, 350);

    sf::Text buttonText("START", font, 50);
    buttonText.setFillColor(sf::Color(50, 50, 50));
    buttonText.setPosition(startButton.getPosition().x + 30, startButton.getPosition().y + 5);

    // Score setup
    sf::Text score_text;
    score_text.setFont(font);
    score_text.setCharacterSize(20);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(10.f, 10.f);

    // HPtext setup
    sf::Text HPtext;
    HPtext.setFont(font);
    HPtext.setCharacterSize(20);
    HPtext.setFillColor(sf::Color::White);
    HPtext.setPosition(10.f, 30.f);

    // Player setup
    int score = 0;
    Player player;
    if (!player.loadTexture("assets\\player.png"))
    {
        std::cerr << "Error loading player sprite!" << std::endl;
        return -1;
    }
    player.setPosition(100, 500);
    player.scale(0.2f, 0.2f);

    // Bullet setup
    // std::vector<Bullet> bullets; // Vector to store bullets

    // Enemy setup
    sf::Texture enemytex;
    enemytex.loadFromFile("assets\\file.png");
    sf::Texture enemytex2;
    enemytex2.loadFromFile("assets\\EnemyBig.png");
    sf::Texture enemytex3;
    enemytex3.loadFromFile("assets\\Enemy3.png");
    int EnemySpawnTimer = 0;
    std::vector<Enemy *> enemies;

    GameState currentState = GameState::MENU;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    currentState = GameState::GAME;
                }
            }

            // Update
            //  Shooting bullets when spacebar is pressed
            if (currentState == GameState::GAME && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space) // Switch to Bullet
                {
                    player.weapon.switchWeaponType(WeaponType::BULLET);
                    player.weapon.fire(player.getPosition().x, player.getPosition().y);
                }
                else if (event.key.code == sf::Keyboard::L) // Switch to Laser
                {
                    player.weapon.switchWeaponType(WeaponType::LASER);
                    player.weapon.fire(player.getPosition().x, player.getPosition().y);
                }
            }
        }

        // Draw
        window.clear(sf::Color::Black);
        window.draw(background);

        if (currentState == GameState::MENU)
        {
            window.draw(background);
            window.draw(message);
            window.draw(startButton);
            window.draw(buttonText);
        }
        else if (currentState == GameState::GAME)
        {
            player.update();
            window.draw(gameBackground);
            player.draw(window);
            player.updateBullets(window.getSize().y);
            

            // Check for collisions between bullets and enemies
            for (size_t i = 0; i < player.weapon.bullets.size(); i++)
            {
                for (size_t j = 0; j < enemies.size(); j++)
                {
                    if (player.weapon.bullets[i].getBounds().intersects(enemies[j]->enemySprite.getGlobalBounds()))
                    {
                        if (enemies[j]->type==0){score++;} // Increase score
                        if (enemies[j]->type==1){score+=3;}
                        if (enemies[j]->type==2){score+=5;}
                        
                        // Bullet hit the enemy, remove both bullet and enemy
                        delete enemies[j];                  // Remove the enemy
                        enemies.erase(enemies.begin() + j); // Remove enemy from vector

                        player.weapon.bullets.erase(player.weapon.bullets.begin() + i); // Remove bullet from vector
                        break;                                                          // Exit inner loop to avoid invalidating iterator after erasing an element
                    }
                }
            }
            // Collision detection for lasers
            for (size_t i = 0; i < player.weapon.lasers.size(); i++)
            {
                for (size_t j = 0; j < enemies.size(); j++)
                {
                    if (player.weapon.lasers[i].getBounds().intersects(enemies[j]->enemySprite.getGlobalBounds()))
                    {
                        if (enemies[j]->type==0){score++;} // Increase score
                        if (enemies[j]->type==1){score+=3;}
                        if (enemies[j]->type==2){score+=5;}
                        delete enemies[j];
                        enemies.erase(enemies.begin() + j);
                        player.weapon.lasers.erase(player.weapon.lasers.begin() + i);
                        break;
                    }
                }
            }

            // Enemy
            if (EnemySpawnTimer < 200)
                EnemySpawnTimer++;
            if (EnemySpawnTimer >= 200)
            {
                // Generate a random type for the next enemy
                int enemyType = rand() % 3; // 0: Enemy, 1: EnemyDiagonal, 2: EnemySmall
                // Spawn the enemy based on the random type
                if (enemyType == 0)
                {
                    enemies.push_back(new Enemy(&enemytex, 1.0f, window.getSize()));
                    // speed = 1.0f;
                }
                else if (enemyType == 1)
                {
                    enemies.push_back(new Enemy2(&enemytex2, 2.0f, window.getSize()));
                    // speed = 1.0f;
                }
                else if (enemyType == 2)
                {
                    enemies.push_back(new Enemy3(&enemytex3, 1.0f, window.getSize()));
                }
                EnemySpawnTimer = 0;
            }
            for (size_t i = 0; i < enemies.size(); i++)
            {
                enemies[i]->update();
                if (enemies[i]->isOffScreen(window.getSize().y))
                {
                    delete enemies[i];
                    enemies.erase(enemies.begin() + i);
                }
                if (enemies[i]->enemySprite.getGlobalBounds().intersects(player.GetGlobalBounds()))
                {
                    delete enemies[i];
                    enemies.erase(enemies.begin() + i);
                    
                    player.HP--;//Decrease Player's HP
                    // Check if player's HP has reached 0 and end the game if so
                    if (player.getHP() <= 0)
                    {
                        currentState = GameState::MENU;  // You can replace this with a game over screen
                        player.setHP(3); //Reset HP
                        break; // Break the loop if the game is over
                    }
                }
            }
            for (size_t i = 0; i < enemies.size(); i++)
            {
                enemies[i]->draw(window);
            }

            // score update
            score_text.setString("Score: " + std::to_string(score));
            window.draw(score_text);
        }

        window.display();
        // HP update
        HPtext.setString("HP: " + std::to_string(player.getHP()));
        window.draw(HPtext);
    }

    return 0;
}
