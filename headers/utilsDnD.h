#pragma once
/*Section for "Choosing" aspect of character*/
/*Structures used to define a given character*/

void calculateBAB(Class selectedClass, Character character);

std::map<int,int> smart_stat_distribution(std::vector<int> bad_class_stats, std::vector<int> bad_available_stats, std::vector<int> good_class_stats, std::vector<int> good_available_stats);

void chooseClass(Class selectedClass, Character character);

void chooseLevel(Character character);

/*Section for Calculating other features of character*/

void determineStats(Stats statsList, Class selectedClass, int *rolledStats);

void calcAgeWeightHeight(Stats statlist, Class selectedClass, Character character);

int determineBonus(int stat);

void determineAlignment(Class selectedClass, Character character);

void calcHitPoints(Class selectedClass, Character character, Stats statlist);

//int updateSkills(std::vector<Skill> skill_list, int skp, int rank_cap);

int get_ability_stat(std::string stat, Stats stat_list);

//std::vector<Skill> generateSkills(Class selectedClass, Character character, Stats statsList);

//void printSkillList(std::vector<Skill> skills_list);

void printCharInfo(Character character);

void printStats(Stats statList);
