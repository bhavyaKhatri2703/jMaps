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
   {0, "Gate 1 Exit"},
   {1, "Gate 1"},
   {2, "Turn 1"},
   {3, "Turn 2"},
   {4, "Lift No. 1"},
   {5, "Lift No. 2"},
   {6, "OAT"},
   {7, "ABB1"},  
   {8, "ABB1"},  
   {9, "Turn 3"},
   {10, "Mandir"},
   {11, "Gate 2"},
   {12, "Green Gate 1"},
   {13, "Basketball Ground"},
   {14, "Sarojni"},
   {15, "Mandir"},
   {16, "Mandir Gate"},
   {17, "Annapurna"},
   {18, "A2Z"},
   {19, "H3 / Dispensary"},
   {20, "H4 / H5"},
   {21, "Green Gate 2"},
   {22, "Turn 3"},
   {23, "Turn 4"},
   {24, "Laundry"},
   {25, "Turn 5"},
   {26, "Gate 3"},
   {27, "Gate 3 Exit"},
   {28, "Jbs"},
   {29, "Cafe"}
};
