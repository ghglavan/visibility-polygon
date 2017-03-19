#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QtCore>
#include <QGridLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("Visibility Polygon");

    //w.showMaximized();

    w.show();

    return a.exec();
}
