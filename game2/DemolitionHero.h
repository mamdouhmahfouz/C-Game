#ifndef DEMOLITIONHERO_H
#define DEMOLITIONHERO_H

#include "Hero.h"
#include "Gun.h"
#include "Ammo.h"

class DemolitionHero : public Hero {
private:
    Gun* weapon2;

public:
    DemolitionHero(char t, int x, int y, int hp);

    DemolitionHero& operator+ (Ammo& a);

    void useSpecial();

    void setWeapon2(Gun* g);

    Gun* getWeapon2();

};

#endif
