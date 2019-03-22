#include "faction.h"

Faction::Faction(int faction_id) {
    id = faction_id;

    //they're all between 0 and 100
    //total cannot sum to more than 300
    unsigned int total = 300;
    unsigned int nums[5];
    unsigned int sum = 0;
    for (int i = 0; i < 5; i++) {
        nums[i] = rand()%100;
        sum += nums[i];
    }
    float scale = (float)total/sum;
    speed = nums[i] * scale;
    strength = nums[i] * scale;
    accuracy = nums[i] * scale;
    armor = nums[i] * scale;
    health = nums[i] * scale;
}
