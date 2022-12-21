//
// Created by atlas1323 on 6/25/2022.
//

#pragma once

#include "Node.h"
#include "Point.h"
#include "Heap.h"
#include "DataLog.h"

#include <functional>
#include <string>
#include <vector>
#include <tuple>


class Contender {
public:
    static std::vector<Point> Points;
    static DataLog logger;

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

    std::string getHeapString();

    std::string LogString();

    void treePrint();


    // Static variable getters/setters
    static int getEvalCount();

    static void ResetEvaluationCount();

    static double DiversityComp(const Contender &A, const Contender &B, const std::vector<Point> &points);

    static void PopDivserity(const std::vector<Contender> &pop, const std::vector<Point> &points);

    static void PopDivserity(const std::vector<std::vector<Contender>> &pop, const std::vector<Point> &points);




    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Member functions ------------------------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

    double EqParser(const int &index, const double &x) const;

    // std::function<double (double)> parseFun(int index);

    // Node Generation and field updates
    void calcFitness(const Point *data, int num_points);

    double testFitness(const std::vector<Point> &sub_series);

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

    bool safeMutate(int &index, const oprtr &mutKey);

    void randMutate();

    // TODO: GP Tools {Selection, RandCrossover}
    // GP Tools - Selection

    // GP Tools - RandCrossover
    static void RandCrossover(const Contender &Parent1, const Contender &Parent2, Contender &child1, Contender &child2);

    static void Crossover(const Contender &Parent1, const Contender &Parent2, const int &index1, Contender &child1,
                          const int &index2, Contender &child2);

    static int ProportionalSelection(const std::vector<Contender> &population, const double &sum_fit);



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
    static std::uniform_int_distribution<> key_range_;

    static int evaluations_;

    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // Private Static Member functions ---------------------------------------------------------------------------------
    // █████████████████████████████████████████████████████████████████████████████████████████████████████████████████

};

