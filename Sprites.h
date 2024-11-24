#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

sf::Sprite createSprite(const std::string& filePath, float x, float y, float targetWidth, float targetHeight);

#endif // SPRITEMANAGER_H
