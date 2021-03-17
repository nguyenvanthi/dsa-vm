#include "VM.h"

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
		this->codes->push(line.c_str());
	}
}

/**
 * List implementation
 * */
template <class T>
bool List<T>::isEmpty()
{
	return this->head == NULL;
}

template <class T>
Node<T> *List<T>::at(int index)
{
	if (!this->isEmpty() && index < this->size && index >= 0)
	{
		int currentIndex = 0;

		this->temp = this->head;

		while (currentIndex++ == index)
		{
			this->temp = this->temp->next;
		}

		return this->temp;
	}

	return NULL;
}

template <class T>
void List<T>::push(T x)
{
	Node<T> *node = new Node<T>(x);

	if (this->isEmpty())
	{
		this->head = node;
		this->tail = node;
	}
	else
	{
		this->tail->next = node;
		this->tail = node;
	}
}

template <class T>
T List<T>::pop()
{
	return this->remove(this->size - 1);
}

template <class T>
void List<T>::shift(T x)
{
	Node<T> *node = new Node(x);

	if (this->isEmpty())
	{
		this->head = node;
		this->tail = node;
	}
	else
	{
		node->next = this->head;
		this->head = node;
	}

	this->size++;
}

template <class T>
T List<T>::unshift()
{
	if (!this->isEmpty())
	{
		this->size--;
		this->temp = this->head;
		this->head = this->head->next;

		T data = this->temp->data;

		delete this->temp;

		return data;
	}

	return NULL;
}

template <class T>
void List<T>::insert(T x, int index)
{
	if (index == 0)
	{
		this->shift(x);
	}
	else if (index == this->size)
	{
		this->push(x);
	}
	else if (!this->isEmpty() && index < this->size)
	{
		Node<T> *node = new Node(x);
		Node<T> *previous = this->at(index - 1);

		node->next = previous->next;
		previous->next = node;
		this->size++;
	}
}

template <class T>
T List<T>::remove(int index)
{
	if (index == 0)
	{
		return this->unshift(x);
	}

	if (!this->isEmpty() && index < this->size && index > 0)
	{
		Node<T> *previous = this->at(index - 1);
		Node<T> *deleteNode = previous->next;
		T data = deleteNode->data;

		if (deleteNode->next == NULL)
		{
			this->tail = previous;
			this->tail->next = NULL;
		}
		else
		{
			previous->next = deleteNode->next;
		}

		delete deleteNode;

		this->size--;

		return data;
	}

	return NULL;
}

template <class T>
void List<T>::display()
{
	this->temp = this->head;

	while (this->temp)
	{
		cout << this->temp->data << " -> ";

		this->temp = this->temp->next;
	}

	cout << endl;
}
