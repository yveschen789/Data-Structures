/*
 * BinarySearchTree-unittest.cpp
 * COMP15
 * Spring 2019
 * 
 * Name: Yves Chen
 * Date: 2/26/19
 * Purpose: unit test for the Binary Search Tree class using google Test 
 *
 */

#include "BinarySearchTree.h"
#include <gtest/gtest.h>
#include <limits>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;


class BSTtests : public ::testing::Test {
protected:
/**
 * This a TEST Fixture in Google Test. It is used to define data that
 * many tests can use. Each test gets its own copy of the same data.
 * Here, We define a testdata vector with some predefined numbers
 * The array is initialized in the constructor. No clean up is needed.
**/
        const std::vector<int> testdata;
        BSTtests()
            : testdata{258,  579,  814, -566, -686, -3,  -600,
                       382,  -562, -55, -768, 172,  252, 397,
                       -155, -898, 430, -520, 154,  255} {}
};

/*
 * Unit testing for find_min
 */
TEST_F(BSTtests, find_min) {
        BinarySearchTree bst;
        constexpr int    errorVal    = std::numeric_limits<int>::min();
        constexpr int    testdataMin = -898;

        // We start testng an edge case: find the 
        // minimum in an empty tree
        EXPECT_EQ(bst.find_min(), errorVal)
            << "find_min on an empty tree should"
               " return INT_MIN";

        // edge case: root is min
        bst.insert(0);
        EXPECT_EQ(bst.find_min(), 0);

        for (int num : testdata)
                bst.insert(num);

        // typical usage: we look for minimum after inserting many numbers
        EXPECT_EQ(bst.find_min(), testdataMin);

        //bst.print_tree();
}


//unit testing to find max
TEST_F(BSTtests, find_max) {
        
        BinarySearchTree bst;
        constexpr int    errorVal    = std::numeric_limits<int>::min();
        constexpr int    testdataMax = 814; //the max number in testdata

        //edge case of testing finding the max of an empty tree
        EXPECT_EQ(bst.find_max(), errorVal)
            << "find_max on empty tree should"
               "return INT_MIN";        

        //inserting testdata elements
        for (int num : testdata)
            bst.insert(num);

        // the max should be equal to the max of the numbers inserted
        EXPECT_EQ(bst.find_max(), testdataMax);

}


// testing that insert works
TEST_F(BSTtests, insert){
        
        //rudimentary and insert simple values
        BinarySearchTree bst;
        bst.insert (0);
        bst.insert (1);
        bst.insert (4);
        bst.insert (7);

        //mimics linked list
        bst.print_tree();

        //checks if the right number of nodes as insert,
        //node_count() traverses the tree
        EXPECT_EQ(bst.node_count(), 4);
       

   
}

// unit tests for remove function
TEST_F(BSTtests, remove){
        
        BinarySearchTree bst;

        //inserting elements from test data
        for (int num : testdata)
            bst.insert(num);

        //first check if the tree contains -55, which was inserted
        EXPECT_TRUE(bst.contains(-55));

        //removed element -55
        bst.remove(-55);

        //checks after removal if -55 is there. should be false
        EXPECT_FALSE(bst.contains(-55));
}

// unit tests for if the node count function properly counts
TEST_F(BSTtests, node_count){
        
        BinarySearchTree bst;

        //inserts all the test data elements -- 20 elements
        for (int num : testdata)
            bst.insert(num);

        //the function should return the amount of elements, 20
        EXPECT_EQ(bst.node_count(), 20);
}

// unit tests for if the count total properly counts all the nodes data
TEST_F(BSTtests, count_total){

        BinarySearchTree bst;

        //inserts all the test data elements
        for (int num : testdata)
        bst.insert(num);

        //the function should return the total sum of elements data, -1120
        EXPECT_EQ(bst.count_total(), -1120);
}


