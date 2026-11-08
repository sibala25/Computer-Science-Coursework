//  Actor.cpp
#include "Actor.h"
#include "GameObjects.h"
#include "utilities.h"
#include "Temple.h"
#include <vector>
#include <string>
#include <climits>

using namespace std;

Actor::Actor(int r, int c, int hit, Weapon* weapon, int armor, int strength, int dexterity, char symbol) : m_row(r), m_col(c), m_hit(hit), m_weapon(weapon), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleep(0), m_level(0), m_symbol(symbol) {}
int Actor::getR() const { return m_row; }
int Actor::getC() const { return m_col; }
int Actor::getHit() const { return m_hit; }
Weapon* Actor::getWeapon() const { return m_weapon; }
int Actor::getArmor() const { return m_armor; }
int Actor::getStrength() const { return m_strength; }
int Actor::getDexterity() const { return m_dexterity; }
int Actor::getSleep() const { return m_sleep; }
int Actor::getLevel() const { return m_level; }
char Actor::getSymbol() const { return m_symbol; }

string Actor::getName() const {
    if (getSymbol() == '@') {
        return "Player";
    }
    else if (getSymbol() == 'B') {
        return "the Bogeyman";
    }
    else if (getSymbol() == 'D') {
        return "the Dragon";
    }
    else if (getSymbol() == 'G') {
        return "the Goblin";
    }
    else if (getSymbol() == 'S') {
        return "the Snakewomen";
    }
    else {
        return "invalid character";
    }
}

void Actor::setR(int r) {
    m_row = r;
}

void Actor::setC(int c) {
    m_col = c;
}

void Actor::setHit(int hit) {
    if (hit <= 0) {
        m_hit = 0;
    }
    if (hit >= 99) {
        m_hit = 99;
    }
    else {
        m_hit = hit;
    }
}
void Actor::setWeapon(Weapon* weapon) { 
    if (weapon != nullptr) {
        m_weapon = weapon;
    }
}

void Actor::setArmor(int armor) {
    if (armor <= 0) {
        m_armor = 0;
    }
    if (armor >= 99) {
        m_armor = 99;
    }
    else {
        m_armor = armor;
    }
}
void Actor::setStrength(int strength) {
    if (strength <= 0) {
        m_strength = 0;
    }
    if (strength >= 99) {
        m_strength = 99;
    }
    else {
        m_strength = strength;
    }
}
void Actor::setDexterity(int dexterity) {
    if (dexterity <= 0) {
        m_dexterity = 0;
    }
    if (dexterity >= 99) {
        m_dexterity = 99;
    }
    else {
        m_dexterity = dexterity;
    }
}

void Actor::setSleep(int sleep) { m_sleep = sleep; }

void Actor::setLevel(int level) { m_level = level; }

bool Actor::hitByFangs(Actor* victim) {
    // if someone is hit by fangs outcome true
    bool outcome = trueWithProbability(0.2);
    if (outcome) {
        int X = randInt(2,6);
        int Y = victim->getSleep();
        victim->setSleep(max(X,Y));         // if random integer is greater than their sleep level, inc sleep level to that int
        return true;
    }
    else {
        return false;
    }
}

bool Actor::attack(const Actor* attacker, Actor* victim) {
    if (attacker && victim) {
        Weapon* weapon = attacker->getWeapon();
        if (weapon != nullptr) {
            if (weapon->getName() == "magic fangs of sleep") {
                bool asleep = hitByFangs(victim);                   // if the attacker's weapon is fangs, call that fn to test if it inc sleep
                if (!asleep) {                                      // attack not successful so return false
                    return false;
                }
            }
        }
        
        // calculations to decide if attack succeeded or not
        int attackerPts = attacker->getDexterity() + weapon->getDamage();
        int victimPts = victim->getDexterity() + victim->getArmor();
        
        if (randInt(1, attackerPts) >= randInt(1,victimPts)) {                  // attack succeeded so make needed changes based on weapon below
            int weaponDmg = weapon->getDamage();
            int dmgPts = randInt(0,attacker->getStrength() + weaponDmg - 1);
            int currentHit = victim->getHit();
            victim->setHit(currentHit - dmgPts);
            return true;
        } else {
            return false;
        }
    }
    return false;
}


Actor::~Actor() {
    delete getWeapon();
}

void Actor::attackResult(Actor& attacker, Actor& victim, bool hit, Temple* temple) const {
    string result = "";
    
    // if the attack was successful, generate matching string message to my attack message vector
    if (hit) {
        if (victim.isDead()) {
            result = attacker.getName() + " " + attacker.getWeapon()->getAction() + " " + victim.getName() + " dealing a final blow.";
        }
        else if (attacker.getWeapon()->getName() == "magic fangs of sleep") {
           result = attacker.getName() + " " + attacker.getWeapon()->getAction() + " " + victim.getName() + " and hits, putting " + victim.getName() + " to sleep.";
        }
        else {
            result = attacker.getName() + " " + attacker.getWeapon()->getAction() + " " + victim.getName() + " and hits.";
        }
    }
    // if attack failed, generate string message that it missed
    else {
        result = attacker.getName() + " " + attacker.getWeapon()->getAction() + " " + victim.getName() + " and misses.";
    }
    // if a message was generated, push it into the vector we will output later in the console after both player+all monsters' turns are done
    if (result != "") {
        temple->m_attacks.push_back(result);
    }
    
}

bool Actor::isDead() {
    // less than or equal to 0 hit points signifies death
    return (getHit() <= 0);
}

void Actor::setSymbol(char sym) {
    m_symbol = sym;
}

Player::Player(int r, int c, int maxhit) : Actor(r, c, 20, new Weapon(r,c,"short sword","weapon",')',0,2), 2, 2, 2, '@'), max_hit(maxhit) {
    m_inventory.push_back(new Weapon(r,c,"short sword","weapon",')',0,2));
}
void Player::setHit(int hit) {
    if (hit <= 0) {
        Actor::setHit(0);
    }
    if (hit >= max_hit) {               // since max hit can be changed by reading certain scrolls, override base fn
        Actor::setHit(max_hit);
    }
    else {
        Actor::setHit(hit);
    }
}

void Player::setMaxHit(int max) {
    max_hit = max;
}

void Player::walk(char direction, Temple* temple) {         // function for taking the players turn
    int currentR = getR();
    int currentC = getC();

    if (getSleep() > 0) {                                   // if asleep, cannot take a turn but can dec sleep by 1
        int currentSleep = getSleep();
        setSleep(currentSleep - 1);
        setC(currentC);
        setR(currentR);
        return;
    }
    
    char future;
    switch (direction) {
        case ARROW_UP:
            future = temple->getChar(currentR-1, currentC);
    
            // if "up" coord if a valid spot to move to, change row val and move up
            if (currentR-1 > 0 && (future == ' ' || future == ')' || future == '?' || future == '>' || future == '&') && currentR-1 < 17) {
                setR(currentR-1);
                temple->setGrid(currentR-1, currentC, '@');
                temple->setGrid(currentR, currentC, ' ');
            }
            
            // if up is a monster, attack it and display result
            else if (future == 'B' || future == 'D' || future == 'G' || future == 'S') {
                Actor* monster = temple->getMonster(currentR-1, currentC, future);
                bool hit = attack(this, monster);
                attackResult(*this, *monster, hit, temple);
                
            // if up is a wall, don't move
            } else {
                setR(currentR);
            }
            break;
        case ARROW_DOWN:
            future = temple->getChar(currentR+1, currentC);
            
            // if "down" coord if a valid spot to move to, change row val and move down
            if (currentR+1 > 0 && (future == ' ' || future == ')' || future == '?' || future == '>' || future == '&') && currentR+1 < 17) {
                setR(currentR+1);
                temple->setGrid(currentR+1, currentC, '@');
                temple->setGrid(currentR, currentC, ' ');
            }
            
            // if down is a monster, attack it and display result
            else if (future == 'B' || future == 'D' || future == 'G' || future == 'S') {
                Actor* monster = temple->getMonster(currentR+1, currentC, future);
                bool hit = attack(this, monster);
                attackResult(*this, *monster, hit, temple);
            
            // if down is a wall, don't move
            } else {
                setR(currentR);
            }
            break;
        case ARROW_LEFT:
            future = temple->getChar(currentR, currentC-1);
            
            // if "left" coord if a valid spot to move to, change col val and move left
            if (currentC-1 > 0 && (future == ' ' || future == ')' || future == '?' || future == '>' || future == '&') && currentC-1 < 69) {
                setC(currentC-1);
                temple->setGrid(currentR, currentC-1, '@');
                temple->setGrid(currentR, currentC, ' ');
            }
            
            // if left is a monster, attack it and display result
            else if (future == 'B' || future == 'D' || future == 'G' || future == 'S') {
                Actor* monster = temple->getMonster(currentR, currentC-1, future);
                bool hit = attack(this, monster);
                attackResult(*this, *monster, hit, temple);
            
            // if left is a wall, don't move
            } else {
                setC(currentC);
            }
            break;
        case ARROW_RIGHT:
            future = temple->getChar(currentR, currentC+1);
            
            // if "right" coord if a valid spot to move to, change col val and move right
            if (currentC+1 > 0 && (future == ' ' || future == ')' || future == '?' || future == '>' || future == '&') && currentC+1 < 69) {
                setC(currentC+1);
                temple->setGrid(currentR, currentC+1, '@');
                temple->setGrid(currentR, currentC, ' ');
            }
            
            // if right is a monster, attack it and display result
            else if (future == 'B' || future == 'D' || future == 'G' || future == 'S') {
                Actor* monster = temple->getMonster(currentR, currentC+1, future);
                bool hit = attack(this, monster);
                attackResult(*this, *monster, hit, temple);
            
                // if right is a wall, don't move
            } else {
                setC(currentC);
            }
            break;
    }
}

bool Player::pickUpObj(Object* obj, Temple* temple) {
    if (obj != nullptr) {
        if (obj->getSymbol() == ')' || obj->getSymbol() == '?' || obj->getSymbol() == '&') {
            if (m_inventory.size() <= 25) {                                         // if less than 26 items in inventory, add it
                if (obj->getType() == "weapon") {
                    m_inventory.push_back(obj);
                    temple->m_attacks.push_back("You pick up " + obj->getName() + ".");
                } else if (obj->getType() == "scroll") {
                    m_inventory.push_back(obj);
                    temple->m_attacks.push_back("You pick up a scroll called " + obj->getName() + ".");
                } else if (obj->getType() == "golden idol") {
                    m_inventory.push_back(obj);
                    temple->m_attacks.push_back("You pick up " + obj->getName() + ".");
                    temple->m_attacks.push_back("Congratulations, you won!");
                    temple->m_attacks.push_back("Press q to exit game.");
                }
                obj = nullptr;
                
                return true;
            }
            else {
                // if inventory at max (26), do not add it to inventory vector
                temple->m_attacks.push_back("Your knapsack is full; you can't pick that up.");
                return false;
            }
        }
    }
    return false;
}

void Player::showInventory() {
    cout << "Inventory: " << endl;
    for (int i = 0; i < m_inventory.size(); i++) {
        char letter = 'a' + i;                                              // calculating for list ordering ('a','b'...)
        cout << letter << ". " << m_inventory[i]->getName() << endl;
    }
}

void Player::readScroll(char letter, Temple* temple) {
    int index = letter - 'a';                                               // convert user input letter to inventory index
    if (index >= 0 && index < m_inventory.size()) {
        Object* obj = m_inventory[index];
        if (obj != nullptr && obj->getType() == "scroll") {
            Scroll* scroll = dynamic_cast<Scroll*>(m_inventory[index]);     // dynamic cast m_inventory has object pointers
            
            string type = scroll->getName();
            if (type == "scroll of teleportation") {
                int r;
                int c;
                
                bool empty = false;
                while(!empty) {                                             // generate random coordinates that are in-bounds
                    r = randInt(1, 16);
                    c = randInt(1, 68);
                    if (temple->getChar(r,c) == ' ' || temple->getChar(r,c) == ')' || temple->getChar(r,c) == '?' || temple->getChar(r,c) == '>' || temple->getChar(r,c) == '&' ) {
                        setR(r);
                        setC(c);
                        empty = true;                                       // keep generating until coords are 'empty" and player can move there
                    }
                }
            }
            else if (type == "scroll of strength") {
                int current = getStrength();
                setStrength(current+2);
            }
            else if (type == "scroll of enhance armor") {
                int current = getArmor();
                setArmor(current+1);
            }
            else if (type == "scroll of enhance health") {
                setMaxHit(max_hit + 1);
            }
            else if (type == "scroll of enhance dexterity") {
                int current = getDexterity();
                setDexterity(current+2);
            }
            temple->m_attacks.push_back("You read the scroll called " + scroll->getName() + ". ");
            temple->m_attacks.push_back(scroll->getAction());
            // once you read a scroll, erase it from the inventory, using the index to find it
            delete obj;
            m_inventory.erase(m_inventory.begin()+index);
        }
        else if (obj != nullptr && obj->getType() == "weapon") {
            temple->m_attacks.push_back("You can't read a " + obj->getName() + ". ");
        }
    }
}

void Player::wieldWeapon(char letter, Temple* temple) {
    int index = letter - 'a';                                               // calculating for list ordering ('a','b'...)
    if (index >= 0 && index < m_inventory.size()) {
        Object* obj = m_inventory[index];
        if (obj != nullptr && obj->getType() == "weapon") {
            Weapon* weapon = dynamic_cast<Weapon*>(m_inventory[index]);
            temple->m_attacks.push_back("You are wielding " + weapon->getName() + ". ");
            
            // added below
            delete getWeapon();
            
            string w_name = weapon->getName();
            int w_bonus = weapon->getBonus();
            int w_damage = weapon->getDamage();
            Weapon* newWeapon = new Weapon(0,0,w_name,"weapon",')',w_bonus,w_damage);
            
            setWeapon(newWeapon);
            // till here
        }
        if (obj != nullptr && obj->getType() == "scroll") {
            temple->m_attacks.push_back("You can't wield " + obj->getName() + ". ");
        }
    }
}

int Player::getMaxHit() { return max_hit; }

void Player::transferInventory(Player* newPlayer) {
    // iterate over inventory and transfer from old to new player at each new level
    for (int i = 1; i < m_inventory.size(); i++) {
        // scrolls have: action, name, type, symbol
        // Scroll(int r, int c, string name, string type, char symbol);
        if (m_inventory[i]->getType() == "scroll") {
            Scroll* scroll = dynamic_cast<Scroll*>(m_inventory[i]);
            string name = scroll->getName();
            newPlayer->m_inventory.push_back(new Scroll(0,0,name,"scroll",'?'));
        }
        // weapons have: action, name, type, symbol, bonus, damage
        // Weapon(int r, int c, string name, string type, char symbol, int bonus, int damage)
        if (m_inventory[i]->getType() == "weapon") {
            Weapon* weapon = dynamic_cast<Weapon*>(m_inventory[i]);
            string name = weapon->getName();
            int bonus = weapon->getBonus();
            int damage = weapon->getDamage();
            newPlayer->m_inventory.push_back(new Weapon(0,0,name,"weapon",')',bonus,damage));
        }
    }
}

Player::~Player() {
    //iterate over inventory and delete
    for (int i = 0; i < m_inventory.size(); i++) {
        delete m_inventory[i];
    }
}

Monster::Monster(int r, int c, int hit, Weapon* weapon, int armor, int strength, int dexterity, char symbol) : Actor(r, c, hit, weapon, armor, strength, dexterity, symbol) {
    
}

void Monster::move(Player* player, Temple* temple, int smell) { // function for moving Bogeyman and Snakewomen, NOT Goblins or Dragons
                                                                // called in moveMonsters() in temple class
    if (!player || !temple) {
        return;
    }
    int monsterR = getR();
    int monsterC = getC();
    
    if (getSleep() > 0) {                                       // if asleep, cannot take a turn but can dec sleep by 1
        int currentSleep = getSleep();
        setSleep(currentSleep - 1);
        setC(monsterC);
        setR(monsterR);
        return;
    }
    
    int playerR = player->getR();
    int playerC = player->getC();
    
    char future;
    int distance = abs(monsterC - playerC) + abs(monsterR - playerR);
    
    // if abs val of player and monster distance is 1, attack it
    if (distance == 1) {
        bool hit = attack(this, player);
        attackResult(*this, *player, hit, temple);
        return;
    }

    // if player is in smellable distance, AND more than 1 away (since we do not want to move onto player)
    // determine which way to go based on difference between monster and player r/c coordinates
    if (distance <= smell  && distance > 1) {
        
        // if player col < monster col move left if it is a valid space, DO NOT move otherwise
        if (playerC < monsterC) {
            future = temple->getChar(monsterR, monsterC-1);
            if (future == ' ' || future == ')' || future == '?'|| future == '>'|| future == '&') {
                setC(monsterC-1);
                temple->setGrid(monsterR, monsterC-1, getSymbol());
                temple->setGrid(monsterR, monsterC, ' ');
                return;
            }
            else {
                setC(monsterC);
            }
        }
        
        // if player col > monster col move right if it is a valid space
        if (playerC > monsterC) {
            future = temple->getChar(monsterR, monsterC+1);
            if (future == ' ' || future == ')' || future == '?'|| future == '>'|| future == '&') {
                setC(monsterC+1);
                temple->setGrid(monsterR, monsterC+1, getSymbol());
                temple->setGrid(monsterR, monsterC, ' ');
                return;
            }
            else {
                setC(monsterC);
            }
        }
        
        // if player row > monster row move down if it is a valid space
        if (playerR > monsterR) {
            future = temple->getChar(monsterR+1, monsterC);
            if (future == ' ' || future == ')' || future == '?'|| future == '>'|| future == '&') {
                setR(monsterR+1);
                temple->setGrid(monsterR+1, monsterC, getSymbol());
                temple->setGrid(monsterR, monsterC, ' ');
                return;
            }
            else {
                setR(monsterR);
            }
        }
        
        // if player row < monster row move up if it is a valid space
        if (playerR < monsterR) {
            future = temple->getChar(monsterR-1, monsterC);
            if (future == ' ' || future == ')' || future == '?'|| future == '>'|| future == '&') {
                setR(monsterR-1);
                temple->setGrid(monsterR-1, monsterC, getSymbol());
                temple->setGrid(monsterR, monsterC, ' ');
                return;
            }
            else {
                setR(monsterR);
            }
        }
    }
}

Monster::~Monster() {}

Bogeyman::Bogeyman(int r, int c) : Monster(r, c, randInt(5,10), new Weapon(r,c,"short sword","weapon",')',0,2), 2, randInt(2,3), randInt(2,3), 'B') {}

Bogeyman::~Bogeyman() {}

Snakewomen::Snakewomen(int r, int c) : Monster(r, c, randInt(3,6), new Weapon(r,c,"magic fangs of sleep","weapon",')',3,2), 3, 2, 3, 'S') {}

Snakewomen::~Snakewomen() {}

Dragon::Dragon(int r, int c) : Monster(r, c, randInt(20, 25), new Weapon(r,c,"long sword","weapon",')',2,4), 4, 4, 4, 'D') {}

void Dragon::move(Player* player, Temple* temple, int smell) {           // dragon's move function, called in moveMonsters() in temple class
    
    // 1 in 10 chance of a dragon's hit point increasing
    bool gainPoint = trueWithProbability(0.1);
    if (gainPoint) {                                        // inc hit points if true
        int currentHit = getHit();
        setHit(currentHit+1);
    }
    
    // dragons do not move, just attack
    int monsterR = getR();
    int monsterC = getC();
    int playerR;
    int playerC;
    if (player != nullptr)  {
        playerR = player->getR();
        playerC = player->getC();
    } else {
        return;
    }
    
    // if player is one away, attack it and generate result
    if ( (monsterR == playerR && abs(monsterC-playerC) == 1) || (monsterC == playerC && abs(monsterR-playerR) == 1) ) {
        bool hit = attack(this, player);
        attackResult(*this, *player, hit,temple);
    }
}


Dragon::~Dragon() {}

Goblin::Goblin(int r, int c) : Monster(r, c, randInt(15,20), new Weapon(r,c,"short sword","weapon",')',0,2), 1, 3, 1,'G'){}

bool Goblin::shortestPathExists(Player* player, Temple* temple, int smell, int sr, int sc, int &pathLen, int currLen, char copy[MAXROWS][MAXCOLS]) {

    // mark your spot
    copy[sr][sc] = '.';
    
    // if spot to start from is not valid, do not check and return false
    if (sr < 0 || sr > 16 || sc < 0 || sc > 68) {
        return false;
    }
    
    int er = player->getR();
    int ec = player->getC();
    
    // if player is not in reachable difference, automatically false
    if ( (abs(sr - er) + abs(sc - ec)) > smell ) {
        return false;
    }
    
    if (smell < 0) {
        return false;
    }
            
    // if goblin's coordinates equal player's coordinates, return true b/c successful
    // if the length is shorter than the previous shortest length, update overall pathLen
    if (sr == er && sc == ec) {
        copy[sr][sc] = temple->getChar(sr, sc);
        if (currLen < pathLen) {
                pathLen = currLen;
        }
        return true;
    }
    
    bool pathFound = false;
        
    // check up
    if (copy[sr-1][sc] != '.'  && (copy[sr-1][sc] == ' ' || copy[sr-1][sc] == '?' || copy[sr-1][sc] == ')' || copy[sr-1][sc] == '>' || copy[sr-1][sc] == '&' || copy[sr-1][sc] == '@') && shortestPathExists(player, temple, smell-1, sr-1, sc, pathLen, currLen+1, copy)) {
        pathFound = true;
    }

    // check down
    if (copy[sr+1][sc] != '.'  && (copy[sr+1][sc] == ' ' || copy[sr+1][sc] == '?' || copy[sr+1][sc] == ')' || copy[sr+1][sc] == '>' || copy[sr+1][sc] == '&' || copy[sr+1][sc] == '@') && shortestPathExists(player, temple, smell-1, sr+1, sc, pathLen, currLen+1, copy)) {
        pathFound = true;
    }
    // check left
    if (copy[sr][sc-1] != '.'  && (copy[sr][sc-1] == ' ' || copy[sr][sc-1] == '?' || copy[sr][sc-1] == ')' || copy[sr][sc-1] == '>' || copy[sr][sc-1] == '&' || copy[sr][sc-1] == '@') && shortestPathExists(player, temple, smell-1, sr, sc-1, pathLen, currLen+1, copy)) {
        pathFound = true;
    }
    // check right
    if (copy[sr][sc+1] != '.'  && (copy[sr][sc+1] == ' ' || copy[sr][sc+1] == '?' || copy[sr][sc+1] == ')' || copy[sr][sc+1] == '>' || copy[sr][sc+1] == '&' || copy[sr][sc+1] == '@') && shortestPathExists(player, temple, smell-1, sr, sc+1, pathLen, currLen+1, copy)) {
        pathFound = true;
    }
    
    // unmark spot
    copy[sr][sc] = temple->getChar(sr, sc);
    
    return pathFound;
}


void Goblin::move(Player* player, Temple* temple, int smell) {
    if (!player || !temple) {
        return;
    }
    
    int monsterR = getR();
    int monsterC = getC();
    
    int playerR = player->getR();
    int playerC = player->getC();
    
    // if asleep, do not move
    if (getSleep() > 0) {
        int currentSleep = getSleep();
        setSleep(currentSleep - 1);
        setC(monsterC);
        setR(monsterR);
        return;
    }
    
    // if player is one away, attack it
    if ( (monsterR == playerR && abs(monsterC-playerC) == 1) || (monsterC == playerC && abs(monsterR-playerR) == 1) ) {
        bool hit = attack(this, player);
        attackResult(*this, *player, hit,temple);
        return;
    }
    
    // grid copy to pass into function
    char copy1[MAXROWS][MAXCOLS];
    
    for (int r = 0; r < MAXROWS; r++) {
        for (int c = 0; c < MAXCOLS; c++) {
               copy1[r][c] = temple->getChar(r, c);
            }
        }

    // if can move up, find length of shortest path
    int pathlen1 = INT_MAX;
    int up_path;
    
    if ((temple->getChar(monsterR-1,monsterC) == ' ' ||
        temple->getChar(monsterR-1,monsterC) == ')' ||
        temple->getChar(monsterR-1,monsterC) == '?' ||
        temple->getChar(monsterR-1,monsterC) == '&' ||
        temple->getChar(monsterR-1,monsterC) == '>') &&
        shortestPathExists(player, temple, smell-1, monsterR-1, monsterC, pathlen1, 0, copy1)) {
        
        up_path = pathlen1;
        
    } else {                                            // if no path found, mark it as int max
        up_path = INT_MAX;
    }

    // grid copy to pass into function
    char copy2[MAXROWS][MAXCOLS];
    
    for (int r = 0; r < MAXROWS; r++) {
        for (int c = 0; c < MAXCOLS; c++) {
               copy2[r][c] = temple->getChar(r, c);
            }
        }

    // if can move down, find length of shortest path
    int pathlen2 = INT_MAX;
    int down_path;

    if ((temple->getChar(monsterR+1,monsterC) == ' ' ||
        temple->getChar(monsterR+1,monsterC) == ')' ||
        temple->getChar(monsterR+1,monsterC) == '?' ||
        temple->getChar(monsterR+1,monsterC) == '&' ||
        temple->getChar(monsterR+1,monsterC) == '>') &&
        shortestPathExists(player, temple, smell-1, monsterR+1, monsterC, pathlen2, 0, copy2)) {
        
        down_path = pathlen2;
        
    } else {
        down_path = INT_MAX;                            // if no path found, mark it as int max
    }
    
    // grid copy to pass into function
    char copy3[MAXROWS][MAXCOLS];
    
    for (int r = 0; r < MAXROWS; r++) {
        for (int c = 0; c < MAXCOLS; c++) {
               copy3[r][c] = temple->getChar(r, c);
            }
        }

    // if can move right, find length of shortest path
    int pathlen3 = INT_MAX;
    int right_path;

    if ((temple->getChar(monsterR,monsterC+1) == ' ' ||
        temple->getChar(monsterR,monsterC+1) == ')' ||
        temple->getChar(monsterR,monsterC+1) == '?' ||
        temple->getChar(monsterR,monsterC+1) == '&' ||
        temple->getChar(monsterR,monsterC+1) == '>') && 
        shortestPathExists(player, temple, smell-1, monsterR, monsterC+1, pathlen3, 0, copy3))  {
        
        right_path = pathlen3;
        
    } else {
        right_path = INT_MAX;                           // if no path found, mark it as int max
    }
    
    // grid copy to pass into function
    char copy4[MAXROWS][MAXCOLS];
    
    for (int r = 0; r < MAXROWS; r++) {
        for (int c = 0; c < MAXCOLS; c++) {
               copy4[r][c] = temple->getChar(r, c);
            }
        }

    int pathlen4 = INT_MAX;
    int left_path;

    if ((temple->getChar(monsterR,monsterC-1) == ' ' ||
        temple->getChar(monsterR,monsterC-1) == ')' ||
        temple->getChar(monsterR,monsterC-1) == '?' ||
        temple->getChar(monsterR,monsterC-1) == '&' ||
        temple->getChar(monsterR,monsterC-1) == '>') &&
        shortestPathExists(player, temple, smell-1, monsterR, monsterC-1, pathlen4, 0, copy4)) {
        
        left_path = pathlen4;
        
    } else {
        left_path = INT_MAX;                            // if no path found, mark it as int max
    }
       
    // if all directions do not have a shortest path, just return
    if (up_path == INT_MAX && down_path == INT_MAX && right_path == INT_MAX && left_path == INT_MAX) {
        return;
    }
    
    // determine direction with smallest path and move in that direction
    int min_path = min(up_path, min(down_path, min(right_path, left_path)));

    if (min_path == up_path) {
        setR(monsterR - 1);
        temple->setGrid(monsterR-1, monsterC, getSymbol());
        temple->setGrid(monsterR, monsterC, ' ');
    } else if (min_path == down_path) {
        setR(monsterR + 1);
        temple->setGrid(monsterR+1, monsterC, getSymbol());
        temple->setGrid(monsterR, monsterC, ' ');
    } else if (min_path == right_path) {
        setC(monsterC + 1);
        temple->setGrid(monsterR, monsterC+1, getSymbol());
        temple->setGrid(monsterR, monsterC, ' ');
    } else if (min_path == left_path) {
        setC(monsterC - 1);
        temple->setGrid(monsterR, monsterC-1, getSymbol());
        temple->setGrid(monsterR, monsterC, ' ');
    }
    
}


Goblin::~Goblin() {}
