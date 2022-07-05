#include "..\headers\Race.h"
#include "..\headers\dnd_template_functions.h"
#include <iostream>

using namespace std;

Race::Race()
{
	std::string name;
	int base_age;
	int base_height;
	int base_weight;
	std::vector<int> stats_mod;
}

//Race::setters
void Race::set_age(int x)
{
	this->base_age = x;
}
void Race::set_height(int x)
{
	this->base_height = x;
}
void Race::set_weight(int x)
{
	this->base_weight = x;
}
void Race::set_race_name(std::string race_name)
{
	this->name = race_name;
}

void Race::set_gender(int gender)
{
	this->gender = gender;
}

//Race::getters
int Race::get_age() const
{
	return base_age;
}

int Race::get_height() const
{
	return base_height;
}

int Race::get_weight() const
{
	return base_weight;
}

int Race::get_gender() const
{
	return gender;
}

std::string Race::get_race_name() const
{
	return name;
}

std::vector<int> Race::get_stats_modifier() const
{
	return stats_mod;
}
//Misc Functions
void Race::determine_race()
{
	/*Idea here is to have a list of all generic races, generate a random index and return the race associated with said index.*/
	std::vector<std::string> races = {"Human", "Elf", "Dwarf", "Halfling", "Gnome", "Half-Elf", "Half-Orc"};
	//Need to ask about this one
	std::random_device rd;
	// obtain a random number from hardware
	std::mt19937 eng(rd());
	// seed the generator
	std::uniform_int_distribution<> distr(0, 6); // define the range
	int randIndex = distr(eng);
	std::string race = races[randIndex];
	set_race_name(race);
}

/**
 * @brief Figure out what stats need to be modified based on the race that is chosen.
 * 
 * In D&D 3.5 Edition, selecting the race of your character typically modified two stats.
 * The exception to this is Half-Orc, which two stats are lowered (for reasons unknown).
 * 
 * NOTE: Here is an illustration of stats_mod. The indices correspond to reading a character stat block from top to bottom.
 * 				STRENGTH        DEXTERITY        CONSTITUTION        INTELLIGENCE          WISDOM        CHARISMA
 * 	STATS_MOD = {		0,				0,					0,					0,				0,				0}
 * 
 *	All values should be added to whatever stats are rolled for the character, meaning this generally should take place after stats are rolled,
 * 	but BEFORE stats are fully allocated to avoid having a stat exceed 18 (as this is considered the cap for level 1 characters).
 */
void Race::generate_stats_modifier()
{
	if (!name.compare("Dwarf"))
	{
		stats_mod = {0, 0, 2, 0, 0, -2};
	}
	if (!name.compare("Elf"))
	{
		stats_mod = {0, 2, -2, 0, 0, 0};
	}
	if (!name.compare("Gnome"))
	{
		stats_mod = {-2, 0, 2, 0, 0, 0};
	}
	if (!name.compare("Halfling"))
	{
		stats_mod = {-2, 2, 0, 0, 0, 0};
	}
	if (!name.compare("Human") || !name.compare("Half-Elf"))
	{
		stats_mod = {0, 0, 0, 0, 0, 0};
	}
	if (!name.compare("Half-Orc"))
	{
		stats_mod = {2, 0, 0, -2, 0, -2};
	}
}

/**
 * @brief Based on race and class selected, randomly determine a plausible age for the character.
 * 
 * @param complexity - The 'complexity' of the class they have chosen. In essence, D&D 3.5 has some implicit notion of how long a person would need to train
 * in order to be considered of the specified class. The higher the complexity, the longer it is presumed the character had to study.
 */
void Race::determine_age(int complexity)
{
	int age;
	int num_die;
	int die_face;
	vector<vector<pair<int, int>>> matrix(7, vector<pair<int, int>>(3));
	matrix.push_back({{1, 4}, {1, 6}, {2, 6}});	 //Human
	matrix.push_back({{3, 6}, {5, 6}, {7, 6}});	 //Dwarf
	matrix.push_back({{4, 6}, {6, 6}, {10, 6}}); //Elf
	matrix.push_back({{4, 6}, {6, 6}, {9, 6}});	 //Gnome
	matrix.push_back({{1, 6}, {2, 6}, {3, 6}});	 //Half-Elf
	matrix.push_back({{1, 4}, {1, 6}, {2, 6}});	 //Half-Orc
	matrix.push_back({{2, 4}, {3, 6}, {4, 6}});	 //Halfling
	if (!name.compare("Dwarf"))
	{
		num_die = matrix.at(1).at(complexity).first;
		die_face = matrix.at(1).at(complexity).second;
		age = 40 + rollXdX(num_die, die_face);
	}
	if (!name.compare("Elf"))
	{
		num_die = matrix.at(2).at(complexity).first;
		die_face = matrix.at(2).at(complexity).second;
		age = 110 + rollXdX(num_die, die_face);
	}
	if (!name.compare("Gnome"))
	{
		num_die = matrix.at(3).at(complexity).first;
		die_face = matrix.at(3).at(complexity).second;
		age = 40 + rollXdX(num_die, die_face);
	}
	if (!name.compare("Halfling"))
	{
		num_die = matrix.at(6).at(complexity).first;
		die_face = matrix.at(6).at(complexity).second;
		age = 20 + rollXdX(num_die, die_face);
	}
	if (!name.compare("Human"))
	{
		num_die = matrix.at(0).at(complexity).first;
		die_face = matrix.at(0).at(complexity).second;
		age = 15 + rollXdX(num_die, die_face);
	}
	if (!name.compare("Half-Elf"))
	{
		num_die = matrix.at(4).at(complexity).first;
		die_face = matrix.at(4).at(complexity).second;
		age = 20 + rollXdX(num_die, die_face);
	}
	if (!name.compare("Half-Orc"))
	{
		num_die = matrix.at(5).at(complexity).first;
		die_face = matrix.at(5).at(complexity).second;
		age = 14 + rollXdX(num_die, die_face);
	}
	set_age(age);
}

/**
 * @brief Based on the race selected, select a plausible height and weight for the character.
 * 
 * In D&D 3.5 edition, there appears to be sexual dimorphism present in all races, which is shown
 * in the base height and weight values being slightly different (typically lower values for females).
 * 
 */
void Race::determine_height_weight()
{
	int height_mod;
	int weight_mod;
	int base_height;
	int base_weight;
	if (!name.compare("Dwarf"))
	{ //M: 130,45; F: 100,43
		height_mod = rollXdX(2, 4);
		weight_mod = rollXdX(2, 6);
		if (gender == 0)
		{ //If Male
			base_height = 45;
			base_weight = 130;
		}
		else
		{ //If Female
			base_height = 43;
			base_weight = 100;
		}
	}
	if (!name.compare("Elf"))
	{
		height_mod = rollXdX(2, 6);
		weight_mod = rolldX(6);
		if (gender == 0)
		{ //If Male
			base_height = 53;
			base_weight = 85;
		}
		else
		{ //If Female
			base_height = 53;
			base_weight = 80;
		}
	}
	if (!name.compare("Gnome"))
	{ //W40;H36;W35;H34
		height_mod = rollXdX(2, 4);
		weight_mod = 1;

		if (gender == 0)
		{ //If Male
			base_height = 36;
			base_weight = 40;
		}
		else
		{ //If Female
			base_height = 34;
			base_weight = 40;
		}
	}
	if (!name.compare("Halfling"))
	{
		height_mod = rollXdX(2, 4);
		weight_mod = 1;
		if (gender == 0)
		{ //If Male
			base_height = 32;
			base_weight = 30;
		}
		else
		{ //If Female
			base_height = 30;
			base_weight = 25;
		}
	}
	if (!name.compare("Human"))
	{
		height_mod = rollXdX(2, 10);
		weight_mod = rollXdX(2, 4);
		if (gender == 0)
		{ //If Male
			base_height = 58;
			base_weight = 120;
		}
		else
		{ //If Female
			base_height = 53;
			base_weight = 85;
		}
	}
	if (!name.compare("Half-Elf"))
	{
		height_mod = rollXdX(2, 8);
		weight_mod = rollXdX(2, 4);
		if (gender == 0)
		{ //If Male
			base_height = 55;
			base_weight = 100;
		}
		else
		{ //If Female
			base_height = 53;
			base_weight = 80;
		}
	}
	if (!name.compare("Half-Orc"))
	{
		height_mod = rollXdX(2, 12);
		weight_mod = rollXdX(2, 6);
		if (gender == 0)
		{ //If Male
			base_height = 58;
			base_weight = 150;
		}
		else
		{ //If Female
			base_height = 53;
			base_weight = 110;
		}
	}
	set_weight(base_height + (height_mod * weight_mod));
	set_height(base_weight + height_mod);
}

/**
 * @brief Determine the gender of the character based on essentially a coin flip.
 * 
 * This matters mostly for determining height and weight. 
 */
void Race::determine_gender()
{
	int randBin = rand() % 2;
	set_gender(randBin);
}

/**
 * @brief A helper function that prints out the basic information handled by this CPP file.
 * This includes:
 * 	- Race
 * 	- Sex
 * 	- Height
 * 	- Weight
 * 	- Age
 */
void Race::print_race_info()
{
	cout << "Race: " << get_race_name() << endl;
	if (gender == 0)
	{
		cout << "Gender: Male" << endl;
	}
	else
	{
		cout << "Gender: Female " << endl;
	}
	cout << "Height: " << get_height() << " Inches" << endl;
	cout << "Weight: " << get_weight() << " lbs" << endl;
	cout << "Age: " << get_age() << " Years Old" << endl;
}