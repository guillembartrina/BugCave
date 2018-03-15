
#include "RandomGenerator.hpp"

RandomGenerator::RandomGenerator()
{
    randEngine.seed(time(0));
}

RandomGenerator::~RandomGenerator()
{

}

int RandomGenerator::getRandInt(int min, int max)
{
    std::uniform_int_distribution<int> intBetween(min, max);

    return intBetween(randEngine);
}

float RandomGenerator::getRandFloat(float min, float max)
{
    std::uniform_real_distribution<float> floatBetween(min, max);

    return floatBetween(randEngine);
}

double RandomGenerator::getRandDouble(double min, double max)
{
    std::uniform_real_distribution<double> doubleBetween(min, max);

    return doubleBetween(randEngine);
}


