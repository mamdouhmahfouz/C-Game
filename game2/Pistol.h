#ifndef PISTOL_H
#define PISTOL_H

#include "Gun.h"
#include "Hero.h"


class Pistol : public Gun {
public:
    Pistol();

    void useSpecial(Hero& h1 , Object* map[15][15]);
};

#endif

