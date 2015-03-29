#include "defender.h"
#include <QDebug>
Defender::Defender()
{
}

void Defender::updateState(const Pitch *pitch)
{
    qDebug()<<"Updating DEFENDER state, address"<<this;
}
