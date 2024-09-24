#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode{
public:
  TreeNode(T d);
  virtual ~TreeNode();
  T getData();
  int getDepth();
  template <typename S>
  friend class LazyBST;

  TreeNode<T>* m_left;
  TreeNode<T>* m_right;
  int m_depth;
  T m_data;
private:
  
};

template <typename T>
TreeNode<T>::TreeNode(T d){
  m_left = NULL;
  m_right = NULL;
  m_depth = 1;
  m_data = d;
}

template <typename T>
TreeNode<T>::~TreeNode(){
  if(m_left != NULL){
    delete m_left;
  }

  if(m_right != NULL){
    delete m_right;
  }
}

template <typename T>
T TreeNode<T>::getData(){
  return m_data;
}

template <typename T>
int TreeNode<T>::getDepth(){
  return m_depth;
}

#endif
