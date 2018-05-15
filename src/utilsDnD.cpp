#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <cstring>
#include <string>
#include <random>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "roll.h"
#include "utilsDnD.h"
#include "Stats.h"
#include "Class.h"
#include "Character.h"
#include "Race.h"
using namespace std;

template<typename T> void printElement(T t, const int& num_width, const char& separator)
{
    cout << left << setw(num_width) << setfill(separator) << t;
}

/*
The purpose of determineRace is to randomly select the race of the generated character-to-be.
Since we would want each race to be equally likely as the next, a uniform distribution is utilized.
Upon selecting a race, which is stored as a string (or an array of characters), it finds the attributes it needs to modify.
These attributes include bonuses and penalties to the 6 stats and the base age, or age of adulthood for that particular race.
This function is called in CharGen.cpp
*/

std::map<int,int> smart_stat_distribution(std::vector<int> bad_class_stats, std::vector<int> bad_available_stats, std::vector<int> good_class_stats, std::vector<int> good_available_stats){
	std::map<int,int> stats_map;
	int counter = bad_available_stats.size();
	for (int i = 0; i < counter; i++)
	{
		int ins;
		int roll;
		//std::cout << "badStat contains:";
		//for (unsigned i = 0; i < badStats.size(); ++i)
		//	std::cout << ' ' << badStats[i];
		//cout << endl;
		//bad_stats[i] refers to each index that I labeled as a "bad stat" in the Class object.
		if (bad_available_stats.size() != 1)
		{
			roll = rolldX(bad_available_stats.size());
			ins = bad_available_stats.at(roll - 1);
		}
		else
		{
			ins = bad_available_stats.at(0);
		}
		stats_map.insert(std::pair<int, int>(bad_class_stats.at(i), ins));
		if (bad_available_stats.size() != 1)
		{
			bad_available_stats.erase(bad_available_stats.begin() + (roll - 1));
		}
		else
		{
			bad_available_stats.erase(bad_available_stats.begin());
		}
		//printf("Good Stat of %d is %d\n", i, statsRolled[rolled]);
	}
	counter = good_available_stats.size();
	for (int i = 0; i < counter; i++)
	{
		int ins;
		int roll;
		//std::cout << "badStat contains:";
		//for (unsigned i = 0; i < badStats.size(); ++i)
		//	std::cout << ' ' << badStats[i];
		//cout << endl;
		//bad_stats[i] refers to each index that I labeled as a "bad stat" in the Class object.
		if (good_available_stats.size() != 1)
		{
			roll = rolldX(good_available_stats.size());
			ins = good_available_stats.at(roll - 1);
		}
		else
		{
			ins = good_available_stats.at(0);
		}
		stats_map.insert(std::pair<int, int>(good_class_stats.at(i), ins));
		if (good_available_stats.size() != 1)
		{
			good_available_stats.erase(good_available_stats.begin() + (roll - 1));
		}
		else
		{
			good_available_stats.erase(good_available_stats.begin());
		}
		//printf("Good Stat of %d is %d\n", i, statsRolled[rolled]);
	}

	return stats_map;
}

/*
Due to extra restrictions that are placed upon the Cleric class, this function is only called when the class selected is "Cleric".
It is meant to adjust for alignment restrictions and therefore is called before determineAlignment.
*/


/*
TODO: Create function that takes in all character information. Have it determine the number of Ability Point Raises (APR), then distribute said raises in a 
	  random but "smart" fashion based on roughly 4 different options (1. Raise a "Good Stat" if the stat is odd (meaning bonus will increase) OR if you have more than one APR left 2. Raise a "bad stat" for the same reasons minus the OR 3. Raise CON if HD is greater than 6 (d8, d12) 4. Raise a random stat)
	  These options will have percent chance such that options 1 and 4 are more likely than 2 or 3 (might just delete 3 honestly).
	  Then if any rolls affect the CON bonus, a flag must be marked along with which level the CON bonus was changed (4, 8, 12 ...). When determining the HP gains, this flag must also be factored in, as
	  HP gains due to CON bonuses are not retroactive.
*/

/*Section for Calculating other features of Character&*/

/*
The function determineStats attempts to take in the 6 randomly rolled numbers [3,18] and allocate them in a "smart" fashion.
For the sake of complexity, each class is assumed to have 3 preferred stats, as well as 3 dump stats. 
What this means is that the 3 highest values rolled will be allocated to a class's preferred stats (albeit at random), while remaining stats are allocated (again, at random) to the dump stats.
This function is called by CharGen.cpp
*/

// void determineStats(struct Stats& statsList, struct Class& selectedClass, int* statsRolled) {
// 	vector<int> prefStats;
// 	std::vector<int> badStats;
// 	std::map<int, int> statsMap;
// 	for (int x = 0; x < 6; x++) {
// 		if (x < 3) {
// 			int ins = statsRolled[x];
// 			badStats.push_back(ins);
// 		}
// 		else {
// 			prefStats.push_back(statsRolled[x]);
// 		}
// 	}
// 	//Handle allocation of bad stats
// 	for (int i = 0; i < 3; i++) {
// 		int ins;
// 		int* roll;
// 			//std::cout << "badStat contains:";
// 			//for (unsigned i = 0; i < badStats.size(); ++i)
// 			//	std::cout << ' ' << badStats[i];
// 			//cout << endl;

// 			if (badStats.size() != 1) {
// 				roll = rollXdX(1, badStats.size());
// 				ins = badStats.at(roll[0]-1);
// 			}
// 			else {
// 				ins = badStats.at(0);
// 			}
// 			statsMap.insert(std::pair<int,int>(selectedClass.badStats[i],ins));
// 			if (badStats.size() != 1) {
// 				badStats.erase(badStats.begin() + (roll[0]-1));
// 			}
// 			else {
// 				badStats.erase(badStats.begin());
// 			}
// 		//printf("Good Stat of %d is %d\n", i, statsRolled[rolled]);
// 	}
// 	//Handle allocation of good stats
// 	for (int i = 0; i < 3; i++) {
// 		int ins;
// 		int* roll;
// 		//std::cout << "Prefstat contains:";
// 		//for (unsigned i = 0; i < prefStats.size(); ++i) {
// 		//	std::cout << ' ' << prefStats[i];
// 		//}
// 		//cout << endl;

// 		if (prefStats.size() != 1) {
// 			roll = rollXdX(1, prefStats.size());
// 			ins = prefStats.at(roll[0]-1);
// 		}
// 		else {
// 			ins = prefStats.at(0);
// 		}
// 		statsMap.insert(std::pair<int,int>(selectedClass.goodStats[i],ins));
// 		if (prefStats.size() != 1) {
// 			prefStats.erase(prefStats.begin() + (roll[0]-1));
// 		}
// 		else {
// 			prefStats.erase(prefStats.begin());
// 		}
// 	}
	
// 	statsList.str = statsMap.at(1);
// 	statsList.dex = statsMap.at(2);
// 	statsList.con = statsMap.at(3);
// 	statsList.intl = statsMap.at(4);
// 	statsList.wis = statsMap.at(5);
// 	statsList.cha = statsMap.at(6);

// }

/*
The function calcAgeWeightHeight uses a combination of character information and the user-specified class to modify their characters height, weight and age.
While the first is purely cosmetic and weight having only niche application, age does affect the stats of the character-to-be.
Thus once the age is calculated it must also be checked against a threshold to determine the severity of stat changes due to aging.
This function is called in CharGen.cpp
*/

/*
This function is called to determine the bonus attributed to a given stat value.
This function is called by printCharInfo and calcHitPoints located in utilsDnD.cpp
*/

// int get_ability_stat(std::string stat, Stats stat_list)
// {
// 	if (!strcmp(stat.c_str(), "strength"))
// 	{
// 		return stat_list.str;
// 	}
// 	if (!strcmp(stat.c_str(), "dexterity"))
// 	{
// 		return stat_list.dex;
// 	}
// 	if (!strcmp(stat.c_str(), "constitution"))
// 	{
// 		return stat_list.con;
// 	}
// 	if (!strcmp(stat.c_str(), "intelligence"))
// 	{
// 		return stat_list.intl;
// 	}
// 	if (!strcmp(stat.c_str(), "wisdom"))
// 	{
// 		return stat_list.wis;
// 	}
// 	if (!strcmp(stat.c_str(), "charisma"))
// 	{
// 		return stat_list.cha;
// 	}
// }
/*
The function determineNumAbilityPoints is called when determining how many ability points should be granted to a player
based on their level. Every 4 levels grants the player one extra ability point which will be allocated into the six main stats
*/

int determineNumAbilityPoints(int level) {
	int number = floor(level / 4);
	return number;
}
int determineNumSkillPoints(int level, int base_gain, int int_modifier){
	return ((base_gain+int_modifier)*4)+((base_gain+int_modifier)*(level-1));
}
/*
calcHitPoints is utilized in determining the HP of the character-to-be. Using the ECL (Effective Character Level) and HD (Hit Die) of the class,
the raw HP value per level is randomly rolled, and the appropriate CON Bonus is applied at each level.
*/
//TODO: Refactor CON bonus applicaiton to health
// void calcHitPoints(struct Class& selectedClass, struct Character& character, struct Stats& statlist) {
// 	int numRoll = character.effectiveLevel;
// 	int conScore = statlist.con;
// 	int numFace = selectedClass.classHitDie;
// 	int r;
// 	r = rollXdX(numRoll, numFace);
// 		character.totalHP += r;
// 	character.totalHP += ((determineBonus(conScore))*numRoll);
// }

// int getSkillCap(Character& character){
// 	/*
// 	If it's a class skill it's character level + 3
// 	if not it's 1/2 (no rounding) of character level + 3.
// 	*/
// 	int lvl = character.effectiveLevel;
// 	return lvl+3;
// }

// int updateSkills(vector<Skill> &skill_list, int skp, int rank_cap){
// 	for (auto x : skill_list)
// 	{
// 		if (skp > 0)
// 		{
// 			if (x.base_rank < rank_cap)
// 			{
// 				int additional_ranks = std::min((rolldX((rank_cap - x.base_rank) + 1) - 1), skp);
// 				skp -= additional_ranks;
// 				x.base_rank += additional_ranks;
// 				int modified_total_rank = x.base_rank + x.ability_bonus;
// 				x.total_rank = modified_total_rank;
// 				// printElement(x.name, 30, ' ');
// 				// printElement(x.ability_modifier, 16, ' ');
// 				// printElement(x.total_rank, 19, ' ');
// 				// printElement(x.ability_bonus, 21, ' ');
// 				// printElement(x.base_rank, 5, ' ');
// 				// cout << endl;
// 			}
// 			else
// 			{
// 				continue;
// 			}
// 		}
// 		else
// 		{
// 			return 0;
// 		}
// 	}
// 	return skp;
// }

// vector<Skill> generateSkills(struct Class& selectedClass, struct Character& character, struct Stats& statsList){
// 	vector<Skill> skill_list;
// 	int rank_cap = character.effectiveLevel + 3;
// 	int base_gain = 2;
// 	if(!strcmp(selectedClass.name,"Rogue")){
// 		base_gain =8;
// 	}
// 	else if(!strcmp(selectedClass.name,"Ranger") || !strcmp(selectedClass.name,"Bard")){
// 		base_gain = 6;
// 	}
// 	else if(!strcmp(selectedClass.name,"Barbarian")||(!strcmp(selectedClass.name,"Druid"))||(!strcmp(selectedClass.name,"Monk"))){
// 		base_gain = 4;
// 	}
// 	int skp = determineNumSkillPoints(character.effectiveLevel,base_gain,statsList.intl);
// 	int ability_bonus = 0;
// 	for(auto s : selectedClass.classSkills){
// 		Skill sk = Skill();
// 		sk.name = s.first;
// 		sk.ability_modifier = s.second;

// 		if(!strcmp(sk.ability_modifier.c_str(),"strength")){
// 			ability_bonus = determineBonus(statsList.str);
// 		} 
// 		if(!strcmp(sk.ability_modifier.c_str(),"dexterity")){
// 			ability_bonus = determineBonus(statsList.dex);
// 		} 
// 		if(!strcmp(sk.ability_modifier.c_str(),"constitution")){
// 			ability_bonus = determineBonus(statsList.con);
// 		} 
// 		if(!strcmp(sk.ability_modifier.c_str(),"intelligence")){
// 			ability_bonus = determineBonus(statsList.intl);
// 		} 
// 		if(!strcmp(sk.ability_modifier.c_str(),"wisdom")){
// 			ability_bonus = determineBonus(statsList.wis);
// 		} 
// 		if(!strcmp(sk.ability_modifier.c_str(),"charisma")){
// 			ability_bonus = determineBonus(statsList.cha);
// 		}
// 		int base_rank = std::min((rolldX(rank_cap+1) - 1),skp);
// 		skp -= base_rank;
// 		sk.ability_bonus = ability_bonus;
// 		int total_rank = base_rank + ability_bonus;
// 		sk.total_rank = total_rank;
// 		skill_list.push_back(sk);
// 	}
// 	//If we stil have leftover skill points we redistribute across skills that haven't hit their skill cap
// 	// while(skp>0){
// 	// 	skp = updateSkills(skill_list,skp,rank_cap);
// 	// }
// 	return skill_list;
// }

// void printSkillList(vector<Skill> skills_list){
// 	printElement("Skill",30,' ');
// 	printElement("Key Ability", 16, ' ');
// 	printElement("Skill Modifier",19,' ');
// 	printElement("Ability Modifier",21,' ');
// 	printElement("Ranks",5,' ');
// 	cout << endl;
// 	for(const auto s : skills_list){
// 		printElement(s.name,30,' ');
// 		printElement(s.ability_modifier,16,' ');
// 		printElement(s.total_rank,19,' ');
// 		printElement(s.ability_bonus,21,' ');
// 		printElement(s.base_rank,5,' ');
// 		cout << endl;
// 	}
// }

// void printCharInfo(struct Character character) {
// 	cout << "Race: " << character.race << endl;
// 	if (character.gender == 0) {
// 		cout << "Gender: Male" << endl;
// 	}
// 	else {
// 		cout << "Gender: Female " << endl;
// 	}
// 	cout << "Height: " << character.baseHeight << " Inches" << endl;
// 	cout << "Weight: " << character.baseWeight << " lbs" << endl;
// 	cout << "Age: " << character.baseAge << " Years Old" << endl;
// 	cout << "Alignment: " << character.alignment << endl;
// 	cout << "Deity: " << character.deity << endl;
// 	cout << "Total Hitpoints: " << character.totalHP << " HP" << endl;
// }

// void printStats(struct Stats statList) {
// 	int strBonus = determineBonus(statList.str);
// 	int dexBonus = determineBonus(statList.dex);
// 	int conBonus = determineBonus(statList.con);
// 	int intBonus = determineBonus(statList.intl);
// 	int wisBonus = determineBonus(statList.wis);
// 	int chaBonus = determineBonus(statList.cha);
// 	cout << "Strength: " << statList.str << " (" << std::showpos << strBonus << ") " << std::noshowpos << endl;
// 	cout << "Dexterity: " << statList.dex << " (" << std::showpos << dexBonus << ") " << std::noshowpos << endl;
// 	cout << "Constitution: " << statList.con << " (" << std::showpos << conBonus << ") " << std::noshowpos << endl;
// 	cout << "Intelligence: " << statList.intl << " (" << std::showpos << intBonus << ") " << std::noshowpos << endl;
// 	cout << "Wisdom: " << statList.wis << " (" << std::showpos << wisBonus << ") " << std::noshowpos << endl;
// 	cout << "Charisma: " << statList.cha << " (" << std::showpos << chaBonus << ") " << std::noshowpos << endl;
// 	cout << endl;
// }

