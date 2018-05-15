#ifndef RACE_H
#define RACE_H
#include <string>
#include <vector>
#include <random>

class Race{
private:
    std::string name;
    int gender;
    int base_age;
    int base_height;
    int base_weight;
    std::vector<int> stats_mod;
public:
    Race();
    //Setters
    void set_race_name(std::string race_name);
    void set_age(int x);
    void set_height(int x);
    void set_weight(int x);
    void set_gender(int gender);
    //Getters
    std::string get_race_name() const;
    std::vector<int> get_stats_modifier() const;
    int get_gender() const;
    int get_age() const;
    int get_height() const;
    int get_weight() const;
    //Misc
    void generate_stats_modifier();
    void determine_race();
    void determine_age(int complexity);
    void determine_gender();
    void determine_height_weight();
    void print_race_info();
};

#endif