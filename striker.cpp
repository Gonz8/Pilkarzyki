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
    QPointF myGoal = findMyGoal(up_side,pitch);
    float xDiff = (pitch->ball->getX() - this->x);
    float yDiff = (pitch->ball->getY() - this->y);
    qDebug()<<"xDiff,yDiff : "<<xDiff<<","<<yDiff;

    Player *teammateNrst = this->nearest(this,pitch,true);
    Player *oppNrst = this->nearest(this,pitch,false);

    //warunkowanie posiadania pilki
    if(xDiff < 3 && xDiff >(-3) && yDiff > (-3) && yDiff < 3){
        //dojdzie jeszcze sprawdzenie kto przejal
        this->inPoss = true;
        xVel = 0;
        if (up_side) {
            yVel = 1.5;
        }
        else
            yVel = (-1)*1.5;
    } else{
        //pozbywa sie pilki
        this->inPoss = false;
    }

//zachowanie gdy w posiadaniu lub nie
    //jeżeli nie posiada
    if(!this->inPoss) {
        //jezeli jestem blizej pilki
        if(teammateNrst->findBallDist(pitch) >= this->findBallDist(pitch)) {
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
                this->yVel = 0; this->xVel = 0;//teoretycznie posiada pilke
            }
        }
        //jezeli teammate biegnie do piłki
        else {
            QPointF ballPt = this->findBallPt(pitch);
            if(up_side){
                if(ballPt.y() > (-10)) {
                    if(yVel > 0){
                       yVel += 0.1;
                    }else {
                       yVel = 0;
                       yVel += 0.1;
                    }
                }
                else {
                    if(yVel > 0) {
                       yVel = 0;
                       yVel -= 0.07;
                    } else {
                        yVel -= 0.07;
                    }

                }
                if(myGoal.y() < (-1)* pitch->sizeY/10) {
                    if(yVel > 0) {
                       yVel += 0.1;
                    } else {
                        yVel = 0; yVel += 0.1;
                    }
                }
                if(goal.y() < pitch->sizeX/15) {
                    if(yVel > 0){
                        yVel = 0; yVel -= 0.1;
                    }else {
                        yVel -= 0.1;
                    }
                }
                if(oppNrst->getX() - this->x < 0 ) {
                    //moze tu jeszcze dodac aby sledzil i x. pilki
                    if(xVel > 0){
                        xVel += 0.1;
                    } else {
                        xVel = 0; xVel += 0.1;
                    }
                } else {
                    if(xVel > 0) {
                        xVel = 0; xVel -= 0.1;
                    }else {
                        xVel -= 0.1;
                    }

                }
            }else {
                if(ballPt.y() < 10) {
                    if(yVel < 0) {
                        yVel -= 0.1;
                    }else {
                        yVel = 0; yVel -= 0.1;
                    }
                } else {
                    if(yVel > 0){
                        yVel += 0.07;
                    }else {
                        yVel = 0;
                        yVel += 0.07;
                    }
                }
                if(myGoal.y() < pitch->sizeY/10){
                    if (yVel > 0){
                        yVel = 0; yVel -=0.1;
                    } else {
                        yVel -=0.1;
                    }
                }
                if(goal.y() > (-1)*pitch->sizeX/15) {
                    if(yVel > 0){
                        yVel += 0.1;
                    }else {
                        yVel = 0; yVel += 0.1;
                    }
                }
                if(oppNrst->getX() - this->x < 0) {
                    if (xVel > 0){
                        xVel += 0.1;
                    } else {
                        xVel = 0; xVel += 0.1;
                    }
                } else {
                    if (xVel > 0) {
                        xVel = 0;
                        xVel -= 0.1;
                    } else {
                        xVel -= 0.1;
                    }
                }
            }
            if(this->x < pitch->sizeX/30){
                xVel = 0 ; xVel += 0.3;
            }
            else if(this->x > 29*pitch->sizeX/30){
                xVel = 0; xVel -= 0.3;
            }

//            if(pitch->ball->getY() - 80 > this->y) {
//                if (this->yVel > 0) {
//                    this->yVel += 0.1;
//                } else {
//                    this->yVel=0;
//                    this->yVel += 0.1;
//                }
//            }else {
//                if (this->yVel < 0) {
//                    this->yVel -= 0.1;
//                } else {
//                    this->yVel=0;
//                    this->yVel -= 0.1;
//                }
//            }
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
    float myMaxSpeed = this->maxSpeed*(this->stamina/100);
    if (this->xVel > myMaxSpeed)
        this->xVel = myMaxSpeed;
    if (this->yVel > myMaxSpeed)
        this->yVel = myMaxSpeed;
    if (this->xVel < (-1)*myMaxSpeed)
        this->xVel = (-1)*myMaxSpeed;
    if (this->yVel < (-1)*myMaxSpeed)
        this->yVel = (-1)*myMaxSpeed;


}
