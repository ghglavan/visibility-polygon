#ifndef LIST_H
#define LIST_H

#include "list.h"

#include "node.h"
#include <iostream>

using namespace std;

template<class T>
class List
{
public:
    List(){ first = last = nullptr; size = 0; }
    ~List()
    {
        Node<T> *p = first;
        last->setNext(nullptr);

        while( p )
        {
            Node<T>* q = p;
            p = p->getNext();
            delete q;
        }
    }

    Node<T>* getFirst(){ return first; }
    Node<T>* getLast(){ return last; }
    void setFirst( Node<T>* first ){ this->first = first; }
    void setLast( Node<T>* last ){ this->last = last; }

    void push_back( T elem )
    {
        if( size == 0 )
        {
            first = new Node<T>(elem);
            last = first;
            first->setNext(first);
            first->setPrev(first);
        }
        else
        {
            Node<T>* new_node = new Node<T>(elem);
            new_node->setNext(first);
            first->setPrev(new_node);
            last->setNext(new_node);
            new_node->setPrev(last);
            last = new_node;
        }
        ++size;
    }

    void erase( Node<T>* node )
    {
        if( size == 0 || node == nullptr )
            return;
        if( size == 1 )
        {
            first = last = nullptr;
        }
        else if( node == first )
        {
            first = first->getNext();
            first->setPrev(last);
            last->setNext(first);
        }
        else if( node == last )
        {
            last = last->getPrev();
            last->setNext(first);
            first->setPrev(last);
        }
        else
        {
            Node<T>* prev = node->getPrev();
            Node<T>* next = node->getNext();
            prev->setNext(next);
            next->setPrev(prev);
        }
        delete node;
        node = nullptr;
        --size;
    }

private:
    Node<T>* first;
    Node<T>* last;
    int size;
};


#endif // LIST_H
