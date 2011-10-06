#include "spaceIndenter.h"
#define _USE_MATH_DEFINES
#include <cmath>

spaceIndenter::spaceIndenter(double _density, double _coefficient, double _friction, double _strength, double _mass, double _initialSpeed) {
	density0 = _density;
	coefficient0 = _coefficient;
	friction0 = _friction;
	strength0 = _strength;
	mass = _mass;
	initialSpeed = _initialSpeed;
}

spaceIndenter::~spaceIndenter() {};

double spaceIndenter::density(double x) {
	return density0;
};

double spaceIndenter::coefficient(double x) {
	return coefficient0;
};

double spaceIndenter::friction(double x) {
	return friction0;
};

double spaceIndenter::strength(double x) {
	return strength0;
};

double spaceIndenter::f1(double x) {
	double z;
	double k = spaceIndenter::coefficient(0);
	double ro = spaceIndenter::density(0);
	double alpha = M_PI / 4;

	return k * ro * tan(alpha) * surface(x);
};

double spaceIndenter::f2(double x) { // ћетод численного интегрировани€ формулы формулы (sigma0*Tan[alpha]+tau*Surface[z])
	return x;
}

double spaceIndenter::func(double x, double y) {
		return -4 * M_PI * f1(x) * y / mass - 4 * M_PI * f2(x) / mass;
}

double spaceIndenter::solve(double x_n) {
	return 0;
};

double spaceIndenter::surface(double z) {
	double c = 1.0;

	return c * z;
}