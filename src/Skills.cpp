#include "../headers/Skills.h"
// const unsigned int seed = time(0);
// std::mt19937_64 rng(seed);
// std::uniform_int_distribution<int> distribution(0, 44);

/**Constructor/Initializer**/
/**This constructor is improperly done, follow https://www.modernescpp.com/index.php/c-core-guidelines-constructors and re-do this later.**/
Skills::Skills()
{
  this->num_skills;
  this->num_columns;
  this->base_gain;
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  std::vector<int> class_skill_indices;
  std::vector<int> non_class_skill_indices;
  this->skills_ranks_and_bonuses;
}

int Skills::initialize_all_skills()
{
  std::ifstream file_data("data/skills_list.txt", std::ios::in);
  /**Error handling (will be moved in the future)**/
  if (!file_data.is_open())
  {
    std::cout << "File failed to open." << std::endl;
    return 1;
  }
  /**Fetch the first line, which gets the number of skills and number of columns **/
  std::string line;
  std::getline(file_data, line);
  char *dup = strdup(line.c_str());           //Duplicate the string as c_str() creates a const char*
  char *tok = std::strtok(dup, ",");          //Tokenize the duplicate string
  this->num_skills = std::stoi((std::string)tok, nullptr, 10);
  tok = std::strtok(NULL, ",");
  this->num_columns = std::stoi((std::string)tok, nullptr, 10);
  /**Assign the values for future use**/
  std::cout << "Number of skills: " << this->num_skills << std::endl;
  std::cout << "Number of cols: " << this->num_columns << std::endl;
  /**Malloc the appropriate amount of memory for future use**/
  this->skills_ranks_and_bonuses = (double *)malloc(sizeof(double) * (this->num_skills * this->num_columns));

  /**Begin reading in all lines and separating them into their respective data structures**/
  for (int i = 0; i < num_skills; i++)
  {
    std::getline(file_data, line);
    dup = strdup(line.c_str());
    tok = std::strtok(dup, ",");
    this->skill_names.push_back(tok);
    tok = std::strtok(NULL, ",");
    this->skill_ability_modifiers.push_back(tok);
    tok = std::strtok(NULL, ",");
    /**Since C++ doesn't have an inherent conversion from string to bool, we use a conditional instead**/
    if (!strcmp(tok, "True"))
    {
      this->skill_training_required.push_back(true);
    }
    else
    {
      this->skill_training_required.push_back(false);
    }
  }
  // printVector(this->skill_names);

  //Free the duplicate
  free(dup);
  //Close the file
  file_data.close();
  return 0;
}

double Skills::get_skill_cap(int level, bool is_class_skill)
{
  return (is_class_skill) ? level + 3 : (level + 3) / 2.0;
}

int Skills::determine_number_of_skill_points(int int_modifier)
{
  return std::max(1, (this->base_gain + int_modifier));
}

int Skills::determine_number_of_skill_points_batch(int level, int int_modifier)
{
  return (determine_number_of_skill_points(int_modifier) * 4) + (determine_number_of_skill_points(int_modifier) * (level - 1));
}

void Skills::print_class_skills()
{
  printElement("Skill", 30, ' ');
  printElement("Key Ability", 16, ' ');
  printElement("Skill Modifier", 13, ' ');
  printElement("Ranks", 6, ' ');
  printElement("Ability Modifier", 21, ' ');
  printElement("Misc. Modifier", 19, ' ');
  std::cout << std::endl;
  for (auto x : this->class_skill_indices)
  {
    printElement(this->skill_names.at(x), 30, ' ');
    printElement(this->skill_ability_modifiers.at(x), 16, ' ');
    printElement(get_skill_total_ranks_bonus(x), 13, ' ');
    printElement(get_skill_base_ranks_bonus(x), 5, ' ');
    printElement(get_skill_ability_modifier_bonus(x), 21, ' ');
    printElement(get_skill_miscellaneous_bonus(x), 19, ' ');
    std::cout << std::endl;
  }
}

/**Setters (outside of Constructor)**/

void Skills::set_class_skills(std::string class_name)
{
  if (class_name.empty())
  {
    return;
  }
  if (!class_name.compare("Barbarian"))
  {
    this->class_skill_indices = {3, 5, 13, 16, 17, 28, 33, 40, 41};
  }
  else if (!class_name.compare("Bard"))
  {
    this->class_skill_indices = {0, 1, 2, 3, 4, 5, 6, 7, 9, 10, 12, 15, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, 32, 35, 36, 38, 41, 42, 43};
  }
  else if (!class_name.compare("Cleric"))
  {
    this->class_skill_indices = {4, 5, 7, 14, 18, 22, 26, 27, 34, 38};
  }
  else if (!class_name.compare("Druid"))
  {
    this->class_skill_indices = {4, 5, 7, 13, 14, 24, 28, 32, 33, 38, 39, 40, 41};
  }
  else if (!class_name.compare("Fighter"))
  {
    this->class_skill_indices = {3, 5, 13, 16, 17, 33, 41};
  }
  else if (!class_name.compare("Monk"))
  {
    this->class_skill_indices = {1, 3, 4, 5, 7, 10, 14, 25, 32, 33, 35};
  }
  else if (!class_name.compare("Paladin"))
  {
    this->class_skill_indices = {4, 5, 7, 13, 15, 17, 18, 26, 28, 29, 31, 35, 39, 41, 42};
  }
  else if (!class_name.compare("Ranger"))
  {
    this->class_skill_indices = {3, 4, 5, 13, 14, 15, 17, 20, 21, 24, 28, 29, 31, 33, 34, 39, 40, 41, 44};
  }
  else if (!class_name.compare("Rogue"))
  {
    this->class_skill_indices = {0, 1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 15, 16, 17, 23, 28, 29, 30, 31, 34, 35, 36, 39, 41, 42, 43, 44};
  }
  else if (!class_name.compare("Sorcerer"))
  {
    this->class_skill_indices = {2, 4, 5, 18, 32, 38};
  }
  else if (!class_name.compare("Wizard"))
  {
    this->class_skill_indices = {4, 5, 6, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 32, 38};
  }
  else
  {
    return;
  }
}

void Skills::set_base_gain(std::string class_name)
{
  if (class_name.empty())
  {
    return;
  }
  else if (!class_name.compare("Rogue"))
  {
    this->base_gain = 8;
  }
  else if (!class_name.compare("Bard") || !class_name.compare("Ranger"))
  {
    this->base_gain = 6;
  }
  else if (!class_name.compare("Barbarian") || (!class_name.compare("Druid")) || (!class_name.compare("Monk")))
  {
    this->base_gain = 4;
  }
  else if ((!class_name.compare("Cleric")) || (!class_name.compare("Fighter")) || (!class_name.compare("Paladin")) || (!class_name.compare("Sorcerer")) || (!class_name.compare("Wizard")))
  {
    this->base_gain = 2;
  }
  else
  {
    return;
  }
}

void Skills::set_skill_ranks_and_bonuses(int row_index, int column_index, double value_to_set)
{
  if (row_index < 0 || (row_index * 4) > ((this->num_skills * this->num_columns) - 4))
  {
    return;
  }
  else if (column_index < 0 || column_index > 3)
  {
    return;
  }
  else
  {
    this->skills_ranks_and_bonuses[((row_index * 4) + column_index)] = value_to_set;
  }
}

void Skills::determine_total_skill_bonus(int row_index)
{
  if (row_index < 0 || (row_index * 4) > ((this->num_skills * this->num_columns) - 4))
  {
    return;
  }
  else
  {
     set_skill_total_ranks_bonus(row_index, array_summation(get_skill_ranks_and_bonuses(row_index), 4, 1));
  }
}

void Skills::set_skill_total_ranks_bonus(int row_index, double value_to_set){
  set_skill_ranks_and_bonuses(row_index, 0, value_to_set);
}

void Skills::set_skill_base_ranks_bonus(int row_index, double value_to_set)
{
  set_skill_ranks_and_bonuses(row_index, 1, value_to_set);
}

void Skills::set_skill_ability_modifier_bonus(int row_index, double value_to_set)
{
  set_skill_ranks_and_bonuses(row_index, 2, value_to_set);
}

void Skills::set_skill_miscellaneous_bonus(int row_index, double value_to_set)
{
  set_skill_ranks_and_bonuses(row_index, 3, value_to_set);
}

void Skills::manual_set_class_skills(std::vector<int> class_skill_indices)
{
  if (class_skill_indices.empty())
  {
    return;
  }
  if (this->class_skill_indices.empty())
  {
    this->class_skill_indices = std::move(class_skill_indices);
  }
  else
  {
    combine(this->class_skill_indices, class_skill_indices);
  }
}

void Skills::set_non_class_skills(std::vector<int> class_skill_indices, int num_skills)
{
  if (class_skill_indices.empty() || num_skills < 0)
  {
    return;
  }

  int i;
  for (i = 0; i < num_skills; i++)
  {
    if (!contains(class_skill_indices, i))
    {
      this->non_class_skill_indices.push_back(i);
    }
  }
  return;
}

/**Getters**/

std::vector<std::string> Skills::get_all_skill_names() const
{
  return this->skill_names;
}

std::string Skills::get_skill_name(int index) const
{
  std::string result;
  try
  {
    result = skill_names.at(index);
  }
  catch (const std::out_of_range &e)
  {
    result = "(null)";
  }
  return result;
}

std::vector<std::string> Skills::get_all_skill_ability_modifiers() const
{
  return skill_ability_modifiers;
}

std::string Skills::get_skill_ability_modifier(int index) const
{
  std::string result;
  try
  {
    result = skill_ability_modifiers.at(index);
  }
  catch (const std::out_of_range &e)
  {
    result = "(null)";
  }
  return result;
}

std::vector<int> Skills::get_class_skill_indices() const
{
  if (this->class_skill_indices.empty())
  {
    return {};
  }
  else
  {
    return this->class_skill_indices;
  }
}

std::vector<int> Skills::get_non_class_skill_indices() const
{
  if (this->non_class_skill_indices.empty())
  {
    return {};
  }
  else
  {
    return this->non_class_skill_indices;
  }
}

double *Skills::get_all_skill_ranks_and_bonuses()
{
  return this->skills_ranks_and_bonuses;
}

double *Skills::get_skill_ranks_and_bonuses(int row_index)
{
  double *skill_row = (double *)malloc(sizeof(double) * 4);
  int i;
  if (row_index < 0 || (row_index * 4) > ((this->num_skills * this->num_columns) - 4))
  {
    for (i = 0; i < 4; i++)
    {
      skill_row[i] = -1;
    }
    return skill_row;
  }
  for (i = 0; i < 4; i++)
  {
    skill_row[i] = this->skills_ranks_and_bonuses[((row_index * 4) + i)];
  }
  return skill_row;
}

double Skills::get_skill_total_ranks_bonus(int row_index){
  return get_skill_ranks_and_bonuses(row_index)[0];
}

double Skills::get_skill_base_ranks_bonus(int row_index)
{
  return get_skill_ranks_and_bonuses(row_index)[1];
}

double Skills::get_skill_ability_modifier_bonus(int row_index)
{
  return get_skill_ranks_and_bonuses(row_index)[2];
}

double Skills::get_skill_miscellaneous_bonus(int row_index)
{
  return get_skill_ranks_and_bonuses(row_index)[3];
}

/** Destroyers (used only for testing/debugging purposes)**/

void Skills::destroy_class_skill_indices()
{
  if (!this->class_skill_indices.empty())
  {
    this->class_skill_indices.clear();
  }
}

void Skills::destroy_non_class_skill_indices()
{
  if (!this->non_class_skill_indices.empty())
  {
    this->non_class_skill_indices.clear();
  }
}

void Skills::destroy_all_skill_ranks_and_bonuses()
{
  if (this->skills_ranks_and_bonuses != NULL)
  {
    free(this->skills_ranks_and_bonuses);
  }
}

/**Resetters (Soft Destroy) (Used only for testing/debugging purposes)**/
void Skills::reset_all_skill_ranks_and_bonuses(){
  if(get_all_skill_ranks_and_bonuses() != NULL){
    size_t array_size = sizeof(get_all_skill_ranks_and_bonuses());
    memset(get_all_skill_ranks_and_bonuses(), 0, array_size);
  }
  else{
    return;
  }
}


/**Miscellaneous/Auxillary Functions**/

void Skills::determine_ability_modifier(int skill_index, std::vector<int> ability_modifiers){
  std::string ability_modifier_name = this->skill_ability_modifiers.at(skill_index);
  int value_to_set;
  if(ability_modifiers.empty() || skill_index < 0 || skill_index > this->num_skills){
    return;
  }
  if(!ability_modifier_name.compare("strength")){
    value_to_set = ability_modifiers.at(0);
  }
  else if(!ability_modifier_name.compare("dexterity")){
    value_to_set = ability_modifiers.at(1);
}
  else if(!ability_modifier_name.compare("constitution")){
    value_to_set = ability_modifiers.at(2);
  }
  else if(!ability_modifier_name.compare("intelligence")){
    value_to_set = ability_modifiers.at(3);
  }
  else if(!ability_modifier_name.compare("wisdom")){
    value_to_set = ability_modifiers.at(4);
  }
  else if(!ability_modifier_name.compare("charisma")){
    value_to_set = ability_modifiers.at(5);
  }
  else{
    return;
  }
  set_skill_ability_modifier_bonus(skill_index,value_to_set);
}

void Skills::update_skill(double num_ranks_increase, int skill_index)
{
  if (num_ranks_increase <= 0)
  {
    return;
  }
  else
  {
    if (contains(this->non_class_skill_indices, skill_index))
    {
      num_ranks_increase = num_ranks_increase / 2.0;
    }

    else if (contains(this->class_skill_indices, skill_index))
    {
      set_skill_base_ranks_bonus(skill_index, (get_skill_base_ranks_bonus(skill_index) + num_ranks_increase));
    }
    else
    {
      return;
    }
  }
}

void Skills::update_skills(int num_levels, std::string race_name, int int_modifier)
{
  //-5 is the lowest the modifier possible in Dungeons & Dragons v3.5 as it corresponds to a score of 1.
  // However, it should be -4 since PC characters must have an INT of 3 to be sapient but whatever.
  if (num_levels < 1 || int_modifier < -4)
  {
    return;
  }
  int available_skill_points;
  for (int i = 1; i <= num_levels; i++)
  {
    available_skill_points = 0;
    /**Determine number of available skill points for the level.**/
    if (i == 1)
    {
      available_skill_points += determine_number_of_skill_points(int_modifier) * 4;
      if (!race_name.compare("Human"))
      {
        available_skill_points += 4;
      }
    }
    else
    {
      available_skill_points += determine_number_of_skill_points(int_modifier);
      if (!race_name.compare("Human"))
      {
        available_skill_points += 1;
      }
    }
    // std::cout << "Starting Skill Points for Level " << i << ": " << available_skill_points << std::endl;
    for(size_t x = 0; x < this->class_skill_indices.size(); x++){
      int skill_index = this->class_skill_indices.at(x);
      double skill_cap = (double) get_skill_cap(i,true);
      double skill_cap_gap = (skill_cap - get_skill_base_ranks_bonus(skill_index));
      skill_cap_gap = (skill_cap_gap > 0) ? skill_cap_gap : 0;
      double num_ranks_increase = std::min((double) available_skill_points,(double)rolldX(((int)skill_cap_gap) + 1)-1);
      update_skill(num_ranks_increase, skill_index);
      available_skill_points -= num_ranks_increase;
    }
    // if(available_skill_points > 0){
    //   std::cout << "Remaining Skill Points for Level " << i << ": " << available_skill_points << std::endl;
    // }
    // else{
    //   std::cout << "All Skill Points for Level " << i << " expended." << std::endl;
    // }
    // while (available_skill_points > 0)
    // {
    //   /**Determine which skill is to be raised. For testing, this will be done using a unifrom distribution**/
    //   int skill_index = this->class_skill_indices.at(rolldX(this->class_skill_indices.size())-1);
    //   bool is_class_skill = contains(this->class_skill_indices, skill_index) ? true : false;
    //   /**Determine how many skill ranks are to be purchased. For testing, it will be done as uniform.**/
    //   /**We want the minimum of (available skill points, (skill_cap - current ranks), and the roll which is from [0,skill_cap])**/
    //   double skill_cap = (double) get_skill_cap(i,is_class_skill);
    //   double num_ranks_increase = std::min(std::min((double) available_skill_points, (skill_cap - get_skill_base_ranks_bonus(skill_index))), \
    //                                       (double)rolldX(((int)skill_cap) + 1));
    //   update_skill(num_ranks_increase, skill_index);
    //   available_skill_points -= num_ranks_increase;
    // }
  }
  for(auto x : this->class_skill_indices){
    determine_total_skill_bonus(x);
  }

}
