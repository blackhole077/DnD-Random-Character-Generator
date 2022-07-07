#include "..\headers\Stats.h"
using namespace std;

Stats::Stats() {}

void Stats::set_base_strength(int x)
{
    this->base_strength = x;
}
void Stats::set_base_dexterity(int x)
{
    this->base_dexterity = x;
}
void Stats::set_base_constitution(int x)
{
    this->base_constitution = x;
}
void Stats::set_base_intelligence(int x)
{
    this->base_intelligence = x;
}
void Stats::set_base_wisdom(int x)
{
    this->base_wisdom = x;
}
void Stats::set_base_charisma(int x)
{
    this->base_charisma = x;
}

const int Stats::get_base_strength()
{
    return base_strength;
}
const int Stats::get_base_dexterity()
{
    return base_dexterity;
}
const int Stats::get_base_constitution()
{
    return base_dexterity;
}
const int Stats::get_base_intelligence()
{
    return base_intelligence;
}
const int Stats::get_base_wisdom()
{
    return base_wisdom;
}
const int Stats::get_base_charisma()
{
    return base_charisma;
}

void Stats::set_modifier_strength(int x)
{
    this->strength_modifier = x;
}
void Stats::set_modifier_dexterity(int x)
{
    this->dexterity_modifier = x;
}
void Stats::set_modifier_constitution(int x)
{
    this->constitution_modifier = x;
}
void Stats::set_modifier_intelligence(int x)
{
    this->intelligence_modifier = x;
}
void Stats::set_modifier_wisdom(int x)
{
    this->wisdom_modifier = x;
}
void Stats::set_modifier_charisma(int x)
{
    this->charisma_modifier = x;
}

const int Stats::get_modifier_strength()
{
    return strength_modifier;
}
const int Stats::get_modifier_dexterity()
{
    return dexterity_modifier;
}
const int Stats::get_modifier_constitution()
{
    return constitution_modifier;
}
const int Stats::get_modifier_intelligence()
{
    return intelligence_modifier;
}
const int Stats::get_modifier_wisdom()
{
    return wisdom_modifier;
}
const int Stats::get_modifier_charisma()
{
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

const std::vector<int> Stats::get_bad_stats()
{
    return bad_stats;
}

const std::vector<int> Stats::get_good_stats()
{
    return good_stats;
}

/**
 * @brief Calculate the stat modifier based on the base stat provided.
 * 
 * @param stat The base value of a stat.
 * @return int The modifier based on the stat calculated using ⌊(X-10)/2⌋, where X is the base value of the stat.
 */
int Stats::determine_stat_bonus(int base_stat_value)
{
    double bonus_value = (double)base_stat_value - 10;
    bonus_value = floor(bonus_value / 2);
    return bonus_value;
}

/**
 * @brief Generate the stats of the character
 * 
 */
void Stats::generate_stats()
{
    // The stats that are rolled based on the 4d6 drop lowest method of stats generation
    std::vector<int> rolled_stats = {cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll(), cdfRoll()}; //Sort this from least to greatest then split into two arrays
    std::sort(std::begin(rolled_stats), std::end(rolled_stats));
    const std::size_t halfway_point = rolled_stats.size() / 2;
    std::vector<int> top_three_stats(rolled_stats.begin(), rolled_stats.begin() + halfway_point);
    std::vector<int> bottom_three_stats(rolled_stats.begin() + halfway_point, rolled_stats.end());
    set_good_stats(top_three_stats);
    set_bad_stats(bottom_three_stats);
}

/**
 * @brief Generate the vector of base stats. Used when modifying the stats list due to race selection.
 * 
 */
void Stats::generate_stats_vector()
{
    stats_vector = {base_strength, base_dexterity, base_constitution, base_intelligence, base_wisdom, base_charisma};
}

/**
 * @brief Modify the character's base stats based on what race was chosen.
 * 
 * @param racial_modifier_array An array that represents the numerical changes to make to the character's base stats.
 */
void Stats::modify_stats_race(std::vector<int> racial_modifier_array)
{
    std::transform(stats_vector.begin(), stats_vector.end(), racial_modifier_array.begin(), stats_vector.begin(), std::plus<int>());
}

/**
 * @brief Helper function that prints out the base stats and the modifier for said stats.
 * 
 */
void Stats::printStats()
{
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