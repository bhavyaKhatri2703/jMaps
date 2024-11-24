#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Rendering.h"
#include "Constants.h"
#include <iostream>
#include <vector>
#include <SFML/System/Clock.hpp> // For sf::Clock

using namespace std;

enum Algorithm
{
    DIJKSTRA,
    ALL_PATHS,
    MST,
    INTERMEDIATES
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1370, 768), "Campus Map");

    int currentPathIndex = 0; // Start with the first path
    sf::Clock pathTimer;      // Timer to track elapsed time
    float displayInterval = 2.0f;
    std::vector<sf::Color> colorPalette;

    // Initialization
    sf::CircleShape dot(10.0f);
    dot.setFillColor(sf::Color(0, 255, 0, 128));

    sf::CircleShape movingCircle(8.0f);
    movingCircle.setFillColor(sf::Color::Yellow);

    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    // Populate graph edges
    for (const auto &edge : edges)
    {
        addEdge(edge.first, edge.second, points);
    }

    // Variables for user choice and results
    Algorithm selectedAlgorithm = DIJKSTRA;
    std::vector<std::vector<int>> allPaths;
    std::vector<int> dijkstraPath;
    std::vector<std::pair<int, int>> mstEdges;
    std::vector<int> intermediatePath;

    int animationIndex = -1;           // Current index in the path
    float animationProgress = 0.0f;    // Progress along the current edge (0.0 - 1.0)
    const float animationSpeed = 1.0f; // Speed of the animation
    sf::Clock animationClock;

    int sourceNode = -1, targetNode = -1;
    vector<int> intermidiate;
    bool algorithmChosen = false;

    // Render loop (initial render without waiting for user input)
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (animationIndex >= 0)
{
    const std::vector<int> &currentPath = 
        (selectedAlgorithm == DIJKSTRA) ? dijkstraPath : intermediatePath;

    if (animationIndex < static_cast<int>(currentPath.size()) - 1)
    {
        sf::Vector2f start = points[currentPath[animationIndex]];
        sf::Vector2f end = points[currentPath[animationIndex + 1]];

        // Update progress
        animationProgress += animationSpeed * animationClock.restart().asSeconds();

        if (animationProgress >= 1.0f)
        {
            // Move to the next segment
            animationIndex++;
            animationProgress = 0.0f;

            // If the animation is complete, stop
            if (animationIndex >= static_cast<int>(currentPath.size()) - 1)
            {
                animationIndex = -1; // Animation complete
            }
        }
        else
        {
            // Interpolate position
            movingCircle.setPosition(
                start.x + animationProgress * (end.x - start.x),
                start.y + animationProgress * (end.y - start.y));
        }
    }
}


        // Clear and render
        window.clear();

        // Draw the nodes and edges initially
        drawNodes(window, points, MAX_NODES, dot, font);
        drawEdges(window, edges, points);

        // Render computed paths if an algorithm has been chosen
        if (algorithmChosen)
        {
            switch (selectedAlgorithm)
            {
            case DIJKSTRA:
                if (!dijkstraPath.empty())
                {
                    drawPaths(window, std::vector<std::vector<int>>{dijkstraPath}, points, std::vector<sf::Color>{sf::Color::Red});
                    if (animationIndex >= 0)
                    {
                        window.draw(movingCircle);
                    }
                }
                break;

            case ALL_PATHS:
                if (!allPaths.empty())
                {
                    // Check if enough time has passed to show the next path
                    if (pathTimer.getElapsedTime().asSeconds() > displayInterval)
                    {
                        currentPathIndex++;  // Move to the next path
                        pathTimer.restart(); // Reset the timer

                        // If the current index exceeds available paths, loop back to the first path
                        if (currentPathIndex >= allPaths.size())
                            currentPathIndex = 0;
                    }

                    // Clear the window before drawing
                    window.clear();

                    // Redraw static elements (nodes and edges)
                    drawNodes(window, points, MAX_NODES, dot, font);
                    drawEdges(window, edges, points);

                    // Draw the current path
                    drawPaths(window, std::vector<std::vector<int>>{allPaths[currentPathIndex]}, points, std::vector<sf::Color>{colorPalette[currentPathIndex]});

                    // Display the updated frame
                    window.display();
                }

                break;

            case MST:

                if (!mstEdges.empty())
                {
                    // Draw each edge in the MST
                    sf::VertexArray lines(sf::Lines, 2);
                    for (const auto &edge : mstEdges)
                    {
                        lines[0].position = points[edge.first];
                        lines[1].position = points[edge.second];
                        lines[0].color = sf::Color::Red;
                        lines[1].color = sf::Color::Red;
                        window.draw(lines);
                    }
                }
                break;

            case INTERMEDIATES:
                drawPaths(window, std::vector<std::vector<int>>{intermediatePath}, points, std::vector<sf::Color>{sf::Color::Red});
                  if (animationIndex >= 0)
                    {
                        window.draw(movingCircle);
                    }
                break;
            }
        }

        window.display();

        // Allow user input after initial render
        if (!algorithmChosen)
        {
            // Interactive menu
            std::cout << "Welcome to the Campus Map!" << std::endl;
            std::cout << "Choose an algorithm:" << std::endl;
            std::cout << "1. Dijkstra's Shortest Path" << std::endl;
            std::cout << "2. All Paths" << std::endl;
            std::cout << "3. Minimum Spanning Tree" << std::endl;
            std::cout << "4. Intermediates Locations" << std::endl;
            int choice;
            std::cin >> choice;

            switch (choice)
            {
            case 1:
                selectedAlgorithm = DIJKSTRA;
                break;
            case 2:
                selectedAlgorithm = ALL_PATHS;
                break;
            case 3:
                selectedAlgorithm = MST;
                break;
            case 4:
                selectedAlgorithm = INTERMEDIATES;
                break;
            default:
                std::cout << "Invalid choice. Defaulting to Dijkstra's algorithm." << std::endl;
                selectedAlgorithm = DIJKSTRA;
                break;
            }

            if (selectedAlgorithm == DIJKSTRA || selectedAlgorithm == ALL_PATHS)
            {
                std::cout << "\nAvailable Nodes:\n";
                for (const auto &entry : nodeNames)
                {
                    std::cout << entry.first << ": " << entry.second << std::endl;
                }

                std::cout << "\nEnter source node (0-" << MAX_NODES - 1 << "): ";
                std::cin >> sourceNode;
                std::cout << "Enter target node (0-" << MAX_NODES - 1 << "): ";
                std::cin >> targetNode;

                if (sourceNode < 0 || sourceNode >= MAX_NODES || targetNode < 0 || targetNode >= MAX_NODES)
                {
                    std::cerr << "Invalid source or target node. Exiting..." << std::endl;
                    return -1;
                }
            }

            if (selectedAlgorithm == INTERMEDIATES)
            {
                std::cout << "\nAvailable Nodes:\n";
                for (const auto &entry : nodeNames)
                {
                    std::cout << entry.first << ": " << entry.second << std::endl;
                }

                std::cout << "\nEnter source node (0-" << MAX_NODES - 1 << "): ";
                std::cin >> sourceNode;
                std::cout << "Enter target node (0-" << MAX_NODES - 1 << "): ";
                std::cin >> targetNode;
                if (sourceNode < 0 || sourceNode >= MAX_NODES || targetNode < 0 || targetNode >= MAX_NODES)
                {
                    std::cerr << "Invalid source or target node. Exiting..." << std::endl;
                    return -1;
                }
                while (1)
                {
                    int n;
                    cout << "Enter Intermediate Location (-1 for exit): ";
                    cin >> n;
                    if (n == -1)
                    {
                        break;
                    }
                    else
                    {
                        intermidiate.push_back(n);
                    }
                }
            }

            // Path computations (done after user input)
            switch (selectedAlgorithm)
            {
            case DIJKSTRA:
                dijkstraPath = dijkstra(sourceNode, targetNode);
                if (!dijkstraPath.empty())
                {
                    std::cout << "Computed Dijkstra Path: ";
                    for (int node : dijkstraPath)
                        std::cout << node << " ";
                    std::cout << std::endl;

                    animationIndex = 0; // Start at the first segment
                    animationProgress = 0.0f;
                    movingCircle.setPosition(points[dijkstraPath[0]]); // Set to the starting position
                    animationClock.restart();
                }
                else
                {
                    std::cerr << "No path exists between " << sourceNode << " and " << targetNode << std::endl;
                }
                break;

            case ALL_PATHS:
                allPaths = findAllPaths(sourceNode, targetNode, MAX_NODES, edges);
                if (!allPaths.empty())
                {
                    std::cout << "Computed All Paths:" << std::endl;
                    colorPalette = generateColorPalette(allPaths.size());
                    for (const auto &path : allPaths)
                    {
                        for (int node : path)
                            std::cout << node << " ";
                        std::cout << std::endl;
                    }
                }
                else
                {
                    std::cerr << "No paths exist between " << sourceNode << " and " << targetNode << std::endl;
                }
                break;

            case MST:
                mstEdges = kruskalMST(edges, points, MAX_NODES);
                std::cout << "Computed MST Edges:" << std::endl;
                for (const auto &edge : mstEdges)
                {
                    std::cout << edge.first << " - " << edge.second << std::endl;
                }
                break;

            case INTERMEDIATES:
                intermediatePath = shortestPathWithIntermediate(sourceNode, targetNode, intermidiate);
                if (!intermediatePath.empty())
                {
                    std::cout << "Computed Dijkstra Path: ";
                    for (int node : intermediatePath)
                        std::cout << node << " ";
                    std::cout << std::endl;

                           animationIndex = 0; // Start at the first segment
                    animationProgress = 0.0f;
                    movingCircle.setPosition(points[intermediatePath[0]]); // Set to the starting position
                    animationClock.restart();
                }
                else
                {
                    std::cerr << "No path exists between " << sourceNode << " and " << targetNode << std::endl;
                }
                break;
            }

            // Mark that the algorithm has been chosen and computed
            algorithmChosen = true;
        }
    }

    return 0;
}