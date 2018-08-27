#include "..\headers\Feats.h"
using namespace std;

Feats::Feats(std::string arg_name, std::string arg_description, std::string arg_special_notes="",bool is_multiple_allowed = false, const std::vector<std::pair<std::string,int>> arg_required_stats = {}, const std::vector<Feats> arg_required_feats, const std::vector<std::string> arg_required_classes, int arg_required_base_attack_bonus = 0){
    std::string name = arg_name;
    std::string description = arg_description;
    std::string special_notes = arg_special_notes;
    bool multiple_allowed = is_multiple_allowed;
    std::vector<std::pair<std::string,int>> required_stats(arg_requiredstats);
    std::vector<Feats> required_feats(arg_required_feats);
    std::vector<std::string> required_classes(arg_required_classes);//Maybe make this <std::string, int> for class and class level
    int required_bab = arg_required_base_attack_bonus;

}

//Getters
std::string Feats::get_name() const{
    return name;
}

std::string Feats::get_description() const{
    return description;
}

std::string Feats::get_special_notes() const{
    return speical_notes;
}

bool Feats::is_multiple_allowed() const{
    return multiple_allowed;
}

std::vector<std::pair<std::string,int>> Feats::get_required_stats() const{
    return required_stats;
}

std::vector<Feats> Feats::get_required_feats() const{
    return required_feats;
}
std::vector<std:string> Feats::get_required_classes() const{
    return required_classes;
}

int Feats::get_required_base_attack_bonus() const{
    return required_bab;
}

//Setters

void Feats::set_name(std::string x){
    this->name = x;
}
void Feats::set_description(std::string x){
    this->description = x;
}
void Feats::set_special_notes(std::string x){
    this->special_notes = x;
}
void Feats::set_multiple_allowed(bool x){
    this->multiple_allowed = x;
}
void Feats::set_required_stats(std::vector<std::pair<std::string,int>> vector){
    this->required_stats = std::move(vector);
}
void Feats::set_required_feats(std::vector<Feats> vector){
    this->required_feats = std::move(vector);
}
void Feats::set_required_classes(std::vector<std::string> vector){
    this->required_classes = std::move(vector);
}
void Feats::set_required_bab(int x){
    this->required_bab = x;
}