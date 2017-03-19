#ifndef NODE_H
#define NODE_H


#include "node.h"


template<class T>
class Node
{
public:
    Node(){ next = prev = nullptr; }

    Node( T info )
    {
        next = prev = nullptr;
        this->info = info;
    }

    ~Node(){ next = prev = nullptr; }

    Node<T>* getNext(){ return next; }
    Node<T>* getPrev(){ return prev; }
    T getInfo(){ return info; }

    void setNext( Node<T>* next){ this->next = next; }
    void setPrev( Node<T>* prev){ this->prev = prev; }
    void setInfo( T info ){ this->info = info; }

private:
    T info;
    Node<T>* next;
    Node<T>* prev;
};

#endif // NODE_H
