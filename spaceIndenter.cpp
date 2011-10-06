#include "cone.h"
#define _USE_MATH_DEFINES
#include <cmath>

Cone::Cone(double _density, double _coefficient, double _friction, double _strength, double _mass, double _initialSpeed) {
	density0 = _density;
	coefficient0 = _coefficient;
	friction0 = _friction;
	strength0 = _strength;
	mass = _mass;
	initialSpeed = _initialSpeed;
}

Cone::~Cone() {};

double Cone::density(double x) {
	return density0;
};

double Cone::coefficient(double x) {
	return coefficient0;
};

double Cone::friction(double x) {
	return friction0;
};

double Cone::strength(double x) {
	return strength0;
};

double Cone::f1(double x) {
	double z;
	double k = Cone::coefficient(0);
	double ro = Cone::density(0);
	double alpha = M_PI / 4;

	return k * ro * tan(alpha) * surface(x);
};

double Cone::f2(double x) { // ћетод численного интегрировани€ формулы формулы (sigma0*Tan[alpha]+tau*Surface[z])
	return x;
}

double Cone::func(double x, double y) {
		return -4 * M_PI * f1(x) * y / mass - 4 * M_PI * f2(x) / mass;
}

double Cone::solve(double x_n) {
	return 0;
};

double Cone::surface(double z) {
	double c = 1.0;

	return c * z;
}