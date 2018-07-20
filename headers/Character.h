#ifndef CHARACTER_H
#define CHARACTER_H
#include "Race.h"
#include "Stats.h"
#include <string>
#include <cstring>

class Character{
private:
    Race race;
    Stats stats;
    int gender;
    int effective_level;
    int total_hitpoints;
public:
    Character(Race race, Stats stats);

    void set_gender(int gender);
    void set_effective_level(int level);
    void set_total_hitpoints(int hp);

    int get_gender() const;
    int get_effective_level() const;
    int get_total_hitpoints() const;
    Race get_race() const;
    Stats get_stats() const;
    void print_character_info();
};

#endif