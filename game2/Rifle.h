#ifndef RIFLE_H
#define RIFLE_H

#include "Gun.h"
#include "Hero.h"

class Rifle : public Gun {
public:
    Rifle();

    void useSpecial(Hero& h1 , Object* map[15][15]);
};

#endif
