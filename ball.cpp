#include "ball.h"
#include <QDebug>
#include <pitch.h>
Ball::Ball(const Pitch *pitch)
{
    x = pitch->sizeX/2;
    y = pitch->sizeY/2;
    radius = 5;
    free = true;
}

void Ball::updateState(const Pitch* pitch)
{

    // Jako input tutaj jest sytuacja na boisku i teraz jezeli na przyklad pilke dotyka jakis player to wtedy pilka kopiuje jego predkosc
    // Jezeli pilke dotyka dwóch pilkarzy to wtedy pilka dostaje predkosc jakas wypadkową albo predkosc pilkarza o lepszym wspolczynniku
    // silay/kiwania whatever. Jezeli pilkarz obok pilki ma ustawione ze wykonuje kopniecie to np pilka zyskuje dodatkowa predkosc.
    //qDebug()<<"Updating ball state"<<getFree();

    float myMaxSpeed = this->maxSpeed;

    //sprawdzenie stanu czy pilka w posiadaniu przez gracza
    for(const auto& player : pitch->teamA->players){
        if(player->inPoss) {
            setFree(false);
            //nadaj jej predkosc gracza
            this->xVel = player->getXVel();
            this->yVel = player->getYVel();
            break;
        } else {
            setFree(true);
        }
    }
    if(getFree()) {
        for(const auto& player : pitch->teamB->players){
            if(player->inPoss) {
                setFree(false);
                this->xVel = player->getXVel();
                this->yVel = player->getYVel();
                break;
            } else {
                setFree(true);
            }
        }
    }

    //sprawdzanie czy na pilce wykonywane sa akcje kicking/passing
    for(const auto& player : pitch->teamA->players){
        if(player->passing && player->inPoss){
            //qDebug()<<"PLAYER "<<player<<" PODAJE";
            Player *teammate = player->nearest(player,pitch,true);
            myMaxSpeed = this->maxSpeed*(player->strength/100);
            float xDiff = teammate->getX() - this->x;
            float yDiff = teammate->getY() - this->y;
            qDebug()<<player<<" xDiff:"<<xDiff<<" yDiff:"<<yDiff;
            if(xDiff && yDiff) {
                if(fabs(xDiff) > fabs(yDiff)){
                    this->xVel = xDiff > 0 ? myMaxSpeed/3 : (-1)*myMaxSpeed/3;
                    this->yVel = this->xVel * yDiff/xDiff;
                }
                else {
                    this->yVel = yDiff > 0 ? myMaxSpeed/3 : (-1)*myMaxSpeed/3;
                    this->xVel = yVel * xDiff/yDiff;
                }
            }else {
                if(xDiff){
                    this->yVel = 0;
                    this->xVel = myMaxSpeed/3;
                } else {
                    this->yVel = myMaxSpeed/3;
                    this->xVel = 0;
                }
            }
            qDebug()<<"Ball "<<this->xVel<<" xVel, "<<this->yVel<<" yVel.";
        }
        if(player->kicking && player->inPoss) {
            //qDebug()<<"PLAYER "<<player<<" STRZELA";
            QPointF goal = player->findGoal(player->up_side, pitch);
            Player *goalkeeper = player->oppGoalkeeper;
            myMaxSpeed = this->maxSpeed*(player->strength/100);
            float xDiff;
            float yDiff;
            float toFarPost;
            if(goal.x() > goalkeeper->getX() - this->x) {
                if(chance(player->skill)){
                   toFarPost = pitch->goalLength/3;
                }else {
                    if(chance(50)){
                        toFarPost = pitch->goalLength/5;
                    }else {
                        toFarPost = pitch->goalLength;
                    }
                }
            }
            else {
                if(chance(player->skill)){
                   toFarPost = (-1)*pitch->goalLength/3;
                }else {
                    if(chance(50)){
                        toFarPost = (-1)*pitch->goalLength/6;
                    }else {
                        toFarPost = (-1)*pitch->goalLength;
                    }
                }
            }
            xDiff = goal.x() + toFarPost;
            yDiff = goal.y();
            if(xDiff && yDiff) {
                if(fabs(xDiff) > fabs(yDiff)){
                    this->xVel = xDiff > 0 ? myMaxSpeed : (-1)*myMaxSpeed;
                    this->yVel = this->xVel * yDiff/xDiff;
                }
                else {
                    this->yVel = yDiff > 0 ? myMaxSpeed : (-1)*myMaxSpeed;
                    this->xVel = yVel * xDiff/yDiff;
                }
            }else {
                if(xDiff){
                    this->yVel = 0;
                    this->xVel = myMaxSpeed;
                } else {
                    this->yVel = myMaxSpeed;
                    this->xVel = 0;
                }
            }
            qDebug()<<"Ball "<<this->xVel<<" xVel, "<<this->yVel<<" yVel.";
        }
    }
    for(const auto& player : pitch->teamB->players){
        if(player->passing && player->inPoss){
            //qDebug()<<"PLAYER "<<player<<" PODAJE";
            Player *teammate = player->nearest(player,pitch,true);
            //qDebug()<<" Do podania nadaje sie ZAWODNIK adress: "<<teammate;
            myMaxSpeed = this->maxSpeed*(player->strength/100);
            float xDiff = teammate->getX() - this->x;
            float yDiff = teammate->getY() - this->y;
            qDebug()<<player<<" xDiff:"<<xDiff<<" yDiff:"<<yDiff;
            if(xDiff && yDiff) {
                if(fabs(xDiff) > fabs(yDiff)){
                    this->xVel = xDiff > 0 ? myMaxSpeed/3 : (-1)*myMaxSpeed/3;
                    this->yVel = this->xVel * yDiff/xDiff;
                }
                else {
                    this->yVel = yDiff > 0 ? myMaxSpeed/3 : (-1)*myMaxSpeed/3;
                    this->xVel = yVel * xDiff/yDiff;
                }
            }else {
                if(xDiff){
                    this->yVel = 0;
                    this->xVel = myMaxSpeed/3;
                } else {
                    this->yVel = myMaxSpeed/3;
                    this->xVel = 0;
                }
            }
            qDebug()<<"Ball "<<this->xVel<<" xVel, "<<this->yVel<<" yVel.";
        }
        if(player->kicking && player->inPoss) {
            //qDebug()<<"PLAYER "<<player<<" STRZELA";
            QPointF goal = player->findGoal(player->up_side, pitch);
            Player *goalkeeper = player->oppGoalkeeper;
            myMaxSpeed = this->maxSpeed*(player->strength/100);
            float xDiff;
            float yDiff;
            float toFarPost;
            if(goal.x() > goalkeeper->getX() - this->x) {
                if(chance(player->skill)){
                   toFarPost = pitch->goalLength/3;
                }else {
                    if(chance(50)){
                        toFarPost = pitch->goalLength/5;
                    }else {
                        toFarPost = pitch->goalLength;
                    }
                }
            }
            else {
                if(chance(player->skill)){
                   toFarPost = (-1)*pitch->goalLength/3;
                }else {
                    if(chance(50)){
                        toFarPost = (-1)*pitch->goalLength/6;
                    }else {
                        toFarPost = (-1)*pitch->goalLength;
                    }
                }
            }
            xDiff = goal.x() + toFarPost;
            yDiff = goal.y();
            if(xDiff && yDiff) {
                if(fabs(xDiff) > fabs(yDiff)){
                    this->xVel = xDiff > 0 ? myMaxSpeed : (-1)*myMaxSpeed;
                    this->yVel = this->xVel * yDiff/xDiff;
                }
                else {
                    this->yVel = yDiff > 0 ? myMaxSpeed : (-1)*myMaxSpeed;
                    this->xVel = yVel * xDiff/yDiff;
                }
            }else {
                if(xDiff){
                    this->yVel = 0;
                    this->xVel = myMaxSpeed;
                } else {
                    this->yVel = myMaxSpeed;
                    this->xVel = 0;
                }
            }
            qDebug()<<"Ball "<<this->xVel<<" xVel, "<<this->yVel<<" yVel.";
        }
    }


//    if(getFree()) {

//    }


    //ograniczenia maksymalnej predkosci
    if (this->xVel > myMaxSpeed)
        this->xVel = myMaxSpeed;
    if (this->yVel > myMaxSpeed)
        this->yVel = myMaxSpeed;
    if (this->xVel < (-1)*myMaxSpeed)
        this->xVel = (-1)*myMaxSpeed;
    if (this->yVel < (-1)*myMaxSpeed)
        this->yVel = (-1)*myMaxSpeed;

}

Ball::~Ball()
{

}

bool Ball::getFree() const
{
    return free;
}

void Ball::setFree(bool value)
{
    free = value;
}

