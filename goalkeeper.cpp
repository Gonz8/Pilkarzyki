#include "goalkeeper.h"
#include <pitch.h>
#include <QDebug>
Goalkeeper::Goalkeeper(bool host, QColor color) :Player(host,color)
{
}

void Goalkeeper::updateState(const Pitch *pitch)
{
    qDebug()<<"Updating GOALKEEPER state, address"<<this->xVel<<" yVel:"<<this->yVel<<" poss: "<<inPoss;
   // float speedRatio = this->findBall(pitch);

    QPointF myGoal = findMyGoal(up_side,pitch);
    QPointF ballPt = this->findBallPt(pitch);
    Player *teammateNrst = this->nearest(this,pitch,true);
    Player *oppNrst = this->nearest(this,pitch,false);

    if(!inPoss){
    //warunkowanie posiadania pilki/obrony po strzale
        if(ballPt.x() < 4 && ballPt.x() >(-4) && ballPt.y() > (-4) && ballPt.y() < 4){
            //dojdzie jeszcze sprawdzenie kto przejal
            if(oppNrst->inPoss){
                float skillDiff = (oppNrst->skill + oppNrst->strength) - (this->skill + this->strength);
                //qDebug()<<"UWAGA skillDiff = "<<skillDiff;
                if(skillDiff > 20) {
                    if( this->chance(15) ) {
                        inPoss = true;
                    }else {
                        inPoss = false;
                    }
                }
                else if (skillDiff < (-20)) {
                    if( this->chance(85) ) {
                        inPoss = true;
                    }else {
                        inPoss = false;
                    }
                }
                else {
                    if( this->chance(50) ) {
                        inPoss = true;
                    }else {
                        inPoss = false;
                    }
                }
            }
            else if(pitch->ball->getXVel() > pitch->ball->maxSpeed/2 || pitch->ball->getYVel() > pitch->ball->maxSpeed/2 ){
                if(chance(4*skill/5)) {
                    inPoss = true;
                }else {
                    inPoss = false;
                }
            }else {
                if(chance(skill)) {
                    inPoss = true;
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
                up_side ? yVel = 0.3 : yVel = (-0.3);
            }
        } else{
            //pozbywa sie pilki
            inPoss = false;
        }
    }
    if( !(ballPt.x() < 4 && ballPt.x() > (-4) && ballPt.y() > (-4) && ballPt.y() < 4) ){
        inPoss = false;
    }

    //poruszanie sie bramkarza
    if(inPoss){
        float xTOdiff = oppNrst->getX() - teammateNrst->getX();
        float yTOdiff = oppNrst->getY() - teammateNrst->getY();
        if( xTOdiff < 15 && xTOdiff > (-15) && yTOdiff < 12 && yTOdiff > (-12)) {
            // rusz sie na lepsza pozycje i podaj dopiero do lepiej ustawionego
        }
        else {
            //pass();
        }
    }else {

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
    //ograniczenia co do pola karnego
    //pole karne ~= 3/22 pitch.sizeY i 4/10 pitch.sizeY (czy 3/10?)
    if (up_side){
        if (this->y > 3*pitch->sizeY/22) {
            yVel = 0;
        }
    }else {
        if (this->y < 19*pitch->sizeY/22) {
            yVel = 0;
        }
    }
    if (this->x < 0.3*pitch->sizeX || this->x > 0.7*pitch->sizeX ) {
        xVel = 0;
    }

}
