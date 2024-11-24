#include "Sprites.h"
#include <iostream>

sf::Sprite createSprite(const std::string& filePath, float x, float y, float targetWidth, float targetHeight) {
    sf::Texture* texture = new sf::Texture();
    if (!texture->loadFromFile(filePath)) {
        std::cerr << "Error loading " << filePath << std::endl;
        exit(-1);
    }

    sf::Sprite sprite;
    sprite.setTexture(*texture);

    sf::Vector2u textureSize = texture->getSize();
    float scaleX = targetWidth / textureSize.x;
    float scaleY = targetHeight / textureSize.y;

    sprite.setScale(scaleX, scaleY);
    sprite.setPosition(x, y);

    return sprite;
}
