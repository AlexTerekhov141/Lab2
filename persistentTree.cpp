#include "persistentTree.h"

void PST::make_compressed_coords_from_rectangles(const std::vector<Rectangle>& rectangles) {
    for (const auto& rect : rectangles) {
        this->compressed_xs.push_back(rect.leftBottom.x);
        this->compressed_xs.push_back(rect.RightTop.x);
        this->compressed_xs.push_back(rect.RightTop.x + 1);
    }

    std::sort(this->compressed_xs.begin(), this->compressed_xs.end());
    this->compressed_xs.erase(std::unique(this->compressed_xs.begin(), this->compressed_xs.end()), this->compressed_xs.end());
    this->compressed_xs.shrink_to_fit();

    for (const auto& rect : rectangles) {
        this->compressed_ys.push_back(rect.leftBottom.y);
        this->compressed_ys.push_back(rect.RightTop.y);
        this->compressed_ys.push_back(rect.RightTop.y + 1);
    }

    std::sort(this->compressed_ys.begin(), this->compressed_ys.end());
    this->compressed_ys.erase(std::unique(this->compressed_ys.begin(), this->compressed_ys.end()), this->compressed_ys.end());
    this->compressed_ys.shrink_to_fit();
}

long long PST::get_total_sum(Node* root, long long left, long long right, long long target_idx) {
    if (right - left == 1) {
        return root->sum;
    }
    int middle = (left + right) / 2;
    if (target_idx < middle) {
        if (root->left == nullptr) {
            return root->sum;
        }
        return root->sum + get_total_sum(root->left, left, middle, target_idx);
    } else {
        if (root->right == nullptr) {
            return root->sum;
        }
        return root->sum + get_total_sum(root->right, middle, right, target_idx);
    }
}

Node* PST::persistence(Node* root, long long left, long long right, long long range_start, long long range_end, long long value) {
    if (left >= range_end || right <= range_start) {
        return root;
    }
    if (range_start <= left && right <= range_end) {
        Node* new_root = new Node(*root);
        new_root->sum = root->sum + value;
        return new_root;
    }
    long long middle = (left + right) / 2;
    Node* new_root = new Node(*root);
    if (new_root->left == nullptr) {
        new_root->left = new Node();
    }
    new_root->left = persistence(new_root->left, left, middle, range_start, range_end, value);
    if (new_root->right == nullptr) {
        new_root->right = new Node();
    }
    new_root->right = persistence(new_root->right, middle, right, range_start, range_end, value);
    return new_root;
}



void PST::build(const std::vector<Rectangle>& rectangles) {
    make_compressed_coords_from_rectangles(rectangles);

    std::vector<std::tuple<int, int, int, int>> events;
    for (const auto& rect : rectangles) {
        events.emplace_back(find_pos(compressed_xs, rect.leftBottom.x), 1, find_pos(compressed_ys, rect.leftBottom.y), find_pos(compressed_ys, rect.RightTop.y));
        events.emplace_back(find_pos(compressed_xs, rect.RightTop.x), 0, find_pos(compressed_ys, rect.leftBottom.y), find_pos(compressed_ys, rect.RightTop.y));
    }
    std::sort(events.begin(), events.end());

    Node* root = new Node();
    int prev_zipped_x = std::get<0>(events[0]);
    for (const auto& event : events) {
        if (std::get<0>(event) != prev_zipped_x) {
            roots.push_back(root);
            x_idxs.push_back(prev_zipped_x);
            prev_zipped_x = std::get<0>(event);
        }
        root = persistence(root, 0, compressed_ys.size(), std::get<2>(event), std::get<3>(event), std::get<1>(event) ? 1 : -1);
    }

    x_idxs.push_back(prev_zipped_x);
    roots.push_back(root);
}

long long PST::find_point(const Point& point) {
    if (point.x < this->compressed_xs[0] || point.y < this->compressed_ys[0]) {
        return 0;
    }
    long long zipped_x_idx = find_upper_pos(this->compressed_xs, point.x) - 1;
    long long zipped_y_idx = find_upper_pos(this->compressed_ys, point.y) - 1;
    Node* target_root = this->roots[find_upper_pos(this->x_idxs, zipped_x_idx) - 1];
    return get_total_sum(target_root, 0, this->compressed_ys.size(), zipped_y_idx);
}