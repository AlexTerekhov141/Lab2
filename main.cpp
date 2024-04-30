#include <iostream>
#include <vector>
#include "persistentTree.h"
#include "Rectangle.h"
#include "MAPAlgo.h"
#include "constants.h"
#include <chrono>

typedef  std::chrono::high_resolution_clock Clock;


void bruteforce(std::vector<Rectangle> Rectangles, Point point){
    int count = 0;
    for(int i = 0; i < Rectangles.size(); i++){
        if(Rectangles[i].containsPoint(point)){
            count++;
        }
    }
}
std::vector<Point> generatepoints(int numberOfPoints, int p_x,int p_y) {
    std::vector<Point> points;
    int p = 31;
    for (int i = 0; i < numberOfPoints; ++i) {
        Point newPoint;
        newPoint.x = (p_x * i) ^ p % (20 * numberOfPoints);
        newPoint.y = (p_y * i) ^ p % (20 * numberOfPoints);
        points.push_back(newPoint);
    }
    return points;
}

int main() {
    int rects;
    std::cin >> rects;
    std::vector<Rectangle> Rectangles(rects);
    int n = Rectangles.size();
    int points_number = rects*10;
    std::vector<Point> Points = generatepoints(points_number,p_x,p_y);
    int a,b,c,d;
    for(int i = 0; i < Rectangles.size(); i++){
        int x1 = 10 * i;
        int y1 = 10 * i;
        int x2 = 10 * (2 * n - i);
        int y2 = 10 * (2 * n - i);
        Point first(x1,y1);
        Point second(x2,y2);
        Rectangles[i].setLeftBottom(first);
        Rectangles[i].setRightTop(second);

    }
    double duration_brute = 0;
    double duration_map = 0;
    double duration_tree = 0;
    double duration_map_build = 0;
    double duration_tree_build = 0;
    auto start_brute = Clock::now();
    for(int i = 0; i < Points.size(); i++){
        bruteforce(Rectangles, Points[i]);
    }
    auto end_brute = Clock::now();
    duration_brute += std::chrono::duration_cast<std::chrono::microseconds>(end_brute - start_brute).count();
    std::cout << "brute time: " << duration_brute << " micro_seconds" << std::endl;

    auto start_map_build = Clock::now();
    MAPAlgo m;
    m.build(Rectangles);
    auto end_map_build = Clock::now();
    duration_map_build += std::chrono::duration_cast<std::chrono::microseconds>(end_map_build - start_map_build).count();
    auto start_map = Clock::now();
    for(int i = 0; i < Points.size(); i++){
        int count = m.find_point(Points[i]);
    }
    auto end_map = Clock::now();
    duration_map += std::chrono::duration_cast<std::chrono::microseconds>(end_map - start_map).count();
    std::cout << "map build time: " << duration_map_build << " micro_seconds" << std::endl;
    std::cout << "map find time: " << duration_map << " micro_seconds" << std::endl;
    auto start_tree_build = Clock::now();
    PST tree;
    tree.build(Rectangles);
    auto end_tree_build = Clock::now();
    duration_tree_build += std::chrono::duration_cast<std::chrono::microseconds>(end_tree_build - start_tree_build).count();
    auto start_tree = Clock::now();
    for(int i = 0; i < Points.size(); i++){
        int count = tree.find_point(Points[i]);
    }
    auto  end_tree = Clock ::now();
    duration_tree += std::chrono::duration_cast<std::chrono::microseconds>(end_tree - start_tree).count();
    std::cout << "tree build time: " << duration_tree_build << " micro_seconds" << std::endl;
    std::cout << "tree find time: " << duration_tree << " micro_seconds" << std::endl;
}
