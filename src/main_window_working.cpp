#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h" // Include Bullet header
#include "Enemy.h"
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
    if (!font.loadFromFile("VGA New.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png"))
    {
        std::cerr << "Error loading background image!" << std::endl;
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    sf::Texture gameBackgroundTexture;
    if (!gameBackgroundTexture.loadFromFile("game_background.png"))
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

    // Player setup
    int score = 0;
    Player player;
    if (!player.loadTexture("player.png"))
    {
        std::cerr << "Error loading player sprite!" << std::endl;
        return -1;
    }
    player.setPosition(100, 500);
    player.scale(0.2f, 0.2f);

    // Bullet setup
    std::vector<Bullet> bullets; // Vector to store bullets

    // Enemy setup
    sf::Texture enemytex;
    enemytex.loadFromFile("file.png");
    sf::Texture enemytex2;
    enemytex2.loadFromFile("EnemyBig.png");
    sf::Texture enemytex3;
    enemytex3.loadFromFile("Enemy3.png");
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
            if (currentState == GameState::GAME && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                Bullet bullet(player.getPosition().x + player.getWidth() / 2 - bullet.getWidth() / 2, player.getPosition().y);
                // Create the bullet at the player's location
                bullets.push_back(bullet); // Add the bullet to the vector
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

            // Update and draw all bullets
            for (auto &bullet : bullets)
            {
                bullet.update();     // Move the bullet
                bullet.draw(window); // Draw the bullet
            }
            // //collsion wuth bulletr
            // for (size_t k=0; k<enemies.size(); k++){
            //     if (player.weapon.bullets)
            //      score++

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
                    enemies.push_back(new EnemyDiagonal(&enemytex3, 2.0f, window.getSize()));
                    // speed = 1.0f;
                }
                else if (enemyType == 2)
                {
                    enemies.push_back(new EnemySmall(&enemytex2, 1.0f, window.getSize()));
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
                    player.HP--;
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
    }

    return 0;
}