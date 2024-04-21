//
// Created by mamdo on 18-Dec-23.
//

#ifndef GAMEFINAL_GUN_H
#define GAMEFINAL_GUN_H
using namespace std;
#include <string>
#include "Hero.h"

class Gun {
private:
    string name;
    int bullets;
    int damage;
    int range;

public:
    Gun( string n, int b, int d, int r);

    string getName();

    virtual void useSpecial(Hero& h1 , Object* map[15][15]);

    int getBullets();

    int getDamage();

    int getRange();

    void setBullets(int bullets);

    friend ostream& operator<<(ostream& os, const Gun& g);

};

#endif
