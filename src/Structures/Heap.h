//
// Created by atlas1323 on 7/10/2022.
//

#pragma once

#include <Node.h>
#include <Point.h>

#include <tuple>

class Heap {
public:
//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
//  Constructors/Destructors ----------------------------------------------------------------------------------------
//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    Heap();

    Heap(const int &size, const Node *nodes);

    Heap(const Heap &that);

    Heap(Heap &&that) noexcept;

    ~Heap();

//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
//  Public Methods -------------------------------------------------------------------------------------------------
//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    void clipBranch(const int &index);

    void graftBranch(const int &index, const Heap &branch);

    Heap getBranch(const int &index) const;

    void growHeap(const int &growFactor);

    void trimHeap();

//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
//  Getters/Setters ------------------------------------------------------------------------------------------------
//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    int getSize() const;

    int getDepth() const;

    void setNode(const int &index, const Node &node);

    Node getNode(const int &index);

    oprtr getKey(const int &index) const;

    void setVal(const int &index, double value);

    double getVal(const int &index) const;

//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
//  Overloaded Operators -------------------------------------------------------------------------------------------
//  █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    Heap &operator=(const Heap &that);

    Heap &operator=(Heap &&that) noexcept;

private:
    int size_;
    Node *nodes_;
};