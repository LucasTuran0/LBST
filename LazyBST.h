#ifndef LAZYBST_H
#define LAZYBST_H

#include "TreeNode.h"
#include "DblList.h"
#include <cmath>
#include <algorithm> 
#include <cstdlib>
#include <fstream>
#include <iostream>


template <typename T>
class LazyBST{
public:
  LazyBST();
  virtual ~LazyBST();
  int getSize();
  void insert(T d);
  void remove(T d);
  bool contains(T d);
  T getMin();
  T getMax();
  void printTreeInOrder();
  void balance(TreeNode<T>*& root);
  void deleteTree(TreeNode<T>*& node);
  bool imbalance(TreeNode<T>*& node);
  void updateNodeDepth(TreeNode<T>* node, int currentDepth);
  void printRightmostPath(TreeNode<T>* node);
  TreeNode<T>* getRoot();
  void updateAllDepths(TreeNode<T>* node);
  T findByID(int id);
  void writeTreeToFile(const string& filename);

  
private:
  TreeNode<T>* m_root;
  int m_size;
  void insertHelper(TreeNode<T>*& subTreeRoot,TreeNode<T>* newNode);
  bool containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* target);
  T getMinHelper(TreeNode<T>* subTreeRoot);
  T getMaxHelper(TreeNode<T>* subTreeRoot);
  void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
  void findTarget(T key, TreeNode<T>*& target,TreeNode<T>*& parent);
  TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
  void inOrderToList(TreeNode<T>* node, DblList<T>& list);
  TreeNode<T>* balanceHelper(DblList<T>& list, int start, int end);
  void removeHelper(T d, TreeNode<T>*& node, TreeNode<T>* parent);
  TreeNode<T>* findIdHelper(TreeNode<T>* node, int id);
  void writeTreeToFileHelper(TreeNode<T>* node, ofstream& file);

};

//prints stuff for debugging
// template <typename T>
// void LazyBST<T>::printRightmostPath(TreeNode<T>* node) {
//   cout << "root: " << m_root->getData() << endl;
//   cout << "Right:" << endl;
//   while (node != nullptr) {
//     cout << node->getData() << " " << "depth:" << node->getDepth() << " | ";
//     node = node->m_right;
//   }
//   cout << endl;
//   node = m_root;
//   cout << "Left:" << endl;
//   while (node != nullptr) {
//     cout << node->getData() << " " << "depth:" << node->getDepth() << " | ";
//     node = node->m_left;
//   }
//   cout << endl;
// }


template <typename T>   //default constructor
LazyBST<T>::LazyBST(){
  m_root = NULL;
  m_size = 0;
}

template <typename T>   //overloaded constructor
LazyBST<T>::~LazyBST(){
  if(m_root != NULL){
    delete m_root;
  }
}

template <typename T>   //searches for student or faculty by id
T LazyBST<T>::findByID(int id) {
  TreeNode<T>* node = findIdHelper(m_root, id);
  if (node != nullptr) {
    return node->getData(); // Return the data by value
  } else {
    cout << "ID not found" << endl;
  }
}


template <typename T> 
TreeNode<T>* LazyBST<T>::findIdHelper(TreeNode<T>* node, int id) {
  if (node == nullptr) {
    return nullptr; // Not found
  }

  if (id < node->getData().m_id) {
    return findIdHelper(node->m_left, id); // Search in the left subtree
  } else if (id > node->getData().m_id) {
    return findIdHelper(node->m_right, id); // Search in the right subtree
  } else {
    return node; // Found the node, return it
  }
}

template <typename T>         //gets bst size
int LazyBST<T>::getSize(){
  return m_size;
}

template <typename T>         //insert new node to bst
void LazyBST<T>::insert(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  insertHelper(m_root,newNode);
  ++m_size;
  if (imbalance(m_root) == true) {
    balance(m_root);
  }
}

template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot == NULL){
    subTreeRoot = newNode;
    // Since this is a new node, its depth is 0 (leaf node)
    newNode->m_depth = 0;
  } else {
    if(newNode->m_data < subTreeRoot->m_data){
      insertHelper(subTreeRoot->m_left, newNode);
    } else {
      insertHelper(subTreeRoot->m_right, newNode);
    }

    // Update the depth of the current node
    int leftDepth = subTreeRoot->m_left ? subTreeRoot->m_left->m_depth : -1;
    int rightDepth = subTreeRoot->m_right ? subTreeRoot->m_right->m_depth : -1;
    subTreeRoot->m_depth = 1 + std::max(leftDepth, rightDepth);
  }
}


template <typename T>
TreeNode<T>* LazyBST<T>::getRoot(){     //returns root of bst
  return m_root;
}


template <typename T>       //removes node of bst
void LazyBST<T>::remove(T d) {
  removeHelper(d, m_root, nullptr);

  if (imbalance(m_root) == true) {
    balance(m_root);
  }
}

template <typename T>
void LazyBST<T>::removeHelper(T d, TreeNode<T>*& node, TreeNode<T>* parent) {
  if (node == nullptr) {
    return; // Node not found, end recursion
  }

  if (d < node->m_data) {
    removeHelper(d, node->m_left, node); // Go left
  } else if (d > node->m_data) {
    removeHelper(d, node->m_right, node); // Go right
  } else {
    // Node to be removed is found
    if (node->m_left != nullptr && node->m_right != nullptr) {
      // Node with two children
      TreeNode<T>* successor = getSuccessor(node->m_right);
      node->m_data = successor->m_data;
      removeHelper(successor->m_data, node->m_right, node);
    } else {
      // Node with 0 or 1 child
      TreeNode<T>* oldNode = node;
      node = (node->m_left != nullptr) ? node->m_left : node->m_right;

      // Delete the old node
      delete oldNode;
    }
 }

  updateNodeDepth(m_root, 0);
}


template <typename T>     //updates node depth, used in remove
void LazyBST<T>::updateNodeDepth(TreeNode<T>* node, int currentDepth) {
    if (node == nullptr) {
        return;
    }

    // Update the depth of the current node
    node->m_depth = currentDepth;

    // Recursively update the depth for left and right children
    updateNodeDepth(node->m_left, currentDepth + 1);
    updateNodeDepth(node->m_right, currentDepth + 1);
}



template <typename T>   //updates all the depths in the tree
void LazyBST<T>::updateAllDepths(TreeNode<T>* node) {
    if (node == nullptr) {
        return;
    }

    // Update left and right children first
    updateAllDepths(node->m_left);
    updateAllDepths(node->m_right);

    // Then update this node's depth
    updateNodeDepth(m_root, 0);
}



template <typename T>   //checks tree to see if it contains a certain node
bool LazyBST<T>::contains(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  bool ret =  containsHelper(m_root,newNode);
  delete newNode;
  return ret;
}

template <typename T>
bool LazyBST<T>::containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* target){
  if(subTreeRoot == NULL){
    return false;
  } else if(target->m_data < subTreeRoot->m_data){
    return containsHelper(subTreeRoot->m_left,target);
  } else if (target->m_data > subTreeRoot->m_data){
    return containsHelper(subTreeRoot->m_right,target);
  } else{
    return true;
  }
}

template <typename T>   //gets min value in tree
T LazyBST<T>::getMin(){
  //what if the tree is empty?
  return getMinHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_left == NULL){
    return subTreeRoot->m_data;
  } else{
    return getMinHelper(subTreeRoot->m_left);
  }
}

template <typename T>   //gets max value in tree
T LazyBST<T>::getMax(){
  //what if the tree is empty?
  return getMaxHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_right == NULL){
    return subTreeRoot->m_data;
  } else{
    return getMaxHelper(subTreeRoot->m_right);
  }
}

template <typename T>     //prints tree in order from smallest to largest
void LazyBST<T>::printTreeInOrder(){
  printTreeInOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot) {
  if (subTreeRoot != NULL) {
    // Traverse the left subtree
    if (subTreeRoot->m_left != NULL) {
      printTreeInOrderHelper(subTreeRoot->m_left);
    }

    // Print the current node's data
    subTreeRoot->m_data.printInfo(); // Calls printInfo on the node's data

    // Traverse the right subtree
    if (subTreeRoot->m_right != NULL) {
      printTreeInOrderHelper(subTreeRoot->m_right);
    }
    }
}

template <typename T>     //balances the bst
void LazyBST<T>::balance(TreeNode<T>*& root) {
    DblList<T> list;
    inOrderToList(root, list); // Convert the tree into a sorted list
    deleteTree(root); // Delete the current tree
    root = balanceHelper(list, 0, list.getSize() - 1);

    // Update all node depths after balancing
    updateAllDepths(root);
}


template <typename T>
TreeNode<T>* LazyBST<T>::balanceHelper(DblList<T>& list, int start, int end) {
  if (start > end) {
    return nullptr; // Base case for recursion
  }
  int median = start + (end - start) / 2;
  TreeNode<T>* node = new TreeNode<T>(list.get(median));
  node->m_left = balanceHelper(list, start, median - 1);
  node->m_right = balanceHelper(list, median + 1, end);
  updateNodeDepth(m_root, 0);
  return node;
}


template <typename T>   //checks if the tree needs balancing if its unbalanced by a factor of 1.5
bool LazyBST<T>::imbalance(TreeNode<T>*& node) {
  if (node == nullptr) {
    return false;
  }

  double leftDepth = (node->m_left != nullptr) ? node->m_left->getDepth() : 0;
  double rightDepth = (node->m_right != nullptr) ? node->m_right->getDepth() : 0;

  double depthDiff = abs(leftDepth - rightDepth);

  // Special case when one or both children are missing
  if (leftDepth == 0 || rightDepth == 0) {
    return depthDiff > 1.5;
  }

  // General case
  return depthDiff >= 1.5 * min(leftDepth, rightDepth);
}



template <typename T>   //deletes tree
void LazyBST<T>::deleteTree(TreeNode<T>*& node) {
  if (node != nullptr) {
    deleteTree(node->m_left);
    deleteTree(node->m_right);
    delete node;
    node = nullptr;
  }
}

template <typename T>       //puts the tree in order to a list used for balancing
void LazyBST<T>::inOrderToList(TreeNode<T>* node, DblList<T>& list) {
  if (node == nullptr) {
    return;
  }
  inOrderToList(node->m_left, list);
  list.addBack(node->m_data);
  inOrderToList(node->m_right, list);
}

template <typename T>   //finds target
void LazyBST<T>::findTarget(T key, TreeNode<T>*& target,TreeNode<T>*& parent){
  while(target != NULL && target->m_data != key){
    parent = target;
    if(key < target->m_data){
      target = target->m_left;
    } else{
      target = target->m_right;
    }
  }
}

template <typename T>   // gets child of node
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T>* rightChild){
  while(rightChild->m_left != NULL){
    rightChild = rightChild->m_left;
  }
  return rightChild;
}


#endif