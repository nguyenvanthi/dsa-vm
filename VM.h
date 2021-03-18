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
    this->previous = NULL;
    this->data = x;
  }

  T data;
  Node *next;
  Node *previous;

  void link(Node *previous, Node *next);
};

template <class T>
class Iterator
{
protected:
  Node<T> *head;
  Node<T> *tail;

  int size;
  int capacity;

  bool isEmpty();

public:
  Iterator(int capacity = -1)
  {
    this->head = NULL;
    this->size = 0;
    this->capacity = capacity;
  }

  void forEach(void (*handler)(T, int));
  void forEach(void (*handler)(T));
  void push(T data);
  T pop();
  void display();
  T at(int index);
  T peek();
};

class Instruction;
class VM
{
private:
  Iterator<Instruction> *codes;
  void readCode(string filename);

public:
  int ip;

  VM()
  {
    this->codes = new Iterator<Instruction>();
  }

  void run(string filename);
};

class Instruction
{
protected:
  VM *vm;

public:
  Instruction(VM *vm)
  {
    this->vm = vm;
  }

  virtual void excute();

  static Instruction load(string input, VM * vm);
};

#endif
