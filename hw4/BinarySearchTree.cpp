/*
 * BinarySearchTree.cpp
 */

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>

#include "BinarySearchTree.h"

using namespace std;


//input: nothing
//returns: nothing
//purpose: sets the variable pointer root to null
BinarySearchTree::BinarySearchTree()
{
        root = nullptr;
}

//input: nothing
//returns: nothing
//purpose: deletes the tree and sets the variable pointer root to null
BinarySearchTree::~BinarySearchTree()
{
        // walk tree in post-order traversal and delete
        post_order_delete(root);
        root = NULL;   // not really necessary, since the tree is going 
                       // away, but might want to guard against someone
                       // using a pointer after deleting
}

//input: pointer to Node, usually root
//returns: nothing
//purpose: recurses and deletes all nodes then sets root to null
void BinarySearchTree::post_order_delete(Node *node)
{
        if (node == nullptr)
            return;
        if (node->left == nullptr and node->right == nullptr){
            delete node;
            return;
        }
        post_order_delete(node->left);
        post_order_delete(node->right);
        root = nullptr;
}

// copy constructor
BinarySearchTree::BinarySearchTree(const BinarySearchTree &source)
{
        root = pre_order_copy(source.root);
}

// assignment overload
BinarySearchTree &BinarySearchTree::operator= (const BinarySearchTree &source)
{
    if (this != &source){
        post_order_delete(root);
        root = pre_order_copy(source.root);
        return *this;
    }
    else
        return *this;
}

//input: Node pointer
//returns: Node pointer
//purpose: creates a new set of nodes (tree) that is a copy of the input tree
Node *BinarySearchTree::pre_order_copy(Node *node) const
{
        
        if (node == NULL)
                return NULL;
        Node *new_node = new Node();
        new_node->data = node->data;
        new_node->count = node->count;
        new_node->left = pre_order_copy(node->left);
        new_node->right = pre_order_copy(node->right);

        return new_node;


}

//input: nothing
//returns: an int
//purpose: calls find_min (private) and returns an int (data of node)
int BinarySearchTree::find_min() const
{
        if (root == NULL)
                return INT_MIN;
        return find_min(root)->data;
}

//input: node pointer
//returns: node pointer
//purpose: called by public function and takes root and loops left
// until it finds the minimum leaf and returns it
Node *BinarySearchTree::find_min(Node *node) const
{
        // TODO: Students write code here
        while (node->left != nullptr)
            node = node->left;
        return node;

}

//input: nothing
//returns: an int
//purpose: public function that calls find_max passing in root, and returns
//node returned' data
int BinarySearchTree::find_max() const
{
        // TODO: Students write code here
        if (root == NULL)
            return INT_MIN;
        return find_max(root)->data;
}

//input: node pointer
//returns: node pointer
//purpose: loops right until it finds the max value node
Node *BinarySearchTree::find_max(Node *node) const
{
        // TODO: Students write code here
        while (node->right != nullptr)
            node = node->right;
        return node;
}

//input: an int
//returns: a bool
//purpose: checks if tree is null and calls private function
bool BinarySearchTree::contains(int value) const
{
        if (root == NULL)
            return false;
        return contains(root, value);
}

//input: a node pointer and the int that it searches for
//returns: a bool
//purpose: recurses through the tree, going left or right depending on if value
//is less or larger than the node data and returns if it finds a equal node
bool BinarySearchTree::contains(Node *node, int value) const
{
        if (node == NULL)
            return false;
        if (node->data == value)
            return true;
        if (value < node->data)
            return contains(node->left, value);
        if (value > node->data)
            return contains(node->right, value);

        return false;
}

//input: int
//returns: nothing
//purpose: calls private function and passes int value
void BinarySearchTree::insert(int value)
{
        insert(root, NULL, value);
}

//input: node pointer, node pointer, and int
//returns: nothing
//purpose: checks if the node is null, that will happen at some point while
//code recurses and goes deeper down the tree. Then it creates the node and
//sets its int to be the data of the node and sets the parent path to complete
//tree
void BinarySearchTree::insert(Node *node, Node *parent, int value)
{

        if (node == NULL){
            Node *new_node = new Node();
            new_node->data = value;
            new_node->left = NULL;
            new_node->right = NULL;
            new_node->count = 1;
            if (root == NULL)
                root = new_node;
            if (parent != NULL and value < parent->data)
                parent->left = new_node;
            if (parent != NULL and value > parent->data)
                parent->right = new_node;
            return;
        }

        if (value > node->data)
            insert(node->right, node, value);
        if (value < node->data)
            insert(node->left, node, value);
        if (value == node->data){
            node->count += 1;
            return;
        }
}


//input: int value
//returns: a bool
//purpose: public functon that calls private function remove and passes the int
bool BinarySearchTree::remove(int value)
{
        return remove(root, NULL, value);
}


//input: node pointer, node pointer, int
//return: a bool
//purpose: recurses until it finds node to delete
//while deleting, it calls three functions for three different cases
bool BinarySearchTree::remove(Node *node, Node *parent, int value)
{
        if (node == NULL)
            return false;
        if (value > node->data)
            return remove(node->right, node, value);
        if (value < node->data)
            return remove(node->left, node, value);
        if (value == node->data){
            if (node->count > 1){
                node->count -= 1;
                return true;
            }
            else {
                if (node->left == NULL and node->right == NULL){
                    removeLeaf(node, parent);
                    return true;
                }
                if (node->left != NULL and node->right == NULL){
                    if (parent->data < node->data)
                        parent->right = removeOneChild(node);
                    if (parent->data > node->data){
                        parent->left = removeOneChild(node);
                    }
                    return true;
                }
                if (node->left == NULL and node->right != NULL){
                    if (parent->data < node->data)
                        parent->right = removeOneChild(node);
                    if (parent->data > node->data)
                        parent->left = removeOneChild(node);
                    return true;
                }
                if (node->left != NULL and node->right != NULL){
                    if (parent->data < node->data)
                        parent->right = removeTwoChild(node);
                    if (parent->data > node->data)
                        parent->left = removeTwoChild(node);
                    return true;
                }
                }
        }
    return false;
}

//input: nothing
//return: an int
//purpose: calls private function
int BinarySearchTree::tree_height() const
{
        return tree_height(root);
}

//input: node pointer
//return: int
//purpose: recurses until it finds larger tree height and returns that int
int BinarySearchTree::tree_height(Node *node) const
{
        if (node == NULL)
            return -1;
        if (node->left == NULL and node->right == NULL)
            return 0;
        int ldepth = tree_height(node->left);
        int rdepth = tree_height(node->right);
        if (ldepth > rdepth)
            return ldepth + 1;
        else
            return rdepth + 1;
}

// returns the total number of nodes
int BinarySearchTree::node_count() const
{
        return node_count(root);
}

//input: node pointer
//return: an int
//purpose: returns the number of nodes there are and adds as it recurses
int BinarySearchTree::node_count(Node *node) const
{
        // TODO: Students write code here
        if (node == NULL)
            return 0;
        if (node->right == NULL and node->left == NULL)
            return 1;
        return 1 + node_count(node->right) + node_count(node->left);
}

// return the sum of all the node values (including duplicates)
int BinarySearchTree::count_total() const
{
        return count_total(root);
}

//input: node pointer
//return: an int
//purpose: returns the total count of nodes and adds the node data as it
//recurses and multiplies it by node count
int BinarySearchTree::count_total(Node *node) const
{
        // TODO: Students write code here:
        if (node == NULL)
            return 0;
        if (node->right == NULL and node->left == NULL)
            return node->count * node->data;
        return node->count * node->data +
        count_total(node->right) + count_total(node->left);

}

// use the printPretty helper to make the tree look nice
void BinarySearchTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}


Node *BinarySearchTree::find_parent(Node *node, Node *child) const
{
        if (node == NULL) return NULL;

        // if either the left or right is equal to the child,
        // we have found the parent
        if (node->left == child or node->right == child) {
                return node;
        }

        // Use the binary search tree invariant to walk the tree
        if (child->data > node->data) {
                return find_parent(node->right, child);
        } else {
                return find_parent(node->left, child);
        }
}

//input: node pointer and another node pointer
//return: nothing
//purpose: deletes leaf and sets parent pointer to NULL
void BinarySearchTree::removeLeaf(Node *node, Node *parent){
    if (parent->data < node->data)
        parent->right = NULL;
    if (parent->data > node->data)
        parent->left = NULL;
    delete node;
   // print_tree();
}

//input: node pointer
//return: node pointer
//purpose: deletes node and returns the child of node for the deleted node's
//parent to point to the child
Node *BinarySearchTree::removeOneChild(Node *node){
    if (node->left != NULL and node->right == NULL){
        
        Node *temp = node->left;
        delete node;
        node = NULL;
        return temp;
    }
    if (node->right == NULL and node->left != NULL){
        Node *temp = node->right;
        delete node;
        node = NULL;
        return temp;
    }
    return NULL;
}

//input: node pointer
//return: node pointer
//purpose: replaces node to delete with the smallest of its right and assigns
//the deleted node's children to the new node
Node *BinarySearchTree::removeTwoChild(Node *node){
    Node *temp = find_min(node->right);
    if (temp->right != NULL)
        find_max(node->right)->left = temp->right;
    temp->right = node->right;
    temp->left = node->left;
    node = temp;

    temp = NULL;
    return node;
}