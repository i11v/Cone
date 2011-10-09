/*
 * +����� ����������� ����� ���������� ��������������
 * +����������� ����� ������� ����������������� ���������
 * +������ ������ ��� ������
 * 
 */
class SpaceIndenter {
private:
	double density0; // ��������� �����
	double friction0; // ������
	double strength0; // �������������

	double mass; // ����� ��������
	double initialSpeed; // ��������� ��������
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