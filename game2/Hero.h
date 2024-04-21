#ifndef HERO_H
#define HERO_H


#include "Character.h"
#include "Monster.h"
#include "Potion.h"

#include <iostream>
using namespace std;

class Gun;
class Hero : public Character {
public:
    Gun *weapon;
public:
    Hero(char t, int x, int y, int hp);

    Gun* getWeapon();

    void setWeapon(Gun* g);

    string operator<<(Hero& h);

    ~Hero();

    Hero& operator- (Monster& m);
    Hero& operator+ (Potion& p);
    friend ostream& operator<<(ostream& os, Hero& hero);
};

#endif
