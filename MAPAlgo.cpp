//
// Created by Tereh on 19.04.2024.
//

#include "MAPAlgo.h"





void MAPAlgo::build(std::vector<Rectangle>& rectangles) {
    for (const auto& rectangle : rectangles) {
        xCoords.push_back(rectangle.leftBottom.x);
        xCoords.push_back(rectangle.RightTop.x);
        yCoords.push_back(rectangle.leftBottom.y);
        yCoords.push_back(rectangle.RightTop.y);
    }

    std::sort(xCoords.begin(), xCoords.end());
    xCoords.erase(std::unique(xCoords.begin(), xCoords.end()), xCoords.end());

    std::sort(yCoords.begin(), yCoords.end());
    yCoords.erase(std::unique(yCoords.begin(), yCoords.end()), yCoords.end());

    heightMap = std::vector<std::vector<int>>(xCoords.size(), std::vector<int>(yCoords.size(), 0));

    for (const auto& rectangle : rectangles) {
        int xLeft = std::lower_bound(xCoords.begin(), xCoords.end(), rectangle.leftBottom.x) - xCoords.begin();
        int xRight = std::lower_bound(xCoords.begin(), xCoords.end(), rectangle.RightTop.x) - xCoords.begin();
        int yBottom = std::lower_bound(yCoords.begin(), yCoords.end(), rectangle.leftBottom.y) - yCoords.begin();
        int yTop = std::lower_bound(yCoords.begin(), yCoords.end(), rectangle.RightTop.y) - yCoords.begin();

        for (int x = xLeft; x <= xRight; x++) {
            for (int y = yBottom; y <= yTop; y++) {
                heightMap[x][y]++;
            }
        }
    }
}

int MAPAlgo::find_point(const Point& point) {
    if (point.x < xCoords[0] || point.y < yCoords[0]) {
        return 0;
    }

    int xIndex = std::lower_bound(xCoords.begin(), xCoords.end(), point.x) - xCoords.begin() - 1;
    int yIndex = std::lower_bound(yCoords.begin(), yCoords.end(), point.y) - yCoords.begin() - 1;

    return heightMap[xIndex][yIndex];
}

