#ifndef MYVECTOR3
#define MYVECTOR3
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Matrix3.h"

//Forward Reference the class
class Matrix3;
//@Author Sean Nash De Andrade
//@Login C00217019
//Cube Rotation Assignment

	class MyVector3
	{
	private:
		// The class has three variables x, y and z 
		double m_x;
		double m_y;
		double m_z;

	public:
		double getX();
		double getY();
		double getZ();

		// Constructor 1
		MyVector3();
		// Constructor 2
		MyVector3(double x1, double y1, double z1);
		double length();
		double lengthSquared();
		void normalise();
		MyVector3 operator + (const MyVector3 right) const; //Operator for +
		MyVector3 operator- (const MyVector3 right) const;//Operator for -
		MyVector3 operator -(); //Operator for inverting Vectors
		MyVector3 operator* (const double t_double) const;
		double operator* (const MyVector3 t_vector) const;
		MyVector3 operator* (const float t_float) const;
		MyVector3 operator* (const int t_int) const;
		MyVector3 operator^ (const MyVector3 t_vector) const;
		MyVector3 operator * (Matrix3 t_matrix) const;
		std::string toString(); // String and operator declarations

	};
#endif