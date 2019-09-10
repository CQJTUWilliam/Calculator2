
#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#include <cassert>//use assert

//Node class defination
template <class T=int>
class Node
{
public:
    Node();

    void setData(T data);
    T getData();

    Node<T>*  getNext();
    Node<T>*& setNext();
private:
    T data;
    Node<T>* next;
};
//Node class implemention
template <class T>
Node<T>::Node()
{
    next = 0;
}

template <class T>
void Node<T>::setData(T data)
{
    this->data = data;
}

template <class T>
T Node<T>::getData()
{
    return data;
}

template <class T>
Node<T>* Node<T>::getNext()
{
    return next;
}

template <class T>
Node<T>*& Node<T>::setNext()
{
    return next;
}


//LinkedStack class
template <class T = int>
class LinkedStack
{
public:
    LinkedStack();

    bool isEmpty();

    void push(T element);
    void push(Node<T>* node);
    T pop();

    Node<T>* getTop();
    int getLength();
private:
    Node<T>* top;//point to the top element. It point to a special head node when the stack is empty
    int length;
};

template <class T>
LinkedStack<T>::LinkedStack()
{
    top = new Node<T>;
    top->setNext() = 0;
    length = 0;
}

template <class T>
bool LinkedStack<T>::isEmpty()
{
    if (top->getNext() == 0)
        return true;
    return false;
}

template <class T>
void LinkedStack<T>::push(T element)
{
    Node<T>* node = new Node<T>;

    assert(node != 0);

    node->setData(element);

    node->setNext() = top;
    top = node;
    length++;
}

template <class T>
void LinkedStack<T>::push(Node<T>* node)
{
    assert(node != 0);

    node->setNext() = top;
    top = node;
    length++;
}

template <class T>
T LinkedStack<T>::pop()
{
    T data;
    //memset(&data, 0, sizeof(T));
    if (isEmpty())
        return data;

    Node<T>* temp = top;//store the top element which is gonna be popped
    top = top->getNext();//move the stack top pointer to the next top element
    temp->setNext() = 0;
    data = temp->getData();
    delete temp;
    length--;
    return data;//return the data of the element be popped
}

template <class T>
Node<T>* LinkedStack<T>::getTop()
{
    if (isEmpty())
        return static_cast<Node<T>*>(0);
    return top;
}

template<class T>
inline int LinkedStack<T>::getLength()
{
    return length;
}

#endif