//
// Created by Tereh on 19.04.2024.
//

#ifndef PERSISTENTTREE_MAPALGO_H
#define PERSISTENTTREE_MAPALGO_H
#include <vector>
#include <algorithm>
#include "Rectangle.h"

class MAPAlgo {
public:

    void build(std::vector<Rectangle>& rectangles);
    int find_point(const Point& point);

protected:
    std::vector<long> xCoords;
    std::vector<long> yCoords;
    std::vector<std::vector<int>> heightMap;
};


#endif //PERSISTENTTREE_MAPALGO_H
