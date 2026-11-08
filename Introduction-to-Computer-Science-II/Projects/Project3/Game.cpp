// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
#include "Temple.h"
#include "Actor.h"
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance) : gobSmell(goblinSmellDistance)
{}

void Game::play()
{
    m_temple = new Temple(0);   // starting game
    m_temple->addRooms();
    m_temple->addCorridors();
    m_temple->addObjects();
    m_temple->addActors();
    m_temple->display();
    char move;
    bool lastInputI = false;    // to make sure that if i is clicked twice consecutively, show inventory on first, go back on second
    
    while ((move = getCharacter()) && move != 'q') {
        Player* player = m_temple->getPlayer();
        bool gainPoint = trueWithProbability(0.1);              // 10% chance player will gain a hit point before next turn
        if (gainPoint) {
            int currentHit = player->getHit();
            player->setHit(currentHit+1);
        }
        switch (move) {
            case ARROW_UP:
            case ARROW_DOWN:
            case ARROW_LEFT:
            case ARROW_RIGHT: {
                player->walk(move, m_temple);                   // player goes -> kill any monsters -> monsters go -> check if player dead
                m_temple->killActors();
                m_temple->moveMonsters(gobSmell);
                clearScreen();
                if (player->isDead()) {
                    player->setSymbol(' ');
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                    cout << endl << "Press q to exit game.";
                } else {
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                }
                lastInputI = false;
                break;
            }
            case 'w':
                clearScreen();                                  // wield weapon -> monsters go -> check if player dead
                player->showInventory();
                player->wieldWeapon(getCharacter(), m_temple);
                m_temple->moveMonsters(gobSmell);
                clearScreen();
                if (player->isDead()) {
                    player->setSymbol(' ');
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                    cout << endl << "Press q to exit game.";
                } else {
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                }
                lastInputI = false;
                break;
            case 'r':
                clearScreen();                                  // read scroll -> monsters go -> check if player dead
                player->showInventory();
                player->readScroll(getCharacter(), m_temple);
                m_temple->moveMonsters(gobSmell);
                clearScreen();
                if (player->isDead()) {
                    player->setSymbol(' ');
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                    cout << endl << "Press q to exit game.";
                } else {
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                }
                lastInputI = false;
                break;
            case 'i':
                if (lastInputI) {                               // if I is clicked for second time -> monsters go -> check if player dead
                    m_temple->moveMonsters(gobSmell);
                    clearScreen();
                    if (player->isDead()) {
                        player->setSymbol(' ');
                        m_temple->display();
                        m_temple->displayAttacks();
                        m_temple->clearAttacks();
                        cout << endl << "Press q to exit game.";
                    } else {
                        m_temple->display();
                        m_temple->displayAttacks();
                        m_temple->clearAttacks();
                    }
                    lastInputI = false;
                } else {                                        // if I is clicked for first time, just show inventory
                    clearScreen();
                    player->showInventory();
                    lastInputI = true;
                }
                break;
            case '>': {
                // if the level is 0-3 and on a staircase
                if (m_temple->getLevel() < 4 && m_temple->staircaseAt(player)) {
                    Temple* newTemple = m_temple->newLevel(player);             // initialize a new level
                    delete m_temple;                                            // delete the old Temple
                    m_temple = newTemple;                                       // assign the new temple to m_temple
                    clearScreen();
                    m_temple->display();
                }
                else {                                         // if not on stairs, monsters go -> check if player dead
                    m_temple->moveMonsters(gobSmell);
                    clearScreen();
                    if (player->isDead()) {
                        player->setSymbol(' ');
                        m_temple->display();
                        m_temple->displayAttacks();
                        m_temple->clearAttacks();
                        cout << endl << "Press q to exit game.";
                    } else {
                        m_temple->display();
                        m_temple->displayAttacks();
                        m_temple->clearAttacks();
                    }
                }
                lastInputI = false;
                break;
            }
            case 'c': {                                         // to cheat, change max hit and strength
                player->setMaxHit(50);
                player->setStrength(9);
                m_temple->moveMonsters(gobSmell);               // monsters go -> check if player dead
                clearScreen();
                if (player->isDead()) {
                    player->setSymbol(' ');
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                    cout << endl << "Press q to exit game.";
                } else {
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                }
                lastInputI = false;
                break;
            }
            case 'g': {
                Object* obj = m_temple->getObject();
                bool result = player->pickUpObj(obj, m_temple); // try to pick up the object
                if (result) {
                    m_temple->deleteObject(obj);                // if the player can pick up object, delete it from grid
                }
                m_temple->moveMonsters(gobSmell);               // monsters go -> check if player dead
                clearScreen();
                if (player->isDead()) {
                    player->setSymbol(' ');
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                    cout << endl << "Press q to exit game.";
                } else {
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                }
                lastInputI = false;
                break;
            }
            default: {
                m_temple->moveMonsters(gobSmell);             // even if the player does not make a valid move, monsters go
                clearScreen();
                if (player->isDead()) {
                    player->setSymbol(' ');
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                    cout << endl << "Press q to exit game.";
                } else {
                    m_temple->display();
                    m_temple->displayAttacks();
                    m_temple->clearAttacks();
                }
                lastInputI = false;
                break;
            }
        }
    }
}

Game::~Game() {
    delete m_temple;
}

// You will presumably add to this project other .h/.cpp files for the various
// classes of objects you need to play the game:  player, monsters, weapons, 
// etc.  You might have a separate .h/.cpp pair for each class (e.g., Player.h,
// Bogeyman.h, etc.), or you might put the class declarations for all actors in
// Actor.h, all game objects in GameObject.h, etc.
