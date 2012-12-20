#ifndef __CVECTOR_H
#define __CVECTOR_H

#include <math.h>


typedef float scalar_t;

class CVector
{
public:
     scalar_t x;
     scalar_t y;
     scalar_t z;    // x,y,z coordinates

public:
     CVector(scalar_t a = 0, scalar_t b = 0, scalar_t c = 0) : x(a), y(b), z(c) {}
     CVector(const CVector &vec) : x(vec.x), y(vec.y), z(vec.z) {}

     // vector assignment
     const CVector &operator=(const CVector &vec)
     {
          x = vec.x;
          y = vec.y;
          z = vec.z;

          return *this;
     }

     // vecector equality
     const bool operator==(const CVector &vec) const
     {
          return ((x == vec.x) && (y == vec.y) && (z == vec.z));
     }

     // vecector inequality
     const bool operator!=(const CVector &vec) const
     {
          return !(*this == vec);
     }

     // vector add
     const CVector operator+(const CVector &vec) const
     {
          return CVector(x + vec.x, y + vec.y, z + vec.z);
     }

     // vector add (opposite of negation)
     const CVector operator+() const
     {    
          return CVector(*this);
     }

     // vector increment
     const CVector& operator+=(const CVector& vec)
     {    x += vec.x;
          y += vec.y;
          z += vec.z;
          return *this;
     }

     // vector subtraction
     const CVector operator-(const CVector& vec) const
     {    
          return CVector(x - vec.x, y - vec.y, z - vec.z);
     }
     
     // vector negation
     const CVector operator-() const
     {    
          return CVector(-x, -y, -z);
     }

     // vector decrement
     const CVector &operator-=(const CVector& vec)
     {
          x -= vec.x;
          y -= vec.y;
          z -= vec.z;

          return *this;
     }

     // scalar self-multiply
     const CVector &operator*=(const scalar_t &s)
     {
          x *= s;
          y *= s;
          z *= s;
          
          return *this;
     }

     // scalar self-divecide
     const CVector &operator/=(const scalar_t &s)
     {
          const float recip = 1/s; // for speed, one divecision

          x *= recip;
          y *= recip;
          z *= recip;

          return *this;
     }

     // post multiply by scalar
     const CVector operator*(const scalar_t &s) const
     {
          return CVector(x*s, y*s, z*s);
     }

     // pre multiply by scalar
     friend inline const CVector operator*(const scalar_t &s, const CVector &vec)
     {
          return vec*s;
     }

/*   friend inline const CVector operator*(const CVector &vec, const scalar_t &s)
     {
          return CVector(vec.x*s, vec.y*s, vec.z*s);
     }

*/   // divecide by scalar
     const CVector operator/(scalar_t s) const
     {
          s = 1/s;

          return CVector(s*x, s*y, s*z);
     }

     // cross product
     const CVector CrossProduct(const CVector &vec) const
     {
          return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
     }

     // cross product
     const CVector operator^(const CVector &vec) const
     {
          return CVector(y*vec.z - z*vec.y, z*vec.x - x*vec.z, x*vec.y - y*vec.x);
     }

     // dot product
     const scalar_t DotProduct(const CVector &vec) const
     {
          return x*vec.x + y*vec.y + z*vec.z;
     }

     // dot product
     const scalar_t operator%(const CVector &vec) const
     {
          return x*vec.x + y*vec.y + z*vec.z;
     }


     // length of vector
     const scalar_t Length() const
     {
          return (scalar_t)sqrt((double)(x*x + y*y + z*z));
     }

     // return the unit vector
     const CVector UnitVector() const
     {
          return (*this) / Length();
     }

     // normalize this vector
     void Normalize()
     {
          (*this) /= Length();
     }

     const scalar_t operator!() const
     {
          return sqrtf(x*x + y*y + z*z);
     }

     // return vector with specified length
     const CVector operator | (const scalar_t length) const
     {
          return *this * (length / !(*this));
     }

     // set length of vector equal to length
     const CVector& operator |= (const float length)
     {
          return *this = *this | length;
     }

     // return angle between two vectors
     const float inline Angle(const CVector& normal) const
     {
          return acosf(*this % normal);
     }

     // reflect this vector off surface with normal vector
     const CVector inline Reflection(const CVector& normal) const
     {    
          const CVector vec(*this | 1);     // normalize this vector
          return (vec - normal * 2.0 * (vec % normal)) * !*this;
     }

};

#endif 