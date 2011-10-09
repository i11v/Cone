#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <fstream>

double density0; // плотность среды
double strength0; // сопротивление
double friction0; // трение среды
double weight; // масса ударника
double initialSpeed; // начальна€ скорость ударника

double density(double); // плотность среды в зависимости от глубины погружени€
double strength(double); // сопротивление
double friction(double); // трение среды в зависимости от глубины погружени€
double f(double); // уравнение поверхности ударника
double df(double); // производна€ уравнени€ поверхности
double k(double); // эмпирический коэффициент
double F1(double); // интеграл
double F2(double); // интеграл
double g(double, double); // права€ часть дифф. уравнени€
double euler(double, double, double, double); // решение дифф. уравнени€ проникновени€ ударника

int main(int argc, char **argv) {
	double conicalIndenterWeight = 0.001 / 981;
	double conicalIndenterInitialSpeed = 30000;
	double solidHalfSpaceDensity = 0.0027 / 981;
	double solidHalfSpaceFriction = 200; 
	double solidHalfSpaceStrength = 1000;

	density0 = solidHalfSpaceDensity;
	strength0 = solidHalfSpaceStrength;
	friction0 = solidHalfSpaceFriction;
	weight = conicalIndenterWeight;
	initialSpeed = conicalIndenterInitialSpeed;
	
	std::cin.get();

	return 0;
}

double density(double z) {
	return density0;
}

double strength(double z) {
	return strength0;
}

double friction(double z) {
	return friction0;
}

double f(double z) {
	return z;
}

double df(double z) {
	double h = 0.0001;

	return (f(z + h) - f(z - h)) / (2 * h);
}

double k(double z) {
	return pow(sin(atan(df(z))), 2);
}

double F1(double x) {
	return 1;
}

double F2(double x) {
	return 1;
}

double g(double x, double y) {
	return -F1(x) - F2(x);
}

double euler(double x0, double y0, double e, double h) {
	double y[1000], 
		y_inci[1000], 
		x[1000];
	int k = 0;
	int i = 0;

	y[0] = y0; 
	x[0] = x0;
	std::cout << std::endl
		<< "i" << "	"
		<< "x" << "	"
		<< "y" << "		"
		<< "y'(x) = F1(x)y(x) + F2(x) " 
		<< std::endl;

	while (x[i] <= (x0 + 1)) {
		std::cout << i * h << "	"
			<< x[i] << "	"
			<< y[i] << "		"
			<< g(x[i], y[i]) << std::endl;
		
		x[i + 1] = x[i] + h;
		y[i + 1] = y[i] + h * g(x[i], y[i]);
		y_inci[0] = y[i] + h * g(x[i], y[i]);

		k = 0;
		do {
			k++;
			y_inci[k] = y[i] + h / 2 * g(x[i + 1], y_inci[k - 1]);
		} while (fabs(y_inci[k] - y_inci[k - 1]) > e); 

		y[i + 1] = y_inci[k];
		i++;
	}

	return g(x[i], y[i]);
}