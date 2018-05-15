#include<random>
#include<vector>
#include<map>
#include<algorithm>
#include<functional>
#include "roll.h"
template<typename T> void printElement(T t, const int& num_width, const char& separator);
std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b);
std::map<int,int> smart_stat_distribution(std::vector<int> bad_class_stats, std::vector<int> bad_available_stats, std::vector<int> good_class_stats, std::vector<int> good_available_stats);


// int cdfRoll();
// int rollXdX(const int numDie, const int numFace);
// int rolldX(const int numFace);