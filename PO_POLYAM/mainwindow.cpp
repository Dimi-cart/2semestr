#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPoint>
#include <iostream>
#include <cstdlib>
#include <QLineF>
#include <QLine>
#include <math.h>

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



void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QBrush ant_brush(Qt::red);
    QBrush fly_brush(Qt::black);
    QBrush tree_brush(Qt::green);

    for (int i = 0; i < MainWindow::height(); i += rectSize)
        for (int j = 0; j < MainWindow::width(); j += rectSize)
            painter.drawRect(j, i, rectSize, rectSize); //сетка

    if (!ant_man.isNull()){ //муравей
        painter.setBrush(ant_brush);
        painter.drawEllipse(ant_man, 5, 5);
    }

    if (!fly_click.isNull()){ //муха
        painter.setBrush(fly_brush);
        painter.drawEllipse(fly_click, 5, 5);
    }
    if (!tree.center.isNull()){ // дерево
        painter.setBrush(tree_brush);
        painter.drawEllipse(tree.center, tree.radius, tree.radius);
    }
    if (!ant_click.isNull() && !fly_click.isNull()) // путь  // черная точка двигается без проблем, красная перерисовывает путь, но рисует линию вверх и поом верхняя точка соединяется с черной точкой
            for(int i = 0; i < path.size() - 1; i++){
                QPen path_brush(Qt::red);
                path_brush.setWidth(4);
                painter.setPen(path_brush);
                painter.drawLine(path[i], path[i + 1]);
            }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() & Qt::LeftButton){
        random_size = 35  + (rand() % 130);
        tree = {event->pos(), random_size};
    }

    if ((event->button() & Qt::RightButton) && (event->modifiers() & Qt::AltModifier)){ //красная точка
        ant_click = event->pos();
        for (int i = 0; i < MainWindow::height(); i += rectSize)
            for (int j = 0; j < MainWindow::width(); j += rectSize)
                if ((abs(i - ant_click.x()) < (rectSize / 2)) && ((j - ant_click.y()) < (rectSize / 2))){
                    ant_man = QPoint(i, j);
                    dvizh_ant = ant_man;
                    path.append(ant_man);
                }
    }
    if ((event->modifiers() & Qt::ControlModifier) && (event->button() & Qt::RightButton)){ // черная точка
        fly_click = event->pos() / rectSize * rectSize;

    }
    repaint();


    while (dvizh_ant != fly_click && !ant_man.isNull() && !fly_click.isNull()) {

        dvizh[0] = dvizh_ant + QPoint(-rectSize, 0);
        dvizh[1] = dvizh_ant + QPoint(0, rectSize);
        dvizh[2] = dvizh_ant + QPoint(rectSize, 0);
        dvizh[3] = dvizh_ant + QPoint(0, -rectSize);
        int min = 10000000;
        for (int i = 0; i < 4; i++){
            if (!contains(tree, dvizh[i]) && (path.size() == 1 || dvizh[i] != path[path.size() - 2])){
                len = (fly_click.x() - dvizh[i].x()) * (fly_click.x() - dvizh[i].x()) + (fly_click.y() - dvizh[i].y()) * (fly_click.y() - dvizh[i].y());
                if (len < min){
                    min = len;
                    min_len = dvizh[i];
                }
            }

        }
        path.append(min_len);
        dvizh_ant = min_len;
    }
    repaint();
}

bool MainWindow::contains(Circle c, QPoint p)
{
    QPoint c1(c.center - p);
    return (c.radius * c.radius > QPoint::dotProduct(c1, c1));
}
