#include "VM.h"

#pragma region Node

template <class T>
void Node<T>::link(Node *previous, Node *next)
{
  this->next = next;
  this->previous = previous;
}

#pragma endregion

#pragma region Iterator

template <class T>
bool Iterator<T>::isEmpty()
{
  return this->size == 0;
}

template <class T>
void Iterator<T>::forEach(void (*handler)(T))
{
  if (!this->isEmpty())
  {
    Node<T> *node = this->head;

    while (node != NULL)
    {
      handler(node->data);

      node = node->next;
    }
  }
}

template <class T>
void Iterator<T>::forEach(void (*handler)(T, int))
{
  if (!this->isEmpty())
  {
    Node<T> *node = this->head;
    int index = 0;

    while (node != NULL)
    {
      handler(node->data, index++);

      node = node->next;
    }
  }
}

template <class T>
void Iterator<T>::push(T x)
{
  Node<T> *node = new Node<T>(x);

  if (this->size > this->capacity)
  {
    // TODO throw the error
    return;
  }

  this->size++;

  if (this->isEmpty())
  {
    this->head = node;
    this->tail = node;
  }
  else
  {
    node->link(this->tail, NULL);

    this->tail = node;
  }
}

template <class T>
T Iterator<T>::pop()
{
  if (!this->isEmpty())
  {
    Node<T> *deleteNode = this->tail;
    T data = deleteNode->data;

    this->size--;
    this->tail = this->tail->previous;

    delete deleteNode;

    return data;
  }
}

template <class T>
void Iterator<T>::display()
{
  cout << "NULL <->";
  void(*printData) = [](T data) {
    cout << data << " <-> ";
  };

  this->forEach(printData);

  cout << "NULL" << endl;
}

template <class T>
T Iterator<T>::at(int index)
{
  if (index < = || index > this->size)
  {
    // TODO throw the error
  }

  T result;

  void(*setResult) = [](T data, int currentIndex) {
    if (index == currentIndex)
    {
      result = currentIndex;
    }
  };

  this->forEach(setResult);

  return result;
}

template <class T>
T Iterator<T>::peek()
{
  if (!this->isEmpty())
  {
    return this->head->data;
  }
}

#pragma endregion

#pragma region Arithmetic instructions
class AddInstruction : public Instruction
{
public:
  AddInstruction(VM *vm) : Instruction(vm) {}

  virtual void excute() {}
};

#pragma endregion

#pragma region Instructions

Instruction Instruction::load(string input, VM *vm)
{
  cout << input;

  return AddInstruction(vm);
}

#pragma endregion

#pragma region VM

void VM::run(string filename)
{
  this->readCode(filename);
  this->codes->display();
}

void VM::readCode(string filename)
{
  ifstream infile(filename);
  string line;

  while (getline(infile, line))
  {
    Instruction instruction = Instruction::load(line, this);

    this->codes->push(instruction);
  }
}

#pragma endregion
