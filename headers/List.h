#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <errno.h>

template<class T>
struct ListNode
{
  T component;
  ListNode<T>* link;
  //int number;
};

template <class T>
class List
{
 private:
  ListNode<T> *head;
  //T **newNode;
  int count;
  //void addElement(ListNode<T>);
 public:
  List();
  ~List();
  //void removeElement(int);

    
  // must be implemented successfully
  void add(T);
  int search(T);
  T get(int = 0);
  T remove(int = 0);
  int getSize();
  // -------
    
};

#include "../src/List.icc"

#endif
