#ifndef MEDICHERO_H
#define MEDICHERO_H

#include "Hero.h"
#include "Ammo.h"

class MedicHero : public Hero {
private:
    int healingAmount;

public:
    MedicHero(char t, int x, int y, int hp, int ha);

    void useSpecial();

    MedicHero& operator+(Ammo& a);

    int getHealingAmount();
};

#endif

