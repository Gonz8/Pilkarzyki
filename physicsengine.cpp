#include "physicsengine.h"



///
/// \brief PhysicsEngine::PhysicsEngine this is class constructor
///
PhysicsEngine::PhysicsEngine()
{
}


///
/// \brief PhysicsEngine::updatePitch this
/// \param pitch
///
void PhysicsEngine::updatePitch(Pitch& pitch)
{
    for(auto& player: pitch.teamA->players){

        player->x += player->xVel;
        player->y += player->yVel;
        if(player->x < 0)
            player->x =0;
        if(player->x>pitch.sizeX)
            player->x = pitch.sizeX;

        if(player->y < 0)
            player->y = 0;
        if(player->y>pitch.sizeY)
            player->y = pitch.sizeY;

    }
    for(auto& player: pitch.teamB->players){
        player->x += player->xVel;
        player->y += player->yVel;
        if(player->x < 0)
            player->x =0;
        if(player->x>pitch.sizeX)
            player->x = pitch.sizeX;

        if(player->y < 0)
            player->y = 0;
        if(player->y>pitch.sizeY)
            player->y = pitch.sizeY;
    }

    pitch.ball->x += pitch.ball->xVel;
    pitch.ball->y += pitch.ball->yVel;
    if(pitch.ball->x < 0)
        pitch.ball->x =0;
    if(pitch.ball->x>pitch.sizeX)
        pitch.ball->x = pitch.sizeX;

    if(pitch.ball->y < 0)
        pitch.ball->y = 0;
    if(pitch.ball->y>pitch.sizeY)
        pitch.ball->y = pitch.sizeY;

    // Pilka ze nie moze wyjsc za boisko domyslnie
    pitch.update();
}
