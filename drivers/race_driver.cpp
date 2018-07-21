#include "..\headers\Race.h"
#include "..\headers\roll.h"

using namespace std;

int main()
{
    Race race; 
    race.determine_race();
    race.determine_age(2);
    race.determine_gender();
    race.determine_height_weight();
    race.print_race_info();
    system("pause");
    return 0;
}