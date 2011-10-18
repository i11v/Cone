#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double density0; // плотность среды
double strength0; // сопротивление
double friction0; // трение среды
double weight; // масса ударника
double initialSpeed; // начальная скорость ударника
double alpha; 

double density(double); // плотность среды в зависимости от глубины погружения
double strength(double); // сопротивление
double friction(double); // трение среды в зависимости от глубины погружения
double f(double); // уравнение поверхности ударника
double df(double); // производная уравнения поверхности
double k(double); // эмпирический коэффициент
double F1(double); // подынтегральная функция
double F2(double); // подынтегральная функция
double f1(double); // подынтегральная функция
double f2(double); // подынтегральная функция
double force(double, double); // сила
double t(double, double, double); // время
double integrate(double (*)(double), double, double); // реализация метода Симпсона
double test(double, double);
double g(double, double); // правая часть дифф. уравнения
double euler(double (*)(double, double), double, double, double); // реализация метода Эйлера
double solve(double (*)(double, double), double, ofstream&, ofstream&); // решение дифф. уравнения проникновения ударника

int main(int argc, char **argv) {
	double conicalIndenterWeight = 0.001 / 981;
	double conicalIndenterInitialSpeed = 30000;
	double solidHalfSpaceDensity = 0.0027 / 981;
	double solidHalfSpaceFriction = 200; 
//	double solidHalfSpaceFriction = 200; 
	double solidHalfSpaceStrength = 1000;
	double initialAngle = M_PI / 6;

	density0 = solidHalfSpaceDensity;
	strength0 = solidHalfSpaceStrength;
	friction0 = solidHalfSpaceFriction;
	weight = conicalIndenterWeight;
	initialSpeed = conicalIndenterInitialSpeed;
	alpha = initialAngle;
	
	ofstream fileX, fileT;
    fileX.open ("spaceIndenterX.dat");
    fileT.open ("spaceIndenterT.dat");
    fileX.precision(6);
    fileX.setf(ios::fixed | ios::showpoint);
    fileT.precision(8);
    fileT.setf(ios::fixed | ios::showpoint);cout.precision(6);
    cout.setf(ios::fixed | ios::showpoint);

	cout << "Working" << endl;
	
	//cout << k(0.5) << "	" << df(0.5) << "	" << f(0.5) << endl;
	//cout << F1(0.5) << endl;
	//cout << integrate(F1, 0, 0.5) << endl;
	solve(g, 0.0001, fileX, fileT);

	fileX.close();
	fileT.close();
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
	return tan(alpha) * z;
}

double df(double z) {
	double h = 0.0001;

	return (f(z + h) - f(z - h)) / (2 * h);
}

double k(double z) {
	return pow(sin(alpha), 2);
}

double F1(double x) {
	return (k(x) * density0 * tan(alpha) * f(x));
}

double F2(double x) {
	return (strength0 * tan(alpha) + friction0) * f(x);
}

double f1(double x) {
	return tan(alpha) * f(x);
}

double f2(double x) {
	return f(x);
}

double force(double x, double y) {
	return 2 * M_PI * ((strength0 + k(x) * density(x) * y) * integrate(f1, 0, x) + friction(x) * integrate(f2, 0, x));
}

double t(double t0, double dx, double v) {
	return t0 + dx / v;
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
	return -(4 * M_PI / weight) * integrate(F1, 0, x) * y - (4 * M_PI / weight) * integrate(F2, 0, x);
}

double test(double x, double y) {
	return -100 * y - 100;
}

double euler(double (*eq)(double, double), double x0, double y0, double xf) {
	double yf;
	
	yf = y0 + eq(x0, y0) * (xf - x0);
	yf = y0 + (eq(x0, y0) + eq(xf, yf)) * 0.5 * (xf - x0);
	
	return yf;
}

double solve(double (*func)(double, double), double step, ofstream &xout, ofstream &tout) {
	double xk, yk, tk;
	double x0 = 0.0;
	double t0 = 0.0;
	double y0 = pow(initialSpeed, 2);
	double dx = step;
	double ymin = 0.0;

	while (y0 > ymin) {
		xk = x0 + dx;
		tk = t(t0, dx, sqrt(y0));

		if (euler(func, x0, y0, xk) >= 0) {
			yk = euler(func, x0, y0, xk);
		} else {
			break;
		}

		xout << setw(12) << xk 
//			<< setw(12) << tk
			<< setw(18) << sqrt(yk) 
			<< setw(18) << force(xk, yk) 
			<< endl;
		tout << setw(12) << tk
			<< setw(18) << sqrt(yk) 
			<< setw(18) << force(xk, yk) 
			<< endl;
		cout << setw(12) << xk
			<< setw(12) << tk
			<< setw(18) << sqrt(yk) 
			<< setw(18) << force(xk, yk) 
			<< endl;
		
		x0 = xk;
		y0 = yk;
		t0 = tk;
	}

	return yk;
}