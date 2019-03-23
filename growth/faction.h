#ifndef FACTION_H
#define FACTION_H

#include <stdlib.h>
#include <vector>
#include <algorithm>
class Faction {
    public:
    void init(int fac_id);

    unsigned char id;
    //determines who goes first
    unsigned int speed;
    //determines damage done
    unsigned int strength;
    //on an attack, accuracy contests armor
    unsigned int accuracy;
    unsigned int armor;
    //max health
    unsigned int health;

    //functions to get values
    unsigned int getSpeed();
    unsigned int getStrength();
    unsigned int getAccuracy();
    unsigned int getArmor();
    unsigned int getHealth();
};

#endif
