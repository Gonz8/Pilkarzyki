#include "striker.h"
#include <pitch.h>
#include <QDebug>
Striker::Striker(bool host, QColor color) : Player(host,color)
{
}

void Striker::updateState(const Pitch *pitch)
{
    qDebug()<<"Updating STRIKER state, xVel:"<<this->xVel<<" yVel:"<<this->yVel;
    float speedRatio = this->findBall(pitch);
    qDebug()<<"SpeedRatio : "<<speedRatio;
    if(!this->inPoss) {
        if(pitch->ball->x > this->x) {
            if (this->xVel > 0) {
                this->xVel += 0.1;
            } else {
                this->xVel=0;
                this->xVel += 0.1;
            }
        } else {
            if (this->xVel < 0) {
                this->xVel -= 0.1;
            } else {
                this->xVel=0;
                this->xVel -= 0.1;
            }
        }
        if(speedRatio != 0) {
           this->yVel = this->xVel/speedRatio;
        }
        else if(pitch->ball->x != this->x){
            this->yVel = 0;
        }
        else if(pitch->ball->y != this->y){
            this->xVel = 0;
            if(pitch->ball->y > this->y) {
                if (this->yVel > 0) {
                    this->yVel += 0.1;
                } else {
                    this->yVel=0;
                    this->yVel += 0.1;
                }
            }else {
                if (this->yVel < 0) {
                    this->yVel -= 0.1;
                } else {
                    this->yVel=0;
                    this->yVel -= 0.1;
                }
            }
        }else{
            this->yVel = 0; this->xVel = 0;
        }
        float xDiff = (pitch->ball->x - this->x);
        float yDiff = (pitch->ball->y - this->y);
        if(xDiff < 0.5 && xDiff >(-0.5) && yDiff > (-0.5) && yDiff < 0.5){
            //dojdzie jeszcze sprawdzenie kto przejal
            this->inPoss = true;
            xVel = 0;
            if (up_side) {
                yVel += 3;
            }
            else
                yVel -= 0.2;
        }
    }
    else {  //w posiadaniu piłki

    }

    if (this->xVel > this->maxSpeed)
        this->xVel = this->maxSpeed;
    if (this->yVel > this->maxSpeed)
        this->yVel = this->maxSpeed;
    if (this->xVel < (-1)*this->maxSpeed)
        this->xVel = (-1)*this->maxSpeed;
    if (this->yVel < (-1)*this->maxSpeed)
        this->yVel = (-1)*this->maxSpeed;


}
