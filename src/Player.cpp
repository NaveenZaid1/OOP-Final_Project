#include "include\Player.h"

bool Player::loadTexture(const std::string &filepath)
{
    if (!playerTexture.loadFromFile(filepath))
    {
        return false;
    }
    playerSprite.setTexture(playerTexture);
    return true;
}

void Player::setPosition(float x, float y)
{
    playerSprite.setPosition(x, y);
}

void Player::scale(float scaleX, float scaleY)
{
    playerSprite.setScale(scaleX, scaleY);
}

void Player::update()
{
    float moveSpeed = 1.05f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        playerSprite.move(-moveSpeed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        playerSprite.move(moveSpeed, 0);
    }
    stayWithinBounds();
}

void Player::stayWithinBounds()
{
    if (playerSprite.getPosition().x < 0)
    {
        playerSprite.setPosition(0, playerSprite.getPosition().y);
    }
    if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width > 800)
    {
        playerSprite.setPosition(800 - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
    }
}

void Player::fire()
{
    weapon.fire(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2,
                playerSprite.getPosition().y);
}

void Player::updateBullets(float windowHeight)
{
    weapon.update(windowHeight);
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(playerSprite);
    weapon.draw(window);
}

sf::Vector2f Player::getPosition() const
{
    return playerSprite.getPosition(); 
}

float Player::getWidth() const
{
    return playerSprite.getGlobalBounds().width; // Get width of player sprite
}

sf::FloatRect Player::GetGlobalBounds() const
{
    return playerSprite.getGlobalBounds();
}
