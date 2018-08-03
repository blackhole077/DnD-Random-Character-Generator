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
  std::string name;
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
  void determine_complexity();
  void determine_hit_die();
  void determine_alignment();
  void determine_deity();
  void determine_cleric_patronage();
  void determine_base_attack_bonus();
  void determine_number_of_attacks();
  void set_stat_distribution();
  void smart_stat_increase(int step);
  void set_alignments();
  void set_skills();

public:
  Class(); //Constructor with no args
  /*
	How I'm implementing the alignment system works like this:
	The first number corresponds to the Law <-> Chaos axis, with 0, 1, and 2 representing L, N, and C respectively.
	The second number corresponds to the Good <-> Evil axis, with 0, 1, and 2 representing G, N, and E respectively.
	This creates a set of "co-ordinates" with pair<int,int>(1,1) being True Neutral (and for the purpose of alignment stuff the center).
	*/

  void create_character();

  int get_skill_rank_gain() const;
  void set_skill_rank_gain(int x);
  int get_complexity() const;    // Getter
  int get_class_level() const;   // Getter
  int get_class_hit_die() const; // Getter
  int get_base_attack_bonus() const;
  int get_number_of_attacks() const;
  std::string get_name() const;
  std::vector<int> get_good_stats() const;
  std::vector<int> get_bad_stats() const;

  void set_complexity(int x);    // Setter
  void set_class_level(int x);   // Setter
  void set_class_hit_die(int x); // Setter
  void set_base_attack_bonus(int x);
  void set_number_of_attacks(int x);
  void set_name(std::string x);
  void print() const;
  void set_good_stats(std::vector<int> vector);
  void set_bad_stats(std::vector<int> vector);
};

#endif