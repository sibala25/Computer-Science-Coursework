//  GameObjects.h

#ifndef GameObjects_h
#define GameObjects_h

#include <string>
using namespace std;

class Object {
public:
    Object(int r, int c, string name, string type, char symbol);
    int getR() const;
    int getC() const;
    string getName() const;
    virtual string getAction() const;
    string getType() const;
    char getSymbol() const;
    virtual ~Object();
private:
    int m_r;
    int m_c;
    string m_name;
    string m_type;
    char m_symbol;
};

// all weapons in one class
class Weapon : public Object {
public:
    Weapon(int r, int c, string name, string type, char symbol, int bonus, int damage);
    string getAction();
    int getBonus();
    int getDamage();
    ~Weapon();
private:
    int m_bonus;
    int m_damage;
    
};

class Scroll : public Object {
public:
    Scroll(int r, int c, string name, string type, char symbol);
    string getAction();
    ~Scroll();
    
};


#endif /* GameObjects_h */
