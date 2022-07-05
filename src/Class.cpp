/* The Point class Implementation file (Point.cpp) */
#include "..\headers\Class.h"
using namespace std;

// Constructor - The default values are specified in the declaration

Class::Class()
{
	char *name;
	int complexity;
	int class_level;
	int class_hit_die; //The Dice you roll for hp
	std::vector<int> good_stats;
	std::vector<int> bad_stats;
	std::vector<std::pair<int, int>> player_alignment;
	std::vector<std::pair<std::string, std::string>> class_skills;
	std::string alignment;
	std::string deity;
	int base_attack_bonus;
	int number_of_attacks;
	int skill_rank_gain;
}

// Getters
const int Class::get_complexity()
{
	return complexity;
} // Getter
const int Class::get_class_level()
{
	return class_level;
} // Getter
const int Class::get_class_hit_die()
{
	return class_hit_die;
}
const int Class::get_base_attack_bonus()
{
	return base_attack_bonus;
}
const int Class::get_number_of_attacks()
{
	return number_of_attacks;
}
const std::string Class::get_name()
{
	return name;
}
const int Class::get_skill_rank_gain()
{
	return skill_rank_gain;
}

const std::vector<int> Class::get_good_stats()
{
	return good_stats;
}

const std::vector<int> Class::get_bad_stats()
{
	return bad_stats;
}

// Setters
void Class::set_complexity(int x)
{
	this->complexity = x;
}
void Class::set_class_level(int x)
{
	this->class_level = x;
}
void Class::set_class_hit_die(int x)
{
	this->class_hit_die = x;
}
void Class::set_base_attack_bonus(int x)
{
	this->base_attack_bonus = x;
}
void Class::set_number_of_attacks(int x)
{
	this->number_of_attacks = x;
}
void Class::set_name(std::string x)
{
	this->name = x;
}
void Class::set_skill_rank_gain(int rank)
{
	this->skill_rank_gain = rank;
}

void Class::set_good_stats(vector<int> vector)
{
	this->good_stats = std::move(vector);
}

void Class::set_bad_stats(vector<int> vector)
{
	this->bad_stats = std::move(vector);
}

//Misc Functions
/**
 * @brief Determine the 'complexity' of the class that is chosen.
 * 
 * 	This is only really useful in making sure the ages of the character of said class lines up with
 * 	how much time the creators of D&D 3.5 think training for that class would take. This means that,
 * 	in essence, someone would be spending much more of their life studying wizardry or martial arts
 * 	than they would studying rogue...stuff.
 */
void Class::determine_complexity()
{
	if (!name.compare("Barbarian") || !name.compare("Rogue") || !name.compare("Sorcerer"))
	{
		complexity = 1;
	}
	if (!name.compare("Bard") || !name.compare("Fighter") || !name.compare("Paladin") || !name.compare("Ranger"))
	{
		complexity = 2;
	}
	if (!name.compare("Cleric") || !name.compare("Druid") || !name.compare("Monk") || !name.compare("Wizard"))
	{
		complexity = 3;
	}
}
/**
 * @brief Determine what the HD of the class selected is.
 * 	
 * 	This matters mainly for determining how much HP you gain per level as, in essence,
 * 	it is the die that you roll when leveling up. There are other uses for it, such as
 * 	for spells determining how many HD of creatures can be affected by spells and whatnot.
 */
void Class::determine_hit_die()
{
	if (!name.compare("Sorcerer") || !name.compare("Wizard"))
	{
		class_hit_die = 4;
	}
	if (!name.compare("Bard") || !name.compare("Rogue"))
	{
		class_hit_die = 6;
	}
	if (!name.compare("Cleric") || !name.compare("Druid") || !name.compare("Monk") || !name.compare("Ranger"))
	{
		class_hit_die = 8;
	}
	if (!name.compare("Paladin") || !name.compare("Fighter"))
	{
		class_hit_die = 10;
	}
	if (!name.compare("Barbarian"))
	{
		class_hit_die = 12;
	}
}
/**
 * @brief Determine which stats should be prioritized over others when creating a new character.
 * 	
 * 	This is especially important in D&D 3.5 since characters are much more dependent on having good stats to function.
 * 	Plus, nobody wants to roll a character that doesn't really work (i.e., High CHA Monk with low WIS? C'mon.) 
 * 
 * 	NOTE: Since it is not exactly clear due to using numeric values, here is a chart for what each number corresponds to.
 *		1 - Strength
 * 		2 - Dexterity
 * 		3 - Constitution
 * 		4 - Intelligence
 * 		5 - Wisdom
 * 		6 - Charisma 
 */
void Class::set_stat_distribution()
{
	// The vector of stats that are preferred, necessary or otherwise useful for the class to function
	std::vector<int> good_stats_vector;
	// The vector of stats that might be nice to have, or might just be the dump stat for the class.
	std::vector<int> bad_stats_vector;
	if (!name.compare("Barbarian") || !name.compare("Fighter"))
	{
		good_stats_vector = {1, 2, 3};
		bad_stats_vector = {4, 5, 6};
	}
	if (!name.compare("Bard") || !name.compare("Rogue"))
	{
		good_stats_vector = {2, 4, 6};
		bad_stats_vector = {1, 3, 5};
	}
	if (!name.compare("Druid") || !name.compare("Ranger"))
	{
		good_stats_vector = {2, 3, 5};
		bad_stats_vector = {1, 4, 6};
	}
	if (!name.compare("Cleric"))
	{
		good_stats_vector = {1, 3, 5};
		bad_stats_vector = {2, 4, 6};
	}
	if (!name.compare("Monk"))
	{
		good_stats_vector = {1, 2, 5};
		bad_stats_vector = {3, 4, 6};
	}
	if (!name.compare("Paladin"))
	{
		good_stats_vector = {1, 5, 6};
		bad_stats_vector = {2, 3, 4};
	}
	if (!name.compare("Sorcerer"))
	{
		good_stats_vector = {2, 3, 6};
		bad_stats_vector = {1, 4, 5};
	}
	if (!name.compare("Wizard"))
	{
		good_stats_vector = {2, 3, 4};
		bad_stats_vector = {1, 5, 6};
	}
	set_good_stats(good_stats_vector);
	set_bad_stats(bad_stats_vector);
}

/**
 * @brief A helper function that simulates the process of (retroactively?) selecting your Ability Score Increases (ASIs) which are gained every 4 levels.
 * 
 * @param level The level of the character that is being rolled. For example, if they are level 15, they should have done their ASI selection 3 times (4, 8, 12).
 */
void Class::smart_stat_increase_loop(int level)
{
	if (level < 4)
	{
		return;
	}
	else
	{
		while (level >= 4)
		{
			if (level % 4 == 0)
			{
				vector<int> choice_weights = {40, 30, 10, 10, 10};
				int choice_to_make = weighted_distribution(choice_weights);
				smart_stat_increase(choice_to_make);
			}
			level--;
		}
		return;
	}
}

/**
 * @brief Attempt to increase the stats of the character using heuristics and some randomness.
 * 
 * To ensure that ASIs are not spent indiscriminately and still provide some benefit to the playability of the
 * randomly selected character, some heuristics are set in place based on developer experience with playing D&D 3.5 Edition.
 * These are then assigned weighted probabilities and the process takes off from there.
 * 
 * @param stat_increase_plan_index - The index that represents which plan of action will be taken. They are as follows:
 * 	Plan 1: Raise a 'good stat' that is an odd value, using random uniform distribution if there is more than one.
 * 	Plan 2: Raise a 'good stat' using random uniform distribution.
 * 	Plan 3: Raise a 'bad stat' that is an odd value, using random distribution if there is more than one.
 * 	Plan 2: Raise a 'bad stat' using random uniform distribution.
 * 	Plan 5: Raise potentially any stat using random distribution.
 * 	Plan X: If we somehow don't meet the criteria for any of the aforementioned plans, then automatically chose Plan 5.
 */
void Class::smart_stat_increase(int stat_increase_plan_index)
{
	vector<int> good_stats;
	vector<int> bad_stats;
	bool raised = false;
	int index;
	cout << "We're going into stat_increase_plan_index " << stat_increase_plan_index << endl;
	system("pause");
	switch (stat_increase_plan_index)
	{
	case 1:
	{ //RAISE GOOD STAT THAT IS ODD (UNIFORM RANDOM DIST. IF MORE THAN ONE)
		good_stats = get_good_stats();
		index = 0;

		//This while loop will continue infinitely if all the stats are even numbers. It would work if we skip the "Check if odd" step but that's basically step 2 so yeah.
		//Consider zipping a copy of the vector with an array {1,2,3} to keep track of which stat would be raised "smartly"? Dunno if this is more expensive or not though, you'll have to check.
		int counter_odd = 0;
		for (int x : good_stats)
		{
			cout << "Stat " << x << endl;
			if (x % 2 == 1)
			{
				counter_odd++;
			}
		}
		if (counter_odd == 0) //edge cases to address to prevent infinite loop
		{
			vector<int> choice_weights = {0, 70, 10, 10, 10};
			int choice_to_make = weighted_distribution(choice_weights);
			cout << "Taking step " << choice_to_make << endl;
			system("pause");
			smart_stat_increase(choice_to_make);

			//Maybe consider doing this instead:
			/**
			 * Weighted Distribution from {40, 30, 10, 10 10} -> {0, 70, 10, 10, 10} of steps 1-5 and do random selection instead?
			 * Seems a bit strange, considering this wouldn't make sense for the second edge case (all 3 stats are odd), so maybe we'll have to split this if statement
			 * 
			 **/
		}
		else if (counter_odd == good_stats.size())
		{
			smart_stat_increase(2);
			break;
		}
		else
		{
			while (!raised)
			{
				index = rolldX(good_stats.size()) - 1;
				if (good_stats.at(index) % 2 == 1)
				{
					good_stats.at(index) += 1;
					raised = true;
				}
				else
				{
				}
			}
		}
		break;
		//If there is more than one good stat that is odd
	}
	case 2:
	{ //RAISE GOOD STAT AT RANDOM (UNIFORM RANDOM DIST.)
		good_stats = get_good_stats();
		index = rolldX(good_stats.size()) - 1;
		good_stats.at(index) += 1;
		break;
	}
	case 3:
	{ //RAISE BAD STAT THAT IS ODD (UNIFORM RANDOM DIST. IF MORE THAN ONE)
		bad_stats = get_bad_stats();
		int index = 0;
		//This while loop will continue infinitely if all the stats are even numbers. It would work if we skip the "Check if odd" step but that's basically step 2 so yeah.
		//Consider zipping a copy of the vector with an array {1,2,3} to keep track of which stat would be raised "smartly"? Dunno if this is more expensive or not though, you'll have to check.
		int counter_odd = 0;
		for (int x : bad_stats)
		{
			if (x % 2 == 1)
			{
				counter_odd++;
			}
		}
		if (counter_odd == 0) //edge cases to address to prevent infinite loop
		{
			vector<int> choice_weights = {10, 10, 0, 70, 10};
			int choice_to_make = weighted_distribution(choice_weights);
			cout << "Taking step " << choice_to_make << endl;
			smart_stat_increase(choice_to_make);

			//Maybe consider doing this instead:
			/**
			 * Weighted Distribution from {40, 30, 10, 10 10} -> {0, 70, 10, 10, 10} of steps 1-5 and do random selection instead?
			 * Seems a bit strange, considering this wouldn't make sense for the second edge case (all 3 stats are odd), so maybe we'll have to split this if statement
			 * 
			 **/
		}
		else if (counter_odd == bad_stats.size())
		{
			smart_stat_increase(4);
			break;
		}
		else
		{
			while (!raised)
			{
				index = rolldX(bad_stats.size()) - 1;
				if (bad_stats.at(index) % 2 == 1)
				{
					bad_stats.at(index) += 1;
					raised = true;
				}
				else
				{
				}
			}
		}
		break;
		//If there is more than one good stat that is odd
	}
	case 4:
	{ //RAISE BAD STAT AT RANDOM (UNIFORM RANDOM DIST.)
		good_stats = get_good_stats();
		index = rolldX(good_stats.size()) - 1;
		good_stats.at(index) += 1;
		break;
	}
	case 5:
	{ //RAISE ANY STAT AT RANDOM (UNIFORM RANDOM DIST.)
		index = rolldX(6) - 1;
		if (index < 3)
		{
			good_stats = get_good_stats();
			good_stats.at(index) += 1;
			return;
		}
		else
		{
			bad_stats = get_bad_stats();
			bad_stats.at(index) += 1;
			return;
		}
		break;
	}
	default:
	{ //DEFINITELY SHOULD NOT END UP HERE, LOG AN ERROR AND CALL IT A DAY (OR JUST CALL STEP 5 I DUNNO)
		cout << "Well you\'re not really supposed to be in this case, so we\'re gonna call case 5 and leave it at that." << endl;
		smart_stat_increase(5);
	}
	}
}
/**
 * @brief Determine the base attack bonus of the class.
 * 
 * For some reason that eludes me, D&D 3.5 edition thought that they should have Base Attack Bonus (BAB)
 * progress differently for certain classes. Namely, most of the martial classes got their BAB equal to their class level,
 * other classes got theirs at some weird progression (noted below), and then Sorcerer and Wizard were absolutely shafted.
 * 
 * I still cannot really understand why the design went in this direction, but luckily this is all stripped out in 5e.
 * 
 */
void Class::determine_base_attack_bonus()
{
	int base_attack_bonus = 0;
	if (!name.compare("Barbarian") || !name.compare("Fighter") || !name.compare("Paladin") || !name.compare("Ranger"))
	{
		base_attack_bonus = class_level; //Are they level 6, 11, or 16
	}
	if (!name.compare("Bard") || !name.compare("Cleric") || !name.compare("Druid") || !name.compare("Monk") || !name.compare("Rogue"))
	{
		if (class_level - 1 % 4 == 0)
		{
			base_attack_bonus = max(class_level - 2, 0);
		}
		else
		{
			base_attack_bonus = class_level - 1;
		}
	}
	if (!name.compare("Sorcerer") || !name.compare("Wizard"))
	{
		if (class_level % 2 == 1)
		{
			base_attack_bonus = max(class_level - 2, 0);
		}
		else
		{
			base_attack_bonus = class_level - 1;
		}
	}
	set_base_attack_bonus(base_attack_bonus);
}

/**
 * @brief Determine how many times the character can attack in a turn.
 * 
 * 	Basically the forumla is simple. For every +5 you have in your BAB, you get another attack.
 * 	When you no longer have enough BAB, then you don't get more attacks.
 * 
 */
void Class::determine_number_of_attacks()
{
	int n_attacks = 1;
	int temp = base_attack_bonus;
	while (temp > 0)
	{
		temp -= 5;
		n_attacks++;
	}
	set_number_of_attacks(n_attacks);
}

/**
 * @brief Determine the character's alignment after considering all constraints placed in advance (i.e., class selected).
 * 
 */
void Class::determine_alignment()
{
	std::map<pair<int, int>, string> alignments;
	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(0, 0), "Lawful Good"));
	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(1, 0), "Netural Good"));
	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(2, 0), "Chaotic Good"));

	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(0, 1), "Lawful Neutral"));
	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(1, 1), "True Neutral"));
	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(2, 1), "Chaotic Neutral"));

	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(0, 2), "Lawful Evil"));
	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(1, 2), "Neutral Evil"));
	alignments.insert(pair<pair<int, int>, string>(pair<int, int>(2, 2), "Chaotic Evil"));

	int numFace = player_alignment.size();
	int roll = rollXdX(1, numFace);
	std::pair<int, int> key = player_alignment.at(roll - 1);
	alignment = alignments.at(key);
}

/*
This function is written under the assumption that non-clerics are free to worship literally any deity they choose, and can/will be revised
should the evidence point to the contrary. Much like chooseClass, there is simply a large array of all possible SRD deities and one is selected at random.
*/
void Class::determine_deity()
{
	static string possible_deities[19] = {"Boccob", "Corellon Larethian", "Ehlonna", "Erythnul", "Fharlanghn", "Garl Glittergold", "Gruumsh", "Hieroneous", "Hextor", "Kord", "Moradin", "Nerull", "Obad-Hai", "Olidammara", "Pelor", "St. Cuthbert", "Vecna", "Wee Jas", "Yondalla"};
	int roll;
	roll = rolldX(possible_deities->size());
	int indx = roll - 1;
	string selected_deity = possible_deities[indx];
	deity = selected_deity;
}

/**
 * @brief Select the deity that a cleric will worship, to inform what alignments are valid for their character.
 *	
 *	Due to extra restrictions that are placed upon the Cleric class, this function is only called when the class selected is "Cleric".
 *	It is meant to adjust for alignment restrictions and therefore is called before determine_alignment.
 * 	NOTE: Another thing to note is, clerics are allowed to be AT MOST ONE step away from their deity chosen. 
 *  This means that, for example, a Chaotic Good character could worship a Neutral Good or Chaotic Neutral deity and still 'be fine'.
 * 
 */
void Class::determine_cleric_patronage()
{
	std::map<string, std::pair<int, int>> player_alignment_deities;
	player_alignment_deities.insert(pair<string, pair<int, int>>("Boccob", std::pair<int, int>(1, 1)));				//							True Neutral
	player_alignment_deities.insert(pair<string, pair<int, int>>("Corellon Larethian", std::pair<int, int>(2, 0))); //							Chaotic Good
	player_alignment_deities.insert(pair<string, pair<int, int>>("Ehlonna", std::pair<int, int>(1, 0)));			//							Neutral Good
	player_alignment_deities.insert(pair<string, pair<int, int>>("Erythnul", std::pair<int, int>(2, 2)));			//							Chaotic Evil
	player_alignment_deities.insert(pair<string, pair<int, int>>("Fharlanghn", std::pair<int, int>(1, 1)));			//							True Neutral
	player_alignment_deities.insert(pair<string, pair<int, int>>("Garl Glittergold", std::pair<int, int>(1, 0)));	//							Neutral Good
	player_alignment_deities.insert(pair<string, pair<int, int>>("Gruumsh", std::pair<int, int>(2, 2)));			//							Chaotic Evil
	player_alignment_deities.insert(pair<string, pair<int, int>>("Hieroneous", std::pair<int, int>(0, 0)));			//							Lawful Good
	player_alignment_deities.insert(pair<string, pair<int, int>>("Hextor", std::pair<int, int>(0, 2)));				//							Lawful Evil
	player_alignment_deities.insert(pair<string, pair<int, int>>("Kord", std::pair<int, int>(2, 0)));				//							Chaotic Good
	player_alignment_deities.insert(pair<string, pair<int, int>>("Moradin", std::pair<int, int>(0, 0)));			//							Lawful Good
	player_alignment_deities.insert(pair<string, pair<int, int>>("Nerull", std::pair<int, int>(1, 2)));				//							Neutral Evil
	player_alignment_deities.insert(pair<string, pair<int, int>>("Obad-Hai", std::pair<int, int>(1, 1)));			//							True Neutral
	player_alignment_deities.insert(pair<string, pair<int, int>>("Olidammara", std::pair<int, int>(2, 1)));			//							Chaotic Neutral
	player_alignment_deities.insert(pair<string, pair<int, int>>("Pelor", std::pair<int, int>(1, 0)));				//							Neutral Good
	player_alignment_deities.insert(pair<string, pair<int, int>>("St. Cuthbert", std::pair<int, int>(0, 1)));		//							Lawful Neutral
	player_alignment_deities.insert(pair<string, pair<int, int>>("Vecna", std::pair<int, int>(1, 2)));				//							Neutral Evil
	player_alignment_deities.insert(pair<string, pair<int, int>>("Wee Jas", std::pair<int, int>(0, 1)));			//							Lawful Neutral
	player_alignment_deities.insert(pair<string, pair<int, int>>("Yondalla", std::pair<int, int>(0, 0)));			//							Lawful Good

	pair<int, int> alignment = player_alignment_deities.at(deity);
	if (alignment.first == 1 || alignment.second == 1)
	{ //Adjust for leeway if one of the two portions of deity's alignment is "Neutral"
		if (alignment.first == 1)
		{
			pair<int, int> newAlign1 = std::pair<int, int>(alignment.first + 1, alignment.second);
			pair<int, int> newAlign2 = std::pair<int, int>(alignment.first - 1, alignment.second);
			player_alignment.push_back(newAlign1);
			player_alignment.push_back(newAlign2);
		}
		if (alignment.second == 1)
		{
			pair<int, int> newAlign1 = std::pair<int, int>(alignment.first, alignment.second + 1);
			pair<int, int> newAlign2 = std::pair<int, int>(alignment.first, alignment.second - 1);
			player_alignment.push_back(newAlign1);
			player_alignment.push_back(newAlign2);
		}
	}
}

/**
 * @brief Determine which alignment the character can and will be based on their class chosen.
 * 
 * 	In D&D 3.5 Edition, certain classes cannot be of certain alignments. For example, Barbarians and Monks cannot take non-chaotic and non-lawful alignments.
 * 	While thematic and interesting from a worldbuilding standpoint, it is still idiotic and luckily no longer a mechanic in later editions.
 * 
 */
void Class::set_alignments()
{
	if (!name.compare("Barbarian"))
	{
		//Barbarian alignment: Chaotic only
		player_alignment.push_back(pair<int, int>(2, 0));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Bard"))
	{
		//Bard alignment: Non-Lawful
		player_alignment.push_back(pair<int, int>(1, 0));
		player_alignment.push_back(pair<int, int>(1, 1));
		player_alignment.push_back(pair<int, int>(1, 2));
		player_alignment.push_back(pair<int, int>(2, 0));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Cleric"))
	{
		//Cleric alignment: Dependent on deity
		determine_cleric_patronage();
	}
	if (!name.compare("Druid"))
	{
		//Druid alignment: Neutral only
		player_alignment.push_back(pair<int, int>(0, 1));
		player_alignment.push_back(pair<int, int>(1, 0));
		player_alignment.push_back(pair<int, int>(1, 1));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(1, 2));
	}
	if (!name.compare("Fighter"))
	{
		//Fighter alignment: Any
		player_alignment.push_back(pair<int, int>(0, 0));
		player_alignment.push_back(pair<int, int>(0, 1));
		player_alignment.push_back(pair<int, int>(0, 2));
		player_alignment.push_back(pair<int, int>(1, 0));
		player_alignment.push_back(pair<int, int>(1, 1));
		player_alignment.push_back(pair<int, int>(1, 2));
		player_alignment.push_back(pair<int, int>(2, 0));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Monk"))
	{
		//Monk alignment: Lawful only

		player_alignment.push_back(pair<int, int>(0, 0));
		player_alignment.push_back(pair<int, int>(0, 1));
		player_alignment.push_back(pair<int, int>(0, 2));
	}
	if (!name.compare("Paladin"))
	{
		//Paladin alignment: Lawful Good only
		player_alignment.push_back(pair<int, int>(0, 0));
	}
	if (!name.compare("Ranger"))
	{
		//Ranger alignment: Any
		player_alignment.push_back(pair<int, int>(0, 0));
		player_alignment.push_back(pair<int, int>(0, 1));
		player_alignment.push_back(pair<int, int>(0, 2));
		player_alignment.push_back(pair<int, int>(1, 0));
		player_alignment.push_back(pair<int, int>(1, 1));
		player_alignment.push_back(pair<int, int>(1, 2));
		player_alignment.push_back(pair<int, int>(2, 0));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Rogue"))
	{
		//Rogue alignment: Any
		player_alignment.push_back(pair<int, int>(0, 0));
		player_alignment.push_back(pair<int, int>(0, 1));
		player_alignment.push_back(pair<int, int>(0, 2));
		player_alignment.push_back(pair<int, int>(1, 0));
		player_alignment.push_back(pair<int, int>(1, 1));
		player_alignment.push_back(pair<int, int>(1, 2));
		player_alignment.push_back(pair<int, int>(2, 0));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Sorcerer"))
	{
		//Sorcerer alignment: Any
		player_alignment.push_back(pair<int, int>(0, 0));
		player_alignment.push_back(pair<int, int>(0, 1));
		player_alignment.push_back(pair<int, int>(0, 2));
		player_alignment.push_back(pair<int, int>(1, 0));
		player_alignment.push_back(pair<int, int>(1, 1));
		player_alignment.push_back(pair<int, int>(1, 2));
		player_alignment.push_back(pair<int, int>(2, 0));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Wizard"))
	{
		//Wizard alignment: Any
		player_alignment.push_back(pair<int, int>(0, 0));
		player_alignment.push_back(pair<int, int>(0, 1));
		player_alignment.push_back(pair<int, int>(0, 2));
		player_alignment.push_back(pair<int, int>(1, 0));
		player_alignment.push_back(pair<int, int>(1, 1));
		player_alignment.push_back(pair<int, int>(1, 2));
		player_alignment.push_back(pair<int, int>(2, 0));
		player_alignment.push_back(pair<int, int>(2, 1));
		player_alignment.push_back(pair<int, int>(2, 2));
	}
}

// Public Functions

/**
 * @brief The main function for creating a new character.
 * 
 */
void Class::create_character()
{
	cout << "Choose your class: ";
	string input_string;
	std::getline(std::cin, input_string);
	std::transform(input_string.begin(), input_string.end(), input_string.begin(), ::tolower);
	if (!input_string.empty())
	{
		input_string[0] = toupper(input_string[0]);
	}
	set_name(input_string);
	cout << "Choose Level of class: ";
	int input_level = 0;
	while (true)
	{
		cout << "Select Character Level: ";
		string input;
		std::getline(std::cin, input);
		std::stringstream levelStream(input);
		if (levelStream >> input_level)
		{
			break;
		}
		else
		{
			cout << "Invalid Number. Please try again." << endl
				 << endl;
		}
	}
	class_level = input_level;
	cout << endl;

	/**
	 * The actual order that leveling up is supposed to go in:
	 * 1. Choose Class to advance in (We're assuming this is not going to change for this program)
	 * 2. Adjust Base Attack Bonus (Since 1 does not change, this does not deviate either)
	 * 3. Adjust Base Save Bonuses (Since 1 does not change, this does not deviate either)
	 * 4. Assign Ability Score Increase (if level % 4 == 0) (This will need to be called every 4th level)
	 * 5. Roll Hit Points for level (This would need to be called at every level instead of calcualted directly)
	 * 6. Calculate and assign skill points (This would need to be called at every level instead of calculated directly)
	 * 7. Assign feat if applicable for level (Not a featuer yet)
	 * 8. Select spells if applicable (Not a feature yet)
	 * 9. Assign Class Features (Not a feature yet)
	 * 
	 * So, based on what we've noted here, our procedure should look something like this:
	 * 1. Set class
	 * 2. Calculate the BAB and Base Saves as if player takes only that class up to selected level
	 * 3. Determine Hit Die based on class
	 * 4. Set the base stats.
	 * 5. Begin the level up procedure 
	 * 	5a. Check if level % 4 is 0; If it is, do the smart_ability_increase, else continue;
	 * 	5b. Roll HD and add (updated) con score to the total_hitpoints
	 * 	5c. Calculate available skill points and add (updated) int modifier to the total_skillpoints
	 * 	5d. Distribute skill points
	 * 6. Proceed as normal.
	 *
	 **/
	determine_base_attack_bonus();
	determine_number_of_attacks();
	determine_complexity();
	set_stat_distribution();
	determine_hit_die(); //Just determines what die to roll for HP
	smart_stat_increase_loop(class_level);
	determine_deity();
	set_alignments();
	determine_alignment();
}

const void Class::print_class_information()
{
	cout << "Class Name: " << name << endl;
	cout << "Complexity: " << complexity << endl;
	cout << "Class Level: " << class_level << endl;
	cout << "Class Hit Die: " << class_hit_die << endl;
	cout << "Base Attack Bonus: " << base_attack_bonus << endl;
	cout << "Number of attacks: " << number_of_attacks << endl;
	cout << "Alignment: " << alignment << endl;
	cout << "Deity: " << deity << endl;
}