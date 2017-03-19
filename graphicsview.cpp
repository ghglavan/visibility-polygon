#include "graphicsview.h"



void GraphicsView::resizeEvent(QResizeEvent * v){

}

void GraphicsView::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    QPointF p = event->scenePos();
    if(item->finished && item->tpolygon.size() == item->pVector.size()-3){
        item->camera = p;

        std::vector<std::pair<int,int> > vec;

        vec  = item->v->getIntersections(p.y(),p.x());

        for(int i = 0; i < vec.size() ; i += 2){
            QPainterPath pa;

            pa.moveTo(vec[i].second,vec[i].first);
            pa.lineTo(vec[i+1].second,vec[i+1].first);
            pa.lineTo(p.x(),p.y());
            pa.lineTo(vec[i].second,vec[i].first);

            item->visibleTriangles.push_back(pa);

        }


        item->tract = true;
        item->updatee();

        //item->visibleTriangles.clear();

        for(int i = 0; i < vec.size(); i += 2){
            cout<<"Triunghiul nr "<<i<<endl;
            cout<<vec[i].second<<" "<<vec[i].first<<" "<<vec[i+1].second<< " "<<vec[i+1].first<<" "<<p.x()<<" "<<p.y();
            cout<<endl;
        }

    }

    QGraphicsScene::mouseMoveEvent(event);
}
