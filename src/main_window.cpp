#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Bullet.h" // Include Bullet header
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

    Player player;
    if (!player.loadTexture("player.png"))
    {
        std::cerr << "Error loading player sprite!" << std::endl;
        return -1;
    }
    player.setPosition(100, 500);
    player.scale(0.2f, 0.2f);

    std::vector<Bullet> bullets; // Vector to store bullets
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

            // Shooting bullets when spacebar is pressed
            if (currentState == GameState::GAME && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                Bullet bullet(player.getPosition().x + player.getWidth() / 2 - bullet.getWidth() / 2, player.getPosition().y);
                // Create the bullet at the player's location
                bullets.push_back(bullet); // Add the bullet to the vector
            }
        }

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
        }

        window.display();
    }

    return 0;
}
