#include "Vector3.h"
//@Author Sean Nash De Andrade
//@Login C00217019
//Cube Rotation Assignment
double MyVector3::getX()
{
	return m_x;
}

double MyVector3::getY()
{
	return m_y;
}

double MyVector3::getZ()
{
	return m_z;
}
std::string MyVector3::toString()//Handles the toString Conversion
{
	char tmpbuf[256];
	sprintf_s(tmpbuf, "[ %g, %g, %g ]", m_x, m_y, m_z);
	return tmpbuf;
}

MyVector3::MyVector3()// Constructor 1 - Default Zero Vector
{	
		m_x = 0.0f;
		m_y = 0.0f;
		m_z = 0.0f;
}

MyVector3::MyVector3(double x1, double y1, double z1)	// Constructor 2 - To allow other values for X, Y and Z to be declared
{
		m_x = x1;
		m_y = y1;
		m_z = z1;
	
}

double MyVector3::length()// A method to return the length of the vector
{
	  
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	
}

double MyVector3::lengthSquared()// A method to return the length squared of the vector
{
	  
		return (m_x * m_x + m_y * m_y + m_z * m_z);
	
}
 
void MyVector3::normalise()// A method to reduce the length of the vector to 1.0 keeping the direction the same
{
		if (length() > 0.0)
		{  // Check for divide by zero
			double magnit = length();
			m_x /= magnit;
			m_y /= magnit;
			m_z /= magnit;
		}	
}

MyVector3 MyVector3::operator + (const MyVector3 right) const //Each component must be added to the other similar component
{
	return MyVector3(m_x + right.m_x, m_y + right.m_y, m_z + right.m_z); 
}



MyVector3 MyVector3::operator- (const MyVector3 right) const
{
	return MyVector3(m_x - right.m_x, m_y - right.m_y, m_z - right.m_z);//Each component must be taken to the other similar component
}

MyVector3 MyVector3::operator - ()
{
	std::cout << "Invert";
	return MyVector3(-m_x,-m_y,-m_z);
}

MyVector3 MyVector3::operator*(const double scalar) const//Each component Must be multiplied by the Scalar
{
	return MyVector3(m_x * scalar, m_y * scalar, m_z * scalar); 
}

double MyVector3::operator*(const MyVector3 right) const// An overloaded operator * to return the scalar product of 2 vectors
{
	return (m_x * right.m_x + m_y * right.m_y + m_z * right.m_z);
}

MyVector3 MyVector3::operator*(const float k) const
{
	return MyVector3(m_x * k, m_y * k, m_z * k);
}

MyVector3 MyVector3::operator*(const int k) const
{
	return MyVector3(m_x * k, m_y * k, m_z * k);
}

MyVector3 MyVector3::operator^(const MyVector3 right) const// An overloaded operator ^ to return the vector product of 2 vectors
{
	return MyVector3(m_y * right.m_z - m_z * right.m_y, m_z * right.m_x - m_x * right.m_z, m_x * right.m_y - m_y * right.m_x);
}

MyVector3 MyVector3::operator*(Matrix3 t_matrix) const
{
	return MyVector3((t_matrix.A11() * m_x) + (t_matrix.A12() * m_y) + (t_matrix.A13() * m_z),
		(t_matrix.A21() * m_x) + (t_matrix.A22() * m_y) + (t_matrix.A23() * m_z),
		(t_matrix.A31() * m_x) + (t_matrix.A32() * m_y) + (t_matrix.A33() * m_z));
}

