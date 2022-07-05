#include "..\headers\roll.h"
#include <random>
using namespace std;

// this sets up a static distribution for the cdf, lowering time issues
const int roll3d6Drop1[19] = { 0, 0, 0, 11, 285, 2187, 8480, 18981, 34095, 53500, 73675, 85007, 87748, 81348, 66142, 44256, 26459, 13260, 4566 };
std::vector<int> weights(roll3d6Drop1, roll3d6Drop1 + sizeof(roll3d6Drop1) / sizeof(roll3d6Drop1[0]));
std::discrete_distribution<> dist(weights.begin(), weights.end());

/*Section for rolling dice*/
int cdfRoll() {

	std::random_device rd;
	std::mt19937 gen(rd());

	return dist(rd);
}

int rollXdX(const int numDie, const int numFace) {//Roll xdx then return result as an array
	int *rolls;
	int sum=0;
	std::random_device rd;
	std::uniform_int_distribution<> die(1, numFace);
	rolls = (int *)malloc(sizeof(int)*numDie);
	for (int i = 0; i < numDie; i++) {
		sum += die(rd);
		//std::printf("roll is %d\n",rolls[i]);
		// rand() isn't truely random, homie
		// it will probably output 1 more often than you expect
		// use a uniform distribution function
	}


	return sum;
	//Returns the sum of the array
}

int rolldX(const int numFace)
{ //Roll 1dx then return result as an array
	int roll;
	std::random_device rd;
	std::uniform_int_distribution<int> die(1, numFace);
	//rolls = (int *)malloc(sizeof(int) * numDie);
	roll = (die(rd));
	return roll;
	//Returns the address to the first element of the array
}