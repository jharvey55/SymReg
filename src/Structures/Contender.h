//
// Created by atlas1323 on 6/25/2022.
//

#pragma once

#include <Node.h>
#include <Point.h>

#include <functional>
#include <string>
#include <vector>
#include <tuple>



class Contender {
public:
    static std::vector<Point> Points;

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

    double getFitness() const;

    // Logging/Display methods
    std::string getEqString();
    std::string LogString();
    void treePrint();

    // Static variable getters/setters
    static int getEvalCount();
    static void ResetEvaluationCount();

    // Member functions ------------------------------------------------------------------
    double EqParser(int index, const double& x);
    // std::function<double (double)> parseFun(int index);

    void calcFitness(const Point * data, int num_points);
    void calcFitness();
    void randy(int index);




    // Overloaded operators
    bool operator<(const Contender& that) const;
    Contender& operator=(const Contender& that);
    Contender& operator=(Contender&& that) noexcept;



private:
    // Private Member Elements -----------------------------------------------------------
    int size_;
    Node* nodes_;
    double fitness_;

    // Private Member Functions ----------------------------------------------------------
    std::string buildEqString_(int index);
    std::string prettyString_(int index);

    // Heap Management
    void growHeap_(int growFactor);
    void swapBranch_(const int& index);
    void clipBranch_(const int& index);
    void graftBranch_(const int& index, const int& branch_size, const Node * branch);
    std::tuple<int, Node*> getBranch_( const int& index);

    // Private Static Member Elements ----------------------------------------------------
    static std::random_device rand_dev_;
    static std::mt19937 rng_;
    static std::uniform_int_distribution<> coin_flip_;
    static int evaluations_;

    // Private Static Member functions ---------------------------------------------------
    static int growthSize_(const int& depth);







};
