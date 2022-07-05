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

void Character::set_gender(int gender)
{
    this->gender = gender;
}

void Character::set_effective_level(int level)
{
    this->effective_level = level;
}
void Character::set_total_hitpoints(int hp)
{
    this->total_hitpoints = hp;
}

int Character::get_gender() const
{
    return gender;
}
int Character::get_effective_level() const
{
    return effective_level;
}
int Character::get_total_hitpoints() const
{
    return total_hitpoints;
}

Race Character::get_race() const
{
    return race;
}

Stats Character::get_stats() const
{
    return stats;
}

void Character::print_character_info()
{
    cout << "Race: " << race.get_race_name() << endl;
    if (gender == 0)
    {
        cout << "Gender: Male" << endl;
    }
    else
    {
        cout << "Gender: Female " << endl;
    }
    cout << "Height: " << race.get_height() << " Inches" << endl;
    cout << "Weight: " << race.get_weight() << " lbs" << endl;
    cout << "Age: " << race.get_age() << " Years Old" << endl;
    cout << "Alignment: " << alignment << endl;
    cout << "Deity: " << deity << endl;
    cout << "Total Hitpoints: " << total_hitpoints << " HP" << endl;
}