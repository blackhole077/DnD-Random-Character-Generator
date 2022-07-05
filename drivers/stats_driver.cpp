#include "..\headers\Stats.h"
#include "..\headers\Class.h"
#include "..\headers\dnd_template_functions.h"
using namespace std;
int main()
{
    cout << "Hello there!" << endl;
    Stats stat_list;
    Class selected_class;
    vector<int> prefStats;
    std::vector<int> badStats;
    std::map<int, int> statsMap;
    // int good_stats[3] = {1, 2, 3};
    // int bad_stats[3] = {4, 5, 6};
    std::vector<int> rolled_stats = {cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll()};//Sort this from least to greatest then split into two arrays
    std::sort(std::begin(rolled_stats), std::end(rolled_stats));
    std::size_t const halfsies = rolled_stats.size() / 2;
    cout << "We've got halvsies!" << endl;
    std::vector<int> bad_stats(rolled_stats.begin(), rolled_stats.begin()+halfsies);
    std::vector<int> good_stats(rolled_stats.begin()+halfsies,rolled_stats.end());
    stat_list.set_bad_stats(bad_stats);
    stat_list.set_good_stats(good_stats);
    cout << "Bad Stats" <<endl;
        for(auto i: bad_stats){
        cout << i << endl;
    }
        cout << "Bad Stats" <<endl;
        for(auto i: stat_list.get_bad_stats()){
        cout << i << endl;
    }

    cout << "Good Stats" << endl;
        for(auto i: good_stats){
        cout << i << endl;
    }
    cout << "Good Stats" << endl;
        for(auto i: stat_list.get_good_stats()){
        cout << i << endl;
    }

    stat_list.set_bad_stats(bad_stats);
    //Handle allocation of bad stats
    selected_class.create_character();
    statsMap = smart_stat_distribution(selected_class.get_bad_stats(),stat_list.get_bad_stats(),selected_class.get_good_stats(),stat_list.get_good_stats());
    cout << "We're gonna print now!" << endl;
    for(auto i: statsMap){
        cout << i.first << "," << i.second << endl;
    }
    stat_list.set_base_strength(statsMap.at(1));
    stat_list.set_base_dexterity(statsMap.at(2));
    stat_list.set_base_constitution(statsMap.at(3));
    stat_list.set_base_intelligence(statsMap.at(4));
    stat_list.set_base_wisdom(statsMap.at(5));
    stat_list.set_base_charisma(statsMap.at(6));
    cout << "Printing now!!!" <<endl;
    stat_list.printStats();
    system("pause");
    return 0;
}