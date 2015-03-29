#include "player.h"
#include <QDebug>
Player::Player()
{
}
Player::~Player()
{

}
void Player::updateState(const Pitch* pitch)
{
    //Jako input masz pitch i na podstawie tego co jest na boisku czyli pozycja pilki pozycja swojej druzyny i pozycja przeciwnika
    //mozesz wywnioskowac jak sie zachowac czyli jak ustawic swoja predkosc zasadnioczo, bo na podstawie predkosci physicsengine ustawi
    //pozycje zawodnika. mozesz ustawic ze np jak ma pilke to ze wykonuje kopniecie itd itp

    //Output jest predkosc i ewentualnie dzialanie np kopniecie
    qDebug()<<"Updating player state, address"<<this;
}
