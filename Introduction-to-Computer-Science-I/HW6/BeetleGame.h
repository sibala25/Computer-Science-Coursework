//
//  BeetleGame.h
//
//

#ifndef BeetleGameH
#define BeetleGameH
#include <string>

#include "Beetle.h"
#include "Die.h"

namespace cs31
{
    
    class BeetleGame
    {
    public:
        BeetleGame();
        
        // the possible outcome choices
        enum class GameOutcome { HUMANWONGAME, COMPUTERWONGAME, GAMENOTOVER };
        
        // draw the board by using a BeetleDrawing to draw the two Beetles
        std::string display( std::string msg = "" ) const;
        
        void humanRoll( int amount = 0 );
        
        int getHumanDie( ) const;
        
        bool humanPlay( );
        
        void computerRoll( int amount = 0 );
        
        int getComputerDie( ) const;
        
        bool computerPlay( );
        
        GameOutcome  determineGameOutcome( ) const;
        std::string  stringifyGameOutcome( ) const;

        bool gameIsOver() const;
        
        // for testing purposes
        Beetle getHumanBeetle( ) const;
        Beetle getComputerBeetle( ) const;
    private:
        Beetle mHuman,    mComputer;
        Die    mHumanDie, mComputerDie;
    };
    
}

#endif
