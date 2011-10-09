/*
 * +нужно реализовать метод численного интегрирования
 * +реализовать метод решения дифференциального уравнения
 * +решить задачу для конуса
 * 
 */
class SpaceIndenter {
private:
	double density0; // плотность среды
	double friction0; // трение
	double strength0; // сопротивление

	double mass; // масса ударника
	double initialSpeed; // начальная скорость
public:
	SpaceIndenter(double, double, double, double, double);
	~SpaceIndenter();
	double density(double); 
	double friction(double); 
	double strength(double);
	double k(double);
	void f1(double, double, double, double&, void*);
	void f2(double, double, double, double&, void*);
	double solve(double);
	double f(double); 
	double df(double);
};