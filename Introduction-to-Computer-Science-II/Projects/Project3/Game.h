// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include <string>

class Temple;
using namespace std;
// You may add data members and other member functions to this class.

class Game
{
public:
    Game(int goblinSmellDistance);
    void play();
    ~Game();
private:
    Temple* m_temple;
    int gobSmell;
};

#endif // GAME_INCLUDED
