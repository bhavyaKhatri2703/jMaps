#include "Graph.h"
#include <vector>
#include <queue>
#include <cmath>
#include <limits>
#include <set>
#include <algorithm>
#include <numeric> // For std::iota (used in Union-Find)



using namespace std;

// Graph.cpp or similar
// Declare points array


std::vector<Edge> graph[MAX_NODES];

// Helper function: Calculate Euclidean distance
float calculateDistance(const sf::Vector2f& p1, const sf::Vector2f& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// Add an edge to the graph
void addEdge(int u, int v, const sf::Vector2f points[]) {
    float weight = calculateDistance(points[u], points[v]);
    graph[u].push_back({v, weight});
    graph[v].push_back({u, weight});
}


std::vector<int> dijkstra(int source, int target) {
    std::vector<float> dist(MAX_NODES, INF);
    std::vector<int> prev(MAX_NODES, -1);
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (u == target) break;

        for (const auto& edge : graph[u]) {
            int v = edge.destination;
            float weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<int> path;
    for (int at = target; at != -1; at = prev[at])
        path.push_back(at);
    std::reverse(path.begin(), path.end());

    if (path.size() == 1 && path[0] != source)
        path.clear(); // No path found

    return path;
}





void findPathsDFS(int current, int target, vector<int>& path, vector<bool>& visited, 
                  const vector<vector<int>>& adjacencyList, vector<vector<int>>& allPaths) {
    // Mark the current node as visited and add it to the current path
    visited[current] = true;
    path.push_back(current);

    // If we reach the target, store the path
    if (current == target) {
        allPaths.push_back(path);
    } else {
        // Continue exploring neighbors
        for (int neighbor : adjacencyList[current]) {
            if (!visited[neighbor]) {
                findPathsDFS(neighbor, target, path, visited, adjacencyList, allPaths);
            }
        }
    }

    // Backtrack: unmark the current node and remove it from the path
    visited[current] = false;
    path.pop_back();
}



// Wrapper function to find all paths
vector<vector<int>> findAllPaths(int source, int target, int numNodes, 
                                 const vector<pair<int, int>>& edges) {
    // Create an adjacency list from the edges
    vector<vector<int>> adjacencyList(numNodes);
    for (const auto& edge : edges) {
        adjacencyList[edge.first].push_back(edge.second);
        adjacencyList[edge.second].push_back(edge.first); // Undirected graph
    }

    // To store all paths
    vector<vector<int>> allPaths;
    vector<int> path;
    vector<bool> visited(numNodes, false);

    // Start DFS
    findPathsDFS(source, target, path, visited, adjacencyList, allPaths);

    return allPaths;
}









class UnionFind {
private:
    std::vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0); // Initialize parent to itself
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Helper function to calculate Euclidean distance


// Kruskal's MST Algorithm
std::vector<std::pair<int, int>> kruskalMST(const std::vector<std::pair<int, int>>& edges, 
                                            const sf::Vector2f* points, int numNodes) {
    // Create a list of edges with weights
    struct WeightedEdge {
        int src;
        int dest;
        float weight;
    };
    std::vector<WeightedEdge> weightedEdges;

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        float weight = calculateDistance(points[u], points[v]);
        weightedEdges.push_back({u, v, weight});
    }

    // Sort edges by weight
    std::sort(weightedEdges.begin(), weightedEdges.end(), [](const WeightedEdge& a, const WeightedEdge& b) {
        return a.weight < b.weight;
    });

    // Initialize Union-Find
    UnionFind uf(numNodes);
    std::vector<std::pair<int, int>> mstEdges;

    // Iterate through the sorted edges and build the MST
    for (const auto& edge : weightedEdges) {
        if (uf.find(edge.src) != uf.find(edge.dest)) {
            uf.unite(edge.src, edge.dest);
            mstEdges.push_back({edge.src, edge.dest});
            // If we already have (numNodes - 1) edges, we can stop
            if (mstEdges.size() == numNodes - 1)
                break;
        }
    }

    return mstEdges;
}


std::vector<std::vector<int>> buildAdjacencyList(const std::vector<std::pair<int, int>>& mstEdges, int numNodes) {
    std::vector<std::vector<int>> adjacencyList(numNodes);
    for (const auto& edge : mstEdges) {
        adjacencyList[edge.first].push_back(edge.second);
        adjacencyList[edge.second].push_back(edge.first);
    }
    return adjacencyList;
}


void dfs(int current, int parent, const std::vector<std::vector<int>>& adjacencyList, 
         std::vector<int>& path) {
    path.push_back(current);

    for (int neighbor : adjacencyList[current]) {
        if (neighbor != parent) {
            dfs(neighbor, current, adjacencyList, path);
        }
    }
}







std::vector<int> shortestPathWithIntermediate(
    int source, 
    int destination, 
    const std::vector<int>& intermediateLocations) 
{
    // Complete path to return
    std::vector<int> completePath;

    // Start from the source
    int current = source;

    // Append all intermediate locations and finally the destination
    std::vector<int> allStops = intermediateLocations;
    allStops.push_back(destination);

    for (int next : allStops) {
        // Get shortest path from current to next
        std::vector<int> segment = dijkstra(current, next);

        // If no path exists, return an empty vector
        if (segment.empty()) {
            return {};
        }

        // Add segment to the complete path, avoiding duplicates
        if (!completePath.empty()) {
            segment.erase(segment.begin()); // Remove duplicate start node
        }
        completePath.insert(completePath.end(), segment.begin(), segment.end());

        // Move to the next node
        current = next;
    }

    return completePath;
}


/*
class UnionFind {
private:
    std::vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        std::iota(parent.begin(), parent.end(), 0); // Initialize each node's parent as itself
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

struct edge {
    int src;
    int dest;
    float weight;

    // Constructor
    edge(int source, int destination, float w) : src(source), dest(destination), weight(w) {}
};


// Kruskal's algorithm
std::vector<std::pair<int, int>> kruskalMST(const std::vector<std::pair<int, int>> &edges, const sf::Vector2f *points, int nodeCount) {
    std::vector<edge> edgeList;

    // Create a list of edges with their weights
    for (const auto &edges : edges) {
        int src = edges.first;
        int dest = edges.second;
        float weight = calculateDistance(points[src], points[dest]);
        edgeList.push_back({src, dest, weight});
    }

    // Sort edges by weight
    std::sort(edgeList.begin(), edgeList.end(), [](const Edge &a, const Edge &b) {
        return a.weight < b.weight;
    });

    UnionFind uf(nodeCount);
    std::vector<std::pair<int, int>> mstEdges;

    // Iterate over sorted edges and add them to the MST if they don't form a cycle
    for (const auto &edge : edgeList) {
        if (uf.find(edge.src) != uf.find(edge.dest)) {
            uf.unite(edge.src, edge.dest);
            mstEdges.push_back({edge.src, edge.dest});

            // If MST contains (nodeCount - 1) edges, stop
            if (mstEdges.size() == nodeCount - 1)
                break;
        }
    }

    return mstEdges;
}


*/

/* vector<pair<int, int>> primMST(const sf::Vector2f points[], int numNodes) {
    vector<bool> inMST(numNodes, false);
    vector<float> minEdgeWeight(numNodes, numeric_limits<float>::max());
    vector<int> parent(numNodes, -1);
    vector<pair<int, int>> mstEdges;

    // Priority queue to pick the minimum weight edge
   using Edge = std::pair<float, int>; // {weight, node}
std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;


    // Start from node 0
    pq.emplace(0.0f, 0);
    minEdgeWeight[0] = 0.0f;

    while (!pq.empty()) {
        int currentNode = pq.top().second;
        pq.pop();

        // Skip if already in MST
        if (inMST[currentNode]) continue;
        inMST[currentNode] = true;

        // Add the edge to the MST
        if (parent[currentNode] != -1) {
            mstEdges.emplace_back(parent[currentNode], currentNode);
        }

        // Check all nodes to update edge weights
        for (int i = 0; i < numNodes; i++) {
            if (!inMST[i]) {
                float weight = calculateDistance(points[currentNode], points[i]);
                if (weight < minEdgeWeight[i]) {
                    minEdgeWeight[i] = weight;
                    parent[i] = currentNode;
                    pq.emplace(weight, i);
                }
            }
        }
    }

    return mstEdges;
} */
