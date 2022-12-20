//
// Created by atlas1323 on 9/16/2022.
//

#include "gtest/gtest.h"
#include <Node.h>
#include <Heap.h>
#include "../src/Optimizers/Contender.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

class SelectionTest : public ::testing::Test {
protected:
    void SetUp() override {

        // SET UP POINTS
        double x;
        double y;
        for (int i = -10; i < 10; i++) {
            x = (double) i;
            y = 4.0f * sin(x + 1.0f);
            points.emplace_back(x, y);
        }
        Contender::Points = points;


        // SET UP GOOD CONTENDER
        Node good_nodes[16];
        good_nodes[0] = Node(ROOT);
        for (int i = 1; i < 16; i++)
            good_nodes[i] = Node(BLANK);

        good_nodes[1] = Node(MLT);
        good_nodes[2] = Node(VAL, 3.0f);
        good_nodes[3] = Node(SIN);
        good_nodes[6] = Node(ADD);
        good_nodes[12] = Node(VAR);
        good_nodes[13] = Node(VAL, 1.0f);

        good_con = Contender(16, good_nodes);
        good_con.calcFitness();

        // SET UP POPULATION
        for (int i = 0; i < 20; i++) {
            population.emplace_back();
            population[i].calcFitness();
        }

        population[10] = good_con;


    }

    // variables
    std::vector<Point> points;
    std::vector<Contender> population;
    Contender good_con;

    // methods
};


TEST_F(SelectionTest, GoodSelected) {
    double sum_fit = 0.0f;
    for (auto &i: population) {
        sum_fit += 1.0f / i.getFitness();
    }

    double proportion = (1.0f / good_con.getFitness()) / sum_fit;
    double upper_bound = proportion + 0.1f * proportion;
    double lower_bound = proportion - 0.1f * proportion;
    double count = 0.0f;

    for (int i = 0; i < 100; i++) {
        int pick = Contender::ProportionalSelection(population, sum_fit);
        if (pick == 10)
            count += 0.01f;
    }

//    EXPECT_EQ(count, proportion);
    EXPECT_TRUE(count >= lower_bound && count <= upper_bound);

}

