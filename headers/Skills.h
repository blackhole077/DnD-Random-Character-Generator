#ifndef SKILLS_H
#define SKILLS_H
#include "Race.h"
#include "Stats.h"
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Skills{
private:
  int num_skills;
  int num_columns;
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  /**45 skills with 4 columns: Total Skill Rank, Base Ranks (The player directly modifies this), Ability Modifier, Miscellaneous Modifiers (The player indirectly modifies this)**/
  /**For simplicity, I'll change this to be a 1-D array containing (num_skills * num_cols) elements (i.e. 45*4 = 180 elements).
     Also, I'll just have the constructor malloc the memory for the array instead of making it static to avoid potential maintenance issues.**/
  // int skills_ranks_and_bonuses[45][4];
  int *skills_ranks_and_bonuses;
  /** Initialization functions kept private since this iteration assumes that Skills is static.**/
  int initialze_skill_names(std::vector<std::string> *skill_names);
  int initialze_skill_ability_modifiers(std::vector<std::string> *skill_ability_modifiers);
  std::vector<bool> initialize_skill_training_required(std::vector<bool> *skill_training_required);
  int initialze_skill_ranks_and_bonuses(int *skills_ranks_and_bonuses);
public:
  Skills();
  int initialize_all_skills(Skills skill);

  //Getters
  std::vector<std::string> get_all_skill_names() const;
  std::string get_skill_name(int index) const;
  std::vector<std::string> get_all_skill_ability_modifiers() const;
  std::string get_skill_ability_modifier(int index) const;

  int *get_all_skill_ranks_and_bonuses() const;
  int* get_skill_ranks_and_bonuses(int index) const;

};

#endif
