/*
 * test.cpp
 * COMP15
 * Spring 2019
 * 
 * Name: Yves Chen
 * Date: 2/26/19
 * Purpose: unit test for the Trie class using google Test 
 *
 */

#include "Trie.h"
#include <gtest/gtest.h>
#include <limits>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

class Trietests : public ::testing::Test {
 protected:
 
};

TEST_F(Trietests, insert){
	Trie test;
	std::cout << "here" << std::endl;
	//test.insert("ATTGC");
}