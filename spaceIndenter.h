/*
 * +����� ����������� ����� ���������� ��������������
 * +����������� ����� ������� ����������������� ���������
 * +������ ������ ��� ������
 * 
 */
class Cone {
private:
	double density0; // ��������� �����
	double coefficient0; // ���������� k �� ������������ �������
	double friction0; // ������
	double strength0; // �������������

	double mass; // ����� ��������
	double initialSpeed; // ��������� ��������
public:
	Cone(double, double, double, double, double, double);
	~Cone();
	double density(double); 
	double coefficient(double); 
	double friction(double); 
	double strength(double);
	double f1(double); // ����� ���������� �������������� ������� k*ro*Tan[alpha]*Surface[z]
	double f2(double); // ����� ���������� �������������� ������� (sigma0*Tan[alpha]+tau*Surface[z])
	double func(double, double); // ������� �������������� ������ ����� ����. ��������� D[y]=-2*Pi*F1(x)*y/0.5*m + F2(x)/0.5*m
	double solve(double); // ������� ����������������� ��������� 0.5*m*D[y]=-2*Pi*F1(x)*y+F2(x)
	double surface(double); // ��������� �����������
};