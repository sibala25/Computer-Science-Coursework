//  Temple.cpp
#include "Temple.h"
#include "Actor.h"
#include <vector>
#include "GameObjects.h"
#include <string>

Temple::Temple(int level) : m_rows(MAXROWS), m_cols(MAXCOLS), m_level(level) {
    // initialize m_grid
    for (int r = 0; r < MAXROWS; r++) {
        for (int c = 0; c < MAXCOLS; c++) {
                m_grid[r][c] = '#';
        }
    }
}

void Temple::addRooms() {
    int numRooms = randInt(4,6);
    
    // one loop for each successful created room
    for (int i = 0; i < numRooms; i++) {
        
        // do not go to next iteration of for loop till roomDone is true, aka non-overlapping room has been made
        bool roomDone = false;
        
        int roomTopLeftR;
        int roomTopLeftC;
        
        // if the function cannot find anywhere else to place a non-overlapping room after 100 attempts, just return with rooms so far
        int attempts = 0;
        while (!roomDone) {
            attempts++;
            if (attempts > 100) {
                return;
            }
            
            // keep generating top left room coordinates until you find ones that are not already part of a room
            // i.e. must be # rather than empty spaces
            int height = randInt(4,7);
            int width = randInt(11,13);
            
            do {
                roomTopLeftR = randInt(1, m_rows-1-height);
                roomTopLeftC = randInt(1, m_cols-1-width);
            } while (m_grid[roomTopLeftR][roomTopLeftC] != '#');
            
            
            // check that you do not go into walls with height and width, and if you do just stop before the wall
            height = min(height, m_rows - roomTopLeftR - 1);
            width = min(width, m_cols - roomTopLeftC - 1);
            
            // loop through every point of the room and make sure it is not already part of another room
            bool overlaps = false;
            
            for (int r = roomTopLeftR-1; r < (roomTopLeftR + height+1); r++) {
                for (int c = roomTopLeftC-1; c < (roomTopLeftC + width+1); c++) {
                    if (m_grid[r][c] == ' ') {
                        overlaps = true;
                        break;
                    }
                }
                
                // if rooms overlap, break and try again
                if (overlaps) {
                    break;
                }
            }
            
            // if rooms do not overlap, draw them in and mark it as done to go to the next iteration of for loop to draw next one
            if (!overlaps) {
                for (int r = roomTopLeftR; r < (roomTopLeftR + height); r++) {
                    for (int c = roomTopLeftC; c < (roomTopLeftC + width); c++) {
                        m_grid[r][c] = ' ';
                    }
                }
                roomDone = true;
                
                // store row/col coordinates of rooms centers in a vector of vectors to draw corridors later
                vector<int>toPush;
                
                toPush.push_back(roomTopLeftR + (height / 2) );
                toPush.push_back(roomTopLeftC + (width / 2) );
                
                centers.push_back(toPush);
            }
        }
    }
}

void Temple::addCorridors() {
    
    // if there is only one room, return since nothing to draw corridors between
    if (centers.size() < 2) {
        return;
    }
    
    // order centers by their column coordinate
    // from least to greatest or left to right -- so we can build corridors from left to right
    for (int i = 0; i < centers.size()-1; i++) {
        for (int j = i + 1; j < centers.size(); j++) {
            if (centers[i][1] > centers[j][1]) {
                swap(centers[i],centers[j]);
            }
        }
    }

    // get center coordinates of two rooms
    for (int i = 0; i < centers.size()-1; i++) {
        int r1 = centers[i][0];
        int c1 = centers[i][1];
        int r2 = centers[i+1][0];
        int c2 = centers[i+1][1];
        
        // if centers are in same row, just draw a horizontal line by inc col until you get to second center
        if (r1 == r2) {
            int startC = c1;
            int endC = c2;
            
            for (int c = startC; c < endC; c++) {
                m_grid[r1][c] = ' ';
            }
            
        // if centers are in same col, just draw a vertical line
        } else if (c1 == c2) {
            int startR = min(r1,r2);                                    // start at whichever row is higher up
            int endR = max(r1,r2);
            
            for (int r = startR; r < endR; r++) {                       // keep inc row till second one is reached
                m_grid[r][c1] = ' ';
            }
            
        // if cols and rows are different, need to draw an L-shaped corridor
        } else {
            
            // keep inc center1 col until it matches center2 col (horizontal part of L)
            while (c1 != c2) {
                m_grid[r1][c1] = ' ';
                c1++;
            }
            
            // if the center1 row is LESSER, inc till center2 row is reached (vertical part of L; going down)
            if (r1 < r2) {
                while (r1 != r2) {
                    m_grid[r1][c2] = ' ';
                    r1++;
                }
            }
            
            // if the center1 row is GREATER, dec till center2 row is reached (vertical part of L; going up)
            else if (r1 > r2) {
                while (r1 != r2) {
                    m_grid[r1][c2] = ' ';
                    r1--;
                }
            }
        }
    }
}

void Temple::addObjects() {
    int m_r;
    int m_c;
    
    if (m_level < 4) {                            // if not at last level, add a staircase
        
        do {                                      // generate random coordinates for object until you find one that is valid (not a wall)
            m_r = randInt(1, m_rows-2);
            m_c = randInt(1, m_cols-2);
        } while (m_grid[m_r][m_c] == '#');
        
        m_objects.push_back(new Object(m_r,m_c,"n/a","stairs",'>'));                                       // staircase
    }
    
    if (m_level == 4) {                            // if at last level, add a golden idol
        
        do {                                       // generate random coordinates for object until you find one that is valid (not a wall)
            m_r = randInt(1, m_rows-2);
            m_c = randInt(1, m_cols-2);
        } while (m_grid[m_r][m_c] == '#');
        
        m_objects.push_back(new Object(m_r,m_c,"the golden idol","golden idol",'&'));                      // golden idol
    }
    

    int numObjs = randInt(2,3);                     // randomly decide number of objects to place
        
    for (int i = 0; i < numObjs; i++) {
        int type = randInt(1,6);                    // randomly decide which type of weapon or scroll to place

        do {                                        // generate random coordinates for object until you find one that is valid (not a wall)
            m_r = randInt(1, m_rows-2);
            m_c = randInt(1, m_cols-2);
        } while (m_grid[m_r][m_c] == '#');
        
        if (m_grid[m_r][m_c] == ' ') {             // depending on the type, add that object to object vector for grid later
            if (type == 1) {
                m_objects.push_back(new Scroll(m_r,m_c,"scroll of enhance armor","scroll",'?'));            // armor scroll
            }
            if (type == 2) {                                                                                // strength scroll
                m_objects.push_back(new Scroll(m_r,m_c,"scroll of strength","scroll",'?'));
            }
            if (type == 3) {                                                                                // health scroll
                m_objects.push_back(new Scroll(m_r,m_c,"scroll of enhance health","scroll",'?'));
            }
            if (type == 4) {                                                                                // dexterity scroll
                m_objects.push_back(new Scroll(m_r,m_c,"scroll of enhance dexterity","scroll",'?'));
            }
            if (type == 5) {                                                                                // mace
                m_objects.push_back(new Weapon(m_r,m_c,"mace","weapon",')',0,2));
            }
            if (type == 6) {                                                                                // short sword
                m_objects.push_back(new Weapon(m_r,m_c,"short sword","weapon",')',0,2));
            }
            if (type == 7) {                                                                                // long sword
                m_objects.push_back(new Weapon(m_r,m_c,"long sword","weapon",')',2,4));
            }
        }
    }
}
void Temple::addActors() {
    int r;
    int c;
    
    // add Player
    bool empty = false;
    while(!empty) {
        r = randInt(1, m_rows-2);
        c = randInt(1, m_cols-2);
        if (m_grid[r][c] == ' ' || m_grid[r][c] == ')' || m_grid[r][c] == '?' || m_grid[r][c] == '>' || m_grid[r][c] == '&' ) {
            m_actors.push_back(new Player(r,c,20));
            m_grid[r][c] = m_actors[0]->getSymbol();
            empty = true;
        }
    }
    
    // add monsters
    
    // B appears on level 2 and on           1234
    // S appears on any level               01234
    // D appears on level 3 and on            234
    // G appears on any level               01234
    
    int L = getLevel();
    int M = randInt(2, 5*(L+1)+1);                                  // number of monsters to place on level
    
    // loop through M times and add appropriate monsters to vector - randomly assign x and y coordinates
    for (int i = 1; i <= M;) {
        int type;
        if (L == 0) {                               // only S and G
            type = randInt(2);
        }
        else if (L == 1) {                          // only B, S, and G
            type = randInt(3);
        }
        else {                                      // B, S, D, and G
            type = randInt(4);
        }
        
        int m_r;
        int m_c;
        bool empty2 = false;                        // to keep generating coordinates until they are valid
        
        while (!empty2) {
            m_r = randInt(1, m_rows-2);
            m_c = randInt(1, m_cols-2);
            
            // if r/c is not a wall or the player fine -- otherwise, regenerate coordinates
            if (m_grid[m_r][m_c] == ' ' || m_grid[m_r][m_c] == '(' || m_grid[m_r][m_c] == '?' || m_grid[m_r][m_c] == '>' || m_grid[m_r][m_c] == '&') {
                if (type == 0) {
                    m_actors.push_back(new Snakewomen(m_r,m_c));
                }
                if (type == 1) {
                    m_actors.push_back(new Goblin(m_r,m_c));
                }
                if (type == 2) {
                    m_actors.push_back(new Bogeyman(m_r,m_c));
                }
                if (type == 3) {
                    m_actors.push_back(new Dragon(m_r,m_c));
                }
                empty2 = true;
                i++;
            }
        }
    }
}
void Temple::display() {
    
    // rewrite last grid, to get rid of old player/monster spots
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            if (getChar(r, c) != '#') {
                m_grid[r][c] = ' ';
            }
        }
    }
    
    // print objects
    for (int i = 0; i < m_objects.size(); i++) {
        int r = m_objects[i]->getR();
        int c = m_objects[i]->getC();
        m_grid[r][c] = m_objects[i]->getSymbol();
    }
    
    // print monsters and player
    for (int i = 0; i < m_actors.size(); i++) {
        int r = m_actors[i]->getR();
        int c = m_actors[i]->getC();
        m_grid[r][c] = m_actors[i]->getSymbol();
    }

    // display walls and corridors
    for (int r = 0; r < m_rows; r++) {
        for (int c = 0; c < m_cols; c++) {
            cout << m_grid[r][c];
        }
        cout << endl;
    }
    cout << "Level: " << getLevel() << ", Hit points: " << getPlayer()->getHit() << ", Armor: " << getPlayer()->getArmor() << ", Strength: " << getPlayer()->getStrength() << ", Dexterity: " << getPlayer()->getDexterity() << endl << endl;
}

int Temple::getLevel() {
    return m_level;
}

char Temple::getChar(int r, int c) const {                          // fn to return grid's current char at r,c coordinates
    if (r >= 0 && r < m_rows && c >= 0 && c < m_cols) {
        return m_grid[r][c];
    }
    return ' ';
}

Player* Temple::getPlayer() const {                                 // fn to access current player on the grid and access mem fn
    for (int i = 0; i < m_actors.size(); i++) {
        Player* ptr = dynamic_cast<Player*>(m_actors[i]);
        if (ptr != nullptr) {
            return ptr;
        }
    }
    return nullptr;
}

Object* Temple::getObject() const {                                 // fn to access object on grid, for use in pickUpObj in actor class
    Player* player = getPlayer();
    int r = player->getR();
    int c = player->getC();
    
    for (int i = 0; i < m_objects.size(); i++) {
        Object* obj = dynamic_cast<Object*>(m_objects[i]);
        if (obj->getR() == r && obj->getC() == c) {
            return obj;
        }
    }
    return nullptr;
}

Monster* Temple::getMonster(int row, int col, int symbol) const {   // fn to access monster on grid, for use in player walk fn to attack monster
    for (int i = 0; i < m_actors.size(); i++) {
        Monster* ptr = dynamic_cast<Monster*>(m_actors[i]);
        if (ptr != nullptr && ptr->getR() == row && ptr->getC() == col && ptr->getSymbol() == symbol) {
            return ptr;
        }
    }
    return nullptr;
}

void Temple::moveMonsters(int goblinSmell) {                       // move all monsters--B+S: monster move fn; D: dragon move fn; G: goblin move fn
    for (int i = 1; i < m_actors.size(); i++) {
        if (m_actors[i]->getSymbol() == 'B') {
            Monster* currentMonster = dynamic_cast<Monster*>(m_actors[i]);      // pass in bogeyman smell parameter of 5
            currentMonster->move(getPlayer(), this, 5);
        }
        if (m_actors[i]->getSymbol() == 'D') {
            Monster* currentMonster = dynamic_cast<Monster*>(m_actors[i]);
            currentMonster->move(getPlayer(), this, 0);                         // no smell ability so pass in 0
        }
        if (m_actors[i]->getSymbol() == 'G') {
            Goblin* currentMonster = dynamic_cast<Goblin*>(m_actors[i]);
            currentMonster->move(getPlayer(), this, goblinSmell);               // goblinSmell passed into moveMonsters from game constructor call
        }
        if (m_actors[i]->getSymbol() == 'S') {
            Monster* currentMonster = dynamic_cast<Monster*>(m_actors[i]);     // pass in snakewomen smell parameter of 5
            currentMonster->move(getPlayer(), this, 3);
        }
    }
}

void Temple::killActors() {                                         // after each turn, check if any characters have died and drop appropriate weapon
    vector<Actor*>::iterator it;
    it = next(m_actors.begin());
    
    while (it != m_actors.end()) {
        int updateR = (*it)->getR();
        int updateC = (*it)->getC();
        
        if ((*it)->isDead()) {
            bool objectThere = false;
            for (int i = 0; i < m_objects.size(); i++) {
                int objR = m_objects[i]->getR();
                int objC = m_objects[i]->getC();
                // if there is an object at the spot, just make the grid equal to that and do not drop anything
                if (objR == updateR && objC == updateC) {
                    objectThere = true;
                    break;
                }
            }
            if (!objectThere) {
                if ((*it)->getSymbol() == 'B') {                    // Bogeyman might drop magic axe
                    bool drop = trueWithProbability(0.1);
                    if (drop) {
                        m_objects.push_back(new Weapon(updateR,updateC,"magic axe","weapon",')',5,5));
                    }
                }
                else if ((*it)->getSymbol() == 'D') {               // Dragon might drop scroll
                    m_objects.push_back(new Scroll(updateR,updateC,"scroll of teleporation","scroll",'?'));
                }
                else if ((*it)->getSymbol() == 'G') {               // Goblin might drop magic axe or fangs
                    bool drop = trueWithProbability(0.33);
                    if (drop) {
                        int type = randInt(1, 2);
                        if (type == 1) {
                            m_objects.push_back(new Weapon(updateR,updateC,"magic axe","weapon",')',5,5));
                        }
                        if (type == 2) {
                            m_objects.push_back(new Weapon(updateR,updateC,"magic fangs of sleep","weapon",')',3,2));
                        }
                    }
                }
                else if ((*it)->getSymbol() == 'S') {               // Snakewomen might drop fangs
                    bool drop = trueWithProbability(0.33);
                    if (drop) {
                        m_objects.push_back(new Weapon(updateR,updateC,"magic fangs of sleep","weapon",')',3,2));
                    }
                }
            }
            
            m_grid[updateR][updateC] = ' ';
            delete *it;
            it = m_actors.erase(it);
        }
        else {
            it++;
        }
    }
}

void Temple::deleteObject(Object* obj) {                            // to "erase" objects from the grid after player picks it up
    
    // get the object you want to deletes row and col
    int objR = obj->getR();
    int objC = obj->getC();
    
    // look through vector, once you find object w same row and col -- erase it
    vector<Object*>::iterator it;
    it = m_objects.begin();
    
    while (it != m_objects.end()) {
        int otherObjR = (*it)->getR();
        int otherObjC = (*it)->getC();
        
        if (otherObjR == objR && otherObjC == objC) {
            it = m_objects.erase(it);
            return;
        }
        else {
            it++;
        }
    }
}

void Temple::displayAttacks() {                                     // loop through attack strings and display each on a new line
    for (int i = 0; i < m_attacks.size(); i++) {
        cout << m_attacks[i] << endl;
    }
}
void Temple::clearAttacks() {                                       // to clear vector after the attack results have been displayed for each turn
    m_attacks.clear();
}

void Temple::setGrid(int r, int c, char symbol) {
    m_grid[r][c] = symbol;
}

bool Temple::staircaseAt(Player* player) {                          // fn to get staircase coords, to ensure player CAN go to next level at their spot
    int pR = player->getR();
    int pC = player->getC();
    
    for (int i = 0; i < m_objects.size(); i++) {
        if (m_objects[i]->getSymbol() == '>' && m_objects[i]->getR() == pR && m_objects[i]->getC() == pC) {
            return true;
        }
    }
    return false;
}

Temple* Temple::newLevel(Player* player) {
    // get current player's stats
    int hit = player->getHit();
    int armor = player->getArmor();
    int strength = player->getStrength();
    int dexterity = player->getDexterity();
    int sleep = player->getSleep();
    int level = (player->getLevel()) + 1;
    int max = player->getMaxHit();
    
    // get current player's weapon's stats
    string w_name = player->getWeapon()->getName();
    int w_bonus = player->getWeapon()->getBonus();
    int w_damage = player->getWeapon()->getDamage();
    Weapon* weapon = new Weapon(0,0,w_name,"weapon",')',w_bonus,w_damage);
    
    // create a new temple
    Temple* newTemple = new Temple(getLevel()+1);
    newTemple->addRooms();
    newTemple->addCorridors();
    newTemple->addObjects();
    newTemple->addActors();
    
    Player* newPlayer = newTemple->getPlayer();
    
    delete newPlayer->getWeapon();
    
    // transfer stats
    newPlayer->setHit(hit);
    newPlayer->setWeapon(weapon);
    newPlayer->setArmor(armor);
    newPlayer->setStrength(strength);
    newPlayer->setDexterity(dexterity);
    newPlayer->setSleep(sleep);
    newPlayer->setLevel(level);
    newPlayer->setMaxHit(max);
    
    // transfer inventory
    player->transferInventory(newPlayer);
    
    return newTemple;
}



Temple::~Temple()
{
    for (int i = 0; i < m_actors.size(); i++) {             // delete all actors dynamically allocated in vector (addActors)
            delete m_actors[i];
    }
    for (int i = 0; i < m_objects.size(); i++) {            // delete all objects dynamically allocated in vector (addObjects)
            delete m_objects[i];
    }
}
