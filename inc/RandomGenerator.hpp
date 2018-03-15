#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <random>
#include <ctime>

/* Random int, float, double generator from TIME seed */

class RandomGenerator
{
public:

    RandomGenerator();
    ~RandomGenerator();

    int getRandInt(int min, int max);
	/* PRE: true */
	/* POST: returns a random int between 'min' and 'max' */

    float getRandFloat(float min, float max);
	/* PRE: true */
	/* POST: returns a random float between 'min' and 'max' */

    double getRandDouble(double min, double max);
	/* PRE: true */
	/* POST: returns a random double between 'min' and 'max' */

private:

    std::default_random_engine randEngine;
	
};

#endif