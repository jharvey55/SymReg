//
// Created by atlas1323 on 6/25/2022.
//

#pragma once

#include <Node.h>
#include <Point.h>

#include <functional>
#include <string>

class Contender {
public:
    // Constructors/Destructors
    Contender();
    Contender(const int& size, const Node *nodes);
    Contender(const Contender& that);
    Contender(Contender&& that) noexcept;
    ~Contender();

    // Getters/Setters -------------------------------------------------------------------
    int getSize() const;
    void setSize(int size);

    Node *getNodes() const;
    void setNodes(Node *nodes);
    void setNode(Node& node, int index);
    std::string getEqString();
    double getFitness() const;
    std::string LogString();

    // Member functions ------------------------------------------------------------------
    double EqParser(int index, const double& x);
    // std::function<double (double)> parseFun(int index);

    void growHeap();
    void calcFitness(const Point * data, int num_points);
    void randy(int index);




    // Overloaded operators
    bool operator<(const Contender& that);
    Contender& operator=(const Contender& that);
    Contender& operator=(Contender&& that) noexcept;



private:
    // Private Member Elements -----------------------------------------------------------
    int size_;
    Node* nodes_;
    double fitness_;

    // Private Member Functions ----------------------------------------------------------
    std::string buildEqString_(int index);

    // Private Static Member Elements ----------------------------------------------------
    static std::random_device rand_dev_;
    static std::mt19937 rng_;
    static std::uniform_int_distribution<> coin_flip_;
    static int evaluations_;

    // Private Static Member functions ---------------------------------------------------
    static int growthSize_(const int& depth);







};
