#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QPoint>
#include <QSize>
#include <QVector>

namespace Ui {

class MainWindow;
}

struct Circle {
    QPoint center;
    int radius;

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);


private:
    Ui::MainWindow *ui;

    QRect pool = QRect(QPoint(100,100), QSize(400, 300));
    QRect rect;
    QVector<QRect> pod; //клумба
    QVector<Circle> clumb;
    int r = 10; // размеры цветка и клумбы

    // сиркл







};

#endif // MAINWINDOW_H
