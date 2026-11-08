//
//  BeetleGame.cpp
//

#include "BeetleGame.h"
#include "BeetleDrawing.h"

#include <iostream>

namespace cs31
{

BeetleGame::BeetleGame() : mHuman(), mComputer(), mHumanDie(), mComputerDie()
{
    
}

// draw the board by using a BeetleDrawing to draw the two Beetles
std::string BeetleGame::display( std::string msg ) const
{
    BeetleDrawing drawing( mHuman, mComputer );
    std::string result = drawing.draw() + "\n" + msg;
    return( result );
}


void BeetleGame::humanRoll( int amount )
{
    // if the amount is zero, roll the Human's die - random roll
    if (amount == 0) {
        mHumanDie.roll();
    }
    // otherwise, cheat by forcing the amount into the Human's die
    else {
        mHumanDie.setValue(amount);
    }
}

// return the value of the Human's die
int BeetleGame::getHumanDie( ) const
{
    return( mHumanDie.getValue() );
}


// if a body part was successfully built, returns true
// otherwise, returns false
bool BeetleGame::humanPlay( )
{
    bool result = false;
    
    // convert human die roll to Beetle body part
    Beetle::BodyPart part = mHuman.convertRollToBodyPart(mHumanDie.getValue());
    
    // depending on which part was called, build that body part if it follows game ordering
    switch (part) {
        // build eye only if head and body are built and at least one eye is missing
        case Beetle::BodyPart::EYE:
            if (mHuman.hasHead() && mHuman.hasBody() && (!mHuman.hasEye1() || !mHuman.hasEye2()) ) {
                mHuman.buildEye();
                result = true;
            }
            break;
        // build antenna only if head and body are built and at least one antenna is missing
        case Beetle::BodyPart::ANTENNA:
            if (mHuman.hasHead() && mHuman.hasBody() && (!mHuman.hasAntenna1() || !mHuman.hasAntenna2()) ) {
                mHuman.buildAntenna();
                result = true;
            }
            break;
        // build leg only if body already built and at least one leg is missing
        case Beetle::BodyPart::LEG:
            if (mHuman.hasBody() && (!mHuman.hasLeg1() || !mHuman.hasLeg2() || !mHuman.hasLeg3() || !mHuman.hasLeg4()) ) {
                mHuman.buildLeg();
                result = true;
            }
            break;
        // build tail only if body already built and tail is missing
        case Beetle::BodyPart::TAIL:
            if (mHuman.hasBody() && !mHuman.hasTail() ) {
                mHuman.buildTail();
                result = true;
            }
            break;
        // build head only if body already built and head is missing
        case Beetle::BodyPart::HEAD:
            if (mHuman.hasBody() && !mHuman.hasHead()) {
                mHuman.buildHead();
                result = true;
            }
            break;
        // build body only if body is missing
        case Beetle::BodyPart::BODY:
            if (!mHuman.hasBody()) {
                mHuman.buildBody();
                result = true;
            }
            break;
        // invalid die roll - nothing built
        case Beetle::BodyPart::NOTVALID:
            result = false;
            break;
    }
    return( result );
}

void BeetleGame::computerRoll( int amount )
{
    // if the amount is zero, roll the Computer's die
    if (amount == 0) {
        mComputerDie.roll();
    }
    // otherwise, cheat by forcing the amount into the Computer's die
    else {
        mComputerDie.setValue(amount);
    }
}

// return the value of the Computer's die
int BeetleGame::getComputerDie( ) const
{
    return( mComputerDie.getValue() );
}

// if a body part was successfully built, returns true
// otherwise, returns false
bool BeetleGame::computerPlay( )
{
    bool result = false;
    
    // convert computer die roll to Beetle body part
    Beetle::BodyPart part = mComputer.convertRollToBodyPart(mComputerDie.getValue());
    
    // depending on which part was called, build that body part if it follows game ordering
    switch (part) {
        // build eye only if head and body are built and at least one eye is missing
        case Beetle::BodyPart::EYE:
            if (mComputer.hasHead() && mComputer.hasBody() && (!mComputer.hasEye1() || !mComputer.hasEye2()) ) {
                mComputer.buildEye();
                result = true;
            }
            break;
        // build antenna only if head and body are built and at least one antenna is missing
        case Beetle::BodyPart::ANTENNA:
            if (mComputer.hasHead() && mComputer.hasBody() && (!mComputer.hasAntenna1() || !mComputer.hasAntenna2()) ) {
                mComputer.buildAntenna();
                result = true;
            }
            break;
        // build leg only if body already built and at least one leg is missing
        case Beetle::BodyPart::LEG:
            if (mComputer.hasBody() && (!mComputer.hasLeg1() || !mComputer.hasLeg2() || !mComputer.hasLeg3() || !mComputer.hasLeg4()) ) {
                mComputer.buildLeg();
                result = true;
            }
            break;
        // build tail only if body already built and tail is missing
        case Beetle::BodyPart::TAIL:
            if (mComputer.hasBody() && !mComputer.hasTail() ) {
                mComputer.buildTail();
                result = true;
            }
            break;
        // build head only if body already built and head is missing
        case Beetle::BodyPart::HEAD:
            if (mComputer.hasBody() && !mComputer.hasHead()) {
                mComputer.buildHead();
                result = true;
            }
            break;
        // build body only if body is missing
        case Beetle::BodyPart::BODY:
            if (!mComputer.hasBody()) {
                mComputer.buildBody();
                result = true;
            }
            break;
        // invalid die roll - nothing built
        case Beetle::BodyPart::NOTVALID:
            result = false;
            break;
    }
    return( result );
}

// determines current state of the game
BeetleGame::GameOutcome  BeetleGame::determineGameOutcome( ) const
{
    // if the human's beetle is complete and computer's is not, human won
    if (mHuman.isComplete() && !mComputer.isComplete()) {
        return GameOutcome::HUMANWONGAME;
    }
    // if the human's beetle is not complete and computer's is, computer won
    else if (!mHuman.isComplete() && mComputer.isComplete()) {
        return GameOutcome::COMPUTERWONGAME;
    }
    // if both human and computer's beetles are complete, human wins since they rolled first
    else if (mHuman.isComplete() && mComputer.isComplete()) {
        return GameOutcome::HUMANWONGAME;
    }
    // if neither beetle is complete, game is not over
    else {
        return GameOutcome::GAMENOTOVER;
    }
}

std::string  BeetleGame::stringifyGameOutcome( ) const
{
    std::string result = "";
    switch( determineGameOutcome() )
    {
        case GameOutcome::COMPUTERWONGAME:
            result = "Computer Won!";
            break;
        case GameOutcome::HUMANWONGAME:
            result = "Human Won!";
            break;
        case GameOutcome::GAMENOTOVER:
            result = "Game Not Over!";
            break;
    }
    return( result );
}

// tells if the game ended with a winner and is thus over
bool BeetleGame::gameIsOver() const
{
    // if game outcome signifies someone won, game over, so return true
    // if it says game not over, return false
    return( determineGameOutcome() != GameOutcome::GAMENOTOVER );
}


Beetle BeetleGame::getHumanBeetle( ) const
{
    return( mHuman );
}

Beetle BeetleGame::getComputerBeetle( ) const
{
    return( mComputer );
}

}


