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
  std::ifstream file_data ("data/skills_list.txt", std::ios::in);
  /**Error handling (will be moved in the future)**/
  if(!file_data.is_open()){
    std::cout << "File failed to open." << std::endl;
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
  /**Malloc the appropriate amount of memory for future use**/
  this->skills_ranks_and_bonuses = (int*) malloc(sizeof(int) * (num_skills * num_columns));
  /**Begin reading in all lines and separating them into their respective data structures**/
  for(int i = 0; i < num_skills; i++){
    std::getline(file_data,line);
    dup = strdup(line.c_str());
    tok = std::strtok(dup,",");
    this->skill_names.push_back(tok);
    tok=std::strtok(NULL,",");
    this->skill_ability_modifiers.push_back(tok);
    tok=std::strtok(NULL,",");
    /**Since C++ doesn't have an inherent conversion from string to bool, we use a conditional instead**/
    if(!strcmp(tok,"True")){
      this->skill_training_required.push_back(true);
    }
    else{
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

double get_skill_cap(int level, bool is_class_skill) const{
	return (is_class_skill) ? level+3 : (level+3)/2.0;
}

int determine_number_of_skill_points(int level, int base_gain, int int_modifier){
	return ((base_gain+int_modifier)*4)+((base_gain+int_modifier)*(level-1));
}

std::vector<std::string> get_all_skill_names() const{
  return skill_names;
}
std::string get_skill_name(int index) const{
  return skill_names.at(index);
}

std::vector<std::string> get_all_skill_ability_modifiers() const{
  return skill_ability_modifiers;
}

std::string get_skill_ability_modifier(int index) const{
  return skill_ability_modifiers.at(index);
}

int *get_all_skill_ranks_and_bonuses() const{
  return skills_ranks_and_bonuses;
}

int* get_skill_ranks_and_bonuses(int row_index){
  if(row_index < 0 || (row_index*4) > (sizeof(skills_ranks_and_bonuses) / sizeof(skills_ranks_and_bonuses[0]))/4){
    return NULL;
  }
  int *skill_row = malloc(sizeof(int) * 4);
  int i;
  for(i=0;i<4;i++){
    skill_row[i] = skills_ranks_and_bonuses[((row_index*4)+i)];
  }
  return skill_row;
}
