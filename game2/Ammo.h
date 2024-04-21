#ifndef AMMO_H
#define AMMO_H

#include "Item.h"

class Ammo : public Item {
private:
    int bullets;

public:
    Ammo(int b);

    int getBullets() const;
};

#endif
