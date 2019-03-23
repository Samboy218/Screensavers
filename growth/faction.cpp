#include "faction.h"

void Faction::init(int faction_id) {
    id = faction_id;

    //total cannot sum to more than 300
    //not uniform random, but whatevs
    unsigned int total = 300;
    std::vector<int> rands;
    for (int i = 0; i < 4; i++) {
        rands.push_back(rand()%300);
    }
    rands.push_back(0);
    rands.push_back(300);
    std::sort(rands.begin(), rands.end());
    int vals[5];
    for (int i = 1; i < rands.size(); i++) {
        vals[i-1] = rands.at(i)-rands.at(i-1);
    }
    speed = vals[0];
    strength = vals[1];
    accuracy = vals[2];
    armor = vals[3];
    health = vals[4];
}

//get a random numer +- 10% of the value
unsigned int Faction::getSpeed() {
    int upper = speed * 1.1;
    upper++;
    int lower = speed * .9;
    return (rand()%upper) + lower;
}

unsigned int Faction::getStrength() {
    int upper = strength * 1.1;
    upper++;
    int lower = strength * .9;
    return (rand()%upper) + lower;
}

unsigned int Faction::getAccuracy() {
    int upper = accuracy * 1.1;
    upper++;
    int lower = accuracy * .9;
    return (rand()%upper) + lower;
}

unsigned int Faction::getArmor() {
    int upper = armor * 1.1;
    upper++;
    int lower = armor * .9;
    return (rand()%upper) + lower + 1;
}

unsigned int Faction::getHealth() {
    int upper = health * 1.1;
    upper++;
    int lower = health * .9;
    return (rand()%upper) + lower;
}

