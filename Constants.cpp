#include "Constants.h"

// Define the points array and initialize it with your data
const sf::Vector2f points[30] = {
    {80, 40}, {80, 90}, {220, 90}, {360, 90}, {220, 200}, {220, 360},
    {290, 200}, {360, 200}, {360, 360}, {1200, 380}, {540, 380}, {540, 90},        
    {80, 600}, {280, 600}, {440, 600}, {500, 600}, {540, 600}, {700, 600},
    {870, 600}, {950, 600}, {1110, 600}, {1200, 600}, {80, 720}, {280, 720},
    {580, 720}, {870, 720}, {1200, 720}, {1240, 720}, {220, 600}, {220, 280}
};

// Define the edges array and initialize it with your data
const std::vector<std::pair<int, int>> edges = {
    {0, 1}, {1, 12}, {12, 22}, {22, 23}, {23, 24}, {24, 25}, {25, 26}, {26, 27}, 
    {26, 21}, {21, 20}, {20, 19}, {19, 18}, {18, 17}, {17, 16}, {16, 15}, 
    {15, 14}, {14, 13}, {13, 28}, {28, 12}, {28, 5}, {5, 29}, {29, 4}, 
    {4, 2}, {4, 6}, {6, 7}, {7, 3}, {7, 8}, {8, 5}, {21, 9}, {9, 10}, 
    {10, 11}, {11, 3}, {3, 2}, {2, 1}, {16, 10}, {13, 23}, {25, 18}
};

// Define the node names map
const std::map<int, std::string> nodeNames = {
   {0, "gate 1 out"},
   {1, "gate 1 cell"},
   {2, "oat backside left"},
   {3, "oat back right"},
   {4, "lift1"},
   {5, "lift2"},
   {6, "oat"},
   {7, "unknown (7)"},  
   {8, "unknown (8)"},  
   {9, "h3 ke piche"},
   {10, "mandir gully"},
   {11, "gate 2"},
   {12, "green gate1"},
   {13, "jbs top r"},
   {14, "saraswati to abb sarojni"},
   {15, "mandir"},
   {16, "mandir gate"},
   {17, "mess"},
   {18, "kuch to hai"},
   {19, "h3"},
   {20, "h4"},
   {21, "greengate2"},
   {22, "jbs leftbott corner"},
   {23, "jbs rightmost"},
   {24, "laundry"},
   {25, "h3 se laundry"},
   {26, "gate 3"},
   {27, "gate 3 out"},
   {28, "jbs"},
   {29, "cafe"}
};
