#ifndef CHARACTER_H
#define CHARACTER_H



class Character : public Object {
protected:
    int positionX;
    int positionY;
    int healthPoints;

public:
    Character(char t, int x, int y, int hp);

    int getPositionX();

    int getPositionY();

    int getHealthPoints();

    void setPosition(int x, int y);

    void setHealthPoints(int hp);
};

#endif
