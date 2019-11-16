#include "../headers/Skills.h"

Skills::Skills(){
  int num_skills = 0;
  int num_columns = 0;
  std::vector<std::string> skill_names;
  std::vector<std::string> skill_ability_modifiers;
  std::vector<bool> skill_training_required;
  std::vector<int> class_skill_indices;
  std::vector<int> non_class_skill_indices;
  double *skills_ranks_and_bonuses = NULL;
}

/**Constructor/Initializer**/

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
  this->skills_ranks_and_bonuses = (double*) malloc(sizeof(double) * (num_skills * num_columns));
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

/**Miscellaneous/Auxillary Functions**/

double get_skill_cap(int level, bool is_class_skill){
	return (is_class_skill) ? level+3 : (level+3)/2.0;
}

int determine_number_of_skill_points(int level, int base_gain, int int_modifier){
	return ((base_gain+int_modifier)*4)+((base_gain+int_modifier)*(level-1));
}

/**Setters (outside of Constructor)**/

void Skills::set_class_skills(std::string class_name){
  if(class_name.empty()){
    return;
  }
  if(!class_name.compare("Barbarian")){
    this->class_skill_indices = {3,5,13,16,17,28,33,40,41};
  }
  else if(!class_name.compare("Bard")){
    this->class_skill_indices = {0,1,2,3,4,5,6,7,9,10,12,15,17,18,19,20,21,22,23,24,25,26,27,28,29,31,32,35,36,38,41,42,43};
  }
  else if(!class_name.compare("Cleric")){
    this->class_skill_indices = {4,5,7,14,18,22,26,27,34,38};
  }
  else if(!class_name.compare("Druid")){
    this->class_skill_indices = {4,5,7,13,14,24,28,32,33,38,39,40,41};
  }
  else if(!class_name.compare("Fighter")){
    this->class_skill_indices = {3,5,13,16,17,33,41};
  }
  else if(!class_name.compare("Monk")){
    this->class_skill_indices = {1,3,4,5,7,10,14,25,32,33,35};
  }
  else if(!class_name.compare("Paladin")){
    this->class_skill_indices = {4,5,7,13,15,17,18,26,28,29,31,35,39,41,42};
  }
  else if(!class_name.compare("Ranger")){
        this->class_skill_indices = {3,4,5,13,14,15,17,20,21,24,28,29,31,33,34,39,40,41,44};
  }
  else if(!class_name.compare("Rogue")){
    this->class_skill_indices = {0,1,2,3,5,6,7,8,9,10,11,12,15,16,17,23,28,29,30,31,34,35,36,39,41,42,43,44};
  }
  else if(!class_name.compare("Sorcerer")){
    this->class_skill_indices = {2,4,5,18,32,38};
  }
  else if(!class_name.compare("Wizard")){
    this->class_skill_indices = {4,5,6,18,19,20,21,22,23,24,25,26,27,32,38};
  }
  else{
    return;
  }

}

void Skills::manual_set_class_skills(std::vector<int> class_skill_indices){
  this->class_skill_indices = std::move(class_skill_indices);
}

void Skills::set_non_class_skills(std::vector<int> class_skill_indices, int num_skills){
  if(class_skill_indices.empty() || num_skills < 0){
    return;
  }

  int i;
  for(i = 0; i < num_skills; i++){
    if(!contains(class_skill_indices, i)){
      this->non_class_skill_indices.push_back(i);
    }
  }
  return;
}

/**Getters**/

std::vector<std::string> Skills::get_all_skill_names() const{
  return skill_names;
}

std::string Skills::get_skill_name(int index) const{
  return skill_names.at(index);
}

std::vector<std::string> Skills::get_all_skill_ability_modifiers() const{
  return skill_ability_modifiers;
}

std::string Skills::get_skill_ability_modifier(int index) const{
  return skill_ability_modifiers.at(index);
}

double* Skills::get_all_skill_ranks_and_bonuses() const{
  return skills_ranks_and_bonuses;
}

double* Skills::get_skill_ranks_and_bonuses(int row_index){
  if(row_index < 0 || (row_index*4) > (sizeof(skills_ranks_and_bonuses) / sizeof(skills_ranks_and_bonuses[0]))/4){
    return NULL;
  }
  double *skill_row = malloc(sizeof(double) * 4);
  int i;
  for(i=0;i<4;i++){
    skill_row[i] = skills_ranks_and_bonuses[((row_index*4)+i)];
  }
  return skill_row;
}
