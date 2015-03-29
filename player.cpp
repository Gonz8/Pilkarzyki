#include "player.h"
#include <QDebug>
#include <random>
#include <math.h>
Player::Player()
{
    inPoss = false;

//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_int_distribution<int> distribution(Player::minSkill,Player::maxSkill);
//    stamina = distribution(gen);
//    strength = distribution(gen);
//    skill = distribution(gen);

    int high = Player::maxSkill; int low = Player::minSkill;
    stamina = qrand() % ((high + 1) - low) + low;
    skill = qrand() % ((high + 1) - low) + low;
    strength = qrand() % ((high + 1) - low) + low;
    overall = round((stamina+skill+strength)/3);

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
