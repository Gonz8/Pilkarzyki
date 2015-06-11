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
       QGraphicsEllipseItem *e = scene->addEllipse(player->getX(),player->getY(),player->radius, player->radius, QPen(Acolor), QBrush(Acolor));
       ellipses.push_back(e);
   }
   for(auto player : pitch.teamB->players){
       QGraphicsEllipseItem *e = scene->addEllipse(player->getX(),player->getY(),player->radius, player->radius, QPen(Bcolor), QBrush(Bcolor));
       ellipses.push_back(e);
   }
   QGraphicsEllipseItem *e = scene->addEllipse(pitch.ball->getX(),pitch.ball->getY(),pitch.ball->radius, pitch.ball->radius, QPen(Qt::black), QBrush(Qt::white));
   ellipses.push_back(e);
   ui->labelTeamA->setText(QString::fromStdString(pitch.teamA->name));
   ui->labelTeamA->setStyleSheet("color: red");
   ui->labelTeamB->setText(QString::fromStdString(pitch.teamB->name));
   ui->labelTeamB->setStyleSheet("color: blue");

   connect(&pitch,SIGNAL(updated()),this,SLOT(updateView()));


   timer.setInterval(150);
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
       ellipses[i]->setRect(player->getX(),player->getY(),player->radius, player->radius);
       if(player->inPoss) {
           ellipses[i++]->setPen(QPen(Qt::yellow));
       } else {
           ellipses[i++]->setPen(QPen(player->kitColor));
       }
      // scene->addEllipse(player.x,player.y,player.radius, player.radius, QPen(Qt::red), QBrush(Qt::red));
   }
   for(const auto& player : pitch.teamB->players){
       ellipses[i]->setRect(player->getX(),player->getY(),player->radius, player->radius);
       if(player->inPoss) {
           ellipses[i++]->setPen(QPen(Qt::yellow));
       } else {
           ellipses[i++]->setPen(QPen(player->kitColor));
       }
      // scene->addEllipse(player.x,player.y,player.radius, player.radius, QPen(Qt::blue), QBrush(Qt::blue));
   }
   ellipses[i]->setRect(pitch.ball->getX(),pitch.ball->getY(),pitch.ball->radius, pitch.ball->radius);

}

void MainWindow::goStep(){
   pitch.ball->updateState(&pitch);
   for(auto& player : pitch.teamA->players){
       player->updateState(&pitch);
   }
   for(auto& player : pitch.teamB->players){
       player->updateState(&pitch);
   }

   engine.updatePitch(pitch);

   ui->labelGameTime->setText(QString::number((180 - gameTimer.remainingTime()/1000.0)/2));
   ui->labelScoreA->setText(QString::number(pitch.teamA->score));
   ui->labelScoreB->setText(QString::number(pitch.teamB->score));

   //po strzelonej bramce zatrzymaj czas i rozpocznij mecz po chwili
   float goalHalf = pitch.goalLength/2;
   float firstPost = pitch.sizeX/2 - goalHalf;
   float secondPost = pitch.sizeX/2 + goalHalf;
   if(pitch.ball->getX() > firstPost && pitch.ball->getX() < secondPost){
       if(pitch.ball->getY() == pitch.sizeY) {
           pitch.teamA->score += 1;
           ui->labelScoreA->setText(QString::number(pitch.teamA->score));
           ui->labelScoreB->setText(QString::number(pitch.teamB->score));
           pause();
       }else if (pitch.ball->getY() == 0) {
           pitch.teamB->score += 1;
           ui->labelScoreA->setText(QString::number(pitch.teamA->score));
           ui->labelScoreB->setText(QString::number(pitch.teamB->score));
           pause();
       }
    }
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
    gameTimer.start(180000);
    ui->pushButtonStart->setVisible(false);
    ui->pushButtonResume->setVisible(true);
}
