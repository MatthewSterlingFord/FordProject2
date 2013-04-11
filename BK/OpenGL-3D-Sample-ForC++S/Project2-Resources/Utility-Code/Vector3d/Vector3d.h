//-----------------------------------------------------------------------
//  Best viewed with tabs every 4 columns
//-----------------------------------------------------------------------
//  File:           Vector3d.h
//  Description:    Vectors and Points in 3d
//  Programmer:     Dave Mount
//  For:            CMSC 425 - Spring 2013
//
//  We represent points and vectors in homogeneous coordinates by setting
//  the last (w) coordinate to 1 for points and 0 for vectors. We do no 
//	type checking for valid point-vector operations.
//
//	WARNING! WARNING! WARNING! WARNING! WARNING! WARNING! WARNING!
//
//	This class defines two types, Vector3d and Point3d, but they are
//	in fact exactly the same object (we typedef Point3d to be Vector3d).
//	The only means of distinguishing them is by looking at the last
//	coordinate. If it is a 0, the object is a vector (even if it is
//	declared to be a Point3d). If it is a 1, the object is a point (even
//	if it is declared to be a Vector3d). If it is anything else, then
//	the object is undefined. (You're on your own.)
//
//	There are two ways to define a point or vector object, either by
//	giving all four coordinates or by calling the functions Vector or
//	Point. The latter two functions automatically set the fourth
//	coordinate. For example:
//
//	Vector3d u(1, 2, 3, 0);				// OK: this is a vector
//	Point3d p(1, 2, 3, 1);				// OK: this is a point
//	Vector3d v = Geom::Vector(1, 2, 3);	// OK: this is a vector (w = 0)
//	Point3d q = Geom::Point(1, 2, 3);	// OK: this is a point (w = 1)
//
//	Point3d r(1, 2, 3, 0);				// WARNING: This is a vector!
//	Vector3d w = Geom::Point(1, 2, 3);	// WARNING: This is a point!
//-----------------------------------------------------------------------

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <cstdlib>						// standard C definitions
#include <cmath>						// math includes
#include <iostream>						// C++ I/O

//-----------------------------------------------------------------------
// Global types
//-----------------------------------------------------------------------

typedef double Scalar;					// Scalar is an alias for double

class Vector3d;							// defined below
typedef Vector3d Point3d;				// Point3d is alias for Vector3d

//-----------------------------------------------------------------------
// Useful constants
//-----------------------------------------------------------------------

namespace Geom {
  enum {X = 0, Y = 1, Z = 2, W = 3};	// coordinate names
  enum GeomType {VECTOR3D, POINT3D, ANY}; // geometric object types
  const int DIMENSION = 3;				// dimension of space
  const int N_COORDS = 4;				// number of (homogeneous) coordinates
  const Scalar GEOM_EPS = 1.0E-6;		// small number for floating comparisons
  const Scalar GEOM_INF = 1.0E+30;		// a big number
										// define PI and PI/2, in case your
										// compiler doesn't have it
  const Scalar PI	= 3.14159265358979323846;
  const Scalar PI_2	= 1.57079632679489661923;
}

//-----------------------------------------------------------------------
//	Vector3d - 3-dimensional vector
//
//	This class encapsulates both 3-d point and vector methods, with
//	overloaded operators for simple arithmetic. A vector is represented
//	using homogeneous coordinates, where the last coordinate is 0. Rather
//	than defining a separate class Point3d, we typedef Point3d to Vecto3d
//	just reuse all the methods (without any error checking). All valid
//	combinations of points and vectors "should" work properly (up to
//	small floating point roundoff errors).
//
//	Summary of methods: (x,y,z,w,s are scalars and v and u are vectors)
//		Vector3d()					create vector (0,0,0)
//		Vector3d(x,y,z,w)			create vector (x,y,z,w)
//									[w = 0 for vector, w = 1 for point]
//		Vector3d(v)					create a copy of vector v
//		u = v						vector assignment
//		u += v						u = u + v
//		u -= v						u = u - v
//		u *= s						u = u * s
//		u /= s						u = u / s
//		u + v						returns u + v
//		u - v						returns u - v
//		s * u						returns s * u
//		u * s						returns u * s
//		u / s						returns u / s
//		u.length()					returns u's length
//		u.clamp(min, max)			clamp each coord to interval [min,max]
//		u.clampLength(min, max)		clamp length to interval [min,max]
//		u.normalize()				normalize u's length to unity
//		Vector3d::normalize(u)		returns unit vector in u's direction
//									(u is not modified)
//		Vector3d::dot(v,u)			returns (v . u)
//		Vector3d::cross(v,u)		returns cross product (v x u)
//		Vector3d::parProject(v,u)	returns parallel part of projection
//									of v onto u
//		Vector3d::orthProject(v,u)	returns orthogonal part of
//									projection of v onto u
//		Vector3d::cartesianToSpherical(v) return conversion of v from
//									Cartesian to Spherical coords
//		Vector3d::sphericalToCartesian(v) return conversion of v from
//									Spherical to Cartesian coords
//		Vector3d::zero()			return vector (0,0,0)
//		Vector3d::xUnit()			return vector (1,0,0)
//		Vector3d::yUnit()			return vector (0,1,0)
//		Vector3d::zUnit()			return vector (0,0,1)
//
//		Geom::Point(x, y, z)		return point (x, y, z, 1)
//		Geom::Vector(x, y, z)		return vector (x, y, z, 0)
//
//		Geom::affineComb(a, p, q)	returns (1-a)*p + a*q
//		Geom::distance(p, q)		returns distance from p to q
//		checkMe(GeomType t)			check that I'm of type "t"
//
//		cout << u					output u
//----------------------------------------------------------------------

class Vector3d {
public:
	Vector3d();							// constructors and destructors
	Vector3d(Scalar x, Scalar y, Scalar z, Scalar w);
	Vector3d(const Vector3d& v);

	Scalar operator[](int i) const;		// index (read only)
	Scalar& operator[](int i);			// index (read/write)
										// assignment operators
	Vector3d& operator=(const Vector3d& v);
	Vector3d& operator+= (const Vector3d& v);
	Vector3d& operator-=(const Vector3d& v);
	Vector3d& operator*=(Scalar s);
	Vector3d& operator/=(Scalar s);
										// additional methods
	Scalar length() const;						// get length
	void clamp(Scalar min, Scalar max);			// clamp coords to [min,max]
	void clampLength(Scalar min, Scalar max);	// clamp length to [min,max]
	void normalize();							// normalize to unit length

										// additional utilities
	static Vector3d normalize(const Vector3d& v);
	static Scalar dot(const Vector3d& v, const Vector3d& u);
	static Vector3d cross(const Vector3d& v, const Vector3d& u);
	static Vector3d parallelPart(const Vector3d& v, const Vector3d& u);
	static Vector3d orthogonalPart(const Vector3d& v, const Vector3d& u);
	static Vector3d cartesianToSpherical(const Vector3d& v);
	static Vector3d sphericalToCartesian(const Vector3d& v);

										// commonly used vectors
	static Vector3d zero();						// (0, 0, 0, 0)
	static Vector3d xUnit();					// (1, 0, 0, 0)
	static Vector3d yUnit();					// (0, 1, 0, 0)
	static Vector3d zUnit();					// (0, 0, 1, 0)
	void checkMe(Geom::GeomType t) const;	// check last coord
private:
	Scalar vec[Geom::N_COORDS];			// coordinate array
};

										// vector arithmetic
Vector3d operator-(const Vector3d& v);
Vector3d operator+(const Vector3d& v, const Vector3d& u);
Vector3d operator-(const Vector3d& v, const Vector3d& u);
Vector3d operator*(Scalar s, const Vector3d& v);
Vector3d operator*(const Vector3d& v, Scalar s);
Vector3d operator/(const Vector3d& v, Scalar s);

namespace Geom {
										// create a vector (with w = 0)
	Point3d Vector(Scalar x = 0, Scalar y = 0, Scalar z = 0);
										// create a point (with w = 1)
	Point3d Point(Scalar x = 0, Scalar y = 0, Scalar z = 0);
	Point3d origin();					// = Point(0, 0, 0)
 										// affine comb (1-a)*p + a*q
	Point3d affineComb(Scalar a, const Point3d& p, const Point3d& q);
										// distance from p to q
	Scalar distance(const Point3d& p, const Point3d& q);
}

//----------------------------------------------------------------------
//	Inline methods (for efficiency)
//----------------------------------------------------------------------
											// index (read only)
inline Scalar Vector3d::operator[](int i) const
	{ return vec[i]; }

inline Scalar& Vector3d::operator[](int i)	// index (read/write)
	{ return vec[i]; }

//----------------------------------------------------------------------
//	Output operator
//----------------------------------------------------------------------

std::ostream& operator<<(std::ostream& out, const Vector3d& v);

#endif
