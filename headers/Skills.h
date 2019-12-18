#ifndef SKILLS_H
#define SKILLS_H
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include "../headers/dnd_template_functions.h"

class Skills{
private:
  int num_skills;
  int num_columns;
  int base_gain;
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  std::vector<int> class_skill_indices;
  std::vector<int> non_class_skill_indices;

  /**45 skills with 4 columns:
   * [0] Total Skill Modifier, [1] Base Ranks (The player directly modifies this),
   * [2] Ability Modifier, [3] Miscellaneous Modifiers (The player indirectly modifies this)
   *
   * For simplicity, I'll change this to be a 1-D array containing (num_skills * num_cols) elements
   * (i.e. 45*4 = 180 elements). Also, I'll just have the constructor malloc the memory for the
   * array instead of making it static to avoid potential maintenance issues.
   **/
  double *skills_ranks_and_bonuses;

  /** Function that is called during control loop. This adds the ranks to a given skill
   *  (noted by skill_index), assuming that the number of ranks to increase by is a positive
   *  non-zero value and that the skill_index called is correct. If either of these does not hold,
   *  then nothing occurs. This may cause issues if there is no handling for no ranks being placed
   *  in the control loop.
   **/
  void update_skill(double num_ranks_increase, int skill_index);

  /** This is the general function (that will be private) which modifies the given entry in
   *  the skills_ranks_and_bonuses array to the value_to_set. If the row_index or column_index
   *  are not valid, then nothing will occur. This function will be called by the other three
   *  functions, which modify a given column, that are public.
   **/
  void set_skill_ranks_and_bonuses(int row_index, int column_index, double value_to_set);

  void determine_total_skill_bonus(int row_index);

public:
  Skills();

  /** Initializes a static instance of ALL skills available in the base version of
   *  Dungeons & Dragons v3.5. As it assumes a static instance, the assumption is 44 skills
   *  (Knowledge is expanded to be 9 separate skills) and 4 columns to represent ranks and
   *  their various modifiers.
   **/
  int initialize_all_skills();

  /** If it's a class skill it's character level + 3.
   *  If not it's 1/2 (no rounding) of character level + 3.
   *  Important note, skills CAN increment in 1/2 ranks. However,  any 1/2 rank has no bearing on
   *  the skill it's tied to. Thus, 3.5 ranks in a skill means only +3 is used.
   **/
  double get_skill_cap(int level, bool is_class_skill);

 /*Print out all class skills*/
  void print_class_skills();

  /*
   Given a class name, initialize the class skills associated with
   said class. This will not populate the vector if the name provided
   is not valid.
  */
  void set_class_skills(std::string class_name);

 /** Given a class name, initialize the base rate that skill points are gained per level.
  *  This calculation does not accont for changes in the Intelligence (INT) modifier, so this must
  *  be calculated separately from this function. If the class_name is not valid, then a value of 0
  *  is returned.
  **/
 void set_base_gain(std::string class_name);
  /*
   Given a vector of class skill indices, copy the vector over to
   the Skils struct. This will fail if the input is invalid.
  */
  void manual_set_class_skills(std::vector<int> class_skill_indices);

  /*
   Given a vector of class skill indices and the number of skills total,
   create a vector of all non-class skills (essentially the complement).
   This will not populate if the vector is empty or if the number of skills
   is below 0.
  */
  void set_non_class_skills(std::vector<int> class_skill_indices, int num_skills);

  /** Similar to determine_number_of_skill_points_batch, but for a single level.
   *  This would be used in lieu of the batch function simply because it will be
   *  better equipped for dealing with changes in the intelligence score that affect
   *  the intelligence modifier.
   **/
  int determine_number_of_skill_points(int int_modifier);

  /**Get the number of skill points a character has available to them (all at once).
     This does not assume anything about race (as Human does get extra)
     to avoid complexity. Furthermore, this does not retroactively apply
     additional skill points that would be gained if a character's INT
     modifier increases.
  **/
  int determine_number_of_skill_points_batch(int level, int int_modifier);



  //Setters
  void set_skill_total_ranks_bonus(int row_index, double value_to_set);
  void set_skill_base_ranks_bonus(int row_index, double value_to_set);
  void set_skill_ability_modifier_bonus(int row_index, double value_to_set);
  void set_skill_miscellaneous_bonus(int row_index, double value_to_set);

  //Getters
  std::vector<std::string> get_all_skill_names() const;
  std::string get_skill_name(int index) const;
  std::vector<std::string> get_all_skill_ability_modifiers() const;
  std::string get_skill_ability_modifier(int index) const;
  std::vector<int> get_class_skill_indices() const;
  std::vector<int> get_non_class_skill_indices() const;

  double *get_all_skill_ranks_and_bonuses();

  /**Return the skill ranks and bonuses for a specific skill.
     Because of the design as a 1-D array version of what is
     effectively a 2-D array, this function has to return a
     range from a given index. The parameter will assume the
     2-D structure, meaning if you want the 3rd skill, then
     the parameter should be 3, instead of 12.**/
  double* get_skill_ranks_and_bonuses(int row_index);
  double get_skill_total_ranks_bonus(int row_index);
  double get_skill_base_ranks_bonus(int row_index);
  double get_skill_ability_modifier_bonus(int row_index);
  double get_skill_miscellaneous_bonus(int row_index);
  /**
   * Destroy the contents of the class_skill_indices vector.
   **/
  void destroy_class_skill_indices();
  /**
   * Destroy the contents of the non_class_skill_indices vector.
   **/
  void destroy_non_class_skill_indices();
  /**
   * Destroy the all_skill_ranks_and_bonuses array
   **/
  void destroy_all_skill_ranks_and_bonuses();
  /**
   * Reset the all_skill_ranks_and_bonuses by setting the contents to zero
   **/
  void reset_all_skill_ranks_and_bonuses();

/**Steps for leveling up skills per level
  0. Determine if character will spend a skill point to learn a langauge
    0a. If yes, call a different function and then come back to this with 1 less skill point
    0b. If not, continue;
  1. Determine if the skill chosen is going to be a class skill or not (binomial distribution)
     The number of ranks placed either way is determined by a Poisson distribution, with the
     lambda value (expected number of occurrences) being the median of [0, min((skill_cap - current_skill_level),0)].
     Keep in mind skill_cap is halved for non-class skills.
    1a. If a non-class skill is chosen, then first check if any ranks are placed (binomial distribution; 0.2 success)
        If zero is chosen, then return to step 1.
    ALTERNATE METHOD:
      1. Change the Poisson Distribution to have a lambda value of median(0,skill_cap) or median(0,(skill_cap)/2)
      2. Select a skill via weighted distribution
      3. Apply ranks equal to min((skill_cap - current_skill_level), ranks_to_apply) and decrement by same amount.
**/


  /** This is the main control loop that controls the skill-up process from level 1 to num_levels.
   *  This function also accounts for if the character is human or not, and adjusts the points
   *  accordingly (+4 at level 1, +1 per level on top of the number determined).
   *
   *  First, it determines how many skill ranks are going to be bought (this number will be 1/2)
   *  for non-class skills. Then, it will determine what skill is going to be raised
   *  (90/10 class skill v. non-class skill) with a weighted distribution
   *  (uniform for testing) to detemrine index.
   *
   **/
  void update_skills(int num_levels, std::string race_name, int int_modifier);

  /**
   * Given a skill_index and a vector of the ability_modifiers, determine the appropriate
   * ability modifier to apply to a skill, and set the ability modifier column in the
   * all_skills_ranks_and_bonuses to the value.
   **/
  void determine_ability_modifier(int skill_index, std::vector<int> ability_modifiers);

};

#endif
