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
    std::vector<std::string> required_deities;
    std::vector<std::string> required_alignments;
    int required_bab;
    //SETTERS
    void set_name(std::string arg_name);
    void set_description(std::string arg_description);
    void set_special_notes(std::string arg_special_notes);
    void set_multiple_allowed(bool arg_multiple_allowed);
    void set_required_stats(std::vector<std::pair<std::string,int>> arg_required_stats);
    void set_required_feats(std::vector<Feats> arg_required_feats);
    void set_required_classes(std::vector<std::string>> arg_required_classes);
    void set_required_deities(std::vector<std::string> arg_required_deities);
    void set_required_alignments(std::vector<std::string> arg_required_alignments);
    void set_required_base_attack_bonus(int arg_bab);

public: 
    //CONSTRUCTOR (NOARG)
    Feats();
    //GETTERS
    std::string get_name() const;
    std::string get_description() const;
    std::string get_special_notes() const;
    bool is_multiple_allowed() const;
    std::vector<std::pair<std::string,int>> get_required_stats() const;
    std::vector<Feats> get_required_feats() const;
    std::vector<std::string> get_required_classes() const;
    std::vector<std::string> get_required_deities() const;
    std::vector<std::string> get_required_alignments() const;
    int get_required_base_attack_bonus() const; 
}