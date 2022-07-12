//
// Created by atlas1323 on 7/10/2022.
//

#include "heap.h"
#include <Node.h>
#include <cmath>
#include <iostream>

// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Constructors/Destructors ----------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

/**
 * @brief Default constructor
 */
Heap::Heap() {
    size_ = 2;
    nodes_ = new Node[size_];
    nodes_[0] = Node(ROOT);
    nodes_[1] = Node(BLANK);
}

/**
 * @brief Constructor for predefined Nodes*
 *
 * @param size
 * @param nodes
 */
Heap::Heap(const int &size, const Node *nodes) {
    size_ = size;
    nodes_ = new Node[size_];
    std::copy(nodes, nodes + size, this->nodes_);
    nodes_[0] = Node(ROOT);
}

/**
 * @brief Copy Constructor
 * @param that
 */
Heap::Heap(const Heap &that) {
    this->size_ = that.size_;
    this->nodes_ = new Node[that.size_];
    std::copy(that.nodes_, that.nodes_ + that.size_, this->nodes_);
}

/**
 * @brief Move Constructor
 * @param that
 */
Heap::Heap(Heap &&that) noexcept {
    this->size_ = that.size_;
    that.size_ = 0;

    this->nodes_ = that.nodes_;
    that.nodes_ = nullptr;
}

/**
 * @brief Default Destructor
 */
Heap::~Heap() {
    delete[] nodes_;
}

// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Public Methods -------------------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

/**
 * @brief Turns all nodes in a branch to BLANK
 * @param index
 */
void Heap::clipBranch(const int &index) {
    int base_level = (int) (floor(log2(index)));
    int max_depth = (int) (log2(size_));
    int d = max_depth - base_level;

    for (int l = 0; l < d; l++) {
        int left_node = (int) (pow(2, l)) * index;
        for (int n = 0; n <= (int) (pow(2, l) - 1); n++)
            nodes_[left_node + n] = Node(BLANK);
    }
}

/**
 * @brief attaches a branch to the heap at index
 * @param index
 * @param branch
 */
void Heap::graftBranch(const int &index, const Heap &branch) {
    int base_level = (int) (floor(log2(index)));
    int max_depth = getDepth();
    int diff = max_depth - base_level;

    if (diff < branch.getDepth())
        growHeap(branch.getDepth() - diff);

    int branch_index = 1;
    for (int level = 0; level < getDepth(); ++level) {
        int left_node = (int) (pow(2, level)) * index;
        for (int nodex = 0; nodex <= (int) (pow(2, level) - 1); nodex++) {
            if (branch_index < branch.getSize()) {
                nodes_[left_node + nodex] = branch.nodes_[branch_index];
                branch_index++;
            } else
                nodes_[left_node + nodex] = Node(BLANK);
        }
    }
}

/**
 * @brief Returns heap with root at index of current heap
 * @param index
 * @return
 */
Heap Heap::getBranch(const int &index) {

    Heap branch = Heap();

    // early exit for blank exit
    if (nodes_[index].key == BLANK)
        return branch;

    // real branch continuation
    int base_level = (int) (floor(log2(index)));
    int max_depth = (int) (log2(size_));
    int branch_depth = max_depth - base_level;

    branch.growHeap(branch_depth);

    // Populate branch
    int branch_index = 1;
    for (int level = 0; level < branch_depth; level++) {
        int left_node = (int) (pow(2, level)) * index;
        for (int nodex = 0; nodex <= (int) (pow(2, level) - 1); nodex++) {
            branch.setNode(branch_index, nodes_[left_node + nodex]);
            branch_index++;
        }
    }

    branch.trimHeap();

    return branch;
}


void Heap::growHeap(const int &growFactor) {
    // int temp_size = growthSize_(depth);
    int temp_size = size_ * (int) pow(2, growFactor);
    // Create new array
    Node *temp_nodes = new Node[temp_size];

    // Copy old items to new array
    std::copy(nodes_, nodes_ + size_, temp_nodes);
    // for(int i = 0; i < size_; i++)
    //     temp_nodes[i] = nodes_[i];
    for (int i = size_; i < temp_size; i++)
        temp_nodes[i] = Node(BLANK);
    size_ = temp_size;
    delete[] nodes_;
    nodes_ = temp_nodes;
    temp_nodes = nullptr;
    delete[] temp_nodes;
}

/**
 * @brief Trims heap of all blank layers
 */
void Heap::trimHeap() {
    int max_depth = size_;
    bool exit = false;
    while (max_depth > 1) {

        for (int i = max_depth / 2; i < max_depth; i++) {
            if (nodes_[i].key != BLANK) {
                exit = true;
                break;
            }
        }

        if (exit) break;

        max_depth /= 2;
    }


    if (max_depth != size_) {
        Node *temp_nodes = new Node[max_depth];
        std::copy(nodes_, nodes_ + max_depth, temp_nodes);
        size_ = max_depth;
        nodes_ = temp_nodes;
        temp_nodes = nullptr;
        delete[] temp_nodes;
    }

}




// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Getters/Setters ------------------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

int Heap::getSize() const {
    return size_;
}

int Heap::getDepth() const {
    return (int) (log2(size_));

}

void Heap::setNode(const int &index, const Node &node) {
    nodes_[index] = node;
}

Node Heap::getNode(const int &index) {
    return nodes_[index];
}


// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Overloaded Operators -------------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

/**
 * @brief Copy Assignment
 *
 * @param that
 * @return
 */
Heap &Heap::operator=(const Heap &that) {
    if (this != &that) {
        delete[] this->nodes_;

        this->size_ = that.size_;

        if (that.size_ > 0) {
            this->nodes_ = new Node[that.size_];
            // for(int i = 0; i < that.size_; i++)
            //     this->nodes_[i] = that.nodes_[i];
            std::copy(that.nodes_, that.nodes_ + that.size_, this->nodes_);
        } else {
            this->nodes_ = nullptr;
        }
    }
    return *this;
}

Heap &Heap::operator=(Heap &&that) noexcept {
    if (this != &that) {
        delete[] this->nodes_;
        this->nodes_ = that.nodes_;

        this->size_ = that.size_;

        that.size_ = 0;
        that.nodes_ = nullptr;
    }

    return *this;
}

// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Private Methods -------------------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
