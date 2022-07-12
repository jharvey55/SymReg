//
// Created by atlas1323 on 7/10/2022.
//

#include "gtest/gtest.h"
#include <Node.h>
#include <Heap.h>
#include <cmath>
#include <iostream>

class HeapTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Build testHeap
        Node testHeapNodes[32];
        for (int i = 1; i < 16; ++i)
            testHeapNodes[i] = Node(ADD);
        for (int i = 16; i < 32; i++)
            testHeapNodes[i] = Node(VAL, 1.0f);

        testHeap = Heap(32, testHeapNodes);

        // Build branch
        Node branchNodes[8];
        branchNodes[1] = Node(SUB);
        branchNodes[2] = Node(SUB);
        branchNodes[3] = Node(VAL, 2.0f);
        branchNodes[4] = Node(VAL, 2.0f);
        branchNodes[5] = Node(VAL, 2.0f);
        branchNodes[6] = Node(BLANK);
        branchNodes[7] = Node(BLANK);

        branch = Heap(8, branchNodes);

        // Build Trim Heap
        Node trimNodes[8];
        trimNodes[1] = Node(ADD);
        trimNodes[2] = Node(VAL, 1.0f);
        trimNodes[3] = Node(VAL, 1.0f);

        for (int i = 4; i < 8; i++)
            trimNodes[i] = Node(BLANK);
        trimHeap = Heap(8, trimNodes);
    }

    Heap testHeap;
    Heap branch;
    Heap trimHeap;
};

TEST_F(HeapTest, SetNodeTest) {
    testHeap.setNode(8, Node(SUB));
    EXPECT_EQ(testHeap.getNode(8).key, SUB);

    testHeap.setNode(17, Node(VAL, 2.0f));
    EXPECT_EQ(testHeap.getNode(17).value, 2.0f);
}

TEST_F(HeapTest, TrimTest) {
    ASSERT_EQ(trimHeap.getSize(), 8) << " Failed to initialize trimHeap correctly";
    trimHeap.trimHeap();
    EXPECT_EQ(trimHeap.getSize(), 4);
    branch.trimHeap();
    EXPECT_EQ(branch.getSize(), 8);
}

TEST_F(HeapTest, GraftRootTest) {
    // TESTS GRAFTING AT START
    testHeap.graftBranch(1, branch);
    testHeap.trimHeap();

    ASSERT_EQ(testHeap.getSize(), branch.getSize());
    for (int i = 0; i < testHeap.getSize(); ++i) {
        EXPECT_EQ(testHeap.getNode(i).key, branch.getNode(i).key)
                            << " " << i << ": location differed between testHeap and branch " << testHeap.getNode(i).key
                            <<
                            ", " << branch.getNode(i).key;
    }
}

TEST_F(HeapTest, GraftMidTest) {
    testHeap.graftBranch(3, branch);
    ASSERT_EQ(testHeap.getSize(), 32);
    int blank_count = 0;
    for (int i = 0; i < testHeap.getSize(); i++) {
        if (testHeap.getNode(i).key == BLANK)
            blank_count++;
    }
    EXPECT_EQ(blank_count, 10);
}

TEST_F(HeapTest, GraftGrowTest) {
    testHeap.graftBranch(9, branch);
    ASSERT_EQ(testHeap.getSize(), 64);
    int blank_count = 0;
    for (int i = 0; i < testHeap.getSize(); i++) {
        if (testHeap.getNode(i).key == BLANK)
            blank_count++;
    }
    EXPECT_EQ(blank_count, 30);
    EXPECT_EQ(testHeap.getNode(9).key, SUB);
    EXPECT_EQ(testHeap.getNode(18).key, SUB);
    EXPECT_EQ(testHeap.getNode(19).key, VAL);
    EXPECT_EQ(testHeap.getNode(19).value, 2.0f);
    EXPECT_EQ(testHeap.getNode(36).key, VAL);
    EXPECT_EQ(testHeap.getNode(36).value, 2.0f);
    EXPECT_EQ(testHeap.getNode(37).key, VAL);
    EXPECT_EQ(testHeap.getNode(37).value, 2.0f);
}

TEST_F(HeapTest, ClipTest) {
    Heap testCopy;
    int root;
    int diff;
    int blank_count;

    // Right branch
    testCopy = Heap(testHeap);
    root = 3;
    testCopy.clipBranch(root);
    ASSERT_EQ(testCopy.getSize(), 32);
    diff = testCopy.getDepth() - (int) log2(root);
    for (int i = 0; i < diff; i++) {
        for (int j = 0; j < i; j++)
            EXPECT_EQ(testCopy.getNode(root + j).key, BLANK);
        root *= 2;
    }
    blank_count = 0;
    for (int i = 0; i < testCopy.getSize(); i++) {
        if (testCopy.getNode(i).key == BLANK)
            blank_count++;
    }
    EXPECT_EQ(blank_count, 15);

    // Mid branch
    testCopy = Heap(testHeap);
    root = 5;
    testCopy.clipBranch(root);
    ASSERT_EQ(testCopy.getSize(), 32);
    diff = testCopy.getDepth() - (int) log2(root);
    for (int i = 0; i < diff; i++) {
        for (int j = 0; j < i; j++)
            EXPECT_EQ(testCopy.getNode(root + j).key, BLANK);
        root *= 2;
    }
    blank_count = 0;
    for (int i = 0; i < testCopy.getSize(); i++) {
        if (testCopy.getNode(i).key == BLANK)
            blank_count++;
    }
    EXPECT_EQ(blank_count, 7);
}

TEST_F (HeapTest, GetBranchTest) {
    Heap testBranch;
    testBranch = testHeap.getBranch(2);
    EXPECT_EQ(testBranch.getSize(), 16);
    EXPECT_EQ(testBranch.getNode(15).key, 1);

    testBranch = branch.getBranch(3);
    EXPECT_EQ(testBranch.getSize(), 2);
    EXPECT_EQ(testBranch.getNode(1).key, 1);

    testHeap.clipBranch(3);
    testBranch = testHeap.getBranch(3);
    EXPECT_EQ(testBranch.getSize(), 2);
}