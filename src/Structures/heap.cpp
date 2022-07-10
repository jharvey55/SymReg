//
// Created by atlas1323 on 7/10/2022.
//

#include "heap.h"

// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Constructors/Destructors ----------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

/**
 * @brief Default constructor
 */
Heap::Heap() {
    size_ = 2;
    nodes_ = new Node[size_];
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

void Heap::clipBranch(const int &index) {

}

void Heap::graftBranch(const int &index, const Heap &branch) {

}

Heap Heap::getBranch(const int &index) {

}

// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Getters/Setters ------------------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

int Heap::getSize() const {
    return size_;
}

void Heap::setNode(const Node &node, const int &index) {
    nodes_[index] = node;
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
// Private Member Variables ---------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
int size_;
Node *nodes_;

// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
// Private Methods -------------------------------------------------------------------------------------------------
// █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
void growHeap_(const int &growFactor);

void trimHeap_();


