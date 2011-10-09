#include <iostream>
#include "spaceIndenter.h"

int main() {
	double conicalIndenterWeight = 0.001 / 981;
	double conicalIndenterInitialSpeed = 30000;
	double solidHalfSpaceDensity = 0.0027 / 981;
	double solidHalfSpaceFriction = 200; 
	double solidHalfSpaceStrength = 1000; 

	SpaceIndenter cone(solidHalfSpaceDensity,
		solidHalfSpaceFriction,
		solidHalfSpaceStrength,
		conicalIndenterWeight,
		conicalIndenterInitialSpeed);

	std::cout << cone.solve(0.2);
	
	std::cin.get();

	return 0;
}
