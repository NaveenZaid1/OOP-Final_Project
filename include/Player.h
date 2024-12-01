#ifndef PLAYER_H
#define PLAYER_H

#include "Weapon.h"
#include <SFML/Graphics.hpp>

class Player
{
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    Weapon weapon; // Composite: Player owns a Weapon

public:
    int HP=HPMax;
    int HPMax=10; 
    bool loadTexture(const std::string &filepath); // Load the player texture
    void setPosition(float x, float y);            // Set player position
    void scale(float scaleX, float scaleY);        // Scale the player sprite
    void update();                                 // Update player position
    void stayWithinBounds();                       // Keep player within window bounds
    void fire();                                   // Delegate firing to Weapon
    void updateBullets(float windowHeight);        // Update bullets through Weapon
    void draw(sf::RenderWindow &window);           // Draw player and bullets
    sf::Vector2f getPosition() const;

    // Add this method to get the width of the player sprite
    float getWidth() const;

    //added
    sf::FloatRect GetGlobalBounds() const;

};

#endif
