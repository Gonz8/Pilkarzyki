#include "goalkeeper.h"
#include <QDebug>
Goalkeeper::Goalkeeper(bool host, QColor color) :Player(host,color)
{
}

void Goalkeeper::updateState(const Pitch *pitch)
{
    //qDebug()<<"Updating GOALKEEPER state, address"<<this->xVel<<" yVel:"<<this->yVel;
   // float speedRatio = this->findBall(pitch);

}
