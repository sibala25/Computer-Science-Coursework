//  GameObjects.cpp

#include "GameObjects.h"
#include <string>

Object::Object(int r, int c, string name, string type, char symbol) : m_r(r), m_c(c), m_name(name), m_type(type), m_symbol(symbol) {}

int Object::getR() const { return m_r; }

int Object::getC() const { return m_c; }

string Object::getName() const { return m_name; }

string Object::getAction() const { return " "; }

string Object::getType() const {return m_type;}

char Object::getSymbol() const {return m_symbol;}

Object::~Object() {}

Weapon::Weapon(int r, int c, string name, string type, char symbol, int bonus, int damage) : Object(r, c, name,type,symbol), m_bonus(bonus), m_damage(damage) {}

string Weapon::getAction() {
    if (getName() == "mace") {
        return "swings mace at";
    }
    if (getName() == "short sword") {
        return "slashes short sword at";
    }
    if (getName() == "long sword") {
        return "swings long sword at";
    }
    if (getName() == "magic axe") {
        return "chops magic axe at";
    }
    if (getName() == "magic fangs of sleep") {
        return "strikes magic fangs at";
    }
    else {
        return "";
    }
}

int Weapon::getBonus() {return m_bonus;}

int Weapon::getDamage() {return m_damage;}

Weapon::~Weapon() {}

Scroll::Scroll(int r, int c, string name, string type, char symbol) : Object(r, c, name, type, symbol) {}
string Scroll::getAction() {
    if (getName() == "scroll of teleportation") {
        return "You feel your body wrenched in space and time.";
    }
    if (getName() == "scroll of strength") {
        return "Your muscles bulge.";
    }
    if (getName() == "scroll of enhance armor") {
        return "Your armor glows blue.";
    }
    if (getName() == "scroll of enhance health") {
        return "You feel your heart beating stronger.";
    }
    if (getName() == "scroll of enhance dexterity") {
        return "You feel like less of a klutz.";
    }
    else {
        return "";
    }
}
Scroll::~Scroll() {}
