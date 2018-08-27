#ifndef FEATS_H
#define FEATS_H
#include <map>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <cstring>

class Feats
{
private:
    //VARIABLES
    std::string name;
    std::string description;
    std::string special_notes;
    bool multiple_allowed;
    std::vector<std::pair<std::string,int>> required_stats;
    std::vector<Feats> required_feats;
    std::vector<std::string> required_classes;//Maybe make this <string, int> for class and class level
    int required_bab;
    //SETTERS
    void set_name(std::string arg_name);
    void set_description(std::string arg_description);
    void set_special_notes(std::string arg_special_notes);
    void set_multiple_allowed(bool arg_multiple_allowed);
    void set_required_stats(std::vector<std::pair<std::string,int>> arg_required_stats);
    void set_required_feats(std::vector<Feats> arg_required_feats);
    void set_required_classes(std::vector<std::string>> arg_required_classes);
    void set_required_base_attack_bonus(int arg_bab);

public: 
    //CONSTRUCTOR
    Feats(std::string arg_name, std::string arg_description, std::string arg_special_notes="",bool is_multiple_allowed = false, const std::vector<std::pair<std::string,int>> arg_required_stats = {}, const std::vector<Feats> arg_required_feats, const std::vector<string> arg_required_classes, int arg_required_base_attack_bonus = 0);
    //GETTERS
    std::string get_name() const;
    std::string get_description() const;
    std::string get_special_notes() const;
    bool is_multiple_allowed() const;
    std::vector<std::pair<std::string,int>> get_required_stats() const;
    std::vector<Feats> get_required_feats() const;
    std::vector<std::string> get_required_classes() const;
    int get_required_base_attack_bonus() const; 
    std::map<std::string,Feats> fetch_all_feats();//Name,Feat pair
    /**
     * Steps for fetching all feats:
     * 1. Deserialize JSON representation of data.
     * 2. Navigate the resulting data structure
     * 3. Do a for-each loop and create a feat object for each one, then add it to a map
     * 4. Use map for creating character
     * 5. Remove map once feat selection is done (I guess)
     **/
}