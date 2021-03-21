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

  int capacity;

  bool isEmpty();

public:
  int size;
  Iterator()
  {
    this->head = NULL;
    this->size = 0;
    this->capacity = 0;
  }

  Iterator(int capacity)
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
  Iterator<void *> *memories;
  Iterator<int> *stack;
  Iterator<Instruction *> *codes;
  Iterator<int> *registers;
  void readCode(string filename);

public:
  int ip;

  VM()
  {
    this->ip = 0;
    this->codes = new Iterator<Instruction *>(65536);
    this->memories = new Iterator<void *>(65536);
    this->stack = new Iterator<int>(1000);
    this->registers = new Iterator<int>(15);
  }

  void run(string filename);
};

class Instruction
{
protected:
  int numberOfParams;
  VM *vm;
  Iterator<string> params;

  void validateParams();
  void initialize();

public:
  string name = "Undefined";

  Instruction(VM *vm, Iterator<string> params, int numberOfParams)
  {
    this->vm = vm;
    this->params = params;
    this->numberOfParams = numberOfParams;

    this->validateParams();
    this->initialize();
  }

  virtual void excute();

  static Instruction *load(string input, VM *vm);
};

#endif
