#ifndef DBL_LIST_H
#define DBL_LIST_H

#include "ListNode.h"

template <typename T>
class DblList{
public:
  DblList();
  virtual ~DblList();
  int getSize();
  bool isEmpty();

  //add
  void addBack(T data);
  void addFront(T data);
  void add(int pos, T data);

  //remove
  T removeBack();
  T removeFront();
  T remove(int pos);

  //get function
  T get(int pos);
  bool contains(T data);

  template <typename S>
  friend class PQueue;

private:
  ListNode<T>* m_front;
  ListNode<T>* m_back;
  int m_size;

};

template <typename T>
DblList<T>::DblList(){
  m_size = 0;
  m_front = NULL;
  m_back = NULL;
}

template <typename T>
DblList<T>::~DblList(){
  m_size = 0;
  m_front = NULL;
  m_back = NULL;
}

template <typename T>
int DblList<T>::getSize(){
  return m_size;
}

template <typename T>
bool DblList<T>::isEmpty(){
  return (m_size==0);
}

template <typename T>
T DblList<T>::get(int pos){
  //first check pos is valid
  int cPos = 0;
  ListNode<T>* current = m_front;
  while(cPos != pos){
    current = current->m_next;
    ++cPos;
  }
  return current->m_data;
}

template <typename T>
bool DblList<T>::contains(T data){
  ListNode<T>* current = m_front;
  bool found = false;
  while(current != NULL){
    if(data == current->m_data){
      found = true;
      break;
    }
    current = current->m_next;
  }
  return found;
}

template <typename T>
void DblList<T>::addFront(T data){
  ListNode<T>* newNode = new ListNode<T>(data);
  if(!isEmpty()){
    m_front->m_prev = newNode;
    newNode->m_next = m_front;

  } else{ //empty
    m_back = newNode;
  }
  ++m_size;
  m_front = newNode;
}

template <typename T>
void DblList<T>::addBack(T data){
  ListNode<T>* newNode = new ListNode<T>(data);
  if(!isEmpty()){
    m_back->m_next = newNode;
    newNode->m_prev = m_back;
  } else{ //empty
    m_front = newNode;
  }
  ++m_size;
  m_back = newNode;
}

template <typename T>
void DblList<T>::add(int pos, T data){
  if(isEmpty() || pos==0){
    addFront(data);
  } else if(pos >= m_size){
    addBack(data);
  } else{
    ListNode<T>* current = m_front;
    int cPos = 0; //index of first new
    while(cPos != pos){
      current = current->m_next;
      ++cPos;
    }
    ListNode<T>* newNode = new ListNode<T>(data);
    current->m_prev->m_next = newNode;
    newNode->m_prev = current->m_prev;
    current->m_prev = newNode;
    newNode->m_next = current;
    ++m_size;
  }
}

template <typename T>
T DblList<T>::removeFront(){
  //check if empty, etc
  T data;
  data = m_front->m_data;
  if(m_size==1){//yay
    delete m_front;
    m_front = NULL;
    m_back = NULL;

  } else{ //multiple things in the list
    ListNode<T>* currFront = m_front;
    m_front = m_front->m_next;
    m_front->m_prev = NULL;
    currFront->m_next = NULL;
    delete currFront;

  }
  --m_size;
  return data;
}

template <typename T>
T DblList<T>::removeBack(){
  //check if empty, etc
  T data;
  data = m_back->m_data;
  if(m_size==1){//yay
    delete m_back;
    m_front = NULL;
    m_back = NULL;

  } else{ //multiple things in the list
    ListNode<T>* currBack = m_back;
    m_back = m_back->m_prev;
    m_back->m_next = NULL;
    currBack->m_prev = NULL;
    delete currBack;

  }
  --m_size;
  return data;
}

template <typename T>
T DblList<T>::remove(int pos){
  //make sure to check if empty
  T data;
  if(pos==0){
    data = removeFront();
  } else if(pos >= m_size-1){
    data = removeBack();
  } else{
    ListNode<T>* current = m_front;
    int cPos = 0; //index of first new
    while(cPos != pos){
      current = current->m_next;
      ++cPos;
    }
    data = current->m_data;
    current->m_prev->m_next = current->m_next;
    current->m_next->m_prev = current->m_prev;
    delete current;
    --m_size;

  }
}


#endif
