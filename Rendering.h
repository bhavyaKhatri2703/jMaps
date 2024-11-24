#ifndef RENDERING_H
#define RENDERING_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

// Function prototypes
void drawNodes(sf::RenderWindow& window, const sf::Vector2f points[], int numNodes, sf::CircleShape& dot, sf::Font& font);
void drawEdges(sf::RenderWindow& window, const std::vector<std::pair<int, int>>& edges, const sf::Vector2f points[]);
void drawPaths(sf::RenderWindow& window, const std::vector<std::vector<int>>& paths, const sf::Vector2f points[], const std::vector<sf::Color>& colors);
void drawMSTEdges(sf::RenderWindow& window, const std::vector<std::pair<int, int>>& mstEdges, const sf::Vector2f* points, sf::Color color, float thickness);
void drawLine(sf::RenderWindow& window, const sf::Vector2f& point1, const sf::Vector2f& point2, sf::Color color, float thickness);
std::vector<sf::Color> generateColorPalette(int numColors);
void animatePath(sf::RenderWindow &window, const std::vector<int> &path, 
                 const sf::Vector2f points[30], sf::CircleShape &circle,
                 float speed);
#endif // RENDERING_H
