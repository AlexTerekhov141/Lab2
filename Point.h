//
// Created by Tereh on 19.04.2024.
//

#ifndef PERSISTENTTREE_POINT_H
#define PERSISTENTTREE_POINT_H


class Point {
public:
    int x;
    int y;
    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
};


#endif //PERSISTENTTREE_POINT_H
