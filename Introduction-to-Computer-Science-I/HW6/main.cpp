//
//  main.cpp
//
//
#include <cassert>
#include <iostream>
#include "Beetle.h"
#include "BeetleGame.h"
#include "BeetleDrawing.h"
#include "Die.h"

void clearScreen();

int main()
{
    using namespace cs31;
    using namespace std;
    
    // Die: roll/getvalue
    // Make sure values are between 1-6

    Die d;
    d.roll();
    int value = d.getValue();
    assert( value >= 1 && value <= 6 );

    //Beetle
    //Testing that all build functions work as expected and that eyes (2), legs (4), antennas (2) are built in order
    
    Beetle a;

    assert( a.hasEye1() == false );
    assert( a.hasEye2() == false );
    a.buildEye();
    assert( a.hasEye1() );
    assert( a.hasEye2( ) == false );
    a.buildEye( );
    assert( a.hasEye1() );
    assert( a.hasEye2( ) );

    assert( a.hasAntenna1() == false );
    assert( a.hasAntenna2() == false );
    a.buildAntenna();
    assert( a.hasAntenna1() );
    assert( a.hasAntenna2( ) == false );
    a.buildAntenna( );
    assert( a.hasAntenna1() );
    assert( a.hasAntenna2( ) );

    assert( a.hasLeg1() == false );
    assert( a.hasLeg2() == false );
    assert( a.hasLeg3() == false );
    assert( a.hasLeg4() == false );
    a.buildLeg();
    assert( a.hasLeg1() );
    assert( a.hasLeg2() == false );
    assert( a.hasLeg3() == false );
    assert( a.hasLeg4() == false );
    a.buildLeg();
    assert( a.hasLeg1() );
    assert( a.hasLeg2() );
    assert( a.hasLeg3() == false );
    assert( a.hasLeg4() == false );
    a.buildLeg();
    assert( a.hasLeg1() );
    assert( a.hasLeg2() );
    assert( a.hasLeg3() );
    assert( a.hasLeg4() == false );
    a.buildLeg();
    assert( a.hasLeg1() );
    assert( a.hasLeg2() );
    assert( a.hasLeg3() );
    assert( a.hasLeg4() );

    assert( a.hasTail() == false );
    a.buildTail();
    assert( a.hasTail() );

    assert( a.hasHead() == false );
    a.buildHead();
    assert( a.hasHead() );

    assert( a.hasBody() == false );
    a.buildBody();
    assert( a.hasBody() );

    //Test isComplete
    assert( a.isComplete() );

    // if missing anything, such as legs, NOT complete
    Beetle b;

    b.buildEye();
    b.buildEye();
    b.buildAntenna();
    b.buildAntenna();
    b.buildAntenna();
    b.buildAntenna();
    b.buildLeg();
    b.buildTail();
    b.buildHead();
    b.buildBody();
    assert( b.isComplete() == false);

    b.buildLeg();
    b.buildLeg();
    b.buildLeg();
    assert( b.isComplete() );



    //Testing that convertRollToBodyPart works as expected
    Beetle c;
    assert(c.convertRollToBodyPart(1) == Beetle::BodyPart::EYE);
    assert(c.convertRollToBodyPart(2) == Beetle::BodyPart::ANTENNA);
    assert(c.convertRollToBodyPart(3) == Beetle::BodyPart::LEG);
    assert(c.convertRollToBodyPart(4) == Beetle::BodyPart::TAIL);
    assert(c.convertRollToBodyPart(5) == Beetle::BodyPart::HEAD);
    assert(c.convertRollToBodyPart(6) == Beetle::BodyPart::BODY);
    assert(c.convertRollToBodyPart(7) == Beetle::BodyPart::NOTVALID);
    
    //BeetleGame
    //Test humanRoll, getHumanDie, computerRoll, getComputerDie

    BeetleGame game1;
    game1.humanRoll( 2 );
    assert( game1.getHumanDie() == 2 );
    game1.computerRoll( 6 );
    assert( game1.getComputerDie( ) == 6 );
    
    //A body must be placed first, before ANYTHING - try something before and make sure it returns false

    BeetleGame game2;
    assert( game2.gameIsOver() == false );
    game2.humanRoll( 4 );
    game2.humanPlay();
    game2.computerRoll( 4 );
    game2.computerPlay();

    // should not build an eye
    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasTail() == false );
    assert( game2.getHumanBeetle().hasBody() == false );

    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasTail() == false );
    assert( game2.getComputerBeetle().hasBody() == false );

    // keep playing
    assert( game2.gameIsOver() == false );

    game2.humanRoll( 6 );
    game2.humanPlay();
    game2.computerRoll( 6 );
    game2.computerPlay();

    // both beetles get bodies
    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasBody() );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasBody() );

    //Additionally, a head must be placed before eyes or an antenna can be placed.

    game2.humanRoll( 1 );
    game2.humanPlay();
    game2.computerRoll( 2 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasEye1() == false );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasAntenna1() == false );

    game2.humanRoll( 5 );
    game2.humanPlay();
    game2.computerRoll( 5 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasHead() );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasHead() );

    game2.humanRoll( 1 );
    game2.humanPlay();
    game2.computerRoll( 2 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasEye1() );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasAntenna1() );

    game2.humanRoll( 1 );
    game2.humanPlay();
    game2.computerRoll( 5 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasEye2() );
    assert( game2.getComputerBeetle().isComplete() == false );

    game2.humanRoll( 3 );
    game2.humanPlay();
    game2.computerRoll( 4 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasLeg1() );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasTail() );

    game2.humanRoll( 6 );
    game2.humanPlay();
    game2.computerRoll( 1 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasEye1() );

    game2.humanRoll( 3 );
    game2.humanPlay();
    game2.computerRoll( 1 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasLeg2() );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasEye2() );

    game2.humanRoll( 2 );
    game2.humanPlay();
    game2.computerRoll( 3 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasAntenna1() );
    assert( game2.getHumanBeetle().hasAntenna2() == false );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasLeg1() );

    game2.humanRoll( 2 );
    game2.humanPlay();
    game2.computerRoll( 2 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasAntenna2() );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasAntenna2() );

    game2.humanRoll( 3 );
    game2.humanPlay();
    game2.computerRoll( 2 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasLeg3() );
    assert( game2.getComputerBeetle().isComplete() == false );

    game2.humanRoll( 4 );
    game2.humanPlay();
    game2.computerRoll( 3 );
    game2.computerPlay();

    assert( game2.getHumanBeetle().isComplete() == false );
    assert( game2.getHumanBeetle().hasTail() );
    assert( game2.getComputerBeetle().isComplete() == false );
    assert( game2.getComputerBeetle().hasLeg1() );

    assert( game2.gameIsOver() == false );
    assert( game2.determineGameOutcome() == BeetleGame::GameOutcome::GAMENOTOVER );

    game2.humanRoll( 3 );
    game2.humanPlay();
    assert( game2.getHumanBeetle().hasLeg4() );

    // make sure the first player to win has a body, a head, two eyes, two antennas, four legs and a tail
    assert( game2.getHumanBeetle().isComplete() );
    assert( game2.getComputerBeetle().isComplete() == false );

    // at this point, the human should have won and game is over
    assert( game2.gameIsOver() );


    cout << "all tests cases passed!" << endl;


    
//    clearScreen();
//    
//    BeetleGame game;
//    std::string action, spots, message = "(r)oll (q)uit: ";
//
//    do
//    {
//        cout << game.display( message ) << endl;
//        cin.clear();
//        getline( cin, action );
//        while (action.size() == 0)
//        {
//            getline( cin, action );  // no blank entries allowed....
//        }
//        switch (action[0])
//        {
//            default:   // if bad move, nobody moves
//                cout << '\a' << endl;  // beep
//                continue;
//            case 'Q':
//            case 'q':
//                exit( 0 );
//                break;
//            case 'r':
//            case 'R':
//                game.humanRoll();
//                cout << "human rolled:" << game.getHumanDie() << endl;
//                if (game.humanPlay( ))
//                {
//                }
//                else
//                {
//                    cout << "no Human move possible!" << endl;
//                }
//                game.computerRoll();
//                cout << "computer rolled:" << game.getComputerDie() << endl;
//                if (game.computerPlay())
//                {
//                }
//                else
//                {
//                    cout << "no Computer move possible!" << endl;
//                }
//                break;
//        }
//    } while( !game.gameIsOver() );
//    cout << game.display( ) << endl;
//    cout << game.stringifyGameOutcome() << endl;

    return( 0 );
}



//void clearScreen();



///////////////////////////////////////////////////////////////////////////
//  clearScreen implementations
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++ UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()  // will just write a newline in an Xcode output window
{
    using namespace std;
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
    {
        cout << endl << endl << endl << endl << endl << endl << endl << endl;
    }
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
