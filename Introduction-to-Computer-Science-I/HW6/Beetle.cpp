//
//  Beetle.cpp
//
//

#include "Beetle.h"

namespace cs31
{

Beetle::Beetle()
{
    mBody = false;
    mTail = false;
    mLeg1 = false;
    mLeg2 = false;
    mLeg3 = false;
    mLeg4 = false;
    mHead = false;
    mEye1 = false;
    mEye2 = false;
    mAntenna1 = false;
    mAntenna2 = false;
}

// convert a tossed die value into a BodyPart
Beetle::BodyPart Beetle::convertRollToBodyPart( int die ) const
{
    // if not matching, then return NOTVALID
    BodyPart part = BodyPart::NOTVALID;
    if (die == 6)
        part = BodyPart::BODY;
    if (die == 5)
        part = BodyPart::HEAD;
    if (die == 4)
        part = BodyPart::TAIL;
    if (die == 3)
        part = BodyPart::LEG;
    if (die == 2)
        part = BodyPart::ANTENNA;
    if (die == 1)
        part = BodyPart::EYE;
    return( part );
}

// build the Beetle's body
void Beetle::buildBody()
{
  mBody = true;
}

// has the Beetle's body been built?
bool Beetle::hasBody() const
{
    return( mBody );
}

// build the Beetle's tail but only if the body has already been built (in BeetleGame)
void Beetle::buildTail()
{
    mTail = true;
}

// has the Beetle's tail been built?
bool Beetle::hasTail() const
{
    return( mTail );
}

// build the Beetle's leg but only if the body has already been built (in BeetleGame)
void Beetle::buildLeg()
{
    if (!mLeg1 && !mLeg2 && !mLeg3 && !mLeg4) {      // first time buildLeg is called, build 1st leg
        mLeg1 = true;
    }
    else if (mLeg1 && !mLeg2 && !mLeg3 && !mLeg4) {  // second time buildLeg is called, build 2nd leg
        mLeg2 = true;
    }
    else if (mLeg1 && mLeg2 && !mLeg3 && !mLeg4) {   // third time buildLeg is called, build 3rd leg
        mLeg3 = true;
    }
    else if (mLeg1 && mLeg2 && mLeg3 && !mLeg4) {    // fourth time buildLeg is called, build 4th leg
        mLeg4 = true;
    }
}

// has the Beetle's 1st leg been built?
bool Beetle::hasLeg1() const
{
    return( mLeg1 );
}

// has the Beetle's 2nd leg been built?
bool Beetle::hasLeg2() const
{
    return( mLeg2 );
}

// has the Beetle's 3rd leg been built?
bool Beetle::hasLeg3() const
{
    return( mLeg3 );
}

// has the Beetle's 4th leg been built?
bool Beetle::hasLeg4() const
{
    return( mLeg4 );
}

// build the Beetle's head but only if the body has already been built (in BeetleGame)
void Beetle::buildHead()
{
    mHead = true;
}

// has the Beetle's head been built?
bool Beetle::hasHead() const
{
    return( mHead );
}

// build the Beetle's eye but only if the head has already been built
void Beetle::buildEye()
{
    if (!mEye1 && !mEye2) {      // first time buildEye called build eye 1
        mEye1 = true;
    }
    else if (mEye1 && !mEye2) {  // second time buildEye called build eye 2
        mEye2 = true;
    }
}

// has the Beetle's 1st eye been built?
bool Beetle::hasEye1() const
{
    return( mEye1 );
}

// has the Beetle's 2nd eye been built?
bool Beetle::hasEye2() const
{
    return( mEye2 );
}

// build the Beetle's antenna but only if the head has already been built (in BeetleGame)
void Beetle::buildAntenna()
{
    if (!mAntenna1 && !mAntenna2) {       // first time buildAntenna called build antenna 1
        mAntenna1 = true;
    }
    else if (mAntenna1 && !mAntenna2) {   // second time buildAntenna called build antenna 2
        mAntenna2 = true;
    }
}

// has the Beetle's 1st antenna been built?
bool Beetle::hasAntenna1() const
{
    return( mAntenna1 );
}

// has the Beetle's 2nd antenna been built?
bool Beetle::hasAntenna2() const
{
    return( mAntenna2 );
}


// is this Beetle completely built out? does it have a body, 2 eyes, a head, 4 legs, a tail, and 2 antennas?
bool Beetle::isComplete() const
{
    return( mBody &&
           mEye1 &&
           mEye2 &&
           mHead &&
           mLeg1 &&
           mLeg2 &&
           mLeg3 &&
           mLeg4 &&
           mTail &&
           mAntenna1 &&
           mAntenna2);
}


}


