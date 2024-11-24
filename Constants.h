#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

// Use the same size for points (should match MAX_NODES or the fixed size you want)
extern const sf::Vector2f points[30];  // Consistent size with Graph.h

extern const std::vector<std::pair<int, int>> edges;
extern const std::map<int, std::string> nodeNames;

#endif // CONSTANTS_H
