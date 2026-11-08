//  Actor.h
#ifndef Actor_h
#define Actor_h

#include <string>
#include <iostream>
#include <vector>
#include "Temple.h"

using namespace std;

class Object;
class Weapon;
class Scroll;
class Temple;

class Actor
{
public:
    Actor(int r, int c, int hit, Weapon* weapon, int armor, int strength, int dexterity, char symbol);
    
    // Accessors
    int getR() const;
    int getC() const;
    int getHit() const;
    Weapon* getWeapon() const;
    int getArmor() const;
    int getStrength() const;
    int getDexterity() const;
    int getSleep() const;
    int getLevel() const;
    char getSymbol() const;
    string getName() const;
    
    //Mutators
    void setR(int r);
    void setC(int c);
    virtual void setHit(int hit);           // virtual since player's max hit can be changed, but rest are limited to 99
    void setWeapon(Weapon* weapon);
    void setArmor(int armor);
    void setStrength(int strength);
    void setDexterity(int dexterity);
    void setSleep(int sleep);
    void setLevel(int level);
    void setSymbol(char sym);
 
    bool attack(const Actor* attacker, Actor* victim);
    void attackResult(Actor& attacker, Actor& victim, bool hit, Temple* temple) const;
    bool hitByFangs(Actor* victim);
    bool isDead();
    
    virtual ~Actor();
    
private:
    int m_row;
    int m_col;
    int m_hit;
    Weapon* m_weapon;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleep;
    int m_level;
    char m_symbol;
};

class Player : public Actor {
public:
    Player(int r, int c, int maxhit);
    void walk(char direction, Temple* temple);
    bool pickUpObj(Object* obj, Temple* temple);
    void readScroll(char letter, Temple* temple);
    void wieldWeapon(char letter, Temple* temple);
    void showInventory();
    int getMaxHit();
    void setHit(int hit);
    void setMaxHit(int max);
    void transferInventory(Player* newPlayer);
    ~Player();

private:
    int max_hit;
    //pointer to array of objects
    vector<Object*> m_inventory;
};

class Monster : public Actor {
public:
    Monster(int r, int c, int hit, Weapon* weapon, int armor, int strength, int dexterity, char symbol);
    virtual void move(Player* player, Temple* temple, int smell);
    virtual ~Monster();
};

class Bogeyman : public Monster {
public:
    Bogeyman(int r, int c);
    ~Bogeyman();
};

class Snakewomen : public Monster {
public:
    Snakewomen(int r, int c);
    ~Snakewomen();
};

class Dragon : public Monster {
public:
    Dragon(int r, int c);
    void move(Player* player, Temple* temple, int smell);
    ~Dragon();
};

class Goblin : public Monster {
public:
    Goblin(int r, int c);
    bool shortestPathExists(Player* player, Temple* temple, int smell, int sr, int sc, int &pathLen, int currLen, char copy[MAXROWS][MAXCOLS]);
    int findShortestPath(Player* player, Temple* temple, int smell, int sr, int sc);
    void move(Player* player, Temple* temple, int smell);
    ~Goblin();
};



#endif /* Actor_h */
