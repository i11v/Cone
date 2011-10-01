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

	return k * ro * tan(alpha) * surface(z);
};

double Cone::f2(double x) { // Метод численного интегрирования формулы формулы (sigma0*Tan[alpha]+tau*Surface[z])
	return x;
}

double Cone::func(double x, double y) {
		return -4 * M_PI * f1(x) * y / mass - 4 * M_PI * f2(x) / mass;
}

double Cone::solve(double x_n) {
	double x_0 = 0;	// начальные условия. здесь 0, потому что интрегралы имеет переменный верхний предел x, а нижний 0
	double y_0 = initialSpeed * initialSpeed;	// начальные условия. y = v^2 
	double h = 0.01; // шаг 
	double e = 0.001;	// необходимая точность
	double x_i1;
	double y_i;
	double x_i;
	double y_i_k;
	int i;

	x_i = x_0;
	y_i = y_0;

	do
	{
		x_i1 = x_i + i * h;
		y_i = y_i + h * func(x_i, y_i);
		y_i_k = y_i;
		do
		{
			y_i_k = y_i + (func(x_i1, y_i_k)) * h / 2;
		} while(abs(y_i_k - y_i) < e);
	} while(x_i1 < x_n);

	return y_i_k;
};

double Cone::surface(double z) {
	double c = 1.0;

	return c * z;
}