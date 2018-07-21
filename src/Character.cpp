#include "..\headers\Character.h"
#include "..\headers\Race.h"
#include "..\headers\Stats.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

Character::Character(Race race, Stats stats)
{
    this->race = race;
    this->stats = stats;
}


void Character::set_effective_level(int level)
{
    this->effective_level = level;
}
void Character::set_total_hitpoints(int hp)
{
    this->total_hitpoints = hp;
}

int Character::get_effective_level() const
{
    return effective_level;
}
int Character::get_total_hitpoints() const
{
    return total_hitpoints;
}

Race Character::get_race() const{
    return race;
}

Stats Character::get_stats() const{
    return stats;
}

void Character::print_character_info()
{
}