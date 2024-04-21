#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Hero.h"
#include "Pistol.h"
#include "Bazooka.h"
#include "Rifle.h"
#include "MedicHero.h"
#include "DemolitionHero.h"
#include "Ammo.h"
#include "Potion.h"
#include "TankMonster.h"
#include "GhostMonster.h"

class Game {
private:
    static const int rows = 15;
    static const int cols = 15;
    Object* grid[rows][cols];
    Hero* hero;
    int round;
    bool valid;


public:
    Game();

    ~Game();

    void playRound();

    void generateMap();

    void showMap();

    void startGame();

    void updateMap();

    int checkGameOver();

    void useGunSpecial();

    void move(Hero& h1, char direction);
    void  FireGun(char direction);
};

#endif
