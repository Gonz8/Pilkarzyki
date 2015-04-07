#include "player.h"
#include <QDebug>
#include <random>
#include <math.h>
#include <pitch.h>
Player::Player(bool host, QColor color)
{
    inPoss = false;
    up_side = host;
    kitColor = color;

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

QPointF Player::findGoal(bool up, const Pitch *pitch)
{
    QPointF player(this->x,this->y);
    if(up){
        QPointF goalCenter(pitch->sizeX/2,pitch->sizeY);
        QPointF diff;
        diff = goalCenter - player;
        return diff;
    }
    else {
        QPointF goalCenter(pitch->sizeX/2,0);
        QPointF diff;
        diff = goalCenter - player;
        return diff;
    }
}

QPointF Player::findMyGoal(bool up, const Pitch *pitch)
{
    QPointF player(this->x,this->y);
    if(up){
        QPointF goalCenter(pitch->sizeX/2,0);
        QPointF diff;
        diff = goalCenter - player;
        return diff;
    }
    else {
        QPointF goalCenter(pitch->sizeX/2,pitch->sizeY);
        QPointF diff;
        diff = goalCenter - player;
        return diff;
    }
}

Player *Player::nearest(const Player *ja, const Pitch *pitch)
{
    Player *teammate;
    QPointF myPos(ja->x,ja->y);
    float distance;
    float close = 99999;
    if(ja->kitColor == pitch->teamA->color) {
        for(const auto& player : pitch->teamA->players){
            if(player == ja){
                continue;
            }
            QPointF friendPos(player->x,player->y);
            friendPos -= myPos;
            distance = sqrt( pow(friendPos.x(),2) + pow(friendPos.y(),2) );
            if(distance < close){
                teammate = player;
                close = distance;
            }
        }
    } else {
        for(const auto& player : pitch->teamB->players){
            if(player == ja){
                continue;
            }
            QPointF friendPos(player->x,player->y);
            friendPos -= myPos;
            distance = sqrt( pow(friendPos.x(),2) + pow(friendPos.y(),2) );
            if(distance < close){
                teammate = player;
                close = distance;
            }
        }
    }
    return teammate;
}
void Player::updateState(const Pitch* pitch)
{
    //Jako input masz pitch i na podstawie tego co jest na boisku czyli pozycja pilki pozycja swojej druzyny i pozycja przeciwnika
    //mozesz wywnioskowac jak sie zachowac czyli jak ustawic swoja predkosc zasadnioczo, bo na podstawie predkosci physicsengine ustawi
    //pozycje zawodnika. mozesz ustawic ze np jak ma pilke to ze wykonuje kopniecie itd itp

    //Output jest predkosc i ewentualnie dzialanie np kopniecie
    qDebug()<<"Updating player state, address"<<this<<pitch;
}
