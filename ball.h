#ifndef BALL_H
#define BALL_H


#include "moveableitem.h"

///
/// \brief The Ball class This class is responsible for ...
///
class Ball : public MoveableItem
{
public:
    ///
    /// \brief Ball this function ...
    ///
    Ball(const Pitch* pitch);
    ///
    /// \brief updateState this function ...
    /// \param pitch this paramter is a poinetr to ...
    ///
    virtual void updateState(const Pitch* pitch);
};

#endif // BALL_H
