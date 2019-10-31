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
  // this->num_skills = 45;
  // this->num_cols = 4;
  this->skills_ranks_and_bonuses = malloc(sizeof(int) * (num_skills * num_cols));
  ifstream file_data;
  file_data.open("..\\data\\skills_list.txt");
  /**Fetch the first line, which gets the number of skills and number of columns **/
  std::string line;
  std::string line_chunk;
  getline(file_data, line);
  this->num_skills = stoi(getline(line, line_chunk, ","),nullptr,10);
  this->num_cols = stoi(getline(line, line_chunk, ","),nullptr,10);
  std::cout << "Number of skills: " << this->num_skills << endl;
  std::cout << "Number of cols: " << this->num_skills << endl;

  file_data.close();
  return 0;
}
