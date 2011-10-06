#include "spaceIndenter.h"

int main() {
	double conicalIndenterWeight = 100;
	double conicalIndenterInitialSpeed = 100;
	double solidHalfSpaceDensity = 100;
	double solidHalfSpaceCoefficient = 100;
	double solidHalfSpaceFriction = 100; 
	double solidHalfSpaceStrength = 100; 

	spaceIndenter cone(solidHalfSpaceDensity,
		solidHalfSpaceCoefficient,
		solidHalfSpaceFriction,
		solidHalfSpaceStrength,
		conicalIndenterWeight,
		conicalIndenterInitialSpeed);
	
	return 0;
}
