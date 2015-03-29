#include "ball.h"
#include <QDebug>
#include <pitch.h>
Ball::Ball(const Pitch *pitch)
{
    x = pitch->sizeX/2;
    y = pitch->sizeY/2;
    radius = 5;
}

void Ball::updateState(const Pitch* pitch)
{

    // Jako input tutaj jest sytuacja na boisku i teraz jezeli na przyklad pilke dotyka jakis player to wtedy pilka kopiuje jego predkosc
    // Jezeli pilke dotyka dwóch pilkarzy to wtedy pilka dostaje predkosc jakas wypadkową albo predkosc pilkarza o lepszym wspolczynniku
    // silay/kiwania whatever. Jezeli pilkarz obok pilki ma ustawione ze wykonuje kopniecie to np pilka zyskuje dodatkowa predkosc.
    qDebug()<<"Updating ball state"<<this;

}
bool Ball::getFree() const
{
    return free;
}

void Ball::setFree(bool value)
{
    free = value;
}

