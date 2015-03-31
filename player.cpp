#include "player.h"
#include <QDebug>
#include <random>
#include <math.h>
#include <pitch.h>
Player::Player()
{
    inPoss = false;

    int high = Player::maxSkill; int low = Player::minSkill;
    stamina = qrand() % ((high + 1) - low) + low;
    skill = qrand() % ((high + 1) - low) + low;
    strength = qrand() % ((high + 1) - low) + low;
    overall = round((stamina+skill+strength)/3);

}
Player::~Player()
{

}

float Player::findBall(const Pitch *pitch)
{
    float speedRatio; //xVel/yVel
    float xDiff = pitch->ball->x - this->x;
    float yDiff = pitch->ball->y - this->y;
    if(xDiff == 0 || yDiff == 0) {
       speedRatio = 0;
    }else{
        speedRatio = (xDiff)/(yDiff);
    }
    return speedRatio;

}
void Player::updateState(const Pitch* pitch)
{
    //Jako input masz pitch i na podstawie tego co jest na boisku czyli pozycja pilki pozycja swojej druzyny i pozycja przeciwnika
    //mozesz wywnioskowac jak sie zachowac czyli jak ustawic swoja predkosc zasadnioczo, bo na podstawie predkosci physicsengine ustawi
    //pozycje zawodnika. mozesz ustawic ze np jak ma pilke to ze wykonuje kopniecie itd itp

    //Output jest predkosc i ewentualnie dzialanie np kopniecie
    qDebug()<<"Updating player state, address"<<this;
}
