#include "triangulare.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

triangulare::triangulare(QVector<QPointF> vp)
{
    pVector = new QVector<QPointF>(vp);



    npoints = (*pVector).size();

    polyvector =  new QVector<QPolygonF>();



    pointType = new QVector<int>(npoints);

    earCutter = concavePoints = 0;

    updatePoints();

    pVectorc = new QVector<QPointF>(*pVector);

    pointTypec = new QVector<int>(*pointType);

}

triangulare::~triangulare(){
    if(pVector != nullptr && !pVector->empty())
    pVector->clear();
    if(pVectorc != nullptr && !pVectorc->empty())
    pVectorc->clear();
    if(pointType != nullptr && !pointType->empty())
    pointType->clear();
}

bool triangulare::intersection(QPointF p1,QPointF p2,QPointF p3,QPointF p4 ){
    if(delta(p1,p2,p3) * delta(p1,p2,p4) < 0 && delta(p3,p4,p1) * delta(p3,p4,p2) < 0 ){
            if(delta(p1,p2,p3) != 0){

                return true;

            }else{
                vector<QPointF> p{p1,p2,p3,p4};

                sort(p.begin(),p.end(),[](QPointF a,QPointF b){
                    if(a.rx() == b.rx()){
                        return a.ry() < b.ry();
                    }else{
                        return a.rx() < b.rx();
                    }
                });
                if((p[0] == p1 && p[1] == p2) || (p[0] == p3 && p[1] == p4) ){
                    return false;
                }else{
                    return true;
                }
            }

        }else{
            return false;
        }
}


QVector<QLineF> triangulare::findSpecialLines(QVector<int> sT,QPointF camera){
    QVector<QLineF> ret;
    for(int i = 0; i < polyvector->size(); i++){
        if(sT[i] != 1){
            QVector<QPointF> points;
            for(int j = 0; j < pVectorc->size(); j++){
                //if((*pointType)[j] == 0){
                    for(int k = 0; k < 3; k++){
                        QPointF intersectie = intersectionPoint((*polyvector)[i][k],(*polyvector)[i][(k+1)%3],(*pVectorc)[j],camera);
                        if(delta(intersectie,(*polyvector)[i][k],(*polyvector)[i][(k+1)%3]) == 0){
                            points.push_back(intersectie);
                        }
                    }
                    if(points.size() == 2){
                        ret.push_back(QLineF(points[0],points[1]));
                        std::cout<<" p1: "<<points[0].x()<<" "<<points[0].y()<<" p2 "<<points[1].x()<<" "<<points[1].y()<<std::endl;
                    }
                //}
            }
        }
    }
}

QPointF triangulare::intersectionPoint(QPointF p1,QPointF p2,QPointF p3,QPointF p4){
    QPointF temp;

        temp.rx() = -(((p1.x()*p2.y() - p1.y()*p2.x())*(p3.x()-p4.x()) - (p1.x()-p2.x())*(p3.x()*p4.y()-p3.y()*p4.x())) / ((p1.y()-p2.y())*(p3.x()-p4.x()) - (p1.x()-p2.x())*(p3.y()-p4.y())));
        temp.ry() = (((p1.y()-p2.y())*(p3.x()*p4.y()-p3.y()*p4.x()) - (p1.x()*p2.y() - p1.y()*p2.x()) * (p3.y()-p4.y()) ) / ((p1.y()-p2.y())*(p3.x()-p4.x()) - (p1.x()-p2.x())*(p3.y()-p4.y())));

    return temp;
}


QVector<int> triangulare::trViz(QPointF q){

    QVector<int> v(polyvector->size());

    for(int i = 0; i < polyvector->size(); i++){
        v[i] = 1;
        QPointF p1 = (*polyvector)[i][0];
        QPointF p2 = (*polyvector)[i][1];
        QPointF p3 = (*polyvector)[i][2];


        if(  abs(delta(q,p2,p3)) == abs(delta(q,p1,p3)) + abs(delta(q,p1,p2)) + abs(delta(p2,p1,p3))
                || abs(delta(q,p1,p3)) == abs(delta(q,p2,p3)) + abs(delta(q,p2,p1)) + abs(delta(p2,p1,p3))
                || abs(delta(q,p1,p2)) == abs(delta(q,p3,p1)) + abs(delta(q,p3,p2)) + abs(delta(p2,p1,p3))
                ){
                    int ok = 0;
                    for(int j = 0; j < 3; j ++){

                        for(int k = 0 ;k < pVectorc->size()-1 ;k++){
                            if(k == 0){
                                //if((*pointTypec)[k] == 0){
                                    if(intersection(q,(*polyvector)[i][j],(*pVectorc)[pVectorc->size()-2],(*pVectorc)[0])
                                            || intersection(q,(*polyvector)[i][j],(*pVectorc)[0],(*pVectorc)[1])
                                            ){
                                        v[i] += j+2;
                                        ok = 1;
                                        break;
                                    }
                                //}
                            }else{
                                //if((*pointTypec)[k] == 0){
                                    if(intersection(q,(*polyvector)[i][j],(*pVectorc)[k-1],(*pVectorc)[k])
                                            || intersection(q,(*polyvector)[i][j],(*pVectorc)[k],(*pVectorc)[k+1])){
                                        v[i] += j+2;
                                        ok = 1;
                                        break;
                                  //  }
                                }
                            }
                        }
                    }

            if(ok == 0)
            v[i]++;
            //v[i] = 0;
            continue;
        }


        for(int j = 0; j < 3; j ++){

            for(int k = 0 ;k < pVectorc->size()-1 ;k++){
                if(k == 0){
                    //if((*pointTypec)[k] == 0){
                        if(intersection(q,(*polyvector)[i][j],(*pVectorc)[pVectorc->size()-2],(*pVectorc)[0])
                                || intersection(q,(*polyvector)[i][j],(*pVectorc)[0],(*pVectorc)[1])
                                ){
                            v[i] += j+2;
                            break;
                        }
                    //}
                }else{
                    //if((*pointTypec)[k] == 0){
                        if(intersection(q,(*polyvector)[i][j],(*pVectorc)[k-1],(*pVectorc)[k])
                                || intersection(q,(*polyvector)[i][j],(*pVectorc)[k],(*pVectorc)[k+1])){
                            v[i] += j+2;
                            break;
                      //  }
                    }
                }
            }
        }
    }

    std::cout<<std::endl;
    for(int i = 0 ; i < v.size(); i++){
        std::cout<<v[i]<<" ";
    }
    std::cout<<std::endl;
    return v;
}



void triangulare::updatePoints(){

    delete pointType;

    concavePoints = 0;

    pointType = new QVector<int>(npoints);

    for(int i = 0; i < npoints-1; i++) {
        if(i == 0){
            if(convex((*pVector)[npoints-2],(*pVector)[i],(*pVector)[i+1])){
                (*pointType)[i] = 1;
            }else{
                (*pointType)[i] = 0;
                concavePoints++;
            }
        }else{
            if(convex((*pVector)[i-1],(*pVector)[i],(*pVector)[i+1])){
                (*pointType)[i] = 1;
            }else{
                (*pointType)[i] = 0;
                concavePoints++;
            }
        }
    }
    if(concavePoints > npoints/2){
        for(int i = 0; i < npoints/2; i++){
            QPointF p = (*pVector)[i];
            (*pVector)[i] = (*pVector)[npoints-i-1];
            (*pVector)[npoints-i-1] = p;

        }
        updatePoints();
    }

}

double triangulare::abs(double d){
    return d > 0 ? d  : -d;
}

bool triangulare::triangleContainsPoints(QPointF p1,QPointF p2,QPointF p3){
    int i = 0;
    bool pointsInside = false;

    while(i < npoints - 1 && !pointsInside){
        if((*pointType)[i] == 0 &&
                ((*pVector)[i] != p1 && (*pVector)[i] != p2 && (*pVector)[i] != p3)) {
            if(abs(delta(p1,p2,p3))  == abs(delta(p1,p2,(*pVector)[i])) + abs(delta(p2,p3,(*pVector)[i])) + abs(delta(p1,p3,(*pVector)[i])) ){
                pointsInside = true;
            }
        }
        i++;
    }
    return pointsInside;
}

bool triangulare::ear(QPointF p1,QPointF p2,QPointF p3){
    if(concavePoints != 0){
        return !triangleContainsPoints(p1,p2,p3);
    }
    return true;
}

void triangulare::cutEar(){
    bool earHasBeenCut = false;
    int i = 0;

    while( (i < npoints - 1) && (!earHasBeenCut) && npoints > 4 ){
        if((*pointType)[i] == 1){
             if( i == 0 ){
                    if(ear((*pVector)[npoints-2],(*pVector)[i],(*pVector)[i+1])){
                        updatePoly(i);
                        earHasBeenCut = true;
                    }

            }else{
                if(ear((*pVector)[i-1],(*pVector)[i],(*pVector)[i+1])){
                    updatePoly(i);
                    earHasBeenCut = true;
                }
            }
        }
        i++;
    }
    if(npoints <= 4 && !earHasBeenCut){
        updatePoly(0);
    }


}

void triangulare::updatePoly(int index){
    if(npoints <= 4){
        polyvector->push_back(QVector<QPointF>{(*pVector)[1],(*pVector)[0],(*pVector)[2]});
    }else{
        if(index == 0){
            lines.push_back(QLineF((*pVector)[1],(*pVector)[npoints - 2]));
            polyvector->push_back(QVector<QPointF>{(*pVector)[npoints - 2],(*pVector)[0],(*pVector)[1]});
        }else{
            lines.push_back(QLineF((*pVector)[index-1],(*pVector)[index+1]));
            polyvector->push_back(QVector<QPointF>{(*pVector)[index-1],(*pVector)[index],(*pVector)[index+1]});
        }

        QVector<QPointF>::iterator it = pVector->begin();
        it = it+index;
        pVector->erase(it);
        npoints--;
        if(index == 0){
            (*pVector)[npoints-1] = (*pVector)[0];
        }
        updatePoints();
    }
}

double triangulare::delta(QPointF p1,QPointF p2, QPointF p3){
    return (p1.rx() - p2.rx())*(p2.ry() - p3.ry()) - (p2.rx() - p3.rx()) * (p1.ry() - p2.ry());
}

bool triangulare::convex(QPointF p1,QPointF p2,QPointF p3){

    if(delta(p1,p2,p3) > 0){
        return true;
    }
    return false;
}

