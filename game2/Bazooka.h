#ifndef BAZOOKA_H
#define BAZOOKA_H

#include "Gun.h"
#include "Hero.h"

class Bazooka : public Gun {
public:
    Bazooka();

    void useSpecial(Hero& h1 , Object* map[15][15]);
};

#endif
