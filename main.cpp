#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

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
double integrate(double (*)(double), double, double); // реализаци€ метода —импсона
double g(double, double); // права€ часть дифф. уравнени€
double euler(double (*)(double, double), double, double, double); // реализаци€ метода Ёйлера
double solve(); // решение дифф. уравнени€ проникновени€ ударника

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
	
	ofstream file;
    file.open ("spaceIndenter.dat");
    file.precision(6);
    file.setf(ios::fixed | ios::showpoint);
    cout.precision(6);
    cout.setf(ios::fixed | ios::showpoint);

	cout << integrate(&F2, 0, 1) << endl;

	file.close();
	system("pause");

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
	return k(x) * df(x) * f(x);
}

double F2(double x) {
	return (strength0 * df(x) + friction0) * f(x);
}

double integrate(double (*func)(double), double a, double b) {
	double dx, x;
	double s = 0.0;
	int n = 1000;

	dx = (b - a) / n;
	for (int i = 2; i <= n - 1; i = i + 2) {
		x = a + i * dx;
		s = s + 2.0 * func(x) + 4.0 * func(x + dx);
    }
	s = (s + func(a) + func(b) + 4.0 * func(a + dx) ) * dx / 3.0;
	
	return s;
}

double g(double x, double y) {
	return -(4 * M_PI / weight) * density0 * integrate(&F1, 0, x) * y - (4 * M_PI / weight) * integrate(&F2, 0, x);
}

double euler(double (*eq)(double, double), double x0, double y0, double xf) {
	double yf;
	
	yf = y0 + eq(x0, y0) * (xf - x0);
	xf = y0 + (eq(x0, y0) + eq(xf, yf)) * 0.5 * (xf - x0);
	
	return xf;
}

double solve() {
	double xf, yf;
	double x0 = 0.0;
	double y0 = pow(initialSpeed, 2);
	double dx = 0.01;
	double xmax = 0.2;

	while (x0 <= xmax) {
		xf = x0 + dx;
		yf = euler(g, x0, y0, xf);
		cout << setw(12) << xf << setw(12) << yf << endl;
		x0 = xf;
		y0 = yf;
	}

	return 0;
}