#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QGraphicsScene>
#include "myitem.h"
#include <QResizeEvent>
#include <QTextBrowser>
#include "triangulare.h"
#include "graphicsview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent* event);

private slots:



    void on_clear_clicked();



    void on_info_clicked();

    void on_afisare_clicked();

private:
    Ui::MainWindow *ui;
    GraphicsView *scene;
    MyItem *item;
    QTextBrowser *br;
    triangulare *tri;
};

#endif // MAINWINDOW_H
