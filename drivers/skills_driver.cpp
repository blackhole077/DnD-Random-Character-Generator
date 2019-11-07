#include "../headers/Skills.h"
#include "../headers/dnd_template_functions.h"
using namespace std;

int main(){
  cout << "Hello there!" << endl;
  Skills all_skills;
  int error_code = all_skills.initialize_all_skills();

  return 0;
}
