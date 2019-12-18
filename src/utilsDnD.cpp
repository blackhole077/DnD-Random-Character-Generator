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
#include "..\headers\roll.h"
#include "..\headers\utilsDnD.h"
#include "..\headers\Stats.h"
#include "..\headers\Class.h"
#include "..\headers\Character.h"
#include "..\headers\Race.h"
using namespace std;

/*
The purpose of determineRace is to randomly select the race of the generated character-to-be.
Since we would want each race to be equally likely as the next, a uniform distribution is utilized.
Upon selecting a race, which is stored as a string (or an array of characters), it finds the attributes it needs to modify.
These attributes include bonuses and penalties to the 6 stats and the base age, or age of adulthood for that particular race.
This function is called in CharGen.cpp
*/
/*
The function smart_stat_distribution attempts to take in the 6 randomly rolled numbers [3,18] and allocate them in a "smart" fashion.
For the sake of complexity, each class is assumed to have 3 preferred stats, as well as 3 dump stats.
What this means is that the 3 highest values rolled will be allocated to a class's preferred stats (albeit at random), while remaining stats are allocated (again, at random) to the dump stats.
*/
//TODO: There's a bit of code DRYing we can do for actually allocating the stats (the code is 99% the same, save for what vector is being acted upon.)
std::map<int,int> smart_stat_distribution(std::vector<int> bad_class_stats, std::vector<int> bad_available_stats, std::vector<int> good_class_stats, std::vector<int> good_available_stats){
	std::map<int,int> stats_map;
	int counter = bad_available_stats.size();
	for (int i = 0; i < counter; i++)
	{
		int ins;
		int roll;
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
	}
  /** Begin allocation of "preferred stats", which involves taking the 3 highest rolled stats and
      allocating them into what I believe are the 3 "good" stats for a given class.**/
	counter = good_available_stats.size();
	for (int i = 0; i < counter; i++)
	{
		int ins;
		int roll;
    /**If more than one stat remains available, then roll to see which one is allocated.**/
		if (good_available_stats.size() != 1)
		{
			roll = rolldX(good_available_stats.size());
			ins = good_available_stats.at(roll - 1);
		}
		else
		{
			ins = good_available_stats.at(0);
		}
    /**Insert the pair <i, ins> into the map. The first value is in reference to the stat itself
       the second is the value of said stat. An example is a Strength score of 16 would be <1,16>**/
		stats_map.insert(std::pair<int, int>(good_class_stats.at(i), ins));
    /**If there was more than one stat available, then erase where it was located.**/
		if (good_available_stats.size() != 1)
		{
			good_available_stats.erase(good_available_stats.begin() + (roll - 1));
		}
		else
		{
			good_available_stats.erase(good_available_stats.begin());
		}
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
The function calcAgeWeightHeight uses a combination of character information and the user-specified class to modify their characters height, weight and age.
While the first is purely cosmetic and weight having only niche application, age does affect the stats of the character-to-be.
Thus once the age is calculated it must also be checked against a threshold to determine the severity of stat changes due to aging.
This function is called in CharGen.cpp
*/

/*
The function determineNumAbilityPoints is called when determining how many ability points should be granted to a player
based on their level. Every 4 levels grants the player one extra ability point which will be allocated into the six main stats
*/

int determineNumAbilityPoints(int level) {
	int number = floor(level / 4);
	return number;
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
