#ifndef EDGE_H
#define EDGE_H


#include "edge.h"
#include <iostream>
using namespace std;

enum Vertex_type {
    DEFAULT = 0,
    START = 1,
    STOP = 2,
    MERGE = 3,
    SPLIT = 4,
    REGULAR_LEFT = 5,
    REGULAR_RIGHT = 6
};


class Edge;
class tri;

class Point
{
public:
    std::pair<double,double> coord;
    Edge* 				firstEdge;
    Edge* 				secondEdge;   // each point is contained by 2 edges
    Vertex_type v_type;


public:
    Point( double x = 0.0, double y = 0.0):coord(std::make_pair(x,y)){
        firstEdge = nullptr;
        secondEdge = nullptr;
        v_type = DEFAULT;
    };

    ~Point()
    {

    }

    friend ostream& operator<<( ostream& out, Point& p )
    {
         out << p.coord.first << " " << p.coord.second;
         return out;
    }

};

class Edge
{
public:
    Point* a;
    Point* b;
    tri* t;
    Edge* dual;

    Edge(Point* a = nullptr, Point* b = nullptr, bool inner = false ):a(a),b(b),inner(inner){
        t = nullptr;
        dual = nullptr;
        inner = false;
    };

    ~Edge()
    {
    }

    void swap()
    {
        Point* aux = a;
        a = b;
        b = aux;
    }

    friend ostream& operator<<( ostream& out, Edge e )
    {
        return out << *(e.a) << "  " << *(e.b);
    }

    bool inner;

};


class tri
{
public:
    Edge* e1;
    Edge* e2;
    Edge* e3;

    tri( Edge* e1 = nullptr, Edge* e2 = nullptr, Edge* e3 = nullptr ):e1(e1),e2(e2),e3(e3){ }

    friend ostream& operator<<( ostream& out, tri t )
    {
        return out << *(t.e1) << "    " << *(t.e2) << "     " << *(t.e3);
    }
};


#endif // EDGE_H
