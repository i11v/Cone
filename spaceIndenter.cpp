#include "spaceIndenter.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include "ALGLIB/integration.h"
using namespace alglib;

SpaceIndenter::SpaceIndenter(double _density, double _friction, double _strength, double _mass, double _initialSpeed) {
	density0 = _density;
	friction0 = _friction;
	strength0 = _strength;
	mass = _mass;
	initialSpeed = _initialSpeed;
}

SpaceIndenter::~SpaceIndenter() {};

double SpaceIndenter::density(double x) {
	return density0;
};

double SpaceIndenter::friction(double x) {
	return friction0;
};

double SpaceIndenter::strength(double x) {
	return strength0;
};

double SpaceIndenter::k(double z) {
	return pow(sin(atan(SpaceIndenter::df(z))), 2);
}

void SpaceIndenter::f1(double x1, double xminusa1, double bminusx1, double &y1, void *ptr1) {
	y1 = SpaceIndenter::k(x1) * SpaceIndenter::df(x1) * SpaceIndenter::f(x1);
}

void SpaceIndenter::f2(double x2, double xminusa2, double bminusx2, double &y2, void *ptr2) {
	y2 = (SpaceIndenter::strength0 * SpaceIndenter::df(x2) + SpaceIndenter::friction(x2)) * SpaceIndenter::f(x2);
}

double SpaceIndenter::solve(double x) {
	double a = 0;
	double b = x;
	autogkstate s1, s2;
	double v1, v2;
	autogkreport rep1, rep2;

	autogksmooth(a, b, s1);
	alglib::autogkintegrate(s1, SpaceIndenter::f1);
	autogkresults(s1, v1, rep1);

	autogksmooth(a, b, s2);
	alglib::autogkintegrate(s2, SpaceIndenter::f2);
	autogkresults(s2, v2, rep2);
	
	return v1;
};

double SpaceIndenter::f(double z) {
	double c = 1.0;

	return c * z;
}

double SpaceIndenter::df(double z) {
	double h = 0.0001;

	return (f(z + h) - f(z - h)) / (2 * h);
}