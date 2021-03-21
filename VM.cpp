#include "VM.h"
#define REGISTER_PREFIX "R"

#define ADD_INSTRUCTION "Add"

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

  if (this->capacity > 0 && this->size > this->capacity)
  {
    // TODO throw the error
    return;
  }

  if (this->isEmpty())
  {
    this->head = node;
    this->tail = node;
  }
  else
  {
    node->link(this->tail, NULL);
    this->tail->link(this->tail->previous, node);

    this->tail = node;
  }

  this->size++;
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
void printData(T data)
{
  cout << data << " <-> ";
}

template <class T>
void Iterator<T>::display()
{
  this->forEach(printData);

  cout << "NULL" << endl;
}

template <class T>
T Iterator<T>::at(int index)
{
  if (index < 0 || index > this->size)
  {
    // TODO throw the error
  }

  T result;
  Node<T> *node = this->head;
  int currentIndex = 0;

  while (node != NULL)
  {
    if (currentIndex++ == index)
    {
      result = node->data;
      break;
    }

    node = node->next;
  }

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
  AddInstruction(VM *vm, Iterator<string> params) : Instruction(vm, params, 3)
  {
    this->name = ADD_INSTRUCTION;
    this->numberOfParams = 3;
  }

  virtual void excute() {}
};

#pragma endregion

#pragma region Instructions

Iterator<string> tokenize(string s, string del = " ")
{
  Iterator<string> tokens = Iterator<string>();
  int start = 0;
  int end = s.find(del);
  while (end != -1)
  {
    string word = s.substr(start, end - start);

    tokens.push(word);

    start = end + del.size();
    end = s.find(del, start);
  }

  string word = s.substr(start, end - start);

  tokens.push(word);

  return tokens;
}

void Instruction::excute()
{
}

void Instruction::initialize()
{
}

Instruction *Instruction::load(string input, VM *vm)
{
  Iterator<string> params = tokenize(input);
  Instruction *instruction;

  if (params.at(0).compare(ADD_INSTRUCTION) == 0)
  {
    instruction = new AddInstruction(vm, params);
  }
  // TODO load instruction

  return instruction;
}

void Instruction::validateParams()
{
  if (this->params.size != this->numberOfParams)
  {
    throw InvalidInstruction(this->vm->ip);
  }

  if (this->numberOfParams > 1)
  {
    string param = this->params.at(1);

    // TODO exclude Jump, Call
    if (param.rfind(REGISTER_PREFIX, 0) != 0)
    {
      throw InvalidInstruction(this->vm->ip);
    }
  }
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
    Instruction *instruction = Instruction::load(line, this);

    this->ip++;

    this->codes->push(instruction);
  }

  this->ip = 0;
}

#pragma endregion

#pragma region IN / OUT Helpers

std::ostream &operator<<(std::ostream &os, const Instruction *instruction)
{
  os << instruction->name;

  return os;
}

#pragma endregion
