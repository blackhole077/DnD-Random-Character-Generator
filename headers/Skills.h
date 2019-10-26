#ifndef SKILLS_H
#define SKILLS_H
#include "Race.h"
#include "Stats.h"
#include <vector>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

class Skills{
private:
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  /**4 columns: Total Skill Rank, Base Ranks (The player directly modifies this), Ability Modifier, Miscellaneous Modifiers (The player indirectly modifies this)**/
  int skills_ranks_and_bonuses[50][4];
  /** Initialization functions kept private since this iteration assumes that Skills is static.**/
  int initialze_skill_names(std::vector<std::string> *skill_names);
  int initialze_skill_ability_modifiers(std::vector<std::string> *skill_ability_modifiers);
  std::vector<bool> initialize_skill_training_required(std::vector<bool> *skill_training_required);

  int initialze_skill_ranks_and_bonuses(int skills_ranks_and_bonuses[][4]);
public:
  Skills();
  int initialize_all_skills(Skills skill);

  //Getters
  std::vector<std::string> get_all_skill_names() const;
  std::string get_skill_name(int index) const;
  std::vector<std::string> get_all_skill_ability_modifiers() const;
  std::string get_skill_ability_modifier(int index) const;

  int[][4] get_all_skill_ranks_and_bonuses() const;
  int* get_skill_ranks_and_bonuses(int index) const;

};

#endif
