//
// Created by atlas1323 on 6/25/2022.
//

#include "Node.h"
#include <cmath>
#include <random>
#include <iostream>
#include <string>
#include <stdio.h>

// ################################################################################
// Static member variable initialization (where feasible)
// ################################################################################

std::random_device Node::rand_dev_;
std::mt19937 Node::rng_(Node::rand_dev_());
std::uniform_int_distribution<int> Node::act_dist_(VAR, SIN);
std::uniform_real_distribution<double> Node::val_dist_(-10, 10);



// ################################################################################
// Constructors and constructor tools
// ################################################################################

/**
 * @brief Construct a new random Node:: Node object
 *
 * keys are limited to those defied enum oprtr
 * Values are kept within the domain [-10, 10]
 */
Node::Node() {
    int temp = act_dist_(rng_);
    key = static_cast<oprtr>(temp);
    if (key == VAL)
        value = val_dist_(rng_);
    else
        value = nan("1.0");
}


/**
 * @brief Constructs a specified Node:: Node object
 * 
 * @param act - oprtr of node
 * @param val - value to assign the node if VAL node
 */
Node::Node(oprtr act, double val) {
    key = act;
    if (key == VAL) {
        // Check for forced exit in random eq builder
        if (!std::isnan(val)) {
            value = val;
        } else
            value = val_dist_(rng_);
    }
}

/**
 * @brief Returns the string representation of node i
 *
 * @param i - index of node with desired string
 * @return string representation of node i
 */
std::string Node::nodeString(int i) {
    switch (key) {
        case VAR :
            return "( x )";
        case VAL : {
            char buffer[6];
            std::sprintf(buffer, "(c%2i)", i);
            return buffer;
        }
        case ADD :
            return "( + )";
        case SUB :
            return "( - )";
        case MLT :
            return "( * )";
        case DIV :
            return "( / )";
        case COS :
            return "(cos)";
        case SIN :
            return "(sin)";
        default :
            return "     ";

    }

}
