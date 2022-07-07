#include "..\headers\Character.h"
#include "..\headers\Race.h"
#include "..\headers\Stats.h"
#include "..\headers\Class.h"
#include "..\headers\dnd_template_functions.h"
#include "..\headers\utilsDnD.h"
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

int main(){
    Stats stats_list;
    Race race;
    Class selected_class;
    stats_list.generate_stats();
    race.determine_race();
    race.determine_gender();
    race.determine_height_weight();
    selected_class.create_character();
    std::map<int,int> stats_map = smart_stat_distribution(selected_class.get_bad_stats(),stats_list.get_bad_stats(),selected_class.get_good_stats(),stats_list.get_good_stats());
    stats_list.set_base_strength(stats_map.at(1));
    stats_list.set_base_dexterity(stats_map.at(2));
    stats_list.set_base_constitution(stats_map.at(3));
    stats_list.set_base_intelligence(stats_map.at(4));
    stats_list.set_base_wisdom(stats_map.at(5));
    stats_list.set_base_charisma(stats_map.at(6));
    stats_list.generate_stats_vector();
    race.generate_stats_modifier();
    stats_list.modify_stats_race(race.get_stats_modifier());
    race.determine_age(selected_class.get_complexity());
    selected_class.print_class_information();
    race.print_race_info();
    stats_list.printStats();

    /*
    Step 0: Roll stats
    Step 1a: Determine Race
    Step 1b: Set Base Age
    Step 1c: Set height and weight
    Step 3: Determine Class
    Step 2: Modify Stats (Race)
    Step 4: Set Total Age
    Step 5: Modify Stats (Age)
    */

    Character character(race,stats_list);

}