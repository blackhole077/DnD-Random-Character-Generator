#include<random>
#include<vector>
#include<map>
#include<algorithm>
#include<functional>
#include <string>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
// #include "roll.h"
template <typename T>
void printElement(T t, const int &num_width, const char &separator)
{
	std::cout << std::left << std::setw(num_width) << std::setfill(separator) << t;
}

template<typename T>
void printVector(const T& t) {
	std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
}

template<typename T>
void printVectorInVector(const T& t) {
	std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

template<typename T>
bool contains(std::vector<T> &vector_of_items, const T &element){
	return std::find(vector_of_items.begin(), vector_of_items.end(), element) != vector_of_items.end()
}

std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b);
std::map<int,int> smart_stat_distribution(std::vector<int> bad_class_stats, std::vector<int> bad_available_stats, std::vector<int> good_class_stats, std::vector<int> good_available_stats);


int cdfRoll();
int rollXdX(const int numDie, const int numFace);
int rolldX(const int numFace);
