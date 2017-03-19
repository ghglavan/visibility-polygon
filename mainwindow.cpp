#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myitem.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    br = ui->textBrowser;

    // create our object and add it to the scene
    item = new MyItem(br);

    scene = new GraphicsView(this,item);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setMouseTracking(true);

    scene->addItem(item);

    ui->afisare->setStyleSheet("background-color:#FFFF66");
    ui->info->setStyleSheet("background-color:#FFFF66");
    ui->clear->setStyleSheet("background-color:#FF0000");


    ui->graphicsView->setStyleSheet("background-color:#2e3035");
    this->setStyleSheet("background-color:#1c1504");

    ui->textBrowser->setStyleSheet("background-color:#2e3035");


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::resizeEvent(QResizeEvent* event)
{
   //QSize s = event->oldSize();
   //item->area = new QRectF();
   //*(item->area) = QRectF(0,0,s.rwidth(),s.rheight());
   QMainWindow::resizeEvent(event);

}


//reset
void MainWindow::on_clear_clicked()
{
    item->reset();

    if(item->tpolygon.size() > 0)
    delete(tri);


    item->finished = false;
    item->tract = false;
}



void MainWindow::on_info_clicked()
{
    QMessageBox mBox(QMessageBox::Information,"Information","Lorem ipsum");
    mBox.exec();
}

void MainWindow::on_afisare_clicked()
{
    item->afisare = !item->afisare;

    item->updatee();

}
