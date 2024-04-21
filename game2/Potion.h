#ifndef POTION_H
#define POTION_H

#include "Item.h"

class Potion : public Item {
private:
    int healingAmount;

public:
    Potion(int ha);

    int getHealingAmount() const;
};

#endif
