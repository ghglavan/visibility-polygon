#ifndef TRIANGULARE_H
#define TRIANGULARE_H

#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include <QLine>


class triangulare
{
public:
     triangulare(QVector<QPointF>);

     ~triangulare();

     QVector<QPointF> *pVector = nullptr;

     QVector<QPointF> *pVectorc = nullptr;

     QVector<QPolygonF> *polyvector = nullptr;

     QPolygonF p;

     QVector<QPolygonF> *triangles;

     QVector<QLineF> lines;

     int npoints;

     QVector<int> *pointType = nullptr;
     QVector<int> *pointTypec = nullptr;

     int earCutter;
     int concavePoints;

     double delta(QPointF,QPointF, QPointF);

     bool convex(QPointF,QPointF,QPointF);

     bool intersection(QPointF,QPointF,QPointF,QPointF);

     QVector<int> specialT;

     bool tract = false;

     QVector<int> trViz(QPointF);


     bool triangleContainsPoints(QPointF,QPointF,QPointF);

     double abs(double);

     bool ear(QPointF,QPointF,QPointF);

     void cutEar();

     void updatePoints();

     void updatePoly(int);

     QVector<QLineF> findSpecialLines(QVector<int>,QPointF);

     QPointF intersectionPoint(QPointF,QPointF,QPointF,QPointF);

protected:


};

#endif // TRIANGULARE_H
