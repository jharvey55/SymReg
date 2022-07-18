//
// Created by atlas1323 on 6/25/2022.
//

#pragma once

#include <Node.h>
#include <Point.h>
#include <Heap.h>

#include <functional>
#include <string>
#include <vector>
#include <tuple>



class Contender {
public:
    static std::vector<Point> Points;

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Constructors/Destructors ----------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    Contender();

    Contender(const int &size, const Node *nodes);

    Contender(const Contender &that);

    Contender(Contender &&that) noexcept;

    ~Contender();

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Getters/Setters -------------------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    int getSize() const;

    void setNodes(const int &size, const Node *nodes);

    void setNode(Node &node, int index);

    Node getNode(const int &index);

    double getFitness() const;

    // Logging/Display methods
    std::string getEqString();

    std::string LogString();

    void treePrint();


    // Static variable getters/setters
    static int getEvalCount();

    static void ResetEvaluationCount();

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Member functions ------------------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    double EqParser(int index, const double &x);

    // std::function<double (double)> parseFun(int index);

    // Node Generation and field updates
    void calcFitness(const Point *data, int num_points);

    void calcFitness();

    void randy(const int &index);

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Optomization tools ----------------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    // Spot Mutations
    void valueMutate(const int &index);

    // Section Mutations
    void inversionMutate();

    void scrambleMutate();

    void swapMutate();

    // Mutate broad strokes
    void Mutate(const int &index, const oprtr &op);

    // TODO: GP Tools {Selection, Crossover}
    // GP Tools - Selection

    // GP Tools - Crossover

    // GP Tools - Pruning

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Overloaded Operators --------------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    bool operator<(const Contender &that) const;

    Contender &operator=(const Contender &that);

    Contender &operator=(Contender &&that) noexcept;


private:
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Private Member Elements -----------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

//    int size_;
//    Node *nodes_;
    double fitness_;
    Heap tree_;

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Private Member Functions ----------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    std::string buildEqString_(int index);


    std::string prettyString_(int index);

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Private Static Member Elements ----------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    static std::random_device rand_dev_;
    static std::mt19937 rng_;
    static std::uniform_int_distribution<> coin_flip_;
    static int evaluations_;

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Private Static Member functions ---------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

};
