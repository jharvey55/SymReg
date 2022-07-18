//
// Created by atlas1323 on 7/18/2022.
//
#include <iostream>
#include <cmath>


void tree1(int index) {
//    int index = 2;
    int size_ = 32;
    int branch_size = 8;
    int branch_depth = (int) (log2(branch_size));
    std::cout << "Branch Depth:  " << size_ << std::endl;


    int base_level = (int) (floor(log2(index)));
    std::cout << "Base Level:    " << base_level << std::endl;
    int max_depth = (int) (log2(size_));
    std::cout << "Max depth:     " << max_depth << std::endl;
    int diff = max_depth - base_level;
    std::cout << "DIFF:          " << diff << std::endl;

    std::cout << "\n\n\n";

    if (diff < branch_depth) {
        size_ = size_ * (int) (pow(2, branch_depth - diff));
        std::cout << "New Size: " << size_ << std::endl;
        max_depth = (int) (log2(size_));
        std::cout << "New Max Depth: " << max_depth << std::endl;

        std::cout << "\n\n\n";
    }

    int branch_index = 1;
    for (int level = 0; level < max_depth - base_level; ++level) {
        int left_node = (int) (pow(2, level)) * index;
        for (int nodex = 0; nodex <= (int) (pow(2, level) - 1); nodex++) {
            if (branch_index < branch_size) {
//                nodes_[left_node + nodex] = branch.nodes_[branch_index];
                std::cout << "Copied " << branch_index << " to " << left_node + nodex << std::endl;
                branch_index++;
            } else {
                std::cout << "Set " << left_node + nodex << " to blank" << std::endl;
            }
        }
    }
}

void tree2(int index) {
//    int index = 2;
    int size_ = 32;
    int branch_size = 8;
    int branch_depth = (int) (log2(branch_size));
    std::cout << "Branch Depth:  " << size_ << std::endl;


    int base_level = (int) (floor(log2(index)));
    std::cout << "Base Level:    " << base_level << std::endl;
    int max_depth = (int) (log2(size_));
    std::cout << "Max depth:     " << max_depth << std::endl;
    int diff = max_depth - base_level;
    std::cout << "DIFF:          " << diff << std::endl;

    std::cout << "\n\n\n";

    if (max_depth < branch_depth + base_level) {
        size_ = size_ * (int) (pow(2, branch_depth + base_level - max_depth));
        std::cout << "New Size: " << size_ << std::endl;
        max_depth = (int) (log2(size_));
        std::cout << "New Max Depth: " << max_depth << std::endl;

        std::cout << "\n\n\n";
    }

    int branch_index = 1;
    for (int level = 1; level < pow(2, max_depth - base_level); level *= 2) {
        std::cout << level << std::endl;
        for (int step = 0; step < level; step++) {
            if (level * branch_index + step < branch_size) {
//                nodes_[left_node + nodex] = branch.nodes_[branch_index];
                std::cout << "Copied " << level * branch_index + step << " to " << level * index + step << std::endl;
//                branch_index++;
            } else {
                std::cout << "Set " << level * index + step << " to blank" << std::endl;
            }
        }
    }
}


int main() {

    tree2(8);

    return 0;
}