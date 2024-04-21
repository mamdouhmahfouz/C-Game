#ifndef GHOSTMONSTER_H
#define GHOSTMONSTER_H

#include "Monster.h"

class GhostMonster : public Monster {
private:
    bool isVisible;

public:
    GhostMonster(char t, int x, int y, int hp);
    void setIsVisible(bool t);
    bool isVisibleOnMap() const;
};

#endif
