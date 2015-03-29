#include "pitch.h"

Pitch::Pitch(QObject *parent) :
    QObject(parent)
{
    sizeX = 300;
    sizeY = 440;
    goalLength = 40;
    teamA = new Team(true,this);
    teamB = new Team(false,this);
    ball = new Ball(this);
}

Pitch::~Pitch()
{
    delete teamA;
    delete teamB;
    delete ball;
}

void Pitch::drawPitch(QGraphicsScene * scene)
{
     scene->addRect(0,0,sizeX, sizeY, QPen(Qt::black),QBrush(Qt::green));
     QPen pen(Qt::black, 1);
     QLineF line(0, sizeY/2, sizeX,sizeY/2);
     scene->addLine(line,pen);
     scene->addRect((sizeX-goalLength)/2,-10,goalLength,10,pen,QBrush(Qt::transparent));    //bramka
     scene->addRect((sizeX-goalLength)/2,sizeY,goalLength,10,pen,QBrush(Qt::transparent));    //bramka
}

void Pitch::update()
{
    emit updated();
}
