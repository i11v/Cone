#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <fstream>

double density0; // плотность среды
double strength0; // сопротивление
double friction0; // трение среды
double weight; // масса ударника
double initialSpeed; // начальная скорость ударника

double density(double); // плотность среды в зависимости от глубины погружения
double strength(double); // сопротивление
double friction(double); // трение среды в зависимости от глубины погружения
double f(double); // уравнение поверхности ударника
double df(double); // производная уравнения поверхности
double k(double); // эмпирический коэффициент
double F1(double); // интеграл
double F2(double); // интеграл
double integrate(double (*func)(double), double, double); // реализация метода Симпсона
double g(double); // правая часть дифф. уравнения
double euler(double, double, double, double); // решение дифф. уравнения проникновения ударника

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

double integrate(double (*func)(double), double a, double b) {
	double dx, x;
	double s = 0.0;
	int n = 100;

	dx = (b - a) / static_cast<double>(n);
	for (int i = 2; i <= n - 1; i = i + 2) {
		x = a + static_cast<double>(i) * dx;
		s = s + 2.0 * func(x) + 4.0 * func(x + dx);
    }
	s = (s + func(a) + func(b) + 4.0 * func(a + dx) ) * dx / 3.0;
	
	return s;
}

double g(double x) {
	return -(4 * M_PI / weight) * integrate(&F1, 0, x) - (4 * M_PI / weight) * integrate(&F2, 0, x);
}

double euler(double x0, double y0, double e, double h) {
	return 0;
}