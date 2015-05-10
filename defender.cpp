#include "defender.h"
#include <QDebug>
Defender::Defender(bool host, QColor color) : Player(host,color)
{
}

void Defender::updateState(const Pitch *pitch)
{
    //qDebug()<<"Updating DEFENDER state, address"<<this->xVel<<" yVel:"<<this->yVel;
    Player *teammate = this->nearest(this,pitch,true);
    qDebug()<< "Defender's "<<this->stamina<<" nearest player is "<<teammate<<" (postion: x "<<teammate->getX()<<" y "<<teammate->getY();
}
