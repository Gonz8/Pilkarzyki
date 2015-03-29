#ifndef BALL_H
#define BALL_H


#include "moveableitem.h"

///
/// \brief The Ball class This class is responsible for ...
///
class Ball : public MoveableItem
{
public:
    static const int maxSpeed = 10;
    ///
    /// \brief Ball this function ...
    ///
    Ball(const Pitch* pitch);
    ///
    /// \brief updateState this function ...
    /// \param pitch this paramter is a poinetr to ...
    ///
    virtual void updateState(const Pitch* pitch);
    bool getFree() const;
    void setFree(bool value);

private:
    bool free;
};

#endif // BALL_H
