//
// Created by atlas1323 on 12/1/2022.
//


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::cout << "Building...." << std::endl;
    // Build multidem vec
    std::vector<std::vector<int>> mvi;

    // Give it some data
    mvi.emplace_back();

    for (int i = 0; i < 10; i++) {
        mvi[0].push_back(i);
    }
    std::cout << "Built" << std::endl;
    mvi.emplace_back();

    for (int i = 10; i > 0; i--) {
        mvi[1].push_back(i);
    }

    std::cout << "Built" << std::endl;

    // TODO: Test that you can sort the sub vectors
    for (int i = 0; i < mvi[1].size(); i++)
        std::cout << mvi[1][i] << " ";
    std::cout << std::endl;

    std::sort(mvi[1].begin(), mvi[1].end());

    for (int i = 0; i < mvi[1].size(); i++)
        std::cout << mvi[1][i] << " ";
    std::cout << std::endl;


    return 0;
}