#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pitch.h"
#include "physicsengine.h"
//#include <QGraphicsScene> //include w pitch.h
#include <QTimer>
#include <QGraphicsEllipseItem>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



public slots:
    void updateView();
    void goStep();

    void pause();
    void resume();
    void start();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;

    std::vector<QGraphicsEllipseItem*> ellipses;

    Pitch pitch;
    PhysicsEngine engine;

    QTimer timer;
    int actualTime;
    QTimer gameTimer;
};

#endif // MAINWINDOW_H
