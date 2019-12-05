#include "../headers/Skills.h"
#include "../headers/dnd_template_functions.h"
using namespace std;

int main(){
  cout << "Hello there!" << endl;
  Skills all_skills;
  vector<string> test_classes = {"Barbarian", "Bard", "Cleric", "Druid", "Fighter", "Monk", "Paladin", "Ranger", "Rogue", "Sorcerer", "Wizard"};
  vector<string> test_races = {"Human", "Dwarf", "Elf", "Orc", "Half-Elf", "Half-Orc", "Halfling", "Gnome"};

  cout << "Testing initialize_all_skills...\n" << endl;
  int error_code = all_skills.initialize_all_skills();
  if(error_code != 0){
    cout << "Test failed...\n" << endl;
    return 1;
  }
  else{
    cout << "Test Succeeded!\n" << endl;
  }
  cout << "Testing if proper number of skills allocated...\n" << endl;
  double* test_array = all_skills.get_all_skill_ranks_and_bonuses();

  int num_passed = 0;
  int num_failed = 0;

  int destroy_num_passed = 0;
  int destroy_num_failed = 0;

  /** Test set_class_skills with all base classes **/
  for(auto x : test_classes){
    cout << "Testing set_class_skills with " << x << " class...\n" << endl;
    all_skills.set_class_skills(x);
    if(!all_skills.get_class_skill_indices().empty()){
      num_passed++;
      cout << "Printing class skills...\n" << endl;
      all_skills.print_class_skills();
      cout << endl;
    }
    else{
      cout << "set_class_skills on " << x << " class failed (vector is empty)...\n" << endl;
      num_failed++;
    }
    all_skills.destroy_class_skill_indices();
    if(all_skills.get_class_skill_indices().empty()){
      destroy_num_passed++;
    }
    else{
      destroy_num_failed++;
    }
  }

  cout << "Total Passed (set_class_skills): " << num_passed << "/" << (num_passed + num_failed) << endl;
  cout << "Total Passed (destroy_class_skill_indices): " << destroy_num_passed << "/" << (destroy_num_passed + destroy_num_failed) << endl;

  num_passed = 0;
  num_failed = 0;
  destroy_num_failed = 0;
  destroy_num_passed = 0;
  string test_class;
  string test_race;
  int num_levels;
  int int_modifier;
  vector<int> test_modifiers;
  for(int i = 0; i < 4; i++){
    test_modifiers = {(rolldX(10) - 5),(rolldX(10) - 5),(rolldX(10) - 5),(rolldX(10) - 5),(rolldX(10) - 5),(rolldX(10) - 5)};
    test_class = test_classes.at(rolldX(11)-1);
    test_race = test_races.at(rolldX(7)-1);
    num_levels = rolldX(20);
    int_modifier = test_modifiers.at(3);
    cout << "Testing overall program using RACE:" << test_race << " CLASS: "<< test_class << " LEVEL: " << num_levels << endl;
    cout << "Using modifiers: <";
    printVector(test_modifiers);
    cout << ">" << endl;
    all_skills.set_base_gain(test_class);
    all_skills.set_class_skills(test_class);
    for (int x = 0; x < 45; x++){
      all_skills.determine_ability_modifier(x, test_modifiers);
    }
    all_skills.update_skills(num_levels, test_race, int_modifier);
    all_skills.print_class_skills();
    all_skills.destroy_class_skill_indices();
    all_skills.reset_all_skill_ranks_and_bonuses();
  }
  return 0;
}
