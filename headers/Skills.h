#ifndef SKILLS_H
#define SKILLS_H
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../headers/dnd_template_functions.h"

class Skills{
private:
  int num_skills;
  int num_columns;
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  std::vector<int> class_skill_indices;
  std::vector<int> non_class_skill_indices;
  /**45 skills with 4 columns: Total Skill Rank, Base Ranks (The player directly modifies this), Ability Modifier, Miscellaneous Modifiers (The player indirectly modifies this)**/
  /**For simplicity, I'll change this to be a 1-D array containing (num_skills * num_cols) elements (i.e. 44*4 = 176 elements).
     Also, I'll just have the constructor malloc the memory for the array instead of making it static to avoid potential maintenance issues.**/
  // int skills_ranks_and_bonuses[45][4];
  double *skills_ranks_and_bonuses;
  /** Initialization functions kept private since this iteration assumes that Skills is static.**/
  int initialze_skill_names(std::vector<std::string> *skill_names);
  int initialze_skill_ability_modifiers(std::vector<std::string> *skill_ability_modifiers);
  std::vector<bool> initialize_skill_training_required(std::vector<bool> *skill_training_required);
  int initialze_skill_ranks_and_bonuses(int *skills_ranks_and_bonuses);
public:
  Skills();

  /**Initializes a static instance of ALL skills available in the base version of Dungeons & Dragons v3.5
     As it assumes a static instance, the assumption is 44 skills (Knowledge is expanded to be 9 separate skills)
     and 4 columns to represent ranks and their various modifiers.**/
  int initialize_all_skills();

  /*
  If it's a class skill it's character level + 3
  if not it's 1/2 (no rounding) of character level + 3.
  Important note, skills CAN increment in 1/2 ranks. However,
  any 1/2 rank has no bearing on the skill it's tied to.
  Thus, 3.5 ranks in a skill means only +3 is used.
  */
  double get_skill_cap(int level, bool is_class_skill);
  void print_class_skills();

  void set_class_skills(std::string class_name);

  void manual_set_class_skills(std::vector<int> class_skill_indices);
  void set_non_class_skills(std::vector<int> class_skill_indices, int num_skills);

  /**
  Get the number of skill points a character has available to them.
  This does not assume anything about race (as Human does get extra)
  to avoid complexity. Furthermore, this does not retroactively apply
  additional skill points that would be gained if a character's INT
  modifier increases.
  **/
  int determine_number_of_skill_points(int level, int base_gain, int int_modifier);

  //Getters
  std::vector<std::string> get_all_skill_names() const;
  std::string get_skill_name(int index) const;
  std::vector<std::string> get_all_skill_ability_modifiers() const;
  std::string get_skill_ability_modifier(int index) const;
  std::vector<int> get_class_skill_indices() const;
  std::vector<int> get_non_class_skill_indices() const;

  double *get_all_skill_ranks_and_bonuses() const;

  /**Return the skill ranks and bonuses for a specific skill.
     Because of the design as a 1-D array version of what is
     effectively a 2-D array, this function has to return a
     range from a given index. The parameter will assume the
     2-D structure, meaning if you want the 3rd skill, then
     the parameter should be 3, instead of 12.**/
  double* get_skill_ranks_and_bonuses(int row_index);

};

#endif
