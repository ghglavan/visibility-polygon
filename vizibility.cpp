#include "vizibility.h"



Visibility::Visibility( /*stringstream& ss*/ vector<pair<int,int> > vect )
{
    list = new List<Point*>(); // the list with the points
    //ss >> number_of_vertices;
    number_of_vertices = vect.size();
    int x, y;
    for( int i=0; i<number_of_vertices; ++i )
    {
        //ss >> x >> y;
        list->push_back( new Point(vect[i].first,vect[i].second));
    }
    computeTriangulation();
}

Visibility::~Visibility()
{
    delete list;
}


void Visibility::toClockwise()
{
    List<Point* >* new_list = new List<Point* >();
    Node<Point* >* it = list->getFirst();

    while(1)
    {
        new_list->push_back(it->getInfo());
        if( it->getPrev() == list->getFirst() )
            break;
        it = it->getPrev();
    }

    delete list;
    list = new_list;
}

bool Visibility::checkClockwise()
{
    int sum = 0;
    Node<Point*>*it = list->getFirst();
    for( int i = 0; i<number_of_vertices; ++i )
    {
        sum += curba( it->getInfo()->coord, it->getNext()->getInfo()->coord, it->getNext()->getNext()->getInfo()->coord );
        it = it->getNext();
    }
    if( sum < 0 )
        return true;
    return false;
}

void Visibility::setEdges()
{
    Node<Point*>* it = list->getFirst();
    for( int i=0; i<number_of_vertices; ++i )
    {
        it->getInfo()->firstEdge = it->getPrev()->getInfo()->secondEdge;
        it->getInfo()->secondEdge = new Edge( it->getInfo(), it->getNext()->getInfo() );
        it = it->getNext();
    }
    list->getFirst()->getInfo()->firstEdge = list->getLast()->getInfo()->secondEdge;
}

void Visibility::getTriangles()
{
    int nr = 0;
    Node<Point*>* it = list->getFirst();

    while( nr < number_of_vertices - 3 )
    {
        if( verificare( it->getPrev(), it, it->getNext()/*, list*/ ) == true )
        {
            Point* p1 = new Point(it->getPrev()->getInfo()->coord.first, it->getPrev()->getInfo()->coord.second);
            Point* p2 = new Point(it->getNext()->getInfo()->coord.first, it->getNext()->getInfo()->coord.second);

            it->getInfo()->firstEdge->a = p1;
            it->getInfo()->secondEdge->b = p2;
            p1->secondEdge = it->getInfo()->firstEdge;
            p2->firstEdge  = it->getInfo()->secondEdge;

            p2->secondEdge = new Edge( p2, p1 );
            p1->firstEdge = p2->secondEdge;

            it->getPrev()->getInfo()->secondEdge = new Edge( it->getPrev()->getInfo(), it->getNext()->getInfo() );
            it->getNext()->getInfo()->firstEdge = it->getPrev()->getInfo()->secondEdge;

            it->getPrev()->getInfo()->secondEdge->dual = p2->secondEdge;
            p2->secondEdge->dual = it->getPrev()->getInfo()->secondEdge;

            tri* t = new tri( it->getInfo()->firstEdge, it->getInfo()->secondEdge, p2->secondEdge );

            it->getInfo()->firstEdge->t = t;
            it->getInfo()->secondEdge->t = t;
            p2->secondEdge->t = t;

            vec.push_back(t);

            Node<Point* >* del = it;
            it = it->getNext();
            list->erase(del);
            ++nr;
        }
        else
        {
            it = it->getNext();
        }
    }

    tri* t = new tri( list->getFirst()->getInfo()->firstEdge, list->getFirst()->getInfo()->secondEdge, list->getFirst()->getNext()->getInfo()->secondEdge );
    list->getFirst()->getInfo()->firstEdge->t = t;
    list->getFirst()->getInfo()->secondEdge->t = t;
    list->getFirst()->getNext()->getInfo()->secondEdge->t = t;
    vec.push_back(t);
}

void Visibility::computeTriangulation()
{
    bool clockwise = checkClockwise();
    if( !clockwise )
    {
        toClockwise();
    }

    /*Node<Point*>* it = list->getFirst();
    for( int i=0; i < number_of_vertices; ++ i )
    {
        cout << *(it->getInfo()) << endl;
        it = it->getNext();
    } */ // bucata asta de cod o lasa pentru a verifica mai tarziu daca merge cacatul asta de algoritm :D

    setEdges();
    getTriangles();

    /*cout << endl;
    for( unsigned i = 0; i < vec.size(); ++ i )
    {
        cout << *(vec[i]) << endl;
    }*/
}



vector<pair<int,int> > Visibility::getTriangulation()
{
    vector<pair<int,int> > v;

    for( int i = 0; i < vec.size(); ++ i )
    {
        v.push_back(make_pair(vec[i]->e1->a->coord.first, vec[i]->e1->a->coord.second));
        v.push_back(make_pair(vec[i]->e1->b->coord.first, vec[i]->e1->b->coord.second));
        v.push_back(make_pair(vec[i]->e2->b->coord.first, vec[i]->e2->b->coord.second));
    }

    return v;
}





double Visibility::determinant( pair<double,double> a, pair<double,double> b, pair<double,double> c )
{
    return (a.first * b.second ) + (b.first * c.second ) + (c.first * a.second ) - (c.first * b.second) - (c.second * a.first) - (b.first * a.second);
}

int Visibility::curba( pair<double,double> a, pair<double,double> b, pair<double,double> c )
{
    double det = determinant(a,b,c);
    if( det < 0.0 )
        return -1;
    if( det > 0.0 )
        return 1;
    return 0;
}

bool Visibility::inTriunghi( pair<double,double> a, pair<double,double> b, pair<double,double> c, pair<double,double> pct )
{
    int nr = 0;
    nr += curba( a, b, pct );
    nr += curba( b, c, pct );
    nr += curba( c, a, pct );
    if( nr == 3 || nr == -3 || nr == 2 || nr == -2 )
        return true;
    return false;
}

bool Visibility::verificare( Node<Point*>* a, Node<Point*>* b, Node<Point*>* c /*, List<Point*>* list*/ )
{

    if( determinant( a->getInfo()->coord, b->getInfo()->coord, c->getInfo()->coord ) > 0.0 )
        return false;

    for( Node<Point*>* it = c->getNext(); it != a; it = it->getNext() )
    {
        if( inTriunghi( a->getInfo()->coord, b->getInfo()->coord, c->getInfo()->coord, it->getInfo()->coord ) == true )
        {	return false; }
    }
    return true;
}

pair<double,double> Visibility::intersect( Point* pmisto, Point* celalalt, Edge* muchie )
{
    pair<double, double> a = pmisto->coord;
    pair<double, double> b = celalalt->coord;

    pair<double, double> c = muchie->a->coord;
    pair<double, double> d = muchie->b->coord;


    double a1, a2, b1, b2, c1, c2;

    a1 = b.second - a.second;
    b1 = a.first - b.first;
    c1 = a.second * b.first - a.first * b.second;

    a2 = d.second - c.second;
    b2 = c.first - d.first;
    c2 = c.second * d.first - c.first * d.second;
    double x = (b1 * c2 - c1 * b2)/ ( a1 * b2 - b1 * a2 );
    double y = (a2 * c1 - a1 * c2)/ ( a1 * b2 - b1 * a2 );

    pair<double,double> s = make_pair(x,y);

    return s;
}

void Visibility::functie( tri* t, Edge* e, Point* p1, Point* p2, Point* pmisto )
{
    Edge *e1;
    Edge *e2;

    if( t->e1 == e )
    {
        e1 = t->e2;
        e2 = t->e3;
    }
    else if( t->e2 == e )
    {
        e1 = t->e3;
        e2 = t->e1;
    }
    else
    {
        e1 = t->e1;
        e2 = t->e2;
    }

    // pentru muchia e1 :

    if( curba( pmisto->coord, p1->coord, e1->b->coord ) < 0 )
    {
        Point *cel_mai_misto_point = nullptr;

        if( curba(pmisto->coord, p2->coord, e1->b->coord ) >= 0 )
        {
            cel_mai_misto_point = e1->b;
        }
        else
        {
            cel_mai_misto_point = p2;
        }

        // aici mai ramane de mers mai departe :D

        if( e1->dual == nullptr ) // inseamna ca ii calculam punctele de intersectie :)
        {
            pair<double, double> q1 = intersect( pmisto, p1, e1 );
            pair<double, double> q2 = intersect( pmisto, cel_mai_misto_point, e1 );
            /*cout << *pmisto << "   " <<  q1.first << " " << q1.second << endl ;
            cout <<  *pmisto << "   " <<q2.first << " " << q2.second << endl;
            cout << endl;*/
            inters.push_back(make_pair(q1.first, q1.second));
            inters.push_back(make_pair(q2.first, q2.second));
        }
        else  // mergem mai departe :)
        {
            functie( e1->dual->t, e1->dual, p1 , cel_mai_misto_point , pmisto );
        }
    }

    // pentru muchia e2:

    if( curba( pmisto->coord, p2->coord, e2->a->coord ) > 0 )
    {
        Point *cel_mai_misto_point = nullptr;


        if( curba( pmisto->coord, p1->coord, e2->a->coord ) <= 0 )
        {
            cel_mai_misto_point = e2->a;
        }
        else
        {
            cel_mai_misto_point = p1;
        }

        // aici mai ramane de mers mai departe :)

        if( e2->dual == nullptr ) // acelasi lucru ca mai sus :)
        {
            pair<double,double> q1 = intersect( pmisto, cel_mai_misto_point, e2 );
            pair<double,double> q2 = intersect( pmisto, p2, e2 );
            /*cout << *pmisto << "   " << q1.first << " " << q1.second << endl;
            cout << *pmisto << "   " << q2.first << " " << q2.second << endl;
            cout << endl;*/
            inters.push_back(make_pair(q1.first, q1.second));
            inters.push_back(make_pair(q2.first, q2.second));
        }
        else
        {
            functie( e2->dual->t, e2->dual, cel_mai_misto_point, p2, pmisto );
        }
    }
}


vector<pair<int, int> > Visibility::getIntersections( int x, int y )
{
    inters.clear();

    Point* pmisto = new Point(x,y);

    for( unsigned i = 0; i < vec.size(); ++ i )
    {
        int nr = 0;
        nr += curba( vec[i]->e1->a->coord, vec[i]->e1->b->coord, pmisto->coord );
        nr += curba( vec[i]->e2->a->coord, vec[i]->e2->b->coord, pmisto->coord );
        nr += curba( vec[i]->e3->a->coord, vec[i]->e3->b->coord, pmisto->coord );
        if( nr == 3 || nr == -3 ) // punctul ales este chiar in interiorul triunghiului
        {
            if( vec[i]->e1->dual != nullptr ) // apelam functia pentru ca poate sa vada mai mult :)
            {
                functie( vec[i]->e1->dual->t, vec[i]->e1->dual, vec[i]->e1->dual->b, vec[i]->e1->dual->a, pmisto );
            }
            else // doar afisam :)
            {
                /*cout << *pmisto << "   " << *(vec[i]->e1->a) << endl;
                cout << *pmisto << "   " << *(vec[i]->e1->b) << endl;
                cout << endl;*/
                inters.push_back(make_pair(vec[i]->e1->a->coord.first, vec[i]->e1->a->coord.second));
                inters.push_back(make_pair(vec[i]->e1->b->coord.first, vec[i]->e1->b->coord.second));
            }

            if( vec[i]->e2->dual != nullptr ) // apelam functia pentru ca poate sa vada mai mult :)
            {
                functie( vec[i]->e2->dual->t, vec[i]->e2->dual, vec[i]->e2->dual->b, vec[i]->e2->dual->a, pmisto );
            }
            else // doar afisam :)
            {
                /*cout << *pmisto << "   " << *(vec[i]->e2->a) << endl;
                cout << *pmisto << "   " << *(vec[i]->e2->b) << endl;
                cout << endl;*/
                inters.push_back(make_pair(vec[i]->e2->a->coord.first, vec[i]->e2->a->coord.second));
                inters.push_back(make_pair(vec[i]->e2->b->coord.first, vec[i]->e2->b->coord.second));
            }

            if( vec[i]->e3->dual != nullptr ) // apelam functia pentru ca poate sa vada mai mult :)
            {
                functie( vec[i]->e3->dual->t, vec[i]->e3->dual, vec[i]->e3->dual->b, vec[i]->e3->dual->a, pmisto );
            }
            else // doar afisam :)
            {
                /*cout << *pmisto << "   " << *(vec[i]->e3->a) << endl;
                cout << *pmisto << "   " << *(vec[i]->e3->b) << endl;
                cout << endl;*/
                inters.push_back(make_pair(vec[i]->e3->a->coord.first, vec[i]->e3->a->coord.second));
                inters.push_back(make_pair(vec[i]->e3->b->coord.first, vec[i]->e3->b->coord.second));
            }

            break;
        }
        else if( nr == 2 || nr == -2 ) // punctul ales este pe o dreapta a triunghiului :D
        {	// mai intai verificam pe ce muchie e :)
            //cout << "Punctul e pe o muchie " << endl;
            //cout << *vec[i] << endl;

            if( curba( vec[i]->e2->a->coord, vec[i]->e2->b->coord, pmisto->coord) == 0 )  // daca e pe muchia e3
            {
                //cout << "Sunt in primul if " << endl;
                Edge* aux = vec[i]->e1;
                vec[i]->e1 = vec[i]->e2;
                vec[i]->e2 = vec[i]->e3;
                vec[i]->e3 = aux;
            }
            else if( curba( vec[i]->e3->a->coord, vec[i]->e3->b->coord, pmisto->coord) == 0 ) // daca e pe muchia e2
            {
                //cout << "Sunt in  al doilea if " << endl;
                Edge* aux = vec[i]->e1;
                vec[i]->e1 = vec[i]->e3;
                vec[i]->e3 = vec[i]->e2;
                vec[i]->e2 = aux;
            }

            if( vec[i]->e2->dual != nullptr )
            {
                //cout << "Ma duc in triunghiul " << *(vec[i]->e2->dual->t) << endl;
                functie( vec[i]->e2->dual->t, vec[i]->e2->dual, vec[i]->e2->dual->b, vec[i]->e2->dual->a, pmisto );
            }
            else
            {
                //cout << "Nu ma duc " << endl;
                /*cout << *pmisto << "   " << *(vec[i]->e2->a) << endl;
                cout << *pmisto << "   " << *(vec[i]->e2->b) << endl;
                cout << endl;*/
                inters.push_back(make_pair( vec[i]->e2->a->coord.first, vec[i]->e2->a->coord.second));
                inters.push_back(make_pair( vec[i]->e2->b->coord.first, vec[i]->e2->b->coord.second));
            }

            if( vec[i]->e3->dual != nullptr )
            {
                //cout << "Ma duc in triunghiul " << *(vec[i]->e2->dual->t) << endl;
                functie( vec[i]->e3->dual->t, vec[i]->e3->dual, vec[i]->e3->dual->b, vec[i]->e3->dual->a, pmisto );
            }
            else
            {
                //cout << "Nu ma duc " << endl;
                /*cout << *pmisto << "   " << *(vec[i]->e3->a) << endl;
                cout << *pmisto << "   " << *(vec[i]->e3->b) << endl;
                cout << endl;*/
                inters.push_back(make_pair( vec[i]->e3->a->coord.first, vec[i]->e3->a->coord.second));
                inters.push_back(make_pair( vec[i]->e3->b->coord.first, vec[i]->e3->b->coord.second));
            }

            if( vec[i]->e1->dual != nullptr ) // aici verificam si in celalalt triunghiu pe care il vede :D
            {
                //cout << "Am intrat in dual !!! " << endl;

                tri* t = vec[i]->e1->dual->t;
                //cout << *t << endl;
                Edge* e = vec[i]->e1->dual;

                if( e == t->e1 )
                {
                    if( t->e2->dual != nullptr )
                    {
                        functie( t->e2->dual->t, t->e2->dual, t->e2->dual->b, t->e2->dual->a, pmisto );
                    }
                    else
                    {
                        /*cout << *pmisto << "   " << *(t->e2->a) << endl;
                        cout << *pmisto << "   " << *(t->e2->b) << endl;
                        cout << endl;*/
                        inters.push_back(make_pair(t->e2->a->coord.first, t->e2->a->coord.second));
                        inters.push_back(make_pair(t->e2->b->coord.first, t->e2->b->coord.second));
                    }

                    if( t->e3->dual != nullptr )
                    {
                        functie( t->e3->dual->t, t->e3->dual, t->e3->dual->b, t->e3->dual->a, pmisto );
                    }
                    else
                    {
                        /*cout << *pmisto << "   " << *(t->e3->a) << endl;
                        cout << *pmisto << "   " << *(t->e3->b) << endl;
                        cout << endl;*/
                        inters.push_back(make_pair(t->e3->a->coord.first, t->e3->a->coord.second));
                        inters.push_back(make_pair(t->e3->b->coord.first, t->e3->b->coord.second));
                    }
                }
                else if( e == t->e2 )
                {
                    if( t->e1->dual != nullptr )
                    {
                        functie( t->e1->dual->t, t->e1->dual, t->e1->dual->b, t->e1->dual->a, pmisto );
                    }
                    else
                    {
                        /*cout << *pmisto << "   " << *(t->e1->a) << endl;
                        cout << *pmisto << "   " << *(t->e1->b) << endl;
                        cout << endl;*/
                        inters.push_back(make_pair(t->e1->a->coord.first, t->e1->a->coord.second));
                        inters.push_back(make_pair(t->e1->b->coord.first, t->e1->b->coord.second));
                    }

                    if( t->e3->dual != nullptr )
                    {
                        functie( t->e3->dual->t, t->e3->dual, t->e3->dual->b, t->e3->dual->a, pmisto );
                    }
                    else
                    {
                        /*cout << *pmisto << "   " << *(t->e3->a) << endl;
                        cout << *pmisto << "   " << *(t->e3->b) << endl;
                        cout << endl;*/
                        inters.push_back(make_pair(t->e3->a->coord.first, t->e3->a->coord.second));
                        inters.push_back(make_pair(t->e3->b->coord.first, t->e3->b->coord.second));
                    }
                }
                else
                {
                    if( t->e2->dual != nullptr )
                    {
                        functie( t->e2->dual->t, t->e2->dual, t->e2->dual->b, t->e2->dual->a, pmisto );
                    }
                    else
                    {
                        /*cout << *pmisto << "   " << *(t->e2->a) << endl;
                        cout << *pmisto << "   " << *(t->e2->b) << endl;
                        cout << endl;*/
                        inters.push_back(make_pair(t->e2->a->coord.first, t->e2->a->coord.second));
                        inters.push_back(make_pair(t->e2->b->coord.first, t->e2->b->coord.second));
                    }

                    if( t->e1->dual != nullptr )
                    {
                        functie( t->e1->dual->t, t->e1->dual, t->e1->dual->b, t->e1->dual->a, pmisto );
                    }
                    else
                    {
                        /*cout << *pmisto << "   " << *(t->e1->a) << endl;
                        cout << *pmisto << "   " << *(t->e1->b) << endl;
                        cout << endl;*/
                        inters.push_back(make_pair(t->e1->a->coord.first, t->e1->a->coord.second));
                        inters.push_back(make_pair(t->e1->b->coord.first, t->e1->b->coord.second));
                    }
                }
            }
            break;
        }

    }

    return inters;

}
