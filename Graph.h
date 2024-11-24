#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <SFML/Graphics.hpp>

#define MAX_NODES 30
#define INF std::numeric_limits<float>::infinity()

struct Edge
{
    int destination;
    float weight;
};
extern const sf::Vector2f points[MAX_NODES]; // Same size as in Constants.h
extern const std::vector<std::pair<int, int>> edges;

void addEdge(int u, int v, const sf::Vector2f points[]);
std::vector<int> dijkstra(int source, int target);

std::vector<std::vector<int>> findAllPaths(int source, int target, int numNodes, const std::vector<std::pair<int, int>> &edges);

std::vector<std::pair<int, int>> kruskalMST(const std::vector<std::pair<int, int>> &edges,
                                            const sf::Vector2f *points, int numNodes);
void dfs(int current, int parent, const std::vector<std::vector<int>> &adjacencyList,
         std::vector<int> &path);
std::vector<std::vector<int>> buildAdjacencyList(const std::vector<std::pair<int, int>> &mstEdges, int numNodes);


std::vector<std::vector<float>> computeAllPairsShortestPaths(
    int numNodes,
    const std::vector<std::pair<int, int>>& edges,
    const sf::Vector2f* points);


    std::vector<int> shortestPathVisitingAllNodes(
    int source,
    int destination,
    const std::vector<int>& intermediateLocations,
    const std::vector<std::pair<int, int>>& edges,
    const sf::Vector2f* points,
    int numNodes);


    std::vector<int> shortestPathWithIntermediate(
    int source, 
    int destination, 
    const std::vector<int>& intermediateLocations) ;

#endif
