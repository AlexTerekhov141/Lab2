#include <algorithm>
#include <memory>
#include <vector>

#include "Rectangle.h"
#include "Point.h"

class Node {
public:
    Node *left = nullptr, *right = nullptr;
    long long sum = 0;

};

class PST {
private:
    std::vector<long long> compressed_xs;
    std::vector<long long> compressed_ys;
    std::vector<Node*> roots;
    std::vector<long long> x_idxs;

    static int find_pos(const std::vector<long long>& items, long long target) {
        return std::lower_bound(items.begin(), items.end(), target) - items.begin();
    }

    static int find_upper_pos(const std::vector<long long>& items, long long target) {
        return std::upper_bound(items.begin(), items.end(), target) - items.begin();
    }

    Node *
    persistence(Node *root, long long int left, long long int right, long long int range_start, long long int range_end,
                long long int value);

    long long int get_total_sum(Node *root, long long int left, long long int right, long long int target_idx);

    void make_compressed_coords_from_rectangles(const std::vector<Rectangle> &rectangles);

public:
    void build(const std::vector<Rectangle> &rectangles);

    long long int find_point(const Point &point);
};
