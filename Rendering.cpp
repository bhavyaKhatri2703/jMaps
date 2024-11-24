#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Rendering.h"
#include "Constants.h"
#include <iostream>
#include <vector>
#include <SFML/System/Clock.hpp> 
#include<math.h>

sf::Font font;

void drawNodes(sf::RenderWindow& window, const sf::Vector2f points[], int numNodes, sf::CircleShape& dot, sf::Font& font) {
    for (int i = 0; i < numNodes; i++) {
        // Draw the node as a circle
        dot.setPosition(points[i].x - dot.getRadius(), points[i].y - dot.getRadius());
        window.draw(dot);

        // Create the text label for the node
        sf::Text label;
        label.setFont(font);
        label.setCharacterSize(14); // Set a readable size
        label.setFillColor(sf::Color::White); // Text color
        label.setString(std::to_string(i)); // Display index and name
        label.setPosition(points[i].x + 15, points[i].y - 10); // Position the text near the node
        window.draw(label);
    }
}

void drawEdges(sf::RenderWindow& window, const std::vector<std::pair<int, int>>& edges, const sf::Vector2f points[]) {
    sf::VertexArray lines(sf::Lines, 2);
    for (const auto& edge : edges) {
        lines[0].position = points[edge.first];
        lines[1].position = points[edge.second];
        lines[0].color = sf::Color::White;
        lines[1].color = sf::Color::White;
        window.draw(lines);
    }
}

void drawPaths(sf::RenderWindow& window, const std::vector<std::vector<int>>& paths, const sf::Vector2f points[], const std::vector<sf::Color>& colors) {
    for (size_t i = 0; i < paths.size(); ++i) {
        sf::VertexArray pathLines(sf::Lines, 2);
        for (size_t j = 1; j < paths[i].size(); ++j) {
            pathLines[0].position = points[paths[i][j - 1]];
            pathLines[1].position = points[paths[i][j]];
            pathLines[0].color = colors[i];
            pathLines[1].color = colors[i];
            window.draw(pathLines);
        }
    }
}

std::vector<sf::Color> generateColorPalette(int numColors) {
    std::vector<sf::Color> palette;
    for (int i = 0; i < numColors; ++i) {
        int red = (i * 50) % 255;
        int green = (i * 80) % 255;
        int blue = (i * 120) % 255;
        palette.push_back(sf::Color(red, green, blue));
    }
    return palette;
}


void drawMSTEdges(sf::RenderWindow& window, const std::vector<std::pair<int, int>>& mstEdges, const sf::Vector2f* points, sf::Color color, float thickness) {
    for (const auto& edge : mstEdges) {
        int u = edge.first;
        int v = edge.second;

        sf::Vector2f point1 = points[u];
        sf::Vector2f point2 = points[v];

        drawLine(window, point1, point2, color, thickness);
    }
}

void drawLine(sf::RenderWindow& window, const sf::Vector2f& point1, const sf::Vector2f& point2, sf::Color color, float thickness) {
    sf::Vector2f direction = point2 - point1;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    sf::RectangleShape line(sf::Vector2f(length, thickness));
    line.setPosition(point1);

    float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159265f;
    line.setRotation(angle);

    line.setFillColor(color);
    window.draw(line);
}



void animatePath(sf::RenderWindow &window, const std::vector<int> &path, 
                 const sf::Vector2f points[30], sf::CircleShape &circle,
                 float speed)
{
    if (path.empty())
    {
        std::cout << "Path is empty! No animation to show." << std::endl;
        return;
    }

    sf::Clock clock;         // Clock to handle animation timing
    float progress = 0.0f;   // Progress along the current segment
    int segmentIndex = 0;    // Current segment in the path

    // Set the circle's initial position to the first node
    circle.setPosition(points[path[0]]);

    while (segmentIndex < static_cast<int>(path.size()) - 1)
    {
        // Clear the window
        window.clear();

        // Update the progress
        progress += speed * clock.restart().asSeconds();

        if (progress >= 1.0f)
        {
            // Move to the next segment
            progress = 0.0f;
            segmentIndex++;
            if (segmentIndex >= static_cast<int>(path.size()) - 1)
                break; // Animation complete
        }

        // Interpolate position for the current segment
        sf::Vector2f start = points[path[segmentIndex]];
        sf::Vector2f end = points[path[segmentIndex + 1]];
        circle.setPosition(
            start.x + progress * (end.x - start.x),
            start.y + progress * (end.y - start.y)
        );

        // Draw static elements (e.g., nodes and edges)
        drawNodes(window, points, 30, circle, font); // Pass fixed-size array with size 30
        drawEdges(window, edges, points);

        // Draw the animated circle
        window.draw(circle);

        // Display the updated frame
        window.display();
    }

    // Final position of the circle at the last node
    circle.setPosition(points[path.back()]);
    window.draw(circle);
    window.display();
}



