#include "..\headers\Skills.h"
#include "..\headers\dnd_template_functions.h"

Skills::Skills(){
  int num_skills;
  int num_cols;
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  int *skills_ranks_and_bonuses;
}

int Skills::initialize_all_skills(){
  this->num_skills = 45;
  this->num_cols = 4;
  this->skills_ranks_and_bonuses = malloc(sizeof(int) * (num_skills * num_cols));
  ifstream file_data;
  file_data.open("..\\data\\skills_list.txt");

  return 0;
}
