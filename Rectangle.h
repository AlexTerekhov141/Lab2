//
// Created by Tereh on 19.04.2024.
//

#ifndef PERSISTENTTREE_RECTANGLE_H
#define PERSISTENTTREE_RECTANGLE_H
#include <iostream>
#include "Point.h"

class Rectangle{
public:

    const Point &getLeftBottom() const {
        return leftBottom;
    }

    void setLeftBottom(const Point &leftBottom) {
        Rectangle::leftBottom = leftBottom;
    }

    const Point &getRightTop() const {
        return RightTop;
    }

    void setRightTop(const Point &rightTop) {
        RightTop = rightTop;
    }
    void showData(){
        std::cout << leftBottom.x << " " << leftBottom.y << " " << RightTop.x << " " << RightTop.y << std::endl;
    }

    bool containsPoint(Point a) const {
        return (leftBottom.x <= a.x && a.x < RightTop.x && leftBottom.y <= a.y && a.y < RightTop.y);
    }

    Point leftBottom;
    Point RightTop;
};


#endif //PERSISTENTTREE_RECTANGLE_H
