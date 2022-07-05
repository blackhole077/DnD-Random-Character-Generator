#ifndef CLASS_H
#define CLASS_H
#include "roll.h"
#include <iostream>
#include <map>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>

class Class
{
private:
  // The name of the class.
  std::string name;
  // The complexity of the class that is chosen. Determines how long training for the class would take (and by proxy the age of the character).
  int complexity;
  // How many levels the character has in the class. Necessary bookkeeping for multi-classing.
  int class_level;
  int class_hit_die; //The Dice you roll for hp
  // The 'good stats' (i.e., the stats that make your class functional and fun) that should be prioritized when allocating stats and stat increases.
  std::vector<int> good_stats;
  // The 'bad stats' (i.e., the stats that are more luxury or just not needed) that should not be prioritized when allocating stats and stat increases.
  std::vector<int> bad_stats;
  // The player's alignment. Necessary for making sure there is no contradiction in alignment-class selections.
  std::vector<std::pair<int, int>> player_alignment;
  // The skills that the class can put skill points into for full value
  std::vector<std::pair<std::string, std::string>> class_skills;
  // The player's alignment (as a string)
  std::string alignment;
  // The deity that the player worships.
  std::string deity;
  // The player's base attack bonus for their first attack.
  int base_attack_bonus;
  // The number of attacks the player has. Subsequent attacks essentially take a cumulative -5 to hit.
  int number_of_attacks;
  // How many skill points the class gains by default.
  int skill_rank_gain;
  void determine_complexity();
  void determine_hit_die();
  void determine_alignment();
  void determine_deity();
  void determine_cleric_patronage();
  void determine_base_attack_bonus();
  void determine_number_of_attacks();
  void set_stat_distribution();
  void smart_stat_increase_loop(int level);
  void smart_stat_increase(int step);
  void set_alignments();

public:
  Class(); //Constructor with no args
  /*
	How I'm implementing the alignment system works like this:
	The first number corresponds to the Law <-> Chaos axis, with 0, 1, and 2 representing L, N, and C respectively.
	The second number corresponds to the Good <-> Evil axis, with 0, 1, and 2 representing G, N, and E respectively.
	This creates a set of "co-ordinates" with pair<int,int>(1,1) being True Neutral (and for the purpose of alignment stuff the center).
	*/

  void create_character();

  const int get_skill_rank_gain();
  void set_skill_rank_gain(int x);
  const int get_complexity();    // Getter
  const int get_class_level();   // Getter
  const int get_class_hit_die(); // Getter
  const int get_base_attack_bonus();
  const int get_number_of_attacks();
  const std::string get_name();
  const std::vector<int> get_good_stats();
  const std::vector<int> get_bad_stats();

  void set_complexity(int x);    // Setter
  void set_class_level(int x);   // Setter
  void set_class_hit_die(int x); // Setter
  void set_base_attack_bonus(int x);
  void set_number_of_attacks(int x);
  void set_name(std::string x);
  const void print_class_information();
  void set_good_stats(std::vector<int> vector);
  void set_bad_stats(std::vector<int> vector);
};

#endif