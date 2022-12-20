//
// Created by atlas1323 on 9/7/2022.
//

#include "gtest/gtest.h"
#include <Node.h>
#include <Heap.h>
#include "../src/Optimizers/Contender.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <string>

class FitnessTest : public ::testing::Test {
protected:
    void SetUp() override {

//        for (int i = -10.0; i < 11.0 ; i++) {
//            points.emplace_back(Point((double)i, (double)i));
//            double y2 = std::pow((double)i, 4);
//            points2.emplace_back(Point((double)i, y2));
//            double y3 = cos(double(i));
//            points3.emplace_back(Point((double)i, y3));
//        }

        for (double i = -10.0; i < 11.0; i += 0.01) {
            points.emplace_back(Point(i, i));
            double y2 = std::pow(i, 4);
            points2.emplace_back(Point(i, y2));
            double y3 = cos(i);
            points3.emplace_back(Point(i, y3));
        }


        Contender::Points = points;

        tree_size = 4;

        Node x_nodes[2];
        x_nodes[0] = Node(ROOT);
        x_nodes[1] = Node(VAR);
        x = Contender(2, x_nodes);
        x.calcFitness();

        // Set up 1x
        Node x1_nodes[tree_size];
        x1_nodes[0] = Node(ROOT);
        x1_nodes[1] = Node(MLT);
        x1_nodes[2] = Node(VAL, 1.0);
        x1_nodes[3] = Node(VAR);
        x1 = Contender(tree_size, x1_nodes);
        x1.calcFitness();

        // Set up 2x
        Node x2_nodes[tree_size];
        x2_nodes[0] = Node(ROOT);
        x2_nodes[1] = Node(MLT);
        x2_nodes[2] = Node(VAL, 2.0);
        x2_nodes[3] = Node(VAR);
        x2 = Contender(tree_size, x2_nodes);
        x2.calcFitness();


        // Set up 3x
        Node x3_nodes[tree_size];
        x3_nodes[0] = Node(ROOT);
        x3_nodes[1] = Node(MLT);
        x3_nodes[2] = Node(VAL, 3.0);
        x3_nodes[3] = Node(VAR);
        x3 = Contender(tree_size, x3_nodes);
        x3.calcFitness();


        // Set up add
        Node add_nodes[tree_size];
        add_nodes[0] = Node(ROOT);
        add_nodes[1] = Node(ADD);
        add_nodes[2] = Node(VAL, 1.0);
        add_nodes[3] = Node(VAR);
        x4 = Contender(tree_size, add_nodes);
        x4.calcFitness();


        // Set up x - 1
        add_nodes[2] = Node(VAL, -1.0);
        x5 = Contender(tree_size, add_nodes);
        x5.calcFitness();


        // Set up x + 2
        add_nodes[2] = Node(VAL, 2.0);
        x6 = Contender(tree_size, add_nodes);
        x6.calcFitness();

        // Set up cosnt
        Node x7_nodes[2];
        x7_nodes[0] = Node(ROOT);
        x7_nodes[1] = Node(VAL, 3.0f);
        x7 = Contender(2, x7_nodes);
        x7.calcFitness();

        Node x8_nodes[tree_size];
        x8_nodes[0] = Node(ROOT);
        x8_nodes[1] = Node(COS);
        x8_nodes[2] = Node(VAR);
        x8_nodes[3] = Node(BLANK);
        x8 = Contender(tree_size, x8_nodes);
        x8.calcFitness();

        Node x9_nodes[tree_size];
        x9_nodes[0] = Node(ROOT);
        x9_nodes[1] = Node(SIN);
        x9_nodes[2] = Node(VAR);
        x9_nodes[3] = Node(BLANK);
        x9 = Contender(tree_size, x9_nodes);
        x9.calcFitness();
    }

    // Variables
    std::vector<Point> points;
    std::vector<Point> points2;
    std::vector<Point> points3;


    Contender x;    // x
    Contender x1;   // 1*x
    Contender x2;   // 2*x
    Contender x3;   // 3*x
    Contender x4;   // x + 1
    Contender x5;   // x - 1
    Contender x6;   // x + 2
    Contender x7;   // 3
    Contender x8;   // cos(x)
    Contender x9;   // sin(x)

    int tree_size;

    // Methods
};

TEST_F(FitnessTest, EvalsCorrectly) {

    // TODO: Infinities work

    // TODO: 0 for
//    FAIL();
    EXPECT_EQ(x7.getFitness(), 6.757711644237764);
    EXPECT_EQ(x2.getFitness(), 6.0553007081949835);
    EXPECT_EQ(x8.getFitness(), 6.09839) << "YO " << std::to_string(x8.getFitness());
    EXPECT_EQ(x9.getFitness(), 6.02586) << "YO " << std::to_string(x9.getFitness());

    std::cout << x7.getFitness() - 6.508968172196472 << std::endl;
    std::cout << x8.getFitness() - 5.821475766585341 << std::endl;


    Contender::Points = points2;


    x.calcFitness();
    x1.calcFitness();
    x2.calcFitness();
    x3.calcFitness();
    x4.calcFitness();
    x5.calcFitness();
    x6.calcFitness();
    x7.calcFitness();
    x8.calcFitness();
    x9.calcFitness();

    EXPECT_EQ(x.getFitness(), 3996.804890576138);
    EXPECT_EQ(x8.getFitness(), 3997.085979267499);

    Contender::Points = points3;

    x.calcFitness();
    x1.calcFitness();
    x2.calcFitness();
    x3.calcFitness();
    x4.calcFitness();
    x5.calcFitness();
    x6.calcFitness();
    x7.calcFitness();
    x8.calcFitness();
    x9.calcFitness();

    std::cout << x.getFitness() << std::endl;

    EXPECT_EQ(x.getFitness(), 6.098388306730562);
    EXPECT_EQ(x8.getFitness(), 0);


}

//TEST_F(FitnessTest, EvalsConsistently) {
////    FAIL();
//}

TEST_F(FitnessTest, EvalsRelativeFitness) {
    // TODO: Evaluates 0 for same function
    EXPECT_EQ(x.getFitness(), 0) << "Did not evaluate x to 0";
    EXPECT_EQ(x1.getFitness(), 0) << "Did not evaluate x1 to 0";
    EXPECT_EQ(x1.getFitness(), x.getFitness()) << "Did not evaluate x1 to x";
    EXPECT_GT(x2.getFitness(), x1.getFitness()) << "Did not evaluate x2 larger than x1";
    EXPECT_GT(x3.getFitness(), x2.getFitness()) << "Did not evaluate x3 larger than x2";

    EXPECT_EQ(x4.getFitness(), x5.getFitness()) << "Is not direction agnostic";
    EXPECT_EQ(2.0 * x4.getFitness(), x6.getFitness()) << "Math";
    EXPECT_GT(x6.getFitness(), x4.getFitness()) << "Did not evaluate x6 larger than x4";
}