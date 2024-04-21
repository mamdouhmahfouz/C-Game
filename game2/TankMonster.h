#ifndef TANKMONSTER_H
#define TANKMONSTER_H

#include "Monster.h"

class TankMonster : public Monster {
private:
    int shield;

public:
    TankMonster(char t, int x, int y, int hp, int s);

    int getShield() const;
};

#endif
