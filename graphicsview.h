#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include <QResizeEvent>
#include <QGraphicsSceneMouseEvent>
#include <QTextBrowser>
#include <QString>
#include <QScrollBar>
#include <vector>
#include <algorithm>
#include <triangulare.h>
#include <QGraphicsScene>
#include <iostream>
#include "myitem.h"

class GraphicsView : public QGraphicsScene
{
public:
    GraphicsView(QWidget *parent,MyItem *i): QGraphicsScene(parent),item(i){}

    MyItem *item;

    void resizeEvent(QResizeEvent *);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSVIEW_H
