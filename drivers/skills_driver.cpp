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
  
  return 0;
}
