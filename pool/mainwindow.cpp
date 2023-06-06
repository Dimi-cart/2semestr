#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QBrush>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <math.h>
#include <stdbool.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    centralWidget()->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush brush1(Qt::green);
    QBrush brush2(Qt::blue);
    QBrush brush3(Qt::black);
    painter.setBrush(brush2);
    painter.drawRect(pool);



    for(int i = 0; i < clumb.length(); i++){
       painter.setBrush(brush1);
       painter.drawEllipse(clumb[i].center, clumb[i].radius, clumb[i].radius);
    }

    for(int i = 0; i < pod.length(); i++){
       painter.setBrush(brush3);
       painter.drawRect(pod[i]);
    }

}
//Circle.contains(QPoint) => yes/no

bool contains(Circle c, QPoint p) {
    QPoint tp = c.center - p; // расстояние от точки до центра круга
    return(QPoint::dotProduct(tp, tp) <= c.radius * c.radius);

}

bool CheckClumb(QRect rect, Circle cir) {
    int count = 0;
    if (contains(cir, rect.topLeft())) count++;
    if (contains(cir, rect.bottomRight())) count++;
    if (contains(cir, rect.bottomLeft())) count++;
    if (contains(cir, rect.topRight())) count++;

    if (count == 4) return true;
    if (count != 0) return false;
    return !rect.marginsAdded(QMargins(cir.radius, cir.radius, cir.radius, cir.radius)).contains(cir.center);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(!pool.contains(event->pos()))

    if(event->button() & Qt::LeftButton){
        if(!pool.contains(event->pos()))
            for(int i = 0; i < clumb.length(); i++) {
                QPoint diff = event->pos() - clumb[i].center;
                double len = sqrt(diff.x() * diff.x() + diff.y() * diff.y());

                if (len <= r * 2) return;
            }
            for(int i = 0; i < pod.length(); i++)
                if(!CheckClumb(pod[i], {event->pos(),10})) return;

            clumb.append({event->pos(), 10});
        }
        else if(event->button() & Qt::RightButton){
                    QRect flower = QRect(event->pos(), QSize(10,10));
                    if(!pool.contains(flower.center())){
                        for(QRect r: pod)
                            if(flower.intersects(r)) return;
                    }
                    for(int j = 0; j < clumb.length(); j++)
                        if(!CheckClumb(flower, clumb[j])) return;
                    pod.append(flower);



        }



    repaint();
}





//    c.center = event->pos(); задание центра и радиуса сюркла
//    c.radius = 20;
//    Circle c = {event->pos(), 20}; задание круга





