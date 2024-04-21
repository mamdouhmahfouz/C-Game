

#ifndef GAMEFINAL_OBJECT_H
#define GAMEFINAL_OBJECT_H
#include <iostream>
using namespace std;
class Object {
protected:
    char type;
public:
    Object(char t);

    char getType() const;
    friend ostream& operator<<(ostream& os, const Object& o);
};
#endif
