
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <vector>

namespace Ui {
class MainWindow;
}
struct Circle{
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

    QPoint ant_click, fly_click, ant_man, fly_man, dvizh[4], min_len, dvizh_ant;
    int rectSize = 20, random_size;
    QVector<QPoint> path;
    Circle tree;
    bool contains(Circle c, QPoint p);
    float len;
};

#endif // MAINWINDOW_H



