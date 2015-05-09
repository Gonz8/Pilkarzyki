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
    QPointF goal = findGoal(this->up_side,pitch);


    float xDiff = (pitch->ball->getX() - this->x);
    float yDiff = (pitch->ball->getY() - this->y);
    qDebug()<<"xDiff,yDiff : "<<xDiff<<","<<yDiff;

    //warunkowanie posiadania pilki
    if(xDiff < 3 && xDiff >(-3) && yDiff > (-3) && yDiff < 3){
        //dojdzie jeszcze sprawdzenie kto przejal
        this->inPoss = true;
        xVel = 0;
        if (up_side) {
            yVel = 1.5;
        }
        else
            yVel -= 0.2;
    } else{
        //pozbywa sie pilki
        this->inPoss = false;
    }

//zachowanie gdy w posiadaniu lub nie
    if(!this->inPoss) {
        if(pitch->ball->getX() > this->x) {
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
        else if(pitch->ball->getX() != this->x){
            this->yVel = 0;
        }
        else if(pitch->ball->getY() != this->y){
            this->xVel = 0;
            if(pitch->ball->getY() > this->y) {
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

    }
    else {  //w posiadaniu piłki
        qDebug()<<"w posiadaniu (do bramki x,y : "<<goal.x()<<","<<goal.y()<<")";
        if(this->kitColor == pitch->teamA->color) {
            for(const auto& player : pitch->teamA->players){

            }
            for(const auto& player : pitch->teamB->players){

            }
        }
        else {
            for(const auto& player : pitch->teamB->players){

            }
            for(const auto& player : pitch->teamA->players){

            }
        }

    }


    //ograniczenia maksymalnej predkosci
    if (this->xVel > this->maxSpeed)
        this->xVel = this->maxSpeed;
    if (this->yVel > this->maxSpeed)
        this->yVel = this->maxSpeed;
    if (this->xVel < (-1)*this->maxSpeed)
        this->xVel = (-1)*this->maxSpeed;
    if (this->yVel < (-1)*this->maxSpeed)
        this->yVel = (-1)*this->maxSpeed;


}
