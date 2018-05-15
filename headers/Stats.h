#ifndef STATS_H
#define STATS_H
#include "roll.h"
#include <math.h>
#include <vector>
#include <map>
#include <iostream>
#include<algorithm>
#include<functional>
#include "dnd_template_functions.h"

class Stats{

private:
    int base_strength;
    int strength_modifier;
    int base_dexterity;
    int dexterity_modifier;
    int base_constitution;
    int constitution_modifier;
    int base_intelligence;
    int intelligence_modifier;
    int base_wisdom;
    int wisdom_modifier;
    int base_charisma;
    int charisma_modifier;
    std::vector<int> good_stats;
    std::vector<int> bad_stats;
    std::map<int, int> stats_map;
    std::vector<int> stats_vector;

public:
    Stats();
    //Getters
    int get_base_strength() const;
    int get_modifier_strength() const;
    int get_base_dexterity() const;
    int get_modifier_dexterity() const;
    int get_base_constitution() const;
    int get_modifier_constitution() const;
    int get_base_intelligence() const;
    int get_modifier_intelligence() const;
    int get_base_wisdom() const;
    int get_modifier_wisdom() const;
    int get_base_charisma() const;
    int get_modifier_charisma() const;
    std::vector<int> get_bad_stats() const;
    std::vector<int> get_good_stats() const;
    //Setters
    void set_base_strength(int x);
    void set_modifier_strength(int x);
    void set_base_dexterity(int x);
    void set_modifier_dexterity(int x);
    void set_base_constitution(int x);
    void set_modifier_constitution(int x);
    void set_base_intelligence(int x);
    void set_modifier_intelligence(int x);
    void set_base_wisdom(int x);
    void set_modifier_wisdom(int x);
    void set_base_charisma(int x);
    void set_modifier_charisma(int x);
    void set_bad_stats(std::vector<int> bs);
    void set_good_stats(std::vector<int> gs);
    //Misc
    int determine_stat_bonus(int stat);
    void generate_stats();
    void generate_stats_vector();
    //std::vector<int> generate_stats_modifier_vector();
    void modify_stats_race(std::vector<int> one_hot_stats_modifier);
    void printStats();
};

#endif