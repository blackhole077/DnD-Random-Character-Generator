#include "../headers/Skills.h"
#include "../headers/dnd_template_functions.h"
Skills::Skills(){
  int num_skills;
  int num_columns;
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  int *skills_ranks_and_bonuses;
}

int Skills::initialize_all_skills(){
  // this->num_skills = 45;
  // this->num_cols = 4;
  this->skills_ranks_and_bonuses = (int*) malloc(sizeof(int) * (num_skills * num_columns));
  std::ifstream file_data ("data/skills_list.txt", std::ios::in);
  if(!file_data.is_open()){
    std::cout << "failure to open file. ending." << std::endl;
    return 1;
  }
  /**Fetch the first line, which gets the number of skills and number of columns **/
  std::string line;
  std::getline(file_data, line);
  std::cout << "Line: " << line << std::endl; //Present for debuging purposes
  char *dup = strdup(line.c_str());//Duplicate the string as c_str() creates a const char*
  char *tok = std::strtok(dup,",");//Tokenize the duplicate string
  this->num_skills = std::stoi((std::string)tok,nullptr,10);
  tok = std::strtok(NULL,",");
  this->num_columns = std::stoi((std::string)tok,nullptr,10);
  /**Assign the values for future use**/
  std::cout << "Number of skills: " << this->num_skills << std::endl;
  std::cout << "Number of cols: " << this->num_columns << std::endl;
  //Free the duplicate
  free(dup);
  //Close the file
  file_data.close();
  return 0;
}
