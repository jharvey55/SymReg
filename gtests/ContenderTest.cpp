//
// Created by atlas1323 on 6/25/2022.
//

#include "gtest/gtest.h"
#include <Node.h>
#include "../src/Optimizers/Contender.h"
#include <cmath>
#include <iostream>

class ContenderTest : public ::testing::Test
{
protected:

    void SetUp() override {
        
        big_size = 32;
        Node* big_nodes = new Node[big_size];
        big_nodes[1] = Node(DIV);
        big_nodes[2] = Node(SIN);
        big_nodes[3] = Node(COS);
        big_nodes[4] = Node(SUB);
        big_nodes[8] = Node(MLT);
        big_nodes[16] = Node(VAL, 2.0f);
        big_nodes[17] = Node(VAR);
        big_nodes[9] = Node(VAL, 1.0f);
        big_nodes[6] = Node(ADD);
        big_nodes[12] = Node(VAR);
        big_nodes[13] = Node(VAL, M_PI);
        bigEq = Contender(big_size, big_nodes);
        delete[] big_nodes;
        

        small_size = 4;
        Node* cos_nodes = new Node[small_size];
        cos_nodes[1] = Node(COS);
        cos_nodes[2] = Node(VAR);
        cos_contender = Contender(small_size, cos_nodes);
        delete[] cos_nodes; 


        Node* sin_nodes = new Node[small_size];
        sin_nodes[1] = Node(SIN);
        sin_nodes[2] = Node(VAR);
        sin_contender = Contender(small_size, sin_nodes);
        delete[] sin_nodes; 


        Node* mlt_nodes = new Node[small_size];
        mlt_nodes[1] = Node(MLT);
        mlt_nodes[2] = Node(VAR);
        mlt_nodes[3] = Node(VAL, 1.0f);
        mlt_contender = Contender(small_size, mlt_nodes);
        delete[] mlt_nodes;

        Node* div_nodes = new Node[small_size];
        div_nodes[1] = Node(DIV);
        div_nodes[2] = Node(VAR);
        div_nodes[3] = Node(VAL, 2.0f);
        div_contender = Contender(small_size, div_nodes);
        delete[] div_nodes;

        Node* add_nodes = new Node[small_size];
        add_nodes[1] = Node(ADD);
        add_nodes[2] = Node(VAR);
        add_nodes[3] = Node(VAL, 1.0f);
        add_contender = Contender(small_size, add_nodes);
        delete[] add_nodes; 

        Node* sub_nodes = new Node[small_size];
        sub_nodes[1] = Node(SUB);
        sub_nodes[2] = Node(VAR);
        sub_nodes[3] = Node(VAL, 1.0f);
        sub_contender = Contender(small_size, sub_nodes);
        delete[] sub_nodes;


        const_size = 2;

        Node* var_nodes = new Node[const_size];
        var_nodes[1] = Node(VAR);
        var_contender = Contender(const_size, var_nodes);
        delete[] var_nodes;

        Node* val_nodes = new Node[const_size];
        val_nodes[1] = Node(VAL, 7.0f);
        val_contender = Contender(const_size, val_nodes);
        delete[] val_nodes;


    }

    // Variables
    Contender bigEq;
    Contender cos_contender;
    Contender sin_contender;
    Contender mlt_contender;
    Contender div_contender;
    Contender add_contender;
    Contender sub_contender;
    Contender var_contender;
    Contender val_contender;

    int big_size;
    int const_size;
    int small_size;

    // double* x_vals;


    // Methods
    double rms(const Point * data, int num_points, auto equation) {
        double sum = 0.0f;
        double diff;
        for(int i = 0; i < num_points; i++) {
            diff = data[i].y - equation(data[i].x);
            sum += std::pow(diff, 2);
        }

        // Assign the rms to fitness
        return std::sqrt(sum/num_points);
    }

    void fillData(Point * target, const double * x_series, int size, auto equation) {
        for (int x  = 0; x < size; x++)
            target[x] = Point(x_series[x], equation(x));
    }


};

TEST_F(ContenderTest, ValidConstructorTest) {
    EXPECT_EQ(0, 0);
    Contender test = Contender();
    // double sizeof
    //    FAIL();
    // TODO: Check that size is set correctly
    // TODO: Check that heap is built (if node)
    // TODO: Check if a string is produced
}

TEST_F(ContenderTest, EqParseTest) {
    double x_vals[] = {-100.0f, -1*M_PI, -1.0f, -0.5f, 0.0f, 0.5f, 1.0f, M_PI, 100.0f};

    // TODO: Ensure all parent nodes work
    // TODO: Ensure all termini work
    // TODO:

    auto cos_eq = [&](double x){return cos(x);};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(cos_contender.EqParser(1, x_val), cos_eq(x_val)) << "COS(" << x_val << ") didn't work";
    }
    auto sin_eq = [&](double x){return sin(x);};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(sin_contender.EqParser(1, x_val), sin_eq(x_val)) << "SIN(" << x_val << ") didn't work";
    }
    auto mlt_eq = [&](double x){return x*1.0f;};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(mlt_contender.EqParser(1, x_val), mlt_eq(x_val)) << "MLT: " << x_val << " didn't work";
    }
    auto div_eq = [&](double x){return x/2.0f;};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(div_contender.EqParser(1, x_val), div_eq(x_val)) << "DIV: " << x_val << " didn't work";
    }
    auto add_eq = [&](double x){return x+1.0f;};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(add_contender.EqParser(1, x_val), add_eq(x_val)) << "ADD: " << x_val << " didn't work";
    }
    auto sub_eq = [&](double x){return x-1.0f;};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(sub_contender.EqParser(1, x_val), sub_eq(x_val)) << "SUB: " << x_val << " didn't work";
    }
    auto var_eq = [&](double x){return x;};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(var_contender.EqParser(1, x_val), var_eq(x_val)) << "VAR: " << x_val << " didn't work";
    }

    for(double & x_val : x_vals)
    {
        EXPECT_EQ(val_contender.EqParser(1, x_val), 7.0f) << "VAL: " << x_val << " didn't work";
    }
    auto big_eq = [&](double x){return sin(2*x-1)/cos(x + M_PI);};
    for(double & x_val : x_vals)
    {
        EXPECT_EQ(bigEq.EqParser(1, x_val), big_eq(x_val)) << "Full Stack: " << x_val << " didn't work";
    }
}

TEST_F(ContenderTest, ErrorTest) {
    int size = 9;
    double x_vals[] = {-100.0f, -1*M_PI, -1.0f, -0.5f, 0.0f, 0.5f, 1.0f, M_PI, 100.0f};
    auto data = new Point[size];
    auto uEq = [&](double x){return -1.0f;};
    auto uData = new Point[size];
    fillData(uData, x_vals, size, uEq);

    auto cos_eq = [&](double x){return cos(x);};
    fillData(data, x_vals, size, cos_eq);
    cos_contender.calcFitness(data, size);
    EXPECT_EQ(cos_contender.getFitness(), rms(data, size, cos_eq));
    cos_contender.calcFitness(uData, size);
    EXPECT_EQ(cos_contender.getFitness(), rms(uData, size, cos_eq));
//    EXPECT_EQ(cos_contender.getFitness(), 1.58928);


    if (cos_contender.getFitness() > 1.58927 && cos_contender.getFitness() < 1.58928)
            SUCCEED();
    else
        FAIL() << "VECNA got me";

    auto sin_eq = [&](double x){return sin(x);};
    fillData(data, x_vals, size, sin_eq);
    sin_contender.calcFitness(data, size);
    EXPECT_EQ(sin_contender.getFitness(), rms(data, size, sin_eq));
    sin_contender.calcFitness(uData, size);
    EXPECT_EQ(sin_contender.getFitness(), rms(uData, size, sin_eq));

    auto mlt_eq = [&](double x){return x*1.0f;};
    fillData(data, x_vals, size, mlt_eq);
    mlt_contender.calcFitness(data, size);
    EXPECT_EQ(mlt_contender.getFitness(), rms(data, size, mlt_eq));
    mlt_contender.calcFitness(uData, size);
    EXPECT_EQ(mlt_contender.getFitness(), rms(uData, size, mlt_eq));

    auto div_eq = [&](double x){return x/2.0f;};
    fillData(data, x_vals, size, div_eq);
    div_contender.calcFitness(data, size);
    EXPECT_EQ(div_contender.getFitness(), rms(data, size, div_eq));
    div_contender.calcFitness(uData, size);
    EXPECT_EQ(div_contender.getFitness(), rms(uData, size, div_eq));

    auto add_eq = [&](double x){return x+1.0f;};
    fillData(data, x_vals, size, add_eq);
    add_contender.calcFitness(data, size);
    EXPECT_EQ(add_contender.getFitness(), rms(data, size, add_eq));
    add_contender.calcFitness(uData, size);
    EXPECT_EQ(add_contender.getFitness(), rms(uData, size, add_eq));

    auto sub_eq = [&](double x){return x-1.0f;};
    fillData(data, x_vals, size, sub_eq);
    sub_contender.calcFitness(data, size);
    EXPECT_EQ(sub_contender.getFitness(), rms(data, size, sub_eq));
    sub_contender.calcFitness(uData, size);
    EXPECT_EQ(sub_contender.getFitness(), rms(uData, size, sub_eq));

    auto var_eq = [&](double x){return x;};
    fillData(data, x_vals, size, var_eq);
    var_contender.calcFitness(data, size);
    EXPECT_EQ(var_contender.getFitness(), rms(data, size, var_eq));
    var_contender.calcFitness(uData, size);
    EXPECT_EQ(var_contender.getFitness(), rms(uData, size, var_eq));

    auto const_eq = [&](double x){return 7.0f;};
    fillData(data, x_vals, size, const_eq);
    val_contender.calcFitness(data, size);
    EXPECT_EQ(val_contender.getFitness(), rms(data, size, const_eq));
    val_contender.calcFitness(uData, size);
    EXPECT_EQ(val_contender.getFitness(), rms(uData, size, const_eq));

    auto big_eq = [&](double x){return sin(2*x-1)/cos(x + M_PI);};
    fillData(data, x_vals, size, big_eq);
    bigEq.calcFitness(data, size);
    EXPECT_EQ(bigEq.getFitness(), rms(data, size, big_eq));
    bigEq.calcFitness(uData, size);
    EXPECT_EQ(bigEq.getFitness(), rms(uData, size, big_eq));

    delete[] data;
    delete[] uData;
}

TEST_F(ContenderTest, ToStringTest) {
    EXPECT_EQ(0, 0);
}

//
//TEST_F(ContenderTest, ClipBranchTest) {
//    auto [branch_size, branch] = bigEq.
//}

TEST_F(ContenderTest, MutateTest) {
    int blank_count = 0;
    for (int i = 0; i < bigEq.getSize(); i++) {
        if (bigEq.getNode(i).key == BLANK)
            blank_count++;
    }

    ASSERT_EQ(20, blank_count);
    bigEq.treePrint();
    bigEq.Mutate(6, ADD);
    bigEq.treePrint();
//    FAIL();

    EXPECT_EQ(32, bigEq.getSize());
    blank_count = 0;
    for (int i = 0; i < bigEq.getSize(); i++) {
        if (bigEq.getNode(i).key == BLANK)
            blank_count++;
    }
    ASSERT_EQ(18, blank_count);

}

TEST_F(ContenderTest, CrossTest) {
    Contender copy1 = bigEq;
    Contender copy2 = bigEq;
    Contender temp3 = Contender();
    Contender temp4 = Contender();

    Contender::Crossover(copy1, copy2, 6, temp3, 3, temp4);

    for (int i = 0; i < temp3.getSize(); i++) {
        std::cout << i << " " << temp3.getNode(i).key << std::endl;
    }

    std::cout << "\n\n" << std::endl;

    for (int i = 0; i < temp4.getSize(); i++) {
        std::cout << i << " " << temp4.getNode(i).key << std::endl;
    }

    temp4.treePrint();

    Contender::RandCrossover(copy1, copy2, temp3, temp4);

    for (int i = 0; i < temp3.getSize(); i++) {
        std::cout << i << " " << temp3.getNode(i).key << std::endl;
    }

    std::cout << "\n\n" << std::endl;

    for (int i = 0; i < temp4.getSize(); i++) {
        std::cout << i << " " << temp4.getNode(i).key << std::endl;
    }

    temp4.treePrint();

    Contender::Crossover(copy1, copy2, 1, temp3, 1, temp4);

    for (int i = 0; i < temp3.getSize(); i++) {
        std::cout << i << " " << temp3.getNode(i).key << std::endl;
    }

    std::cout << "\n\n" << std::endl;

    for (int i = 0; i < temp4.getSize(); i++) {
        std::cout << i << " " << temp4.getNode(i).key << std::endl;
    }

    temp4.treePrint();
    std::cout << temp4.getSize() << std::endl;


}
