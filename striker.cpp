#include "striker.h"
#include <pitch.h>
#include <QDebug>
Striker::Striker(bool host, QColor color) : Player(host,color)
{
}

void Striker::updateState(const Pitch *pitch)
{
    //qDebug()<<"Updating STRIKER state, xVel:"<<this->xVel<<" yVel:"<<this->yVel;
    float speedRatio = this->findBall(pitch);
    QPointF goal = findGoal(this->up_side,pitch);
    QPointF myGoal = findMyGoal(up_side,pitch);
    //float xDiff = (pitch->ball->getX() - this->x);
    //float yDiff = (pitch->ball->getY() - this->y);
    //qDebug()<<"xDiff,yDiff : "<<xDiff<<","<<yDiff;

    Player *teammateNrst = this->nearest(this,pitch,true);
    Player *oppNrst = this->nearest(this,pitch,false);
    QPointF ballPt = this->findBallPt(pitch);

    //warunkowanie posiadania pilki/przejęcia jej
        if(ballPt.x() < 3 && ballPt.x() >(-3) && ballPt.y() > (-3) && ballPt.y() < 3){
            //dojdzie jeszcze sprawdzenie kto przejal
            if(oppNrst->inPoss){
                float skillDiff = (oppNrst->skill + oppNrst->strength) - (this->skill + this->strength);
                //qDebug()<<"UWAGA skillDiff = "<<skillDiff;
                if(skillDiff > 20) {
                    if( this->chance(15) ) {
                        if(!kicking && !passing){
                           this->inPoss = true;
                        }
                    }else {
                        inPoss = false;
                    }
                }
                else if (skillDiff < (-20)) {
                    if( this->chance(85) ) {
                        if(!kicking && !passing){
                           this->inPoss = true;
                        }
                    }else {
                        inPoss = false;
                    }
                }
                else {
                    if( this->chance(50) ) {
                        if(!kicking && !passing){
                           this->inPoss = true;
                        }
                    }else {
                        inPoss = false;
                    }
                }
            }
            else if(pitch->ball->getXVel() > pitch->ball->maxSpeed/2 || pitch->ball->getYVel() > pitch->ball->maxSpeed/2 ){
                if(chance(4*skill/5)) {
                    if(!kicking && !passing){
                       this->inPoss = true;
                    }
                }else {
                    inPoss = false;
                }
            }else {
                if(chance(skill)) {
                    if(!kicking && !passing){
                       this->inPoss = true;
                    }
                }else {
                    inPoss = false;
                }
            }
            if(inPoss){
                if(chance(50)){
                    xVel = 0.5;
                }else {
                    xVel = -0.5;
                }
                up_side ? yVel = 1.2 : yVel = (-1.2);
            }
        } else{
            //pozbywa sie pilki
            inPoss = false;
            this->kicking = false; this->passing =false;
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

        float xTOdiff = oppNrst->getX() - this->x;
        float yTOdiff = oppNrst->getY() - this->y;
        if(up_side){
            //przeciwnik jest za mna
            if( yTOdiff < 0 ) {
                if (this->yVel > 0) {
                    this->yVel += 0.1;
                } else {
                    this->yVel=0;
                    this->yVel += 0.1;
                }
                if(goal.x() - this->x > 5) {
                    this->xVel = 1.2;
                }
                else if(goal.x() - this->x < (-5)){
                    this->xVel = (-1.2);
                } else {
                    this->xVel = 0;
                }
                //strzelaj jesli odpowiednio blisko
                if(goal.y() < pitch->sizeY/9){
                    if(chance(85)){
                       shoot();
                    }
                }

            }
            else{
            //przeciwnik jest przede mna
                if(xTOdiff < 0 ) {
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
                float xopp_team = oppNrst->getX() - teammateNrst->getX();
                float yopp_team = oppNrst->getY() - teammateNrst->getY();
                if(xopp_team > 10 && xopp_team < (-10) && yopp_team > 10 && yopp_team < (-10) ) {
                    if(chance(90)){
                       pass();
                    }
                }
                else {
                    if (this->yVel > 0) {
                        this->yVel += 0.1;
                    } else {
                        this->yVel=0;
                        this->yVel += 0.1;
                    }
                    if(yTOdiff < 10) {
                        if(chance(65)){
                           pass();
                        }
                    }
                    if(goal.y() < pitch->sizeY/7){
                        if(chance(40)){
                           shoot();
                        }
                    }
                }
            }
        }
        else {
            // not up_side
            if( yTOdiff > 0 ) {
                //przeciwnik za mna
                if (this->yVel < 0) {
                    this->yVel -= 0.1;
                } else {
                    this->yVel=0;
                    this->yVel -= 0.1;
                }
                if(goal.x() - this->x > 5) {
                    this->xVel = 1.3;
                }
                else if(goal.x() - this->x < (-5)){
                    this->xVel = (-1.3);
                } else {
                    this->xVel = 0;
                }
                //strzelaj jesli odpowiednio blisko
                if(goal.y() > (-1)*pitch->sizeY/9){
                    if(chance(80)){
                       shoot();
                    }
                }

            }
            else{
            //przeciwnik jest przede mna
                if(xTOdiff < 0 ) {
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
                float xopp_team = oppNrst->getX() - teammateNrst->getX();
                float yopp_team = oppNrst->getY() - teammateNrst->getY();
                if(xopp_team > 10 && xopp_team < (-10) && yopp_team > 10 && yopp_team < (-10) ) {
                    if(chance(90)){
                       pass();
                    }
                }
                else {
                    if (this->yVel < 0) {
                        this->yVel -= 0.1;
                    } else {
                        this->yVel=0;
                        this->yVel -= 0.1;
                    }
                    if(yTOdiff > (-10)) {
                        if(chance(70)){
                           pass();
                        }
                    }
                    if(goal.y() > (-1)*pitch->sizeY/7){
                        if(chance(40)){
                           shoot();
                        }
                    }
                }
            }
        }
    qDebug()<<"w posiadaniu (do bramki x,y : "<<goal.x()<<","<<goal.y()<<") shoot: "<<kicking<<" pass: "<<passing;
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
