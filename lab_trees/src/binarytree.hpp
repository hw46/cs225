/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>
#include <stack>
using namespace std;

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
    template <typename T>
void BinaryTree<T>::mirror()
{
    mirrorHelper(root);
}

template <typename T>
void BinaryTree<T>::mirrorHelper(Node*& current) {
    if (current == nullptr) {
        return;
    }
    Node* temp = current->left;
    current->left = current->right;
    current->right = temp;
    mirrorHelper(current->left);
    mirrorHelper(current->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    InorderTraversal<T> t(this->getRoot());
    auto it = t.begin();
    
    // If tree is empty, consider it ordered.
    if (*it == nullptr) {
        return true;
    }

    T prev = (*it)->elem;
    ++it;

    while (*it!=nullptr) {
        if (prev > (*it)->elem) {
            return false;
        }
        prev = (*it)->elem;
        ++it;
    }

    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    vector<T> v;
    isOrderedRecursive(root, v);
    bool ordered = true;
    for(unsigned long i = 0; i < v.size() - 1; i++){
      if(v[i] >= v[i+1]){
        ordered = false;
      }
    }
    return ordered;
}

template <typename T>
void BinaryTree<T>::isOrderedRecursive(Node* subRoot, vector<T> &v)const{
  if(subRoot == NULL){return;}
  isOrderedRecursive(subRoot->left, v);
  v.push_back(subRoot->elem);
  isOrderedRecursive(subRoot->right, v);
}
