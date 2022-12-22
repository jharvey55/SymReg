//
// Created by atlas1323 on 6/25/2022.
//

#include "Contender.h"
#include "Node.h"
#include "Point.h"
#include "../DataIO/DataLog.h"

#include <cmath>
#include <stdio.h>
#include <functional>
#include <vector>
#include <iostream>
#include <random>
#include <tuple>
//#include <sstream>

// ################################################################################
// Static member variable initialization (where feasible)
// ################################################################################

int Contender::evaluations_ = 0;
std::vector<Point> Contender::Points;
DataLog Contender::logger;

std::random_device Contender::rand_dev_;
std::mt19937 Contender::rng_(Contender::rand_dev_());
std::uniform_int_distribution<int> Contender::coin_flip_(0, 1);
std::uniform_int_distribution<int> Contender::key_range_(VAR, BLANK);

// ################################################################################
// Constructors and Destructor
// ################################################################################

/**
 * @brief Construct a new Contender::Contender object
 * 
 */
Contender::Contender() {
//    size_ = 2;
//    nodes_ = new Node[size_];
    tree_ = Heap();
    randy(1);
    fitness_ = 0;

    // TODO: Make eq string
    // TODO: Calc fitness
}

/**
 * @brief Construct a new Contender:: Contender object
 * 
 * @param size size of node array
 * @param nodes node array to fill new contender
 */
Contender::Contender(const int &size, const Node *nodes) {
    // delete[] nodes_;
//    size_ = size;
//    nodes_ = new Node[size_];
    // for(int i = 0; i < size; i++)
    //     nodes_[i] = nodes[i];
//    std::copy(nodes, nodes + size, this->nodes_);
    tree_ = Heap(size, nodes);
    fitness_ = 0.0f;
}


/**
 * @brief Copy Constructor: Construct a new Contender::Contender object
 *
 * @param that Contender to copy
 */
Contender::Contender(const Contender &that) {
//    this->size_ = that.size_;
    this->fitness_ = that.fitness_;
//    this->nodes_ = new Node[that.size_];
    // for(int i = 0; i < that.size_; i++)
    //     this->nodes_[i] = that.nodes_[i];
//    std::copy(that.nodes_, that.nodes_ + that.size_, this->nodes_);
    this->tree_ = that.tree_;

}

Contender::Contender(Contender &&that) noexcept {
//    this->size_ = that.size_;
//    that.size_ = 0;
    this->fitness_ = that.fitness_;
    that.fitness_ = 0;
//    this->nodes_ = that.nodes_;
//    that.nodes_ = nullptr;
    this->tree_ = that.tree_;
    that.tree_ = Heap();
}

Contender::~Contender() {
//    delete[] nodes_;
}

// ################################################################################
// Getters and setters
// ################################################################################

int Contender::getSize() const {
//    return size_;
    return tree_.getSize();
}

void Contender::setNodes(const int &size, const Node *nodes) {
//    nodes_ = nodes;
    tree_ = Heap(size, nodes);
}

void Contender::setNode(Node &node, int index) {
//    nodes_[index] = node;
    tree_.setNode(index, node);
}

Node Contender::getNode(const int &index) {
    return tree_.getNode(index);
}


std::string Contender::getEqString() {
    std::string equation = buildEqString_(1);

    return equation;
}


std::string Contender::getHeapString() {
    std::string equation = "";
    for (int i = 0; i < getSize(); i++) {
        switch (tree_.getKey(i)) {
            case VAR:
                equation += "VAR ";
                break;
            case VAL:
//                equation += "VAL=";
                equation += std::to_string(tree_.getVal(i)) + " ";
                break;
            case ADD:
                equation += "ADD ";
                break;
            case SUB:
                equation += "SUB ";
                break;
            case MLT:
                equation += "MLT ";
                break;
            case DIV:
                equation += "DIV ";
                break;
            case COS:
                equation += "COS ";
                break;
            case SIN:
                equation += "SIN ";
                break;
            case BLANK:
                equation += "BLANK ";
                break;
            default:
                equation += "ROOT ";
        }
    }

    return equation;
}


double Contender::getFitness() const {
    return fitness_;
}

/**
 * Creates log string for experiment tracking
 * @return string representing relevant info for a contenter log entry
 */
std::string Contender::LogString() {
//    std::string log_string = std::to_string(evaluations_) + " | " + std::to_string(fitness_) + " | " + getEqString();
    std::string log_string = std::to_string(evaluations_) + " | " + std::to_string(fitness_) + " | " + getHeapString();

    return log_string;
}

int Contender::getEvalCount() {
    return evaluations_;
}

void Contender::ResetEvaluationCount() {
    evaluations_ = 0;
}

double Contender::DiversityComp(const Contender &A, const Contender &B, const std::vector<Point> &points) {
    double sum = 0.0f;
    double diff;
    double num_points = (double) points.size();

    for (int i = 0; i < num_points; i += 100) {
        double val1 = A.EqParser(1, points[i].x);
        double val2 = B.EqParser(1, points[i].x);

        diff = val1 - val2;
        sum += std::pow(diff, 2);
    }

    // Update rms_
    double rmse = std::sqrt(sum / num_points);

    return rmse;
}

void Contender::PopDivserity(const std::vector<Contender> &pop, const std::vector<Point> &points) {
    int pop_size = (int) pop.size();

    double stdev;
    double mean;
    double sum1 = 0.0f;
    double sum2 = 0.0f;
    double count = 0.0f;

    for (int a = 0; a < pop_size - 1; a++) {
        for (int b = a + 1; b < pop_size; b++) {
            double diversity = DiversityComp(pop[a], pop[b], points);
            sum2 += diversity;
            sum1 += std::pow(diversity, 2);
            count += 1.0f;
        }
    }

    mean = sum2 / count;

    stdev = sum1 - 2.0f * sum2 * mean + std::pow(mean, 2) * count;

    stdev = std::sqrt(stdev / count);

    std::string entry = std::to_string(evaluations_) + " | " + std::to_string(mean) + " | " + std::to_string(stdev);
    logger.LogEntry(DIVERSITY, entry);

}

void Contender::PopDivserity(const std::vector<std::vector<Contender>> &pop, const std::vector<Point> &points) {

    double stdev;
    double mean;
    double sum1 = 0.0f;
    double sum2 = 0.0f;
    double count = 0.0f;

    for (const auto &gen: pop) {
        int pop_size = (int) gen.size();
        for (int a = 0; a < pop_size - 1; a++) {
            for (int b = a + 1; b < pop_size; b++) {
                double diversity = DiversityComp(gen[a], gen[b], points);
                sum2 += diversity;
                sum1 += std::pow(diversity, 2);
                count += 1.0f;
            }
        }
    }

    mean = sum2 / count;

    stdev = sum1 - 2.0f * sum2 * mean + std::pow(mean, 2) * count;

    stdev = std::sqrt(stdev / count);

    std::string entry = std::to_string(evaluations_) + " | " + std::to_string(mean) + " | " + std::to_string(stdev);
    logger.LogEntry(DIVERSITY, entry);

}


//void Contender::treePrint() {
//    std::cout << "Making tree!!!" << std::endl;
//    int n_layers = (int) std::log2(size_);
//    double n_gaps = n_layers - 1;
//    double max_depth = n_layers + n_gaps;
//
//    for (int depth = 0; depth < max_depth; depth++) {
//        int layer = depth / 2;
//        // case for node depth
//        if (depth % 2 == 0) {
//            std::string l_string;
//
//            int lead = 3 * (int) pow(2, n_layers - layer - 1) - 3;
//            int lag = lead + 1;
//            int n_size = 6 + lead + lag;
//
//            int first_node = (int) pow(2, layer);
//            int last_node = 2 * first_node;
//            for (int n = first_node; n < last_node; n++) {
//                char buffer[n_size];
//                std::sprintf(buffer, "%*s%*s", lead + 5, nodes_[n].nodeString(n).c_str(), lag, " ");
//                l_string += buffer;
//            }
//            std::cout << l_string.substr(0, l_string.size() - 1) << std::endl;
//        }
//            // case for gap depth
//        else {
//            std::string l_string;
//            int layer = depth / 2 + 1;
//            int lead = 3 * (int) pow(2, n_layers - layer - 1) - 1;
//            int n_gap = (int) pow(2, layer - 1);
//
//            for (int i = 0; i < n_gap; i++) {
//                int left_node = (int) pow(2, layer) + 2 * i;
//                bool ltest = nodes_[left_node].key != BLANK;
//                bool rtest = nodes_[left_node + 1].key != BLANK;
//
//                l_string.append(lead, ' ');
//
//                if (ltest) {
//                    l_string.append("╔");
//                    for (int j = 0; j < lead; j++)
//                        l_string += "═";
//                } else
//                    l_string.append(lead + 1, ' ');
//
//                if (ltest && rtest)
//                    l_string.append("╩");
//                else if (ltest)
//                    l_string.append("╝");
//                else if (rtest)
//                    l_string.append("╚");
//                else
//                    l_string.append(" ");
//
//                if (rtest) {
//                    for (int j = 0; j < lead; j++)
//                        l_string += "═";
//                    l_string.append("╗");
//                } else
//                    l_string.append(lead + 1, ' ');
//
//                l_string.append(lead + 1, ' ');
//            }
//
//            std::cout << l_string.substr(0, l_string.size() - 1) << std::endl;
//
//        }
//    }
//
//    for (int i = 0; i < size_; i++) {
//        if (nodes_[i].key == VAL)
//            std::printf("c%2d: %f\n", i, nodes_[i].value);
////        if(nodes_[i].key == BLANK)
////            std::cout << "BLANK: " << i << std::endl;
//    }
//
//}

void Contender::treePrint() {
    std::cout << "Making tree!!!" << std::endl;
    int n_layers = tree_.getDepth();
//    std::cout << "Layers retrieved" << std::endl;

//    double n_gaps = n_layers - 1;
//    double max_depth = n_layers + n_gaps;
    int max_depth = 2 * n_layers - 1;
//    std::cout << "depth" << std::endl;

    for (int depth = 0; depth < max_depth; depth++) {
//        std::cout << "New depth" << std::endl;

        int layer = depth / 2;
        // case for node depth
        if (depth % 2 == 0) {
            std::string l_string;

            int lead = 3 * (int) pow(2, n_layers - layer - 1) - 3;
            int lag = lead + 1;
            int n_size = 6 + lead + lag;
//            std::cout << "aqui" << std::endl;

            int first_node = (int) pow(2, layer);
            int last_node = 2 * first_node;
            for (int n = first_node; n < last_node; n++) {
                char buffer[n_size];
//                std::cout << "Aqui2" << std::endl;

                std::sprintf(buffer, "%*s%*s", lead + 5, tree_.getNode(n).nodeString(n).c_str(), lag, " ");
                l_string += buffer;
            }
            std::cout << l_string.substr(0, l_string.size() - 1) << std::endl;
        }
            // case for gap depth
        else {
//            std::cout << "ELSE!!!" << std::endl;

            layer = depth / 2 + 1;
            int lead = 3 * (int) pow(2, n_layers - layer - 1) - 1;
            int n_gap = (int) pow(2, layer - 1);

            for (int i = 0; i < n_gap; i++) {
                std::string l_string;
                int left_node = (int) pow(2, layer) + 2 * i;
                bool ltest = tree_.getNode(left_node).key != BLANK;
                bool rtest = tree_.getNode(left_node + 1).key != BLANK;

                l_string.append(lead, ' ');

                if (ltest) {
                    l_string.append("╔");
                    for (int j = 0; j < lead; j++)
                        l_string += "═";
                } else
                    l_string.append(lead + 1, ' ');

                if (ltest && rtest)
                    l_string.append("╩");
                else if (ltest)
                    l_string.append("╝");

                else if (rtest)
                    l_string.append("╚");
                else
                    l_string.append(" ");

                if (rtest) {
                    for (int j = 0; j < lead; j++)
                        l_string += "═";
                    l_string.append("╗");
                } else
                    l_string.append(lead + 1, ' ');

                l_string.append(lead + 1, ' ');

                std::cout << l_string;;
            }

//            std::cout << l_string.substr(0, l_string.size() - 1) << std::endl;
            std::cout << std::endl;

        }
    }

    for (int i = 0; i < tree_.getSize(); i++) {
        if (tree_.getKey(i) == VAL)
            std::printf("c%2d: %f\n", i, tree_.getNode(i).value);
//        if(nodes_[i].key == BLANK)
//            std::cout << "BLANK: " << i << std::endl;
    }
}


// ################################################################################
// Member functions
// ################################################################################

static double epsilon = 4.94065645841247e-324;
static double max = std::numeric_limits<double>::max();
static double min = std::numeric_limits<double>::lowest();


///**
// *
// * @param index
// * @param x
// * @return
// */
//double Contender::EqParser(int index, const double &x) {
//    int left_node = 2 * index;
//    int right_node = 2 * index + 1;
//    switch (nodes_[index].key) {
//        case VAR :
//            return x;
//        case VAL :
//            return nodes_[index].value;
//        case ADD : {
//            double val = EqParser(left_node, x) + EqParser(right_node, x);
//            if (std::isinf(val))
//                val = val > 0 ? max : min;
//            return val;
//        }
//        case SUB : {
//            double val = EqParser(left_node, x) - EqParser(right_node, x);
//            if (std::isinf(val))
//                val = val > 0 ? max : min;
//            return val;
//        }
//        case MLT : {
//            double val = EqParser(left_node, x) * EqParser(right_node, x);
//            if (std::isinf(val))
//                val = val > 0 ? max : min;
//            return val;
//        }
//        case DIV : {
//            // safe divide
//            double val = EqParser(left_node, x) / EqParser(right_node, x);
//            if (std::isinf(val))
//                val = val > 0 ? max : min;
//            if (std::isnan(val))
//                val = 1.0f;
//            return val;
//        }
//        case COS :
//            return cos(EqParser(left_node, x));
//        case SIN :
//            return sin(EqParser(left_node, x));
//        default :
//            return nan("0.0");
//    }
//}

/**
 *
 * @param index
 * @param x
 * @return
 */
double Contender::EqParser(const int &index, const double &x) const {
    int left_node = 2 * index;
    int right_node = 2 * index + 1;
    switch (tree_.getKey(index)) {
        case VAR :
            return x;
        case VAL :
            return tree_.getVal(index);
        case ADD : {
            double val = EqParser(left_node, x) + EqParser(right_node, x);
            if (std::isinf(val))
                val = val > 0 ? max : min;
            return val;
        }
        case SUB : {
            double val = EqParser(left_node, x) - EqParser(right_node, x);
            if (std::isinf(val))
                val = val > 0 ? max : min;
            return val;
        }
        case MLT : {
            double val = EqParser(left_node, x) * EqParser(right_node, x);
            if (std::isinf(val))
                val = val > 0 ? max : min;
            return val;
        }
        case DIV : {
            // safe divide
            double val = EqParser(left_node, x) / EqParser(right_node, x);
            if (std::isinf(val))
                val = val > 0 ? max : min;
            if (std::isnan(val))
                val = 1.0f;
            return val;
        }
        case COS :
            return cos(EqParser(left_node, x));
        case SIN :
            return sin(EqParser(left_node, x));
        default :
            return nan("0.0");
    }
}

///**
// * \brief Grows the heap!!!!
// * @brief Grows the heap
// * @param depth
// */
//void Contender::growHeap_(const int &growFactor) {
//    // int temp_size = growthSize_(depth);
//    int temp_size = size_ * (int) pow(2, growFactor);
//    // Create new array
//    Node *temp_nodes = new Node[temp_size];
//
//    // Copy old items to new array
//    std::copy(nodes_, nodes_ + size_, temp_nodes);
//    // for(int i = 0; i < size_; i++)
//    //     temp_nodes[i] = nodes_[i];
//    for (int i = size_; i < temp_size; i++)
//        temp_nodes[i] = Node(BLANK);
//    size_ = temp_size;
//    delete[] nodes_;
//    nodes_ = temp_nodes;
//    temp_nodes = nullptr;
//    delete[] temp_nodes;
//}


//void Contender::randy(const int &index) {
//    // Guard rail to keep variable from growing too large
//    if (size_ >= 64 && index > 31) {
//        if (coin_flip_(rng_))
//            nodes_[index] = Node(VAR);
//        else
//            nodes_[index] = Node(VAL);
//    } else {
//        nodes_[index] = Node();
//
//        // Check if node is terminus, move forward if not terminus
//        if (nodes_[index].key != VAR && nodes_[index].key != VAL) {
//            int l_child = 2 * index;
//
//            if (l_child >= size_) {
//                growHeap_(2); // If not big enough, add next layer of depth
//
//            }
//            randy(l_child); // Recursively call for left child
//
//            // CHeck if node has 2 children, continue if true
//            if (nodes_[index].key != COS && nodes_[index].key != SIN) {
//                // Guard for dividing by zero
//                randy(l_child + 1); // Recursively call for right child
//            }
//        }
//    }
//}

void Contender::randy(const int &index) {
    // Guard rail to keep variable from growing too large
    if (tree_.getSize() >= 64 && index > 31) {
        if (coin_flip_(rng_))
            tree_.setNode(index, Node(VAR));
        else
            tree_.setNode(index, Node(VAL));
    } else {
        tree_.setNode(index, Node());

        // Check if node is terminus, move forward if not terminus
        if (tree_.getKey(index) > VAL) {
            int l_child = 2 * index;

            if (l_child >= tree_.getSize())
                tree_.growHeap(2); // If not big enough, add next layer of depth
            randy(l_child); // Recursively call for left child

            // CHeck if node has 2 children, continue if true
            if (tree_.getKey(index) != COS && tree_.getKey(index) != SIN) {
                // Guard for dividing by zero
                randy(l_child + 1); // Recursively call for right child
            }
        }
    }
}

// ################################################################################
// Optimization tools
// ################################################################################

// Mutations -----------------------------------------------------------------------------------------------------------

/**
 * mutates a VAL node by value
 * @param index
 */
void Contender::valueMutate(const int &index) {
    if (tree_.getKey(index) != VAL)
        throw std::invalid_argument("Node must be VALUE type to mutate value");

//    nodes_[index].value *= 0.9 + coin_flip_(rng_) * 0.2;

    switch (coin_flip_(rng_)) {
        case 0 :
            tree_.setVal(index, tree_.getVal(index) - 0.1f);
            break;
        default :
            tree_.setVal(index, tree_.getVal(index) + 0.1f);
            break;
    }
}

// General Mutation

/**
 * Creates a small "safe" mutation
 * @param mutRate
 */
void Contender::Mutate(const int &index, const oprtr &op) {

//    Heap branch;
    switch (op) {
        case VAR : {
            tree_.clipBranch(index);
            tree_.setNode(index, Node(VAR));
            break;
        }
        case VAL : {
            valueMutate(index);
            break;
        }
        case ADD : {
            Heap branch = tree_.getBranch(index);
            tree_.clipBranch(index);
            Node temp[4] = {Node(ROOT), Node(ADD), Node(BLANK), Node(VAL, 0.1f)};
            tree_.graftBranch(index, Heap(4, temp));
            tree_.graftBranch(index * 2, branch);
            break;
        }
        case SUB : {
            Heap branch = tree_.getBranch(index);
            tree_.clipBranch(index);
            Node temp[4] = {Node(ROOT), Node(SUB), Node(BLANK), Node(VAL, 0.1f)};
            tree_.graftBranch(index, Heap(4, temp));
            tree_.graftBranch(index * 2, branch);
            break;
        }
        case MLT : {
            Heap branch = tree_.getBranch(index);
            tree_.clipBranch(index);
            Node temp[4] = {Node(ROOT), Node(MLT), Node(BLANK), Node(VAL, 1.1f)};
            tree_.graftBranch(index, Heap(4, temp));
            tree_.graftBranch(index * 2, branch);
            break;
        }
        case DIV : {
            Heap branch = tree_.getBranch(index);
            tree_.clipBranch(index);
            Node temp[4] = {Node(ROOT), Node(DIV), Node(BLANK), Node(VAL, 1.1f)};
            tree_.graftBranch(index, Heap(4, temp));
            tree_.graftBranch(index * 2, branch);
            break;
        }
        case COS : {
            Heap branch = tree_.getBranch(index);
            tree_.clipBranch(index);
            Node temp[4] = {Node(ROOT), Node(COS), Node(BLANK), Node(BLANK)};
            tree_.graftBranch(index, Heap(4, temp));
            tree_.graftBranch(index * 2, branch);
            break;
        }
        case SIN : {
            Heap branch = tree_.getBranch(index);
            tree_.clipBranch(index);
            Node temp[4] = {Node(ROOT), Node(SIN), Node(BLANK), Node(BLANK)};
            tree_.graftBranch(index, Heap(4, temp));
            tree_.graftBranch(index * 2, branch);
            break;
        }
        case BLANK: {
            tree_.clipBranch(index);
            if (coin_flip_(rng_)) {
                tree_.setNode(index, Node(VAR));
            } else {
                tree_.setNode(index, Node(VAL));
            }
            break;
        }
        default : {
            break;
        }
    }
    tree_.trimHeap();
}

/**
 * @brief Safe mutation operator
 * @param index
 * @param mutKey
 * @return true if successful, false if unsuccessful
 */
bool Contender::safeMutate(int &index, const oprtr &mutKey) {
    // Initial checks all should abide
    if (index == 0 || index >= getSize())
        return false;

    // find a not blank node
    while (tree_.getKey(index) == BLANK) {
        index /= 2;
    }

    // find a val node if possible for VAL mutation
    if (mutKey == VAL && tree_.getKey(index) != VAL) {
        int base_level = (int) (floor(log2(index)));
        int max_depth = tree_.getDepth();
        for (int level = 1; level < pow(2, max_depth - base_level); level *= 2) {
            for (int step = 0; step < level; step++) {
                if (tree_.getKey(index * level + step) == VAL) {
                    index = index * level + step;
                    goto success;
                }
            }
        }
        return false;

    }
    success:
    // Don't destroy the entire tree
//    if (mutKey == BLANK && index == 1) {
//        return false;
//    }

    if (tree_.getKey(index) == VAL) {
        Node temp = Node(VAL);
        switch (mutKey) {
            case ADD : {
                temp.value = tree_.getVal(index) + 0.1;
                tree_.setNode(index, temp);
                return true;
            }
            case SUB : {
                temp.value = tree_.getVal(index) - 0.1;
                tree_.setNode(index, temp);
                return true;
            }
            case MLT : {
                temp.value = tree_.getVal(index) * 1.1;
                tree_.setNode(index, temp);
                return true;
            }
            case DIV : {
                temp.value = tree_.getVal(index) / 1.1;
                tree_.setNode(index, temp);
                return true;
            }
            case COS : {
//                temp.value = cos(tree_.getVal(index));
//                tree_.setNode(index, temp);
                return false;
            }
            case SIN : {
//                temp.value = sin(tree_.getVal(index));
//                tree_.setNode(index, temp);
                return false;
            }
            default : {
                Mutate(index, mutKey);
                return true;
            }
        }
        tree_.trimHeap();
    }

//    // Specific mutaion checks
//    switch (mutKey) {
//        case VAL : {
//            if (tree_.getKey(index) != VAL)
//                return false;
//        }
//        case BLANK : {
//            if (index == 1)
//                return false;
//        }
//        default : {
//            break;
//        }
//    }

    Mutate(index, mutKey);
    return true;
}

/**
 *
 */
void Contender::randMutate() {
    std::uniform_int_distribution<int> index_range(1, getSize() - 1);
    double blank_prob = std::floor((double) getSize() / 4.0f);
    std::discrete_distribution<> disc({1, 1, 1, 1, 1, 1, 1, 1, blank_prob});

//    oprtr mutKey = coin_flip_(rng_) ? BLANK : (oprtr)key_range_(rng_);
    oprtr mutKey = (oprtr) disc(rng_);

    int index = index_range(rng_);

    while (!safeMutate(index, mutKey)) {
        mutKey = coin_flip_(rng_) ? BLANK : (oprtr) key_range_(rng_);
        index = index_range(rng_);
    }
}

// GP Tools ------------------------------------------------------------------------------------------------------------


void
Contender::RandCrossover(const Contender &Parent1, const Contender &Parent2, Contender &child1, Contender &child2) {
    int index1 = 0;
    int index2 = 0;
    std::uniform_int_distribution<> dist1(1, Parent1.getSize() - 1);
    std::uniform_int_distribution<> dist2(1, Parent2.getSize() - 1);

    index1 = dist1(rng_);
    while (Parent1.tree_.getKey(index1) == ROOT || Parent1.tree_.getKey(index1) == BLANK) {
//        index1 = dist1(rng_);
        index1 /= 2;
    }
//    std::cout << index1 << std::endl;
    index2 = dist2(rng_);
    while (Parent2.tree_.getKey(index2) == ROOT || Parent2.tree_.getKey(index2) == BLANK) {
//        index2 = dist2(rng_);
        index2 /= 2;
    }
//    std::cout << index1 << std::endl;

    Crossover(Parent1, Parent2, index1, child1, index2, child2);

}

void Contender::Crossover(const Contender &Parent1, const Contender &Parent2, const int &index1, Contender &child1,
                          const int &index2, Contender &child2) {

    if (Parent1.tree_.getKey(index1) == ROOT || Parent1.tree_.getKey(index1) == BLANK)
        throw std::invalid_argument("Crossover Index1 cannot be ROOT or BLANK");
    else if (index1 > Parent1.getSize())
        throw std::invalid_argument("Invalid Index1");

    if (Parent2.tree_.getKey(index2) == ROOT || Parent2.tree_.getKey(index2) == BLANK)
        throw std::invalid_argument("Crossover Index2 cannot be ROOT or BLANK");
    else if (index2 > Parent2.getSize())
        throw std::invalid_argument("Invalid Index2");

    Heap branch1 = Parent1.tree_.getBranch(index1);

    Heap branch2 = Parent2.tree_.getBranch(index2);

    child1 = Parent1;
    child1.tree_.graftBranch(index1, branch2);
    child1.tree_.trimHeap();
    child1.calcFitness();


    child2 = Parent2;
    child2.tree_.graftBranch(index2, branch1);
    child2.tree_.trimHeap();
    child2.calcFitness();

}

/**
 *
 * @param population
 * @param sum_fit
 * @return
 */
int Contender::ProportionalSelection(const std::vector<Contender> &population, const double &sum_fit) {
    std::uniform_real_distribution<double> r_dist(0.0f, sum_fit);
    double pick = r_dist(rng_);
//    double tracker = 1.0f/((double)(population[0].getSize())*0.01f + population[0].getFitness());
    double tracker = 1.0f / population[0].getFitness();

    int index = 0;

    while (tracker < pick) {
        index++;
//        tracker += 1.0f/((double)(population[index].getSize())*0.01f + population[index].getFitness());
        tracker += 1.0f / population[index].getFitness();

    }
    return index;
}


/**
 * @brief Updates the fitness of a contender
 * Calculates the rms of the contenders equation vs a test dataset (data)
 * 
 * @param data point array holding the data to test
 * @param num_points int representing the number of points in the dataset
 */
void Contender::calcFitness(const Point *data, int num_points) {
    double sum = 0.0f;
    double diff;
    for (int i = 0; i < num_points; i++) {
        diff = data[i].y - EqParser(1, data[i].x);

        sum += std::pow(diff, 2);
    }

    // Update rms_
    fitness_ = std::sqrt(sum / (double) num_points);

    evaluations_++;
}

double Contender::testFitness(const std::vector<Point> &sub_series) {
    double sum = 0.0f;
    double diff;
    double num_points = (double) sub_series.size();

    for (auto &point: sub_series) {
        double prediction = EqParser(1, point.x);
        diff = point.y - prediction;
        sum += std::pow(diff, 2);
    }
    if (std::isnan(sum)) {
        std::cout << "NAN " << std::endl;
        treePrint();

    }

    double rmse = std::sqrt(sum / num_points);
//    fitness_ = rmse;

//    evaluations_++;

    return rmse;
}

void Contender::calcFitness() {
    double sum = 0.0f;
    double diff;
    double num_points = (double) Points.size();

    for (auto &point: Points) {
        double prediction = EqParser(1, point.x);
        diff = point.y - prediction;
        sum += std::pow(diff, 2);
    }
    if (std::isnan(sum)) {
        std::cout << "NAN " << std::endl;
        treePrint();
    }
    // Update rms_
    double rmse = std::sqrt(sum / num_points);
    fitness_ = rmse;
    if (DataLog::dot) {
        std::string entry = std::to_string(evaluations_) + ", " + std::to_string(this->fitness_);
        logger.LogEntry(DOT, entry);
    }
    evaluations_++;
}

// ################################################################################
// Overloaded operators
// ################################################################################

/**
 * @brief Comparison operator: based on fitness
 * @param that
 * @return
 */
bool Contender::operator<(const Contender &that) const {

    if (that.getSize() > this->getSize()) {
//        double handicap = pow(0.99, that.getSize()-);
        double handicap = 0.99 * this->fitness_;
        return handicap < that.fitness_;
    } else if (this->getSize() > that.getSize()) {
        double handicap = 0.99 * that.fitness_;
        return this->fitness_ < handicap;
    }


//    double a = (1 + (float)this->getSize() * 0.005) * this->fitness_;
//    double b = (1 + (float)that.getSize() * 0.005) * that.fitness_;

//    return a < b;


////    double a = std::abs(this->fitness_ - that.fitness_);
////    double b = std::min(this->fitness_, that.fitness_);
////    if(a/b < 0.01f){
////        return this->getSize() < that.getSize();
////    }
//    return this->fitness_ < that.fitness_;

//    return std::log2(this->getSize())*this->fitness_ < std::log2(that.getSize())*that.fitness_;
    return this->fitness_ < that.fitness_;
}

/**
 * @brief Copy Assignment
 *
 * @param that
 * @return Contender&
 */
Contender &Contender::operator=(const Contender &that) {
    if (this != &that) {
//        delete[] this->nodes_;

//        this->size_ = that.size_;
        this->fitness_ = that.fitness_;

//        if (that.size_ > 0) {
//            this->nodes_ = new Node[that.size_];
//            // for(int i = 0; i < that.size_; i++)
//            //     this->nodes_[i] = that.nodes_[i];
//            std::copy(that.nodes_, that.nodes_ + that.size_, this->nodes_);
//            this->tree_ = that.tree_;
//        } else {
//            this->nodes_ = nullptr;
//            this->tree_ = Heap();
//        }
        this->tree_ = that.tree_;
    }
    return *this;
}

/**
 * @brief
 *
 * @param that
 * @return Contender&
 */
Contender &Contender::operator=(Contender &&that) noexcept {
    if (this != &that) {
//        delete[] this->nodes_;
//        this->nodes_ = that.nodes_;
        this->tree_ = that.tree_;

        this->fitness_ = that.fitness_;
//        this->size_ = that.size_;

        that.fitness_ = 0;
//        that.size_ = 0;
//        that.nodes_ = nullptr;
        that.tree_ = Heap();
    }

    return *this;
}

// ################################################################################
// Static Member functions
// ################################################################################

///**
// * Parses equation and returns string representation of equation
// *
// * @param index
// * @return string representation of equation
// */
//std::string Contender::buildEqString_(int index) {
//    switch (nodes_[index].key) {
//        case VAR :
//            return "x";
//        case VAL :
//            return std::to_string(nodes_[index].value);
//        case ADD :
//            return "(" + buildEqString_(2 * index) + " + " + buildEqString_(2 * index + 1) + ")";
//        case SUB :
//            return "(" + buildEqString_(2 * index) + " - " + buildEqString_(2 * index + 1) + ")";
//        case MLT : {
//            int left_node = 2 * index;
//            int right_node = 2 * index + 1;
//            return "(" + buildEqString_(left_node) + " ∙ " + buildEqString_(right_node) + ")";
//
//        }
//        case DIV : {
//            int left_node = 2 * index;
//            int right_node = 2 * index + 1;
//            return "(" + buildEqString_(left_node) + " / " + buildEqString_(right_node) + ")";
//        }
//        case COS :
//            return "cos(" + buildEqString_(2 * index) + ")";
//        case SIN :
//            return "sin(" + buildEqString_(2 * index) + ")";
//        default :
//            return "nan";
//    }
//}

std::string Contender::buildEqString_(int index) {
    switch (tree_.getKey(index)) {
        case VAR :
            return "x";
        case VAL :
            return std::to_string(tree_.getVal(index));
        case ADD :
            return "(" + buildEqString_(2 * index) + " + " + buildEqString_(2 * index + 1) + ")";
        case SUB :
            return "(" + buildEqString_(2 * index) + " - " + buildEqString_(2 * index + 1) + ")";
        case MLT : {
            int left_node = 2 * index;
            int right_node = 2 * index + 1;
            return "(" + buildEqString_(left_node) + " ∙ " + buildEqString_(right_node) + ")";

        }
        case DIV : {
            int left_node = 2 * index;
            int right_node = 2 * index + 1;
            return "(" + buildEqString_(left_node) + " / " + buildEqString_(right_node) + ")";
        }
        case COS :
            return "cos(" + buildEqString_(2 * index) + ")";
        case SIN :
            return "sin(" + buildEqString_(2 * index) + ")";
        default :
            return "nan";
    }
}

//std::string Contender::prettyString_(int index) {
////    switch (nodes_[index].key) {
////        case VAR :
////            return "x";
////        case VAL :
////            return std::to_string(nodes_[index].value);
////        case ADD :
////            return prettyString_(2 * index) + " + " + buildEqString_(2 * index + 1);
////        case SUB :
////            return prettyString_(2 * index) + " - " + buildEqString_(2 * index + 1);
////        case MLT : {
////            int left_node = 2 * index;
////            int right_node = 2 * index + 1;
////            std::string temp;
////
////            if (nodes_[left_node].key == ADD || nodes_[left_node].key == SUB)
////                temp += "(" + prettyString_(left_node) + ")";
////            else
////                temp += prettyString_(left_node);
////            temp += "∙";
////            if (nodes_[right_node].key == ADD || nodes_[right_node].key == SUB)
////                temp += "(" + prettyString_(right_node) + ")";
////            else
////                temp += prettyString_(right_node);
////            return temp;
////        }
////        case DIV : {
////            int left_node = 2 * index;
////            int right_node = 2 * index + 1;
////            std::string temp;
////
////            if (nodes_[left_node].key == ADD || nodes_[left_node].key == SUB)
////                temp += "(" + prettyString_(left_node) + ")";
////            else
////                temp += prettyString_(left_node);
////            temp += "/";
////            if (nodes_[right_node].key == ADD || nodes_[right_node].key == SUB)
////                temp += "(" + prettyString_(right_node) + ")";
////            else
////                temp += prettyString_(right_node);
////            return temp;
////        }
////        case COS :
////            return "cos(" + prettyString_(2 * index) + ")";
////        case SIN :
////            return "sin(" + prettyString_(2 * index) + ")";
////        default :
////            return "nan";
////    }
////}

std::string Contender::prettyString_(int index) {
    switch (tree_.getKey(index)) {
        case VAR :
            return "x";
        case VAL :
            return std::to_string(tree_.getVal(index));
        case ADD :
            return prettyString_(2 * index) + " + " + buildEqString_(2 * index + 1);
        case SUB :
            return prettyString_(2 * index) + " - " + buildEqString_(2 * index + 1);
        case MLT : {
            int left_node = 2 * index;
            int right_node = 2 * index + 1;
            std::string temp;

            if (tree_.getKey(left_node) == ADD || tree_.getKey(left_node) == SUB)
                temp += "(" + prettyString_(left_node) + ")";
            else
                temp += prettyString_(left_node);
            temp += "∙";
            if (tree_.getKey(right_node) == ADD || tree_.getKey(right_node) == SUB)
                temp += "(" + prettyString_(right_node) + ")";
            else
                temp += prettyString_(right_node);
            return temp;
        }
        case DIV : {
            int left_node = 2 * index;
            int right_node = 2 * index + 1;
            std::string temp;

            if (tree_.getKey(left_node) == ADD || tree_.getKey(left_node) == SUB)
                temp += "(" + prettyString_(left_node) + ")";
            else
                temp += prettyString_(left_node);
            temp += "/";
            if (tree_.getKey(right_node) == ADD || tree_.getKey(right_node) == SUB)
                temp += "(" + prettyString_(right_node) + ")";
            else
                temp += prettyString_(right_node);
            return temp;
        }
        case COS :
            return "cos(" + prettyString_(2 * index) + ")";
        case SIN :
            return "sin(" + prettyString_(2 * index) + ")";
        default :
            return "nan";
    }
}