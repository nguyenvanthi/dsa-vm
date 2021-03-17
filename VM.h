#ifndef VM_H
#define VM_H

#include "main.h"

template <class T>
class Node
{
public:
  Node(T x)
  {
    this->next = NULL;
    this->data = x;
  }

  T data;
  Node *next;
};

template <class T>
class List
{
  Node<T> *head;
  Node<T> *tail;
  Node<T> *temp;
  int size;

  bool isEmpty();
  Node<T> *at(int index); // Find an element at its index

public:
  List()
  {
    this->head = NULL;
    this->tail = NULL;
    this->temp = NULL;
    this->size = 0;
  }

  void push(T x);              // Add an element to the last of the list
  T pop();                     // Remove the last element of the list and return it
  void shift(T x);             // Add an element to the top of the list
  T unshift();                 // Remove the first element of the list and return it
  void insert(T x, int index); // Add an element to the list with its position
  T remove(int index);         // Remove element of the list with its position
  void display();              // Print all elements in the list
};

class VM
{
  List<string> *codes;

public:
  VM()
  {
    this->codes = new List<string>();
  }

  void run(string filename);

  void readCode(string filename);
};

#endif
