//
// Created by atlas1323 on 6/25/2022.
//

#pragma once

#include <random>
#include <string>

// operator enum
enum oprtr {
    VAR,    // 0
    VAL,    // 1
    ADD,    // 2
    SUB,    // 3
    MLT,    // 4
    DIV,    // 5
    COS,    // 6
    SIN,    // 7
    BLANK,  // 8
    ROOT
};  // 9

class Node {
public:
    // member variables
    oprtr key;
    double value;

    // Constructors
    Node();
    explicit Node(oprtr act, double val = nan("0.0"));

    // Functions
    std::string nodeString(int i);
    // Static Functions

private:
    static std::random_device rand_dev_;
    static std::mt19937 rng_;
    static std::uniform_int_distribution<> act_dist_;
    static std::uniform_real_distribution<double> val_dist_;
};
