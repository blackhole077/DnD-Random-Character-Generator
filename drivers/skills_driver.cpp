#include "../headers/Skills.h"
#include "../headers/dnd_template_functions.h"
using namespace std;

int main(){
  cout << "Hello there!" << endl;
  Skills all_skills;
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
  cout << "Number of elements allocated..." << sizeof(test_array) / sizeof(double) << endl;
  string test_class = "Rogue";
  cout << "Testing set_class_skills...\n" <<endl;
  all_skills.set_class_skills(test_class);
  if(!all_skills.get_class_skill_indices().empty()){
    cout << "Testing Succeeded\n" << endl;
  }
  cout << "Printing set_class_skills...\n" <<endl;
  printVector(all_skills.get_class_skill_indices());
  cout << endl;
  all_skills.print_class_skills();
  return 0;
}
