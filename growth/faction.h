#ifndef FACTION_H
#define FACTION_H

class Faction {
    public:
    Faction(int fac_id);
    ~Faction();

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
};

#endif
