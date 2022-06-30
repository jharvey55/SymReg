//
// Created by atlas1323 on 6/25/2022.
//

#include "gtest/gtest.h"
#include <Node.h>
#include <Contender.h>
#include <cmath>
#include <iostream>


class ContenderTest : public ::testing::Test
{
protected:

    void SetUp() override {

        // x_vals = new double[7];
        // x_vals[0] = -100.0f;
        // x_vals[1] = -1.0f;
        // x_vals[2] = -0.05f;
        // x_vals[3] = 0.0f;
        // x_vals[4] = 0.05f;
        // x_vals[5] = 1.0f;
        // x_vals[6] = 100.0f;

        big_size = 32;
        Node* big_nodes = new Node[big_size];
        big_nodes[1] = Node(DIV);
        big_nodes[2] = Node(SIN);
        big_nodes[3] = Node(COS);
        big_nodes[4] = Node(SUB);
        big_nodes[8] = Node(MLT);
        big_nodes[16] = Node(VAL, 2.0f);
        big_nodes[17] = Node(VAR);
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
};

TEST_F(ContenderTest, ValidConstructorTest) {
    // EXPECT_EQ(0, 0);
    Contender test = Contender();
    // double sizeof
    //    FAIL();
    // TODO: Check that size is set correctly
    // TODO: Check that heap is built (if node)
    // TODO: Check if a string is produced
}

TEST_F(ContenderTest, EqParseTest) {
    // FAIL();
    EXPECT_EQ(0, 0);
    double x_vals[] = {-100.0f, -1*M_PI, -1.0f, -0.5f, 0.0f, 0.5f, 1.0f, M_PI, 100.0f};

    // TODO: Ensure all parent nodes work
    // TODO: Ensure all termini work
    // TODO: 
    EXPECT_EQ(cos_contender.EqParser(1, 0.0f), 1.0f) << "COS didn't work";
    EXPECT_EQ(sin_contender.EqParser(1, 0.0f), 0.0f) << "SIN didn't work";
    EXPECT_EQ(mlt_contender.EqParser(1, 5.0f), 5.0f) << "MLT didn't work";
    EXPECT_EQ(div_contender.EqParser(1, 4.0f), 2.0f) << "DIV didn't work";
    EXPECT_EQ(add_contender.EqParser(1, 0.0f), 1.0f) << "ADD didn't work";
    EXPECT_EQ(sub_contender.EqParser(1, 0.0f), -1.0f)  << "SUB didn't work";
    EXPECT_EQ(var_contender.EqParser(1, 1.0f), 1.0f)  << "VAR didn't work";
    EXPECT_EQ(val_contender.EqParser(1, 7.0f), 7.0f) << "VAL didn't work";


}

TEST_F(ContenderTest, ToStringTest) {
    EXPECT_EQ(0, 0);
}

