#include "Matrix3.h"
//@Author Sean Nash De Andrade
//@Login C00217019
//Cube Rotation Assignment
Matrix3::Matrix3()// Constructor 1 create a zero matrix
{
	
		m_A11 = 0.0;
		m_A12 = 0.0;
		m_A13 = 0.0;
		m_A21 = 0.0;
		m_A22 = 0.0;
		m_A23 = 0.0;
		m_A31 = 0.0;
		m_A32 = 0.0;
		m_A33 = 0.0;
	
}

Matrix3::Matrix3(MyVector3 Row1, MyVector3 Row2, MyVector3 Row3)// To allow 3 rows of vectors to be declared as a matrix
{  
	m_A11 = Row1.getX();
	m_A12 = Row1.getY();
	m_A13 = Row1.getZ();

	m_A21 = Row2.getX();
	m_A22 = Row2.getY();
	m_A23 = Row2.getZ();

	m_A31 = Row3.getX();
	m_A32 = Row3.getY();
	m_A33 = Row3.getZ();
}

Matrix3::Matrix3(double t_A11, double t_A12, double t_A13, double t_A21, double t_A22, double t_A23, double t_A31, double t_A32, double t_A33)
{// to allow nine double values
	m_A11 = t_A11;
	m_A12 = t_A12;
	m_A13 = t_A13;

	m_A21 = t_A21;
	m_A22 = t_A22;
	m_A23 = t_A23;

	m_A31 = t_A31;
	m_A32 = t_A32;
	m_A33 = t_A33;
}

double Matrix3::A11()
{
	return m_A11;
}

double Matrix3::A12()
{
	return m_A12;
}

double Matrix3::A13()
{
	return m_A13;
}

double Matrix3::A21()
{
	return m_A21;
}

double Matrix3::A22()
{
	return m_A22;
}

double Matrix3::A23()
{
	return m_A23;
}

double Matrix3::A31()
{
	return m_A31;
}

double Matrix3::A32()
{
	return m_A32;
}

double Matrix3::A33()
{
	return m_A33;
}

MyVector3 Matrix3::operator*(MyVector3 &right)// An overloaded operator * to return the  product of the matrix by a vector
{
	return MyVector3(m_A11 * right.getX() + m_A12 * right.getY() + m_A13 * right.getZ(),
		m_A21 * right.getX() + m_A22 * right.getY() + m_A23 * right.getZ(),
		m_A31 * right.getX() + m_A32 * right.getY() + m_A33 * right.getZ());
}

Matrix3 Matrix3::Transpose(Matrix3 M1)// a method to transpose a given matrix
{
	return  Matrix3(M1.m_A11, M1.m_A21, M1.m_A31,
		M1.m_A12, M1.m_A22, M1.m_A32,
		M1.m_A13, M1.m_A23, M1.m_A33);
}

Matrix3 Matrix3::operator+(Matrix3 M2)// An overloaded operator + to return the  sum of two matrix 
{
	return  Matrix3(m_A11 + M2.m_A11, m_A12 + M2.m_A12, m_A13 + M2.m_A13,
		m_A21 + M2.m_A21, m_A22 + M2.m_A22, m_A23 + M2.m_A23,
		m_A31 + M2.m_A31, m_A32 + M2.m_A32, m_A33 + M2.m_A33);
}
Matrix3 Matrix3::operator -(Matrix3 M2)// An overloaded operator * to return the  difference of two matrix
{
	return  Matrix3(m_A11 - M2.m_A11, m_A12 - M2.m_A12, m_A13 - M2.m_A13,
		m_A21 - M2.m_A21, m_A22 - M2.m_A22, m_A23 - M2.m_A23,
		m_A31 - M2.m_A31, m_A32 - M2.m_A32, m_A33 - M2.m_A33);
}
Matrix3 Matrix3::operator*(double x)// An overloaded operator * to return the  product of the matrix by a scalar
{
	Matrix3 answer = Matrix3();
	m_A11 = m_A11 * x;
	m_A12 = m_A12 * x;
	m_A13 = m_A13 * x;

	m_A21 = m_A21 * x;
	m_A22 = m_A22 * x;
	m_A23 = m_A23 * x;

	m_A31 = m_A31 * x;
	m_A32 = m_A32 * x;
	m_A33 = m_A33 * x; 

	return answer;
}

Matrix3 Matrix3::operator*(Matrix3 M2)// An overloaded operator * to return the  product of two matrix
{
	Matrix3 answer = Matrix3();
	answer.m_A11 = Row(0) * M2.Column(0);
	answer.m_A12 = Row(0) * M2.Column(1);
	answer.m_A13 = Row(0) * M2.Column(2);

	answer.m_A21 = Row(1) * M2.Column(0);
	answer.m_A22 = Row(1) * M2.Column(1);
	answer.m_A23 = Row(1) * M2.Column(2);

	answer.m_A31 = Row(2) * M2.Column(0);
	answer.m_A32 = Row(2) * M2.Column(1);
	answer.m_A33 = Row(2) * M2.Column(2);


	return answer;
}

double Matrix3::Determinant()// method to return the determinant of a 3x3 matrix
{
 //                     aei      -     ahf                  + dhc                     - gec                      +    gbh                    -     dbi   
	return m_A11 * m_A22 * m_A33 - m_A11 * m_A32 * m_A23 + m_A21 * m_A32 * m_A13 - m_A31 * m_A22 * m_A13 + m_A31 * m_A12 * m_A23 - m_A21 * m_A12 * m_A33;
}

MyVector3 Matrix3::Row(int i)// a method to return as Row as vector3 0 == first row, default == first row
{
	
	switch (i)
	{
	case 0:
		return  MyVector3(m_A11, m_A12, m_A13);
	case 1:
		return  MyVector3(m_A21, m_A22, m_A23);
	case 2:
		return  MyVector3(m_A31, m_A32, m_A33);
	default:
		return  MyVector3(m_A11, m_A12, m_A13);
	}
}

MyVector3 Matrix3::Column(int i)// a method to return as column as vector3 0 == first column, default == first column
{
	switch (i)
	{
	case 0:
		return  MyVector3(m_A11, m_A21, m_A31);
	case 1:
		return  MyVector3(m_A12, m_A22, m_A32);
	case 2:
		return  MyVector3(m_A13, m_A23, m_A33);
	default:
		return  MyVector3(m_A11, m_A21, m_A31);
	}
}

Matrix3 Matrix3::Inverse()// method to return the inverse of a matrix if exists else zero vector
{
	
	double det = Determinant();
	if (det == 0)
		return  Matrix3();
	else
	{
		double scale = 1 / det;
		Matrix3 answer = Matrix3();
		answer.m_A11 = scale * (m_A22 * m_A33 - m_A23 * m_A32); // ei-fh
		answer.m_A12 = scale * (m_A13 * m_A32 - m_A12 * m_A33); // ch-bi
		answer.m_A13 = scale * (m_A12 * m_A23 - m_A13 * m_A22); // ch-bi

		answer.m_A21 = scale * (m_A23 * m_A31 - m_A21 * m_A33); // fg-di
		answer.m_A22 = scale * (m_A11 * m_A33 - m_A13 * m_A31); // ai-cg
		answer.m_A23 = scale * (m_A13 * m_A21 - m_A11 * m_A23); // cd-af


		answer.m_A31 = scale * (m_A21 * m_A32 - m_A22 * m_A31); // dh-eg
		answer.m_A32 = scale * (m_A12 * m_A31 - m_A11 * m_A32); // bg-ah
		answer.m_A33 = scale * (m_A11 * m_A22 - m_A12 * m_A21); // ae-bd

		return answer;
	}

}

Matrix3 Matrix3::Rotation(int _angle)
{
	double radians = PI / 180 * _angle;
	Matrix3 answer = Matrix3();
	answer.m_A11 = cos(radians);
	answer.m_A12 = sin(radians);
	answer.m_A13 = 0;
	answer.m_A21 = -sin(radians);
	answer.m_A22 = cos(radians);
	answer.m_A23 = 0;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = 1;

	return answer;
}

Matrix3 Matrix3::Translate(double dx, double dy)
{
	Matrix3 answer = Matrix3();
	answer.m_A11 = 1;
	answer.m_A12 = 0;
	answer.m_A13 = dx;
	answer.m_A21 = 0;
	answer.m_A22 = 1;
	answer.m_A23 = dy;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = 1;

	return answer;
}

Matrix3 Matrix3::Scale(double dx, double dy)
{
	return Matrix3(static_cast<double>(dx / 100), 0, 0,
		0, static_cast<double>(dy / 100), 0,
		0, 0, 1);
}

Matrix3 Matrix3::RotationX(double _angle)
{
	double radians = PI / 180 * _angle;
	Matrix3 answer = Matrix3();
	answer.m_A11 = 1;
	answer.m_A12 = 0;
	answer.m_A13 = 0;
	answer.m_A21 = 0;
	answer.m_A22 = cos(radians);
	answer.m_A23 = -sin(radians);
	answer.m_A31 = 0;
	answer.m_A32 = sin(radians);
	answer.m_A33 = cos(radians);

	return answer;
}

Matrix3 Matrix3::RotationY(double _angle)
{
	double radians = PI / 180 * _angle;
	Matrix3 answer = Matrix3();
	answer.m_A11 = cos(radians);
	answer.m_A12 = 0;
	answer.m_A13 = sin(radians);
	answer.m_A21 = 0;
	answer.m_A22 = 1;
	answer.m_A23 = 0;
	answer.m_A31 = -sin(radians);
	answer.m_A32 = 0;
	answer.m_A33 = cos(radians);

	return answer;
}

Matrix3 Matrix3::RotationZ(double _angle)
{
	double radians = PI / 180 * _angle;
	Matrix3 answer = Matrix3();
	answer.m_A11 = cos(radians);
	answer.m_A12 = -sin(radians);
	answer.m_A13 = 0;
	answer.m_A21 = sin(radians);
	answer.m_A22 = cos(radians);
	answer.m_A23 = 0;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = 1;

	return answer;
}

Matrix3 Matrix3::Scale3D(double dx)
{
	Matrix3 answer = Matrix3();
	answer.m_A11 = dx / 100;
	answer.m_A12 = 0;
	answer.m_A13 = 0;
	answer.m_A21 = 0;
	answer.m_A22 = dx / 100;
	answer.m_A23 = 0;
	answer.m_A31 = 0;
	answer.m_A32 = 0;
	answer.m_A33 = dx / 100;

	return answer;
}
