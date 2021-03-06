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
	std::vector<std::pair<int, int>> pAlign;
	std::vector<std::pair<std::string, std::string>> class_skills;
	std::string alignment;
	std::string deity;
	int base_attack_bonus;
	int number_of_attacks;
	int skill_rank_gain;
}

// Getters
int Class::get_complexity() const
{
	return complexity;
} // Getter
int Class::get_class_level() const
{
	return class_level;
} // Getter
int Class::get_class_hit_die() const
{
	return class_hit_die;
}
int Class::get_base_attack_bonus() const
{
	return base_attack_bonus;
}
int Class::get_number_of_attacks() const
{
	return number_of_attacks;
}
std::string Class::get_name() const
{
	return name;
}
int Class::get_skill_rank_gain() const
{
	return skill_rank_gain;
}

std::vector<int> Class::get_good_stats() const
{
	return good_stats;
}

std::vector<int> Class::get_bad_stats() const
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
void Class::determine_complexity(){
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
	if(!name.compare("Paladin")||!name.compare("Fighter")){
		class_hit_die = 10;

	}
	if(!name.compare("Barbarian")){
		class_hit_die = 12;
	}
}
void Class::set_stat_distribution()
{
	std::vector<int> gs;
	std::vector<int> bs;
	if (!name.compare("Barbarian") || !name.compare("Fighter"))
	{
		gs = {1, 2, 3};
		bs = {4, 5, 6};
	}
	if (!name.compare("Bard") || !name.compare("Rogue"))
	{
		gs = {2, 4, 6};
		bs = {1, 3, 5};
	}
	if (!name.compare("Druid") || !name.compare("Ranger"))
	{
		gs = {2, 3, 5};
		bs = {1, 4, 6};
	}
	if(!name.compare("Cleric")){
		gs = {1, 3, 5};
		bs = {2, 4, 6};

	}
	if(!name.compare("Monk")){
		gs = {1, 2, 5};
		bs = {3, 4, 6};
	}
	if(!name.compare("Paladin")){
		gs = {1, 5, 6};
		bs = {2, 3, 4};

	}
	if(!name.compare("Sorcerer")){
		gs = {2, 3, 6};
		bs = {1, 4, 5};

	}
	if(!name.compare("Wizard")){
		gs = {2, 3, 4};
		bs = {1, 5, 6};
	}
	set_good_stats(gs);
	set_bad_stats(bs);
}

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
				printf("%d mod 4 is 0 right?\n",level);
				vector<int> choice_weights = {40, 30, 10, 10, 10};
				int choice_to_make = weighted_distribution(choice_weights);
				smart_stat_increase(choice_to_make);
			}
			level--;
		}
		return;
	}
}

void Class::smart_stat_increase(int step)
{
	vector<int> g_stats;
	vector<int> b_stats;
	bool raised = false;
	int index;
	cout << "We're going into step " << step << endl;
	system("pause");
	switch (step)
	{
	case 1:
	{ //RAISE GOOD STAT THAT IS ODD (UNIFORM RANDOM DIST. IF MORE THAN ONE)
		g_stats = get_good_stats();
		index = 0;
		
		//This while loop will continue infinitely if all the stats are even numbers. It would work if we skip the "Check if odd" step but that's basically step 2 so yeah.
		//Consider zipping a copy of the vector with an array {1,2,3} to keep track of which stat would be raised "smartly"? Dunno if this is more expensive or not though, you'll have to check.
		int counter_odd = 0;
		for (int x : g_stats)
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
		else if (counter_odd == g_stats.size())
		{
			smart_stat_increase(2);
			break;
		}
		else
		{
			while (!raised)
			{
				index = rolldX(g_stats.size()) - 1;
				if (g_stats.at(index) % 2 == 1)
				{
					g_stats.at(index) += 1;
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
		g_stats = get_good_stats();
		index = rolldX(g_stats.size()) - 1;
		g_stats.at(index) += 1;
		break;
	}
	case 3:
	{ //RAISE BAD STAT THAT IS ODD (UNIFORM RANDOM DIST. IF MORE THAN ONE)
		b_stats = get_bad_stats();
		int index = 0;
		//This while loop will continue infinitely if all the stats are even numbers. It would work if we skip the "Check if odd" step but that's basically step 2 so yeah.
		//Consider zipping a copy of the vector with an array {1,2,3} to keep track of which stat would be raised "smartly"? Dunno if this is more expensive or not though, you'll have to check.
		int counter_odd = 0;
		for (int x : b_stats)
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
		else if (counter_odd == b_stats.size())
		{
			smart_stat_increase(4);
			break;
		}
		else
		{
			while (!raised)
			{
				index = rolldX(b_stats.size()) - 1;
				if (b_stats.at(index) % 2 == 1)
				{
					b_stats.at(index) += 1;
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
		g_stats = get_good_stats();
		index = rolldX(g_stats.size()) - 1;
		g_stats.at(index) += 1;
		break;
	}
	case 5:
	{ //RAISE ANY STAT AT RANDOM (UNIFORM RANDOM DIST.)
		index = rolldX(6) - 1;
		if (index < 3)
		{
			g_stats = get_good_stats();
			g_stats.at(index) += 1;
			return;
		}
		else
		{
			b_stats = get_bad_stats();
			b_stats.at(index) += 1;
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

	int numFace = pAlign.size();
	int roll = rollXdX(1, numFace);
	std::pair<int, int> key = pAlign.at(roll - 1);
	alignment = alignments.at(key);
}

/*
This function is written under the assumption that non-clerics are free to worship literally any deity they choose, and can/will be revised
should the evidence point to the contrary. Much like chooseClass, there is simply a large array of all possible SRD deities and one is selected at random.
*/
void Class::determine_deity()
{
	static string possibleDeities[19] = {"Boccob", "Corellon Larethian", "Ehlonna", "Erythnul", "Fharlanghn", "Garl Glittergold", "Gruumsh", "Hieroneous", "Hextor", "Kord", "Moradin", "Nerull", "Obad-Hai", "Olidammara", "Pelor", "St. Cuthbert", "Vecna", "Wee Jas", "Yondalla"};
	int roll;
	roll = rolldX(possibleDeities->size());
	int indx = roll - 1;
	string god = possibleDeities[indx];
	deity = god;
}

/*
Due to extra restrictions that are placed upon the Cleric class, this function is only called when the class selected is "Cleric".
It is meant to adjust for alignment restrictions and therefore is called before determine_alignment.
*/
void Class::determine_cleric_patronage()
{
	std::map<string, std::pair<int, int>> pAlignDeity;
	pAlignDeity.insert(pair<string, pair<int, int>>("Boccob", std::pair<int, int>(1, 1)));			   //							True Neutral
	pAlignDeity.insert(pair<string, pair<int, int>>("Corellon Larethian", std::pair<int, int>(2, 0))); //				Chaotic Good
	pAlignDeity.insert(pair<string, pair<int, int>>("Ehlonna", std::pair<int, int>(1, 0)));			   //							Neutral Good
	pAlignDeity.insert(pair<string, pair<int, int>>("Erythnul", std::pair<int, int>(2, 2)));		   //							Chaotic Evil
	pAlignDeity.insert(pair<string, pair<int, int>>("Fharlanghn", std::pair<int, int>(1, 1)));		   //						True Neutral
	pAlignDeity.insert(pair<string, pair<int, int>>("Garl Glittergold", std::pair<int, int>(1, 0)));   //					Neutral Good
	pAlignDeity.insert(pair<string, pair<int, int>>("Gruumsh", std::pair<int, int>(2, 2)));			   //							Chaotic Evil
	pAlignDeity.insert(pair<string, pair<int, int>>("Hieroneous", std::pair<int, int>(0, 0)));		   //						Lawful Good
	pAlignDeity.insert(pair<string, pair<int, int>>("Hextor", std::pair<int, int>(0, 2)));			   //							Lawful Evil
	pAlignDeity.insert(pair<string, pair<int, int>>("Kord", std::pair<int, int>(2, 0)));			   //								Chaotic Good
	pAlignDeity.insert(pair<string, pair<int, int>>("Moradin", std::pair<int, int>(0, 0)));			   //							Lawful Good
	pAlignDeity.insert(pair<string, pair<int, int>>("Nerull", std::pair<int, int>(1, 2)));			   //							Neutral Evil
	pAlignDeity.insert(pair<string, pair<int, int>>("Obad-Hai", std::pair<int, int>(1, 1)));		   //							True Neutral
	pAlignDeity.insert(pair<string, pair<int, int>>("Olidammara", std::pair<int, int>(2, 1)));		   //						Chaotic Neutral
	pAlignDeity.insert(pair<string, pair<int, int>>("Pelor", std::pair<int, int>(1, 0)));			   //								Neutral Good
	pAlignDeity.insert(pair<string, pair<int, int>>("St. Cuthbert", std::pair<int, int>(0, 1)));	   //						Lawful Neutral
	pAlignDeity.insert(pair<string, pair<int, int>>("Vecna", std::pair<int, int>(1, 2)));			   //								Neutral Evil
	pAlignDeity.insert(pair<string, pair<int, int>>("Wee Jas", std::pair<int, int>(0, 1)));			   //							Lawful Neutral
	pAlignDeity.insert(pair<string, pair<int, int>>("Yondalla", std::pair<int, int>(0, 0)));		   //							Lawful Good

	pair<int, int> alignment = pAlignDeity.at(deity);
	if (alignment.first == 1 || alignment.second == 1)
	{ //Adjust for leeway if one of the two portions of deity's alignment is "Neutral"
		if (alignment.first == 1)
		{
			pair<int, int> newAlign1 = std::pair<int, int>(alignment.first + 1, alignment.second);
			pair<int, int> newAlign2 = std::pair<int, int>(alignment.first - 1, alignment.second);
			pAlign.push_back(newAlign1);
			pAlign.push_back(newAlign2);
		}
		if (alignment.second == 1)
		{
			pair<int, int> newAlign1 = std::pair<int, int>(alignment.first, alignment.second + 1);
			pair<int, int> newAlign2 = std::pair<int, int>(alignment.first, alignment.second - 1);
			pAlign.push_back(newAlign1);
			pAlign.push_back(newAlign2);
		}
	}
}

void Class::set_alignments()
{
	if (!name.compare("Barbarian"))
	{
		//Barbarian alignment: Chaotic only
		pAlign.push_back(pair<int, int>(2, 0));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Bard"))
	{
		//Bard alignment: Non-Lawful
		pAlign.push_back(pair<int, int>(1, 0));
		pAlign.push_back(pair<int, int>(1, 1));
		pAlign.push_back(pair<int, int>(1, 2));
		pAlign.push_back(pair<int, int>(2, 0));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Cleric"))
	{
		//Cleric alignment: Dependent on deity
		determine_cleric_patronage();
	}
	if (!name.compare("Druid"))
	{
		//Druid alignment: Neutral only
		pAlign.push_back(pair<int, int>(0, 1));
		pAlign.push_back(pair<int, int>(1, 0));
		pAlign.push_back(pair<int, int>(1, 1));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(1, 2));
	}
	if (!name.compare("Fighter"))
	{
		//Fighter alignment: Any
		pAlign.push_back(pair<int, int>(0, 0));
		pAlign.push_back(pair<int, int>(0, 1));
		pAlign.push_back(pair<int, int>(0, 2));
		pAlign.push_back(pair<int, int>(1, 0));
		pAlign.push_back(pair<int, int>(1, 1));
		pAlign.push_back(pair<int, int>(1, 2));
		pAlign.push_back(pair<int, int>(2, 0));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Monk"))
	{
		//Monk alignment: Lawful only

		pAlign.push_back(pair<int, int>(0, 0));
		pAlign.push_back(pair<int, int>(0, 1));
		pAlign.push_back(pair<int, int>(0, 2));
	}
	if (!name.compare("Paladin"))
	{
		//Paladin alignment: Lawful Good only
		pAlign.push_back(pair<int, int>(0, 0));
	}
	if (!name.compare("Ranger"))
	{
		//Ranger alignment: Any
		pAlign.push_back(pair<int, int>(0, 0));
		pAlign.push_back(pair<int, int>(0, 1));
		pAlign.push_back(pair<int, int>(0, 2));
		pAlign.push_back(pair<int, int>(1, 0));
		pAlign.push_back(pair<int, int>(1, 1));
		pAlign.push_back(pair<int, int>(1, 2));
		pAlign.push_back(pair<int, int>(2, 0));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Rogue"))
	{
		//Rogue alignment: Any
		pAlign.push_back(pair<int, int>(0, 0));
		pAlign.push_back(pair<int, int>(0, 1));
		pAlign.push_back(pair<int, int>(0, 2));
		pAlign.push_back(pair<int, int>(1, 0));
		pAlign.push_back(pair<int, int>(1, 1));
		pAlign.push_back(pair<int, int>(1, 2));
		pAlign.push_back(pair<int, int>(2, 0));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Sorcerer"))
	{
		//Sorcerer alignment: Any
		pAlign.push_back(pair<int, int>(0, 0));
		pAlign.push_back(pair<int, int>(0, 1));
		pAlign.push_back(pair<int, int>(0, 2));
		pAlign.push_back(pair<int, int>(1, 0));
		pAlign.push_back(pair<int, int>(1, 1));
		pAlign.push_back(pair<int, int>(1, 2));
		pAlign.push_back(pair<int, int>(2, 0));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(2, 2));
	}
	if (!name.compare("Wizard"))
	{
		//Wizard alignment: Any
		pAlign.push_back(pair<int, int>(0, 0));
		pAlign.push_back(pair<int, int>(0, 1));
		pAlign.push_back(pair<int, int>(0, 2));
		pAlign.push_back(pair<int, int>(1, 0));
		pAlign.push_back(pair<int, int>(1, 1));
		pAlign.push_back(pair<int, int>(1, 2));
		pAlign.push_back(pair<int, int>(2, 0));
		pAlign.push_back(pair<int, int>(2, 1));
		pAlign.push_back(pair<int, int>(2, 2));
	}
}

void Class::set_skills()
{
	if (!name.compare("Barbarian"))
	{
		//Barbarian alignment: Chaotic only
		class_skills.push_back(std::make_pair("climb", "strength"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("handle animal", "charisma"));
		class_skills.push_back(std::make_pair("intimidate", "charisma"));
		class_skills.push_back(std::make_pair("jump", "strength"));
		class_skills.push_back(std::make_pair("listen", "wisdom"));
		class_skills.push_back(std::make_pair("ride", "dexterity"));
		class_skills.push_back(std::make_pair("survival", "wisdom"));
		class_skills.push_back(std::make_pair("swim", "strength"));
	}
	if (!name.compare("Bard"))
	{
		//Bard alignment: Non-Lawful
		class_skills.push_back(std::make_pair("appraise", "intelligence"));
		class_skills.push_back(std::make_pair("balance", "dexterity"));
		class_skills.push_back(std::make_pair("bluff", "charisma"));
		class_skills.push_back(std::make_pair("climb", "strength"));
		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("decipher script", "intelligence"));
		class_skills.push_back(std::make_pair("diplomacy", "charisma"));
		class_skills.push_back(std::make_pair("disguise", "charisma"));
		class_skills.push_back(std::make_pair("escape artist", "dexterity"));
		class_skills.push_back(std::make_pair("gather information", "charisma"));
		class_skills.push_back(std::make_pair("hide", "dexterity"));
		class_skills.push_back(std::make_pair("jump", "strength"));
		class_skills.push_back(std::make_pair("knowledge arcana", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge architecture", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge dungeoneering", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge geography", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge history", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge local", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge nature", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge nobility", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge psionics", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge religion", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge planes", "intelligence"));
		class_skills.push_back(std::make_pair("listen", "wisdom"));
		class_skills.push_back(std::make_pair("move silently", "dexterity"));
		class_skills.push_back(std::make_pair("perform", "charisma"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("sense motive", "wisdom"));
		class_skills.push_back(std::make_pair("sleight of hand", "dexterity"));
		class_skills.push_back(std::make_pair("spellcraft", "intelligence"));
		class_skills.push_back(std::make_pair("swim", "strength"));
		class_skills.push_back(std::make_pair("tumble", "dexterity"));
		class_skills.push_back(std::make_pair("use magic device", "charisma"));
	}
	if (!name.compare("Cleric"))
	{
		//Cleric alignment: Dependent on deity

		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("diplomacy", "charisma"));
		class_skills.push_back(std::make_pair("heal", "wisdom"));
		class_skills.push_back(std::make_pair("knowledge arcana", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge history", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge religion", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge planes", "intelligence"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("spellcraft", "intelligence"));
	}
	if (!name.compare("Druid"))
	{
		//Druid alignment: Neutral only
		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("diplomacy", "charisma"));
		class_skills.push_back(std::make_pair("handle animal", "charisma"));
		class_skills.push_back(std::make_pair("heal", "wisdom"));
		class_skills.push_back(std::make_pair("knowledge nature", "intelligence"));
		class_skills.push_back(std::make_pair("listen", "wisdom"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("ride", "dexterity"));
		class_skills.push_back(std::make_pair("spellcraft", "intelligence"));
		class_skills.push_back(std::make_pair("spot", "wisdom"));
		class_skills.push_back(std::make_pair("survival", "wisdom"));
		class_skills.push_back(std::make_pair("swim", "strength"));
	}
	if (!name.compare("Fighter"))
	{
		//Fighter alignment: Any
		class_skills.push_back(std::make_pair("climb", "strength"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("handle animal", "charisma"));
		class_skills.push_back(std::make_pair("intimidate", "charisma"));
		class_skills.push_back(std::make_pair("jump", "strength"));
		class_skills.push_back(std::make_pair("ride", "dexterity"));
		class_skills.push_back(std::make_pair("swim", "strength"));
	}
	if (!name.compare("Monk"))
	{
		//Monk alignment: Lawful only
		class_skills.push_back(std::make_pair("balance", "dexterity"));
		class_skills.push_back(std::make_pair("climb", "strength"));
		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("diplomacy", "charisma"));
		class_skills.push_back(std::make_pair("escape artist", "dexterity"));
		class_skills.push_back(std::make_pair("heal", "wisdom"));
		class_skills.push_back(std::make_pair("knowledge nobility", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge religion", "intelligence"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("ride", "dexterity"));
		class_skills.push_back(std::make_pair("sense motive", "wisdom"));
	}
	if (!name.compare("Paladin"))
	{
		//Paladin alignment: Lawful Good only
		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("diplomacy", "charisma"));
		class_skills.push_back(std::make_pair("handle animal", "charisma"));
		class_skills.push_back(std::make_pair("hide", "dexterity"));
		class_skills.push_back(std::make_pair("jump", "strength"));
		class_skills.push_back(std::make_pair("knowledge arcana", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge religion", "intelligence"));
		class_skills.push_back(std::make_pair("listen", "wisdom"));
		class_skills.push_back(std::make_pair("move silently", "dexterity"));
		class_skills.push_back(std::make_pair("perform", "charisma"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("sense motive", "wisdom"));
		class_skills.push_back(std::make_pair("spot", "wisdom"));
		class_skills.push_back(std::make_pair("swim", "strength"));
		class_skills.push_back(std::make_pair("tumble", "dexterity"));
	}
	if (!name.compare("Ranger"))
	{
		//Ranger alignment: Any
		class_skills.push_back(std::make_pair("climb", "strength"));
		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("handle animal", "charisma"));
		class_skills.push_back(std::make_pair("heal", "wisdom"));
		class_skills.push_back(std::make_pair("hide", "dexterity"));
		class_skills.push_back(std::make_pair("jump", "strength"));
		class_skills.push_back(std::make_pair("knowledge dungeoneering", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge geography", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge nature", "intelligence"));
		class_skills.push_back(std::make_pair("listen", "wisdom"));
		class_skills.push_back(std::make_pair("move silently", "dexterity"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("ride", "dexterity"));
		class_skills.push_back(std::make_pair("search", "intelligence"));
		class_skills.push_back(std::make_pair("spot", "wisdom"));
		class_skills.push_back(std::make_pair("survival", "wisdom"));
		class_skills.push_back(std::make_pair("swim", "strength"));
		class_skills.push_back(std::make_pair("use rope", "dexterity"));
	}
	if (!name.compare("Rogue"))
	{
		//Rogue alignment: Any
		class_skills.push_back(std::make_pair("appraise", "intelligence"));
		class_skills.push_back(std::make_pair("balance", "dexterity"));
		class_skills.push_back(std::make_pair("bluff", "charisma"));
		class_skills.push_back(std::make_pair("climb", "strength"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("decipher script", "intelligence"));
		class_skills.push_back(std::make_pair("diplomacy", "charisma"));
		class_skills.push_back(std::make_pair("disable device", "intelligence"));
		class_skills.push_back(std::make_pair("disguise", "charisma"));
		class_skills.push_back(std::make_pair("escape artist", "dexterity"));
		class_skills.push_back(std::make_pair("forgery", "intelligence"));
		class_skills.push_back(std::make_pair("gather information", "charisma"));
		class_skills.push_back(std::make_pair("hide", "dexterity"));
		class_skills.push_back(std::make_pair("intimidate", "charisma"));
		class_skills.push_back(std::make_pair("jump", "strength"));
		class_skills.push_back(std::make_pair("knowledge local", "intelligence"));
		class_skills.push_back(std::make_pair("listen", "wisdom"));
		class_skills.push_back(std::make_pair("move silently", "dexterity"));
		class_skills.push_back(std::make_pair("open lock", "dexterity"));
		class_skills.push_back(std::make_pair("perform", "charisma"));
		class_skills.push_back(std::make_pair("search", "intelligence"));
		class_skills.push_back(std::make_pair("sense motive", "wisdom"));
		class_skills.push_back(std::make_pair("sleight of hand", "dexterity"));
		class_skills.push_back(std::make_pair("spot", "wisdom"));
		class_skills.push_back(std::make_pair("swim", "strength"));
		class_skills.push_back(std::make_pair("tumble", "dexterity"));
		class_skills.push_back(std::make_pair("use magic device", "charisma"));
		class_skills.push_back(std::make_pair("use rope", "dexterity"));
	}
	if (!name.compare("Sorcerer"))
	{
		//Sorcerer alignment: Any
		class_skills.push_back(std::make_pair("bluff", "charisma"));
		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge arcana", "intelligence"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("spellcraft", "intelligence"));
	}
	if (!name.compare("Wizard"))
	{
		//Wizard alignment: Any
		class_skills.push_back(std::make_pair("concentration", "constitution"));
		class_skills.push_back(std::make_pair("craft", "intelligence"));
		class_skills.push_back(std::make_pair("decipher script", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge arcana", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge architecture", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge dungeoneering", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge geography", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge history", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge local", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge nature", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge nobility", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge psionics", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge religion", "intelligence"));
		class_skills.push_back(std::make_pair("knowledge planes", "intelligence"));
		class_skills.push_back(std::make_pair("profession", "wisdom"));
		class_skills.push_back(std::make_pair("spellcraft", "intelligence"));
	}
}

// Public Functions

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
	set_skills();//Just sets the class skills, does not add ranks or anything like that.
	determine_base_attack_bonus();
	determine_number_of_attacks();
	determine_complexity();
	set_stat_distribution();
	determine_hit_die();//Just determines what die to roll for HP
	smart_stat_increase_loop(class_level);
	determine_deity();
	set_alignments();
	determine_alignment();
}

void Class::print() const
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