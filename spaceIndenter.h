/*
 * +нужно реализовать метод численного интегрировани€
 * +реализовать метод решени€ дифференциального уравнени€
 * +решить задачу дл€ конуса
 * 
 */
class Cone {
private:
	double density0; // плотность среды
	double coefficient0; // коэфициент k из эмпирической формулы
	double friction0; // трение
	double strength0; // сопротивление

	double mass; // масса ударника
	double initialSpeed; // начальна€ скорость
public:
	Cone(double, double, double, double, double, double);
	~Cone();
	double density(double); 
	double coefficient(double); 
	double friction(double); 
	double strength(double);
	double f1(double); // метод численного интегрировани€ формулы k*ro*Tan[alpha]*Surface[z]
	double f2(double); // метод численного интегрировани€ формулы (sigma0*Tan[alpha]+tau*Surface[z])
	double func(double, double); // функци€ представл€юща€ правую часть дифф. уравнени€ D[y]=-2*Pi*F1(x)*y/0.5*m + F2(x)/0.5*m
	double solve(double); // решение дифференциального уравнени€ 0.5*m*D[y]=-2*Pi*F1(x)*y+F2(x)
	double surface(double); // уравнение поверхности
};