#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <player.h>
#include "ball.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   scene = new QGraphicsScene(this);
   ui->graphicsView->setScene(scene);

   pitch.drawPitch(scene);

   QColor Acolor = pitch.teamA->color;
   QColor Bcolor = pitch.teamB->color;
   for(auto player : pitch.teamA->players){
       QGraphicsEllipseItem *e = scene->addEllipse(player->x,player->y,player->radius, player->radius, QPen(Acolor), QBrush(Acolor));
       ellipses.push_back(e);
   }
   for(auto player : pitch.teamB->players){
       QGraphicsEllipseItem *e = scene->addEllipse(player->x,player->y,player->radius, player->radius, QPen(Bcolor), QBrush(Bcolor));
       ellipses.push_back(e);
   }
   QGraphicsEllipseItem *e = scene->addEllipse(pitch.ball->x,pitch.ball->y,pitch.ball->radius, pitch.ball->radius, QPen(Qt::black), QBrush(Qt::white));
   ellipses.push_back(e);
   ui->labelTeamA->setText(QString::fromStdString(pitch.teamA->name));
   ui->labelTeamA->setStyleSheet("color: red");
   ui->labelTeamB->setText(QString::fromStdString(pitch.teamB->name));
   ui->labelTeamB->setStyleSheet("color: blue");

   connect(&pitch,SIGNAL(updated()),this,SLOT(updateView()));


   timer.setInterval(200);
   ui->pushButtonResume->setVisible(false);
   connect(&timer,SIGNAL(timeout()),this,SLOT(goStep()));
   //timer.start(); //startuje zegar button START
   //gameTimer.start(10000);


   connect(ui->pushButtonPause,SIGNAL(clicked()),this,SLOT(pause()));
   connect(ui->pushButtonResume,SIGNAL(clicked()),this,SLOT(resume()));
   connect(ui->pushButtonStart,SIGNAL(clicked()),this,SLOT(start()));
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::updateView()
{
  // scene->clear();
   int i = 0;
   for(const auto& player : pitch.teamA->players){
       ellipses[i]->setRect(player->x,player->y,player->radius, player->radius);
       if(player->inPoss) {
           ellipses[i++]->setPen(QPen(Qt::yellow));
       } else {
           ellipses[i++]->setPen(QPen(player->kitColor));
       }
      // scene->addEllipse(player.x,player.y,player.radius, player.radius, QPen(Qt::red), QBrush(Qt::red));
   }
   for(const auto& player : pitch.teamB->players){
       ellipses[i]->setRect(player->x,player->y,player->radius, player->radius);
       if(player->inPoss) {
           ellipses[i++]->setPen(QPen(Qt::yellow));
       } else {
           ellipses[i++]->setPen(QPen(player->kitColor));
       }
      // scene->addEllipse(player.x,player.y,player.radius, player.radius, QPen(Qt::blue), QBrush(Qt::blue));
   }
   ellipses[i]->setRect(pitch.ball->x,pitch.ball->y,pitch.ball->radius, pitch.ball->radius);

}

void MainWindow::goStep(){
   for(auto& player : pitch.teamA->players){
       player->updateState(&pitch);
   }
   for(auto& player : pitch.teamB->players){
       player->updateState(&pitch);
   }
   pitch.ball->updateState(&pitch);
   engine.updatePitch(pitch);

   ui->labelGameTime->setText(QString::number(90 - gameTimer.remainingTime()/1000.0));
//   ui->labelScoreA->setText(QString::number(pitch.teamA->score));
//   ui->labelScoreB->setText(QString::number(pitch.teamB->score));

}

void MainWindow::pause()
{
   timer.stop();
   actualTime = gameTimer.remainingTime();
   gameTimer.stop();
}

void MainWindow::resume()
{
    timer.start();
    gameTimer.start(actualTime);
}

void MainWindow::start()
{
    timer.start();
    gameTimer.start(90000);
    ui->pushButtonStart->setVisible(false);
    ui->pushButtonResume->setVisible(true);
}
