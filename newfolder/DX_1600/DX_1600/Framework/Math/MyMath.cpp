#include "framework.h"
#include "MyMath.h"

int MyMath::RandomInt(int min, int max)
{
	if (max > min)
		swap(min, max);

	int randInt = (rand() % (max - min + 1)) + min;

	return randInt;
}

float MyMath::RandomFloat(float min, float max)
{
	if (max > min)
		swap(min, max);

	float zeroToOne = rand() / (float)RAND_MAX;

	return (max - min) * zeroToOne + min;

}
