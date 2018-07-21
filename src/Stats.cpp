#include "..\headers\Stats.h"
using namespace std;

Stats::Stats(){}

void Stats::set_base_strength(int x){
    this->base_strength = x;
}
void Stats::set_base_dexterity(int x){
    this->base_dexterity = x;
}
void Stats::set_base_constitution(int x){
    this->base_constitution = x;
}
void Stats::set_base_intelligence(int x){
    this->base_intelligence = x;
}
void Stats::set_base_wisdom(int x){
    this->base_wisdom = x;
}
void Stats::set_base_charisma(int x){
    this->base_charisma = x;
}

int Stats::get_base_strength()const{
    return base_strength;
}
int Stats::get_base_dexterity()const{
    return base_dexterity;
}
int Stats::get_base_constitution()const{
    return base_dexterity;
}
int Stats::get_base_intelligence()const{
    return base_intelligence;
}
int Stats::get_base_wisdom()const{
    return base_wisdom;
}
int Stats::get_base_charisma()const{
    return  base_charisma;
}

void Stats::set_modifier_strength(int x){
    this->strength_modifier = x;
}
void Stats::set_modifier_dexterity(int x){
    this->dexterity_modifier = x;
}
void Stats::set_modifier_constitution(int x){
    this->constitution_modifier = x;
}
void Stats::set_modifier_intelligence(int x){
    this->intelligence_modifier = x;
}
void Stats::set_modifier_wisdom(int x){
    this->wisdom_modifier = x;
}
void Stats::set_modifier_charisma(int x){
    this->charisma_modifier = x;
}

int Stats::get_modifier_strength()const{
    return strength_modifier;
}
int Stats::get_modifier_dexterity()const{
    return dexterity_modifier;
}
int Stats::get_modifier_constitution()const{
    return constitution_modifier;
}
int Stats::get_modifier_intelligence()const{
    return intelligence_modifier;
}
int Stats::get_modifier_wisdom()const{
    return wisdom_modifier;
}
int Stats::get_modifier_charisma()const{
    return charisma_modifier;
}

void Stats::set_bad_stats(std::vector<int> bs)
{
    this->bad_stats = std::move(bs);
}

void Stats::set_good_stats(std::vector<int> gs)
{
    this->good_stats = std::move(gs);
}

std::vector<int> Stats::get_bad_stats() const{
    return bad_stats;
}

std::vector<int> Stats::get_good_stats() const{
    return good_stats;
}

int Stats::determine_stat_bonus(int stat) {
	double bonus = (double)stat-10;
	bonus = floor(bonus / 2);
	return bonus;
}

void Stats::generate_stats(){
    std::vector<int> rolled_stats = {cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll()};//Sort this from least to greatest then split into two arrays
    std::sort(std::begin(rolled_stats), std::end(rolled_stats));
    std::size_t const halfsies = rolled_stats.size() / 2;
    std::vector<int> gs(rolled_stats.begin(), rolled_stats.begin()+halfsies);
    std::vector<int> bs(rolled_stats.begin()+halfsies,rolled_stats.end());
    set_good_stats(gs);
    set_bad_stats(bs);
}

void Stats::generate_stats_vector(){
    stats_vector = {base_strength,base_dexterity,base_constitution,base_intelligence,base_wisdom,base_charisma};
}

void Stats::modify_stats_race(std::vector<int> one_hot_stats_modifier)
{
    std::transform(stats_vector.begin( ), stats_vector.end( ), one_hot_stats_modifier.begin( ), stats_vector.begin( ),std::plus<int>( ));
}

void Stats::printStats() {
	int strBonus = determine_stat_bonus(base_strength);
	int dexBonus = determine_stat_bonus(base_dexterity);
	int conBonus = determine_stat_bonus(base_constitution);
	int intBonus = determine_stat_bonus(base_intelligence);
	int wisBonus = determine_stat_bonus(base_wisdom);
	int chaBonus = determine_stat_bonus(base_charisma);
	cout << "Strength: " << base_strength << " (" << std::showpos << strBonus << ") " << std::noshowpos << endl;
	cout << "Dexterity: " << base_dexterity << " (" << std::showpos << dexBonus << ") " << std::noshowpos << endl;
	cout << "Constitution: " << base_constitution << " (" << std::showpos << conBonus << ") " << std::noshowpos << endl;
	cout << "Intelligence: " << base_intelligence << " (" << std::showpos << intBonus << ") " << std::noshowpos << endl;
	cout << "Wisdom: " << base_wisdom << " (" << std::showpos << wisBonus << ") " << std::noshowpos << endl;
	cout << "Charisma: " << base_charisma << " (" << std::showpos << chaBonus << ") " << std::noshowpos << endl;
	cout << endl;
}