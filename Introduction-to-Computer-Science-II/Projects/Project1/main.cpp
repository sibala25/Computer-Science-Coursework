#include "City.h"
    int main()
    {
        City ct(10, 20);
        ct.addPlayer(2, 2);
    }
//#include "History.h"
//#include "City.h"
//#include "Game.h"
//#include <iostream>
//using namespace std;
//
//// toot.cpp
//
//
///////////////////////////////////////////////////////////////////////////////
//////  main()
///////////////////////////////////////////////////////////////////////////////
////
//int main()
//{
//      // Create a game
//      // Use this instead to create a mini-game:   Game g(3, 4, 2);
//    Game g(7, 8, 25);
//
//      // Play the game
//    g.play();
//}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// YOU MAY MOVE TO ANOTHER FILE ALL THE CODE FROM HERE TO THE END OF THIS FILE,
// BUT BE SURE TO MOVE *ALL* THE CODE AS IS; DON'T REMOVE OR MODIFY ANY #IFDEF,
// ETC.  THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31/g32 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32  //  Windows

#pragma warning(disable : 4005)
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

//#include <iostream>
//#include <cstring>
//#include <cstdlib>
//using namespace std;


#endif
