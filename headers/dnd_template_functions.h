#ifndef DND_TEMPLATE_FUNCTIONS_H
#define DND_TEMPLATE_FUNCTIONS_H
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
#include <time.h>
// #include "roll.h"

template <typename T>
void printElement(T t, const int &num_width, const char &separator)
{
	std::cout << std::left << std::setw(num_width) << std::setfill(separator) << t;
}

template<typename T>
void printVector(const std::vector<T> &t) {
	typename std::vector<T>::const_iterator it;
	for(it = t.begin(); it != t.end(); it++){
		if(it != t.begin()){
			std::cout << ", ";
		}
		std::cout << (*it);
	}
}

template<typename T>
void printVectorInVector(const std::vector<std::vector<T>> &t) {
	std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

template<typename T>
bool contains(std::vector<T> &vector_of_items, const T &element){
	return std::find(vector_of_items.begin(), vector_of_items.end(), element) != vector_of_items.end();
}

template<typename T>
void combine(std::vector<T> &vector_A, std::vector<T> &vector_B){
	if(vector_B.empty()){
		return;
	}
	else if(vector_A.empty()){
		vector_A = std::move(vector_B);
	}
	else{
		for(auto x : vector_B){
			if(!contains(vector_A, x)){
				vector_A.push_back(x);
			}
		}
	}
}

template<typename T>
T array_summation(T* array, size_t array_size, int starting_index){
	T sum = 0;
	if(array == NULL || starting_index < 0){
		return -1;
	}
	else if(starting_index > 0 && ((unsigned) starting_index >= array_size)){
			return -1;
	}
	else{
		for(size_t i = starting_index; i < array_size; i++){
			sum += array[i];
		}
	}
	return sum;
}

std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b);
std::map<int,int> smart_stat_distribution(std::vector<int> bad_class_stats, std::vector<int> bad_available_stats, std::vector<int> good_class_stats, std::vector<int> good_available_stats);

int cdfRoll();
int rollXdX(const int numDie, const int numFace);
int rolldX(const int numFace);
#endif
