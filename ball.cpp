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
    qDebug()<<"Updating ball state"<<getFree();

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

