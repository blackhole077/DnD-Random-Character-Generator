#include "../headers/roll.h"
using namespace std;

// this sets up a static distribution for the cdf, lowering time issues
const int roll_4d6_drop_lowest[19] = {0, 0, 0, 11, 285, 2187, 8480, 18981, 34095, 53500, 73675, 85007, 87748, 81348, 66142, 44256, 26459, 13260, 4566};
std::vector<int> weights(roll_4d6_drop_lowest, roll_4d6_drop_lowest + sizeof(roll_4d6_drop_lowest) / sizeof(roll_4d6_drop_lowest[0]));
std::discrete_distribution<> dist(weights.begin(), weights.end());

/*Section for rolling dice*/
int cdfRoll()
{

	std::random_device rd;
	std::mt19937 gen(rd());

	return dist(rd);
}

/**
 * @brief Roll an arbitrarily sided die an arbitrary number of times, then return the sum.
 * 
 * This is an integral function to character generation, as it is used for calculating hitpoints, age and alignment.
 * 
 * @param numDie The number of times you wish to roll.
 * @param numFace The number of faces the dice will have.
 * @return int The sum of the values rolled.
 */
int rollXdX(const int numDie, const int numFace)
{
	int *rolls;
	int sum = 0;
	std::random_device rd;
	std::uniform_int_distribution<> die(1, numFace);
	rolls = (int *)malloc(sizeof(int) * numDie);
	for (int i = 0; i < numDie; i++)
	{
		sum += die(rd);
	}
	return sum;
}

/**
 * @brief Roll an arbitrary-sided die once and return the result.
 * This is an integral function to character generation, as it is used for calculating weight, and stat distribution.
 * 
 * @param numFace The number of faces the die will have.
 * @return int The result of the die roll.
 */
int rolldX(const int numFace)
{ //Roll 1dx then return result as an array
	int roll;
	std::random_device rd;
	std::uniform_int_distribution<int> die(1, numFace);
	roll = (die(rd));
	return roll;
}

/**
 * @brief Generate an integer using a discrete weighted probability distribution.
 * NOTE: This uses integer weights to avoid issues with floating point numbers. All values should add up to 100.
 * 
 * @param weights The weight of each possible outcome. Should be a number between 0 and 100.
 * @return int The integer that is chosen based on the aforementioned probability distribution
 */
int weighted_distribution(vector<int> weights)
{
	int sum_of_weight = 0;
	int num_choices = weights.size();
	for (int i = 0; i < num_choices; i++)
	{
		sum_of_weight += weights.at(i);
	}
	int rnd = rolldX(sum_of_weight);
	for (int i = 1; i <= num_choices; i++)
	{
		int comparison = weights.at(i - 1);
		if (rnd < comparison)
		{
			return i;
		}
		rnd -= comparison;
	}
	assert(!"should never get here");
	return -1;
}
