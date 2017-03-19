#include "myitem.h"
#include<iostream>
#include<sstream>

using namespace std;

MyItem::MyItem(QTextBrowser *r)
{
    deCateOriAGresitProstu = 0;
    t = r;
    //Pressed = false;
    //setFlag(ItemIsMovable);
}

void MyItem::setRect(QRectF c){
    area = new QRectF();
    *area = c;
}

MyItem::~MyItem(){
    delete(actualPolygon);
    actualPolygon = nullptr;

    delete(transformedPolygon);
    transformedPolygon = nullptr;

    delete(lastP);
    lastP = nullptr;

    delete(firstP);
    firstP = nullptr;

}



/*
QPointF MyItem::intersectie(QPointF p1,QPointF p2,QPointF p3,QPointF p4){
    QPointF temp(((p1.rx()*p2.ry() - p1.ry()*p2.rx())*(p3.rx()-p4.rx()) - (p1.rx()-p2.rx())*(p3.rx()*p4.ry()-p3.ry()*p4.rx())) / ((p1.ry()-p2.ry())*(p3.rx()-p4.rx()) - (p1.rx()-p2.rx())*(p3.ry()-p4.ry())),
                 ((p1.ry()-p2.ry())*(p3.rx()*p4.ry()-p3.ry()*p4.rx()) - (p1.rx()*p2.ry() - p1.y*p2.rx()) * (p3.ry()-p4.ry()) ) / ((p1.ry()-p2.ry())*(p3.rx()-p4.rx()) - (p1.rx()-p2.rx())*(p3.y-p4.ry()))
                 );
    return temp;

}
*/

void MyItem::reset(){
    t->setText("");

    finished = false;

    delete(lastP);
    lastP = nullptr;

    delete(firstP);
    firstP = nullptr;

    pVector.clear();

    tpolygon.clear();

    if(actualPolygon != nullptr){
        delete(actualPolygon);
        actualPolygon = nullptr;
    }
    if(transformedPolygon != nullptr){
        delete (transformedPolygon);
        transformedPolygon = nullptr;
    }
    inchis = false;

    lines.clear();

    update();

}

bool MyItem::autointersectie(){
    std::cout<<lines.size()<<"asdasdas";
    for(int i = 0; i < lines.size(); i ++){
        for(int j = 0 ; j < lines.size() ; j ++){
            if(i != j){
                if(tri->intersection(lines[i].p1(),lines[i].p2(),lines[j].p1(),lines[j].p2())){
                    return true;
                }
            }
        }
    }
    return false;
}

QRectF MyItem::boundingRect() const
{
    // outer most edges
    if(area != nullptr) return *area;
    return QRectF(0,0,1200,1200);
}

void MyItem::updateLines(QVector<QLineF> lines){
    this->lines = lines;
    update();
}

void MyItem::updatee(){
    update();
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option = nullptr, QWidget *widget = nullptr)
{

        QPen dotsPen(Qt::blue, 10,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QPen linesPen(Qt::black, 6,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QPen polPen(Qt::green, 3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QPen trianglesPen(Qt::red, 3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QPen coveredTriPen(Qt::yellow, 3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QPen cameraPen(Qt::gray, 6,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        //QPen polyPen(Qt::blue, 3,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QPen coordPen(Qt::blue, 6,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
        QPen trinumPen(Qt::green, 7,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);

        QBrush filler(Qt::yellow);

        /*
        if(finished && !tract){


            painter->setPen(trianglesPen);
            for(int i = 0; i < tpolygon.size(); i++){
                painter->drawPolygon(tpolygon[i]);

            }

            painter->setPen(cameraPen);
            painter->drawPoint(camera);
        }else if(finished && tract){
            painter->setPen(trianglesPen);
            for(int i = 0; i < specialT.size(); i++){
                painter->drawPolygon(tpolygon[i]);

            }
            painter->setPen(coveredTriPen);
            for(int i = 0; i < visibleTriangles.size(); i++){
                painter->fillPath(visibleTriangles[i],filler);
            }

            painter->setPen(linesPen);
            painter->drawLines(lines);

            visibleTriangles.clear();

            painter->setPen(cameraPen);
            painter->drawPoint(camera);
        }else{
            painter->setPen(linesPen);
            painter->drawLines(lines);
        }


        for(int i = 0; i < pVector.size(); i ++){
            painter->setPen(dotsPen);
            painter->drawPoint(pVector[i]);

            if(i < pVector.size()-1 ){
                painter->setPen(coordPen);
                //painter->drawText(QPointF(pVector[i].rx()+4,pVector[i].ry()+20) , "P"+ QString::number(i) + "(" + QString::number(pVector[i].rx()) + "," + QString::number(pVector[i].ry()) +")");

            }
        }

        painter->setBrush(filler);
        //painter->drawPath(path);
        */


        if(finished){
            if(afisare == true){
            painter->setPen(trianglesPen);
                for(int i = 0; i < tpolygon.size(); i++){
                    painter->drawPolygon(tpolygon[i]);

                }
            }
            painter->setPen(coveredTriPen);
            for(int i = 0; i < visibleTriangles.size(); i++){
                painter->fillPath(visibleTriangles[i],filler);
                painter->drawPath(visibleTriangles[i]);
            }
            painter->setPen(linesPen);
            painter->drawLines(lines);

            visibleTriangles.clear();

            painter->setPen(cameraPen);
            painter->drawPoint(camera);
        }else{
            painter->setPen(linesPen);
            painter->drawLines(lines);
        }



        painter->setPen(dotsPen);

        for(int i = 0; i < pVector.size(); i ++){

            painter->drawPoint(pVector[i]);

            if(i < pVector.size()-1 ){
                //painter->setPen(coordPen);
                //painter->drawText(QPointF(pVector[i].rx()+4,pVector[i].ry()+20) , "P"+ QString::number(i) + "(" + QString::number(pVector[i].rx()) + "," + QString::number(pVector[i].ry()) +")");

            }
        }

        if(afisare == true){
            painter->setPen(trinumPen);
            for(int i = 0; i < tpolygon.size(); i ++){
                painter->drawText(QPointF((tpolygon[i][0].rx()+tpolygon[i][1].rx()+tpolygon[i][2].rx())/3,(tpolygon[i][0].ry()+tpolygon[i][1].ry()+tpolygon[i][2].ry())/3) , "Tr"+ QString::number(i));
            }
        }

}

void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QPointF p = event->buttonDownScenePos(Qt::LeftButton);

    if(lastP != nullptr && (p.rx() - lastP->rx())*(p.rx() - lastP->rx()) + (p.ry() - lastP->ry())*(p.ry() - lastP->ry()) < 30){
        update();
        QGraphicsItem::mousePressEvent(event);
        return;
    }

    if(!finished){
        if(lastP == nullptr){
            lastP = new QPointF();
            firstP = new QPointF();
            path.moveTo(p.x(),p.y());
            *lastP = p;
            *firstP = p;
            pVector.push_back(p);
        }else{

            if((p.rx() - firstP->rx())*(p.rx() - firstP->rx()) + (p.ry() - firstP->ry())*(p.ry() - firstP->ry()) < 300
                    && pVector.size() > 1){
                p = *firstP;
                finished = true;
                lines.push_back(QLineF(*lastP,p));
                path.lineTo(p.x(),p.y());

                if(autointersectie()){
                    reset();

                    if(tpolygon.size() > 0)
                    delete(tri);


                    finished = false;
                    tract = false;

                    QString s = "Poligonul nu trebuie sa se autointersecteze!";

                    /*
                    if(deCateOriAGresitProstu == 0)
                        s = "Baga ba poligonu' cum trebuie!!";
                    else if(deCateOriAGresitProstu == 1)
                        s = "Nu ca esti chiar prost.. Trebuie sa nu se autointersecteze!!";
                    else if(deCateOriAGresitProstu == 2){
                        s = "Hai du-te si citeste putin despre poligoane ca sa nu te injur!";
                    }else{
                        s = "BAAAIAT PROST!!";
                    }
                    */



                    QMessageBox mBox(QMessageBox::Critical,"Poligonul!!",s);
                    mBox.exec();

                    deCateOriAGresitProstu++;

                    QGraphicsItem::mousePressEvent(event);

                    return;
                }else{
                    if(deCateOriAGresitProstu){
                        //QMessageBox mBox(QMessageBox::Information,"Bravo, bravo!!","A dat Dumnezeu... Baiat PROST!!");
                        //mBox.exec();
                    }
                    deCateOriAGresitProstu = 0;


                }

                //lines.clear();
            }else{
            lines.push_back(QLineF(*lastP,p));
            path.lineTo(p.x(),p.y());
            }
            pVector.push_back(p);
            *lastP = p;
        }
    }

    QString s = "<p style = 'color:green'>Ati adaugat punctul de coordonate x:" + QString::number(p.rx()) + " y:" + QString::number(p.ry()) + "</p>";


    if(finished) {
        s += "<p style = 'color:red'>Ati inchis poligonul!</p>";

        //incepe magia



        //item->tri = tri;
        std::vector<std::pair<int,int> > vec;
        for(int i = 0; i < pVector.size()-1 ;i++){
            vec.push_back({pVector[i].y(),pVector[i].x()});
        }
        v = new Visibility(vec);

        vec = v->getTriangulation();

        for(int i = 0; i < vec.size() ; i += 3){
            tpolygon.push_back(QPolygonF({QPointF(vec[i].second,vec[i].first),QPointF(vec[i+1].second,vec[i+1].first),QPointF(vec[i+2].second,vec[i+2].first)}));
        }

    }

       t->append(s);


    update();
    QGraphicsItem::mousePressEvent(event);
}

void MyItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    QGraphicsItem::mouseMoveEvent(event);
}

void MyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
