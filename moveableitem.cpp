#include "moveableitem.h"

MoveableItem::MoveableItem()
{
    radius = 8;
    yVel = 0;
    xVel = 0;
}

bool MoveableItem::chance(float chance, int universe)
{

}

float MoveableItem::distance(float x1, float y1, float x2, float y2)
{
    QPointF firstPos(x1,y1);
    QPointF secondPos(x2,y2);
    float distance;
    secondPos -= firstPos;
    distance = sqrt( pow(secondPos.x(),2) + pow(secondPos.y(),2) );
    return distance;
}

float MoveableItem::getX() const
{
    return x;
}

float MoveableItem::getY() const
{
    return y;
}

float MoveableItem::getXVel() const
{
    return xVel;
}

float MoveableItem::getYVel() const
{
    return yVel;
}

void MoveableItem::setX(float value)
{
    x = value;
}

void MoveableItem::setY(float value)
{
    y = value;
}
