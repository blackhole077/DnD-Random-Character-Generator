#include "../headers/dnd_template_functions.h"
using namespace std;
const int roll3d6Drop1[19] = {0, 0, 0, 11, 285, 2187, 8480, 18981, 34095, 53500, 73675, 85007, 87748, 81348, 66142, 44256, 26459, 13260, 4566};
std::vector<int> weights(roll3d6Drop1, roll3d6Drop1 + sizeof(roll3d6Drop1) / sizeof(roll3d6Drop1[0]));
std::discrete_distribution<> dist(weights.begin(), weights.end());
const unsigned int seed = time(0);
std::mt19937 engine(seed);

std::vector<int> operator+(const std::vector<int> &a, const std::vector<int> &b)
{
	std::vector<int> result;
	result.reserve(a.size());

	std::transform(a.begin(), a.end(), b.begin(),
				   std::back_inserter(result), std::plus<int>());
	return result;
}


/*Section for rolling dice*/
int cdfRoll()
{

	std::random_device rd;
	std::mt19937 gen(rd());

	return dist(rd);
}

int rollXdX(const int numDie, const int numFace)
{ //Roll xdx then return result as an array
	int *rolls;
	int sum = 0;
	std::uniform_int_distribution<> die(1, numFace);
	rolls = (int *)malloc(sizeof(int) * numDie);
	for (int i = 0; i < numDie; i++)
	{
		sum += die(engine);
	}

	return sum;
	//Returns the sum of the array
}

int rolldX(const int num_face)
{ //Roll 1dx then return result as an array
	if(num_face == 0){
		return 0;
	}
	if(num_face == 1){
		return 1;
	}
	int roll;
	std::uniform_int_distribution<> die(1, num_face);
	//rolls = (int *)malloc(sizeof(int) * numDie);
	roll = die(engine);
	return roll;
	//Returns the address to the first element of the array
}

std::map<int, int> smart_stat_distribution(std::vector<int> bad_class_stats, std::vector<int> bad_available_stats, std::vector<int> good_class_stats, std::vector<int> good_available_stats)
{
	std::map<int, int> stats_map;
	int counter = bad_available_stats.size();
	cout << "Setting counter to" << counter << endl;
	for (int i = 0; i < counter; i++)
	{
		int ins;
		int roll;
		//std::cout << "badStat contains:";
		//for (unsigned i = 0; i < badStats.size(); ++i)
		//	std::cout << ' ' << badStats[i];
		//cout << endl;
		//bad_stats[i] refers to each index that I labeled as a "bad stat" in the Class object.
		if (bad_available_stats.size() != 1)
		{
			roll = rolldX(bad_available_stats.size());
			ins = bad_available_stats.at(roll - 1);
		}
		else
		{
			ins = bad_available_stats.at(0);
		}
		stats_map.insert(std::pair<int, int>(bad_class_stats.at(i), ins));
		std::cout << "Current Stats_Map (Bad):"<<endl;
		for (auto i : stats_map)
		{
			cout << i.first << "," << i.second << endl;
		}

		if (bad_available_stats.size() != 1)
		{
			bad_available_stats.erase(bad_available_stats.begin() + (roll - 1));
		}
		else
		{
			bad_available_stats.erase(bad_available_stats.begin());
		}
		//printf("Good Stat of %d is %d\n", i, statsRolled[rolled]);
	}
	counter = good_available_stats.size();
	for (int i = 0; i < counter; i++)
	{
		int ins;
		int roll;
		std::cout << "Current Stats_Map (good):"<<endl;
		for (auto i : stats_map)
		{
			cout << i.first << "," << i.second << endl;
		}
		//bad_stats[i] refers to each index that I labeled as a "bad stat" in the Class object.
		if (good_available_stats.size() != 1)
		{
			roll = rolldX(good_available_stats.size());
			ins = good_available_stats.at(roll - 1);
		}
		else
		{
			ins = good_available_stats.at(0);
		}
		stats_map.insert(std::pair<int, int>(good_class_stats.at(i), ins));
		std::cout << "Current Stats_Map: (Good)" << endl;
		for (auto i : stats_map)
		{
			cout << i.first << "," << i.second << endl;
		}

		if (good_available_stats.size() != 1)
		{
			good_available_stats.erase(good_available_stats.begin() + (roll - 1));
		}
		else
		{
			good_available_stats.erase(good_available_stats.begin());
		}
		//printf("Good Stat of %d is %d\n", i, statsRolled[rolled]);
	}
	std::cout << "Final Stats_Map:"<<endl;
	for (auto i : stats_map)
	{
		cout << i.first << "," << i.second << endl;
	}

	return stats_map;
}
