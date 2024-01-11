#include "randomNumber.h"

int makeRandomNumberInRange(int min, int max)
{	
	return rand() % (max - min) + min;
}

void makeNrandomNumber(std::vector<int>& numVec, int N, int min, int max)
{
	for(int i = 0; i < N; i++)
		numVec.push_back(makeRandomNumberInRange(min, max));
}
