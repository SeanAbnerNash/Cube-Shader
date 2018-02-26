#ifndef MYMATRIX3
#define MYMATRIX3
#include "Vector3.h"
# define PI           3.14159265358979323846
#include <iostream>

//Forward Reference the class
//@Author Sean Nash De Andrade
//@Login C00217019
//Cube Rotation Assignment
class MyVector3;

class Matrix3
{
private:
	// The class has nine variables, 3 rows and 3 columns
	double m_A11;
	double m_A12;
	double m_A13;
	double m_A21;
	double m_A22;
	double m_A23;
	double m_A31;
	double m_A32;
	double m_A33;
public:
	// Constructor 1 create a zero matrix
	Matrix3();

	// Constructor 2
	Matrix3(MyVector3 Row1, MyVector3 Row2, MyVector3 Row3);

	// Constructor 3
	Matrix3(double t_A11, double t_A12, double t_A13,
		double t_A21, double t_A22, double t_A23,
		double t_A31, double t_A32, double t_A33);

	double A11();
	double A12();
	double A13();
	double A21();
	double A22();
	double A23();
	double A31();
	double A32();
	double A33();


	MyVector3 operator *(MyVector3 &right);

	Matrix3 Transpose(Matrix3 M1);

	Matrix3 operator+ (Matrix3 M2);

	Matrix3 operator- (Matrix3 M2);

	Matrix3 operator *(double x);

	Matrix3 operator *(Matrix3 M2);

	double Determinant();

	MyVector3 Row(int i);

	MyVector3 Column(int i);

	Matrix3 Inverse();

	Matrix3 Rotation(int _angle);

	Matrix3 Translate(double dx, double dy);

	Matrix3 Scale(double dx, double dy);

	Matrix3 RotationX(double _angle);

	Matrix3 RotationY(double _angle);

	Matrix3 RotationZ(double _angle);

	Matrix3 Scale3D(double dx);

}; 
#endif