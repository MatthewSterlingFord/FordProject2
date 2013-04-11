//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           Vector3d.cpp
//  Description:    Vectors and Points in 3d
//  Programmer:     Dave Mount
//  For:            CMSC 425 - Spring 2013
//-----------------------------------------------------------------------

#include "Vector3d.h"

using namespace std;					// make std:: accessible
using namespace Geom;					// make Geom:: accessible

//----------------------------------------------------------------------
// Constructors and Destructors
//----------------------------------------------------------------------

Vector3d::Vector3d()
	{ vec[X] = vec[Y] = vec[Z] = vec[W] = 0; }

Vector3d::Vector3d(Scalar x, Scalar y, Scalar z, Scalar w)
	{ vec[X] = x; vec[Y] = y; vec[Z] = z; vec[W] = w; }

Vector3d::Vector3d(const Vector3d& v)
{
	for (int i = 0; i < N_COORDS; i++) vec[i] = v[i];
}

//----------------------------------------------------------------------
// Assignment operators
//----------------------------------------------------------------------

Vector3d& Vector3d::operator=(const Vector3d& v)
{
	if (this != &v) {					// ignore assignment to self
		for (int i = 0; i < N_COORDS; i++) vec[i] = v[i];
	}
	return *this;
}

Vector3d& Vector3d::operator+=(const Vector3d& v)
{
	for (int i = 0; i < N_COORDS; i++) vec[i] += v[i];
	return *this;
}

Vector3d& Vector3d::operator-=(const Vector3d& v)
{
	for (int i = 0; i < N_COORDS; i++) vec[i] -= v[i];
	return *this;
}

Vector3d& Vector3d::operator*=(Scalar s)
{
	for (int i = 0; i < N_COORDS; i++) vec[i] *= s;
	return *this;
}

Vector3d& Vector3d::operator/=(Scalar s)
{
	for (int i = 0; i < N_COORDS; i++) vec[i] /= s;
	return *this;
}

//----------------------------------------------------------------------
// Arithmetic operators
//----------------------------------------------------------------------

Vector3d operator-(const Vector3d& v)
	{ return Vector3d(-v[X], -v[Y], -v[Z], -v[W]); }

Vector3d operator+(const Vector3d& v, const Vector3d& u)
	{ return Vector3d(v[X] + u[X], v[Y] + u[Y], v[Z] + u[Z], v[W] + u[W]); }

Vector3d operator-(const Vector3d& v, const Vector3d& u)
	{ return Vector3d(v[X] - u[X], v[Y] - u[Y], v[Z] - u[Z], v[W] - u[W]); }

Vector3d operator*(Scalar s, const Vector3d& v)
	{ return Vector3d(s * v[X], s * v[Y], s * v[Z], s * v[W]); }

Vector3d operator*(const Vector3d& v, Scalar s)
	{ return Vector3d(v[X] * s, v[Y] * s, v[Z] * s, v[W] * s); }

Vector3d operator/(const Vector3d& v, Scalar s)
	{ return Vector3d(v[X] / s, v[Y] / s, v[Z] /s, v[W] /s); }

//----------------------------------------------------------------------
//	Additional methods
//
//	These methods ignore the homogeneous coordinate and so treat
//	everything like a vector.
//----------------------------------------------------------------------

Scalar Vector3d::length() const
{
	Scalar sum = 0;
	for (int i = 0; i < DIMENSION; i++)
		sum += vec[i] * vec[i];
	return sqrt(sum);
}

void Vector3d::clamp(Scalar min, Scalar max)
{
	for (int i = 0; i < DIMENSION; i++) {
		if (vec[i] < min) vec[i] = min;
		else if (vec[i] > max) vec[i] = max;
	}
}

void Vector3d::clampLength(Scalar min, Scalar max)
{
	Scalar len = length();
	if (max < GEOM_INF && len > max) {	// too long?
		for (int i = 0; i < DIMENSION; i++)
			vec[i] *= (max/len);
	}
	else if (min > 0 && len < min) {	// too short?
		for (int i = 0; i < DIMENSION; i++)
			vec[i] *= (min/len);
    }
}

void Vector3d::normalize()				// normalize to unit length
{
	Scalar len = length();
	if (len < GEOM_EPS) return;			// too short to normalize?
	for (int i = 0; i < DIMENSION; i++)
		vec[i] /= len;
}

										// functional form 
Vector3d Vector3d::normalize(const Vector3d& v)
{
	Scalar len = v.length();
	return (len < GEOM_EPS ? v : (1/len) * v);
}

//----------------------------------------------------------------------
// Additional utilities
//----------------------------------------------------------------------

Scalar Vector3d::dot(const Vector3d& v, const Vector3d& u)
{
	Scalar sum = 0;
	for (int i = 0; i < DIMENSION; i++)
		sum += v[i] * u[i];
	return  sum;
}
										// cross product
Vector3d Vector3d::cross(const Vector3d& v, const Vector3d& u)
{
	return Vector3d(
		v[Y]*u[Z] - v[Z]*u[Y],
		v[Z]*u[X] - v[X]*u[Z],
		v[X]*u[Y] - v[Y]*u[X],
		0);
}

//----------------------------------------------------------------------
//	Projection:
//		parallelPart - parallel part of projection of v onto u
//		orthogonalPart - orthogonal part of projection of v onto u
//
//		Thus: parallelPart(v, u) + orthogonalPart(v, u) == v
//----------------------------------------------------------------------

Vector3d Vector3d::parallelPart(const Vector3d& v, const Vector3d& u)
{
	return Vector3d((Vector3d::dot(v, u)*(1/Vector3d::dot(u, u))) * u);
}

Vector3d Vector3d::orthogonalPart(const Vector3d& v, const Vector3d& u)
{
	return v - Vector3d::parallelPart(v, u);
}


//----------------------------------------------------------------------
// Converts Cartesian to spherical coords
//	from (x,y,z) to (radius, theta, phi) in radians, where theta gives
//	the longitude and phi gives the latitude (start at 0 for north pole)
//----------------------------------------------------------------------

Vector3d Vector3d::cartesianToSpherical(const Vector3d& v)
{
	Scalar lenXY = sqrt(v[X]*v[X] + v[Y]*v[Y]);

	Vector3d spherical;
	spherical[X] = v.length();			// radius
	spherical[Y] = atan2(v[Y], v[X]);	// theta
	spherical[Z] = -atan2(v[Z], lenXY);	// phi

	return spherical;
}

//----------------------------------------------------------------------
// Converts spherical to Cartesian
//	from (radiius, theta, phi) in radians to (x,y,z)
//----------------------------------------------------------------------

Vector3d Vector3d::sphericalToCartesian(const Vector3d& v)
{
	Scalar cartX = v[X] * cos(v[Y]) * sin(v[Z]);
	Scalar cartY = v[X] * sin(v[Y]) * sin(v[Z]);
	Scalar cartZ = v[X] * cos(v[Z]);

	return Vector(cartX, cartY, cartZ);
}

//----------------------------------------------------------------------
//	Common vectors
//----------------------------------------------------------------------
Vector3d Vector3d::zero()	{ return Vector(0, 0, 0); }
Vector3d Vector3d::xUnit()	{ return Vector(1, 0, 0); }
Vector3d Vector3d::yUnit()	{ return Vector(0, 1, 0); }
Vector3d Vector3d::zUnit()	{ return Vector(0, 0, 1); }

//----------------------------------------------------------------------
// Additional functions
//----------------------------------------------------------------------

										// create a vector (w = 0)
Vector3d Geom::Vector(Scalar x, Scalar y, Scalar z)
	{ return Vector3d(x, y, z, 0); }

										// create a point (w = 1)
Point3d Geom::Point(Scalar x, Scalar y, Scalar z)
	{ return Point3d(x, y, z, 1); }

Point3d Geom::origin()					// origin point
	{ return Point(0, 0, 0); }

										// affine combination (1-a)*p + a*q
Point3d Geom::affineComb(Scalar a, const Point3d& p, const Point3d& q)
	{ return Point3d((1 - a)*p[X] + a*q[X], (1 - a)*p[Y] + a*q[Y], (1 - a)*p[Z] + a*q[Z], (1 - a)*p[W] + a*q[W]); }

										// distance from p to q
Scalar Geom::distance(const Point3d& p, const Point3d& q)
	{ return (q - p).length(); }

//----------------------------------------------------------------------
//	Output operator
//----------------------------------------------------------------------
ostream& operator<<(ostream& out, const Vector3d& v)
	{ return out << "[" << v[X] << ", " << v[Y] << ", " << v[Z] << "]"; }

//----------------------------------------------------------------------
//	Check homogenous (for debugging)
//----------------------------------------------------------------------
void Vector3d::checkMe(GeomType t) const
{
	if (fabs(double(vec[W])) < 0.001 && t == VECTOR3D) return;
	else if (fabs(double(vec[W] - 1)) < 0.001 && t == POINT3D) return;
	else {
		if (t == VECTOR3D) cout << "Vector: ";
		else if (t == POINT3D) cout << "Point: ";
		else cout << "Geom: ";
		cout << "[" << vec[X] << ", " << vec[Y] << ", " << vec[Z] << ", " << vec[W] << "]" << " is invalid\n";
	}
}

