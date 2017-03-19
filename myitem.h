// myitem.h

#ifndef MYITEM_H
#define MYITEM_H

#include <QMessageBox>
#include <QPainter>
#include <QGraphicsItem>
#include <QPointF>
#include <QVector>
#include <QGraphicsSceneMouseEvent>
#include <QTextBrowser>
#include <QString>
#include <QScrollBar>
#include <vector>
#include <algorithm>
#include <triangulare.h>
#include <QGraphicsScene>
#include "vizibility.h"


// class for customization
class MyItem :public QGraphicsItem
{
public:
    MyItem(QTextBrowser*);
    ~MyItem();

    void setRect(QRectF c);

    QRectF boundingRect() const;

    // overriding paint()
    void paint(QPainter * painter,
               const QStyleOptionGraphicsItem * option,
               QWidget * widget);

    // item state
    QRectF *area =nullptr;

    void reset();

    QVector<QPointF> pVector;
    QVector<QPolygonF> tpolygon;

    QVector<QPainterPath> visibleTriangles;

    QPolygonF *actualPolygon = nullptr;
    QPolygonF *transformedPolygon = nullptr;

    QPointF camera;

    bool afisare = false;

    int deCateOriAGresitProstu;

    bool inchis = false;

    bool autointersectie();

    QVector<QLineF> lines;
    QPainterPath path;

    void updateLines(QVector<QLineF>);

    QVector<int> specialT;

    bool tract = false;

    void updatee();

    triangulare *tri;

    QVector<QLineF> specialLines;

    bool finished = false;

    Visibility *v = nullptr;

protected:
    // overriding mouse events

    QTextBrowser *t =nullptr;



    QPointF *lastP = nullptr;

    QPointF *firstP = nullptr;





    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYITEM_H
