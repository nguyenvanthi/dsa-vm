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
class Iterator
{
protected:
  Node<T> *head;
  int size;

  bool isEmpty();

public:
  Iterator()
  {
    this->head = NULL;
    this->size = 0;
  }

  void forEach(void (*handler)(T, int));
  void forEach(void (*handler)(T));
};

template <class T>
class List : public Iterator<T>
{
  Node<T> *tail;
  Node<T> *temp;

  Node<T> *at(int index); // Find an element at its index

public:
  List() : Iterator()
  {
    this->tail = NULL;
    this->temp = NULL;
  }

  void push(T x);              // Add an element to the last of the list
  T pop();                     // Remove the last element of the list and return it
  void shift(T x);             // Add an element to the top of the list
  T unshift();                 // Remove the first element of the list and return it
  void insert(T x, int index); // Add an element to the list with its position
  T remove(int index);         // Remove element of the list with its position
  void display();              // Print all elements in the list
};

template <class T>
class Stack : List<T>
{
public:
  T peek(); // Get the top of the stack without removing it from the stack
};

class Instruction;

typedef void (*handleAddCode)(Instruction);

class VM
{
  List<Instruction> *codes;

protected:
  List<Instruction> supportedInstructions;

  void addCode(Instruction instruction) {}

  handleAddCode loadCode(string input)
  {
    return this->addCode;
  };

public:
  int ip;

  VM()
  {
    this->codes = new List<Instruction>();
  }

  void run(string filename);

  void readCode(string filename);
};

class Instruction
{
protected:
  VM *vm;

  List<string> loadInstruction(string input, string prefix, int numberOfParams);

public:
  Instruction(VM *vm)
  {
    this->vm = vm;
  }

  virtual void excute();
  virtual Instruction load(string input);
};

#endif
