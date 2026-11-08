//  Temple.h
#ifndef Temple_h
#define Temple_h

#include "utilities.h"
#include <vector>
#include <string>

using namespace std;

const int MAXROWS = 18;
const int MAXCOLS = 70;

class Actor;
class Player;
class Monster;
class Object;

class Temple
{
  public:
    // Constructor/destructor
    Temple(int level);
    ~Temple();

    void addRooms();
    void addCorridors();
    void addActors();
    void addObjects();
    void display();
    int getLevel();
    char getChar(int r, int c) const;
    Player* getPlayer() const;
    Monster* getMonster(int row, int col, int symbol) const;
    Object* getObject() const;
    void moveMonsters(int goblinSmell);
    void killActors();
    void deleteObject(Object* obj);
    void displayAttacks();
    void clearAttacks();
    void setGrid(int r, int c, char symbol);
    bool staircaseAt(Player* player);
    //vector of attack messages
    vector<string>m_attacks;
    // for new level intialization
    Temple* newLevel(Player* player);

  private:
    int m_rows;
    int m_cols;
    int m_level;
    char m_grid[MAXROWS][MAXCOLS];
    
    //vector of characters (actor pointer) with player and monsters
    vector<Actor*>m_actors;
    
    //vector of objects
    vector<Object*>m_objects;

    //vector of room centers coordinates
    vector<vector<int>>centers;
};


#endif /* Temple_h */
