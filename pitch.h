#ifndef PITCH_H
#define PITCH_H

#include <QObject>
#include "team.h"
#include "ball.h"
#include <QGraphicsScene>
class Pitch : public QObject
{
    Q_OBJECT
public:
    explicit Pitch(QObject *parent = 0);
    ~Pitch();
    float sizeX;
    float sizeY;
    float goalLength;

    Team *teamA;
    Team *teamB;
    Ball ball;

    void drawPitch(QGraphicsScene*);

signals:
    void updated();

public slots:
    void update();

};

#endif // PITCH_H
