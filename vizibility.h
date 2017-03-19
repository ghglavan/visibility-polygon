#ifndef VIZIBILITY_H
#define VIZIBILITY_H

#include <iostream>
#include "edge.h"
#include "list.h"
#include <string>
#include <sstream>
#include <vector>


using namespace std;




// this is where the magic happens
class Visibility
{
public:
    Visibility( /*stringstream& ss*/ vector<pair<int,int> > vect );
    ~Visibility();

    vector<pair<int,int> > getTriangulation();
    vector<pair<int,int> > getIntersections( int x, int y );



private:
    double determinant( pair<double,double> a, pair<double,double> b, pair<double,double> c );
    int curba( pair<double,double> a, pair<double,double> b, pair<double,double> c );
    bool verificare( Node<Point*>* a, Node<Point*>* b, Node<Point*>* c );
    bool inTriunghi( pair<double,double> a, pair<double,double> b, pair<double,double> c, pair<double,double> pct );
    pair<double,double> intersect( Point* pmisto, Point* celalalt, Edge* muchie );
    void functie( tri* t, Edge* e, Point* p1, Point* p2, Point* pmisto );

    void getTriangles();
    void toClockwise();
    bool checkClockwise();
    void setEdges();
    void computeTriangulation();


    vector<tri*> vec;
    List<Point*>* list;
    int number_of_vertices;
    vector<pair<int,int > > inters;

};


#endif // VIZIBILITY_H
