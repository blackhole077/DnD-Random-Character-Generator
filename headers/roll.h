#ifndef ROLL_H
#define ROLL_H

/*Section for rolling dice*/
#include <random>
#include <vector>
#include <assert.h>
int cdfRoll();

int rollXdX(const int numDie, const int numFace);

int rolldX(const int numFace);

int weighted_distribution(std::vector<int> weights);

#endif
