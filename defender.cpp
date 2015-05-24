#include "defender.h"
#include <pitch.h>
#include <QDebug>
Defender::Defender(bool host, QColor color) : Player(host,color)
{
}

void Defender::updateState(const Pitch *pitch)
{
    //qDebug()<<"Updating DEFENDER state, address"<<this->xVel<<" yVel:"<<this->yVel;
    Player *teammate = this->nearest(this,pitch,true);
    //qDebug()<< "Defender's "<<this->stamina<<" nearest player is "<<teammate<<" (postion: x "<<teammate->getX()<<" y "<<teammate->getY();
    QPointF goal = findGoal(this->up_side,pitch);
    QPointF myGoal = findMyGoal(up_side,pitch);

    Player *oppNrst = this->nearest(this,pitch,false);
    QPointF ballPt = this->findBallPt(pitch);

    //warunkowanie posiadania pilki/przejęcia jej
    if(ballPt.x() < 3 && ballPt.x() >(-3) && ballPt.y() > (-3) && ballPt.y() < 3){
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

    float xOppDist = oppNrst->getX() - this->x;
    float yOppDist = oppNrst->getY() - this->y;
    //zachowanie gdy w posiadaniu lub nie
        //jeżeli nie posiada
        if(!this->inPoss) {
            //jesli w linii obrony blizej pilki
            if(teammate->findBallDist(pitch) >= this->findBallDist(pitch) && fabs(ballPt.y()) < pitch->sizeY/10 ) {
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
                float xDiff = ballPt.x();
                float yDiff = ballPt.y();
                if(xDiff && yDiff) {
                    this->yVel = this->xVel * yDiff/xDiff;
                }else {
                    if(xDiff){
                        this->yVel = 0;
                    } else {
                        if(yDiff > 0){
                            if (this->yVel > 0) {
                                this->yVel += 0.1;
                            } else {
                                this->yVel=0;
                                this->yVel += 0.1;
                            }
                        } else {
                            if (this->yVel < 0) {
                                this->yVel -= 0.1;
                            } else {
                                this->yVel=0;
                                this->yVel -= 0.1;
                            }
                        }
                        this->xVel = 0;
                    }
                }
            } else {
                if(myGoal.x() < 0 && ballPt.x() < 0){
                   if(fabs(ballPt.y()) > pitch->sizeY/2){
                       this->yVel = up_side ? 1 : (-1);
                   } else {
                       this->yVel = up_side ? (-0.5) : 0.5;
                   }
                   if(this->x < pitch->sizeX/3){
                       this->xVel = 0.5;
                   }
                   if(this->x > 7*pitch->sizeX/8){
                       this->xVel = -0.5;
                   }
                   else {
                       this->xVel = chance(50) ? 0.7 : -0.7;
                   }
                   if(fabs(myGoal.y()) > 2*pitch->sizeY/3){
                       this->yVel = up_side ? -1 : 1;
                   }
                   else if(fabs(myGoal.y()) < pitch->sizeY/12){
                       this->yVel = up_side ? 1 : -1;
                   }
                }
                else if(myGoal.x() > 0 && ballPt.x() > 0){
                    if(fabs(ballPt.y()) > pitch->sizeY/2){
                        this->yVel = up_side ? 1 : (-1);
                    } else {
                        this->yVel = up_side ? (-0.5) : 0.5;
                    }
                    if(this->x < pitch->sizeX/9){
                        this->xVel = 0.5;
                    }
                    if(this->x > 2*pitch->sizeX/3){
                        this->xVel = -0.5;
                    }
                    else {
                        this->xVel = chance(50) ? 0.7 : -0.7;
                    }
                    if(fabs(myGoal.y()) > 2*pitch->sizeY/3){
                        this->yVel = up_side ? -1 : 1;
                    }
                    else if(fabs(myGoal.y()) < pitch->sizeY/12){
                        this->yVel = up_side ? 1 : -1;
                    }
                }
                else {
                    this->xVel = chance(50) ? 0.6 : -0.6;
                }
            }

        }
        else {
            //w posiadaniu piłki

            if(fabs(goal.y()) < pitch->sizeY/2){
                if(up_side ? yOppDist < 0 : yOppDist > 0){
                    this->yVel = up_side ? 1 : -1;
                    this->xVel = chance(50) ? 0.6 : -0.6;
                    if(chance(25)){
                        pass();
                    }else {
                        if(chance(33)){
                            shoot();
                        }
                    }

                }
                else {
                    chance(65) ? pass() : shoot();
                }
                if(up_side ? teammate->getY() < this->y : teammate->getY() > this->y){
                    chance(80) ? shoot() : pass();
                }
            }
            else {
                if(fabs(xOppDist) > 8 && fabs(yOppDist) > 12){
                    this->yVel = up_side ? 1 : -1;
                    this->xVel = oppGoalkeeper->getX() > this->x ? 0.15 : -0.15;
                    if(chance(15)){
                        pass();
                    }
                }
                else {
                    this->yVel = up_side ? 1 : -1;
                    this->xVel = oppGoalkeeper->getX() > this->x ? 1 : -1;
                    if(chance(90)){
                        pass();
                    }
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
