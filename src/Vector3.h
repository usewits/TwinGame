#pragma once
#include <math.h>

//Inline vector class (a position in 3D space)

//This source file contains parts taken from OGRE (Object-oriented Graphics Rendering Engine)
//For the latest info, see http://www.ogre3d.org/

class Vector3
{
public:
	float x, y, z;

	Vector3(void){}
	Vector3( const float X, const float Y, const float Z ) : x(X), y(Y), z(Z) {}
	Vector3( const float Coordinate[3] ) : x(Coordinate[0]), y(Coordinate[1]), z(Coordinate[2]) {}
	Vector3( float* const Coordinate ) : x(Coordinate[0]), y(Coordinate[1]), z(Coordinate[2]) {}
	Vector3( const float scaler ) : x(scaler), y(scaler), z(scaler) {}
	~Vector3(void){}


	inline float operator [] ( const int i ) const { return *(&x+i); }
	inline float& operator [] ( const int i ) { return *(&x+i); }
	/// Pointer accessor for direct copying
	inline float* ptr() { return &x; }
	/// Pointer accessor for direct copying
	inline const float* ptr() const { return &x; }

    /** Assigns the value of the other vector.
        @param
            rkVector The other vector
    */
    inline Vector3& operator = ( const Vector3& rkVector )
    {
        x = rkVector.x;
        y = rkVector.y;
        z = rkVector.z;

        return *this;
    }

    inline Vector3& operator = ( const float fScaler )
    {
        x = fScaler;
        y = fScaler;
        z = fScaler;

        return *this;
    }

    inline bool operator == ( const Vector3& rkVector ) const
    {
        return ( x == rkVector.x && y == rkVector.y && z == rkVector.z );
    }

    inline bool operator != ( const Vector3& rkVector ) const
    {
        return ( x != rkVector.x || y != rkVector.y || z != rkVector.z );
    }

    // arithmetic operations
    inline Vector3 operator + ( const Vector3& rkVector ) const
    {
        return Vector3(
            x + rkVector.x,
            y + rkVector.y,
            z + rkVector.z);
    }

    inline Vector3 operator - ( const Vector3& rkVector ) const
    {
        return Vector3(
            x - rkVector.x,
            y - rkVector.y,
            z - rkVector.z);
    }

    inline Vector3 operator * ( const float fScalar ) const
    {
        return Vector3(
            x * fScalar,
            y * fScalar,
            z * fScalar);
    }

    inline Vector3 operator * ( const Vector3& rhs) const
    {
        return Vector3(
            x * rhs.x,
            y * rhs.y,
            z * rhs.z);
    }

    inline Vector3 operator / ( const float fScalar ) const
    {
        float fInv = 1.0f / fScalar;

        return Vector3(
            x * fInv,
            y * fInv,
            z * fInv);
    }

    inline Vector3 operator / ( const Vector3& rhs) const
    {
        return Vector3(
            x / rhs.x,
            y / rhs.y,
            z / rhs.z);
    }

    inline const Vector3& operator + () const
    {
        return *this;
    }

    inline Vector3 operator - () const
    {
        return Vector3(-x, -y, -z);
    }

    // overloaded operators to help Vector3
    inline friend Vector3 operator * ( const float fScalar, const Vector3& rkVector )
    {
        return Vector3(
            fScalar * rkVector.x,
            fScalar * rkVector.y,
            fScalar * rkVector.z);
    }

    inline friend Vector3 operator / ( const float fScalar, const Vector3& rkVector )
    {
        return Vector3(
            fScalar / rkVector.x,
            fScalar / rkVector.y,
            fScalar / rkVector.z);
    }

    inline friend Vector3 operator + (const Vector3& lhs, const float rhs)
    {
        return Vector3(
            lhs.x + rhs,
            lhs.y + rhs,
            lhs.z + rhs);
    }

    inline friend Vector3 operator + (const float lhs, const Vector3& rhs)
    {
        return Vector3(
            lhs + rhs.x,
            lhs + rhs.y,
            lhs + rhs.z);
    }

    inline friend Vector3 operator - (const Vector3& lhs, const float rhs)
    {
        return Vector3(
            lhs.x - rhs,
            lhs.y - rhs,
            lhs.z - rhs);
    }

    inline friend Vector3 operator - (const float lhs, const Vector3& rhs)
    {
        return Vector3(
            lhs - rhs.x,
            lhs - rhs.y,
            lhs - rhs.z);
    }

    // arithmetic updates
    inline Vector3& operator += ( const Vector3& rkVector )
    {
        x += rkVector.x;
        y += rkVector.y;
        z += rkVector.z;

        return *this;
    }

    inline Vector3& operator += ( const float fScalar )
    {
        x += fScalar;
        y += fScalar;
        z += fScalar;
        return *this;
    }

    inline Vector3& operator -= ( const Vector3& rkVector )
    {
        x -= rkVector.x;
        y -= rkVector.y;
        z -= rkVector.z;

        return *this;
    }

    inline Vector3& operator -= ( const float fScalar )
    {
        x -= fScalar;
        y -= fScalar;
        z -= fScalar;
        return *this;
    }

    inline Vector3& operator *= ( const float fScalar )
    {
        x *= fScalar;
        y *= fScalar;
        z *= fScalar;
        return *this;
    }

    inline Vector3& operator *= ( const Vector3& rkVector )
    {
        x *= rkVector.x;
        y *= rkVector.y;
        z *= rkVector.z;

        return *this;
    }

    inline Vector3& operator /= ( const float fScalar )
    {
        float fInv = 1.0f / fScalar;

        x *= fInv;
        y *= fInv;
        z *= fInv;

        return *this;
    }

    inline Vector3& operator /= ( const Vector3& rkVector )
    {
        x /= rkVector.x;
        y /= rkVector.y;
        z /= rkVector.z;

        return *this;
    }


    /** Returns the length (magnitude) of the vector.
        @warning
            This operation requires a square root and is expensive in
            terms of CPU operations. If you don't need to know the exact
            length (e.g. for just comparing lengths) use squaredLength()
            instead.
    */
    inline float length () const
    {
        return sqrt( x * x + y * y + z * z );
    }

    /** Returns the square of the length(magnitude) of the vector.
        @remarks
            This  method is for efficiency - calculating the actual
            length of a vector requires a square root, which is expensive
            in terms of the operations required. This method returns the
            square of the length of the vector, i.e. the same as the
            length but before the square root is taken. Use this if you
            want to find the longest / shortest vector without incurring
            the square root.
    */
    inline float squaredLength () const
    {
        return x * x + y * y + z * z;
    }

    /** Returns the distance to another vector.
        @warning
            This operation requires a square root and is expensive in
            terms of CPU operations. If you don't need to know the exact
            distance (e.g. for just comparing distances) use squaredDistance()
            instead.
    */
    inline float distance(const Vector3& rhs) const
    {
        return (*this - rhs).length();
    }

    /** Returns the square of the distance to another vector.
        @remarks
            This method is for efficiency - calculating the actual
            distance to another vector requires a square root, which is
            expensive in terms of the operations required. This method
            returns the square of the distance to another vector, i.e.
            the same as the distance but before the square root is taken.
            Use this if you want to find the longest / shortest distance
            without incurring the square root.
    */
    inline float squaredDistance(const Vector3& rhs) const
    {
        return (*this - rhs).squaredLength();
    }

    /** Calculates the dot (scalar) product of this vector with another.
        @remarks
            The dot product can be used to calculate the angle between 2
            vectors. If both are unit vectors, the dot product is the
            cosine of the angle; otherwise the dot product must be
            divided by the product of the lengths of both vectors to get
            the cosine of the angle. This result can further be used to
            calculate the distance of a point from a plane.
        @param
            vec Vector with which to calculate the dot product (together
            with this one).
        @returns
            A float representing the dot product value.
    */
    inline float dotProduct(const Vector3& vec) const
    {
        return x * vec.x + y * vec.y + z * vec.z;
    }

    /** Calculates the absolute dot (scalar) product of this vector with another.
        @remarks
            This function work similar dotProduct, except it use absolute value
            of each component of the vector to computing.
        @param
            vec Vector with which to calculate the absolute dot product (together
            with this one).
        @returns
            A float representing the absolute dot product value.
    */
    inline float absDotProduct(const Vector3& vec) const
    {
        return fabs(x * vec.x) + fabs(y * vec.y) + fabs(z * vec.z);
    }

    /** Normalises the vector.
        @remarks
            This method normalises the vector such that it's
            length / magnitude is 1. The result is called a unit vector.
        @note
            This function will not crash for zero-sized vectors, but there
            will be no changes made to their components.
        @returns The previous length of the vector.
    */
    inline float normalise()
    {
        float fLength = sqrt( x * x + y * y + z * z );

        // Will also work for zero-sized vectors, but will change nothing
        if ( fLength > 1e-08 )
        {
            float fInvLength = 1.0f / fLength;
            x *= fInvLength;
            y *= fInvLength;
            z *= fInvLength;
        }

        return fLength;
    }

    /** Calculates the cross-product of 2 vectors, i.e. the vector that
        lies perpendicular to them both.
        @remarks
            The cross-product is normally used to calculate the normal
            vector of a plane, by calculating the cross-product of 2
            non-equivalent vectors which lie on the plane (e.g. 2 edges
            of a triangle).
        @param
            vec Vector which, together with this one, will be used to
            calculate the cross-product.
        @returns
            A vector which is the result of the cross-product. This
            vector will <b>NOT</b> be normalised, to maximise efficiency
            - call Vector3::normalise on the result if you wish this to
            be done. As for which side the resultant vector will be on, the
            returned vector will be on the side from which the arc from 'this'
            to rkVector is anticlockwise, e.g. UNIT_Y.crossProduct(UNIT_Z)
            = UNIT_X, whilst UNIT_Z.crossProduct(UNIT_Y) = -UNIT_X.
			This is because OGRE uses a right-handed coordinate system.
        @par
            For a clearer explanation, look a the left and the bottom edges
            of your monitor's screen. Assume that the first vector is the
            left edge and the second vector is the bottom edge, both of
            them starting from the lower-left corner of the screen. The
            resulting vector is going to be perpendicular to both of them
            and will go <i>inside</i> the screen, towards the cathode tube
            (assuming you're using a CRT monitor, of course).
    */
    inline Vector3 crossProduct( const Vector3& rkVector ) const
    {
        return Vector3(
            y * rkVector.z - z * rkVector.y,
            z * rkVector.x - x * rkVector.z,
            x * rkVector.y - y * rkVector.x);
    }

    /** Returns a vector at a point half way between this and the passed
        in vector.
    */
    inline Vector3 midPoint( const Vector3& vec ) const
    {
        return Vector3(
            ( x + vec.x ) * 0.5f,
            ( y + vec.y ) * 0.5f,
            ( z + vec.z ) * 0.5f );
    }

    /** Returns true if the vector's scalar components are all greater
        that the ones of the vector it is compared against.
    */
    inline bool operator < ( const Vector3& rhs ) const
    {
        if( x < rhs.x && y < rhs.y && z < rhs.z )
            return true;
        return false;
    }

    /** Returns true if the vector's scalar components are all smaller
        that the ones of the vector it is compared against.
    */
    inline bool operator > ( const Vector3& rhs ) const
    {
        if( x > rhs.x && y > rhs.y && z > rhs.z )
            return true;
        return false;
    }

    /** Sets this vector's components to the minimum of its own and the
        ones of the passed in vector.
        @remarks
            'Minimum' in this case means the combination of the lowest
            value of x, y and z from both vectors. Lowest is taken just
            numerically, not magnitude, so -1 < 0.
    */
    inline void makeFloor( const Vector3& cmp )
    {
        if( cmp.x < x ) x = cmp.x;
        if( cmp.y < y ) y = cmp.y;
        if( cmp.z < z ) z = cmp.z;
    }

    /** Sets this vector's components to the maximum of its own and the
        ones of the passed in vector.
        @remarks
            'Maximum' in this case means the combination of the highest
            value of x, y and z from both vectors. Highest is taken just
            numerically, not magnitude, so 1 > -3.
    */
    inline void makeCeil( const Vector3& cmp )
    {
        if( cmp.x > x ) x = cmp.x;
        if( cmp.y > y ) y = cmp.y;
        if( cmp.z > z ) z = cmp.z;
    }

    /** Generates a vector perpendicular to this vector (eg an 'up' vector).
        @remarks
            This method will return a vector which is perpendicular to this
            vector. There are an infinite number of possibilities but this
            method will guarantee to generate one of them. If you need more
            control you should use the Quaternion class.
    */
  //  inline Vector3 perpendicular(void) const
  //  {
  //      static const float fSquareZero = 1e-06 * 1e-06;

  //      Vector3 perp = this->crossProduct( Vector3::UNIT_X );

  //      // Check length
  //      if( perp.squaredLength() < fSquareZero )
  //      {
  //          /* This vector is the Y axis multiplied by a scalar, so we have
  //              to use another axis.
  //          */
  //          perp = this->crossProduct( Vector3::UNIT_Y );
  //      }
		//perp.normalise();

  //      return perp;
  //  }

	/** Gets the angle between 2 vectors.
	@remarks
		Vectors do not have to be unit-length but must represent directions.
	*/
	//inline Radian angleBetween(const Vector3& dest)
	//{
	//	float lenProduct = length() * dest.length();

	//	// Divide by zero check
	//	if(lenProduct < 1e-6f)
	//		lenProduct = 1e-6f;

	//	float f = dotProduct(dest) / lenProduct;

	//	f = Math::Clamp(f, (float)-1.0, (float)1.0);
	//	return Math::ACos(f);

	//}
    /** Gets the shortest arc quaternion to rotate this vector to the destination
        vector.
    @remarks
        If you call this with a dest vector that is close to the inverse
        of this vector, we will rotate 180 degrees around the 'fallbackAxis'
		(if specified, or a generated axis if not) since in this case
		ANY axis of rotation is valid.
    */
  //  Quaternion getRotationTo(const Vector3& dest,
		//const Vector3& fallbackAxis = Vector3::ZERO) const
  //  {
  //      // Based on Stan Melax's article in Game Programming Gems
  //      Quaternion q;
  //      // Copy, since cannot modify local
  //      Vector3 v0 = *this;
  //      Vector3 v1 = dest;
  //      v0.normalise();
  //      v1.normalise();

  //      float d = v0.dotProduct(v1);
  //      // If dot == 1, vectors are the same
  //      if (d >= 1.0f)
  //      {
  //          return Quaternion::IDENTITY;
  //      }
		//if (d < (1e-6f - 1.0f))
		//{
		//	if (fallbackAxis != Vector3::ZERO)
		//	{
		//		// rotate 180 degrees about the fallback axis
		//		q.FromAngleAxis(Radian(Math::PI), fallbackAxis);
		//	}
		//	else
		//	{
		//		// Generate an axis
		//		Vector3 axis = Vector3::UNIT_X.crossProduct(*this);
		//		if (axis.isZeroLength()) // pick another if colinear
		//			axis = Vector3::UNIT_Y.crossProduct(*this);
		//		axis.normalise();
		//		q.FromAngleAxis(Radian(Math::PI), axis);
		//	}
		//}
		//else
		//{
  //          float s = Math::Sqrt( (1+d)*2 );
	 //       float invs = 1 / s;

		//	Vector3 c = v0.crossProduct(v1);

  //  	    q.x = c.x * invs;
  //      	q.y = c.y * invs;
  //          q.z = c.z * invs;
  //          q.w = s * 0.5;
		//	q.normalise();
		//}
  //      return q;
  //  }

    /** Returns true if this vector is zero length. */
    inline bool isZeroLength(void) const
    {
        float sqlen = (x * x) + (y * y) + (z * z);
        return (sqlen < (1e-06 * 1e-06));

    }

    /** As normalise, except that this vector is unaffected and the
        normalised vector is returned as a copy. */
    inline Vector3 normalisedCopy(void) const
    {
        Vector3 ret = *this;
        ret.normalise();
        return ret;
    }

    /** Calculates a reflection vector to the plane with the given normal .
    @remarks NB assumes 'this' is pointing AWAY FROM the plane, invert if it is not.
    */
    inline Vector3 reflect(const Vector3& normal) const
    {
        return Vector3( *this - ( 2 * this->dotProduct(normal) * normal ) );
    }

	/** Returns whether this vector is within a positional tolerance
		of another vector.
	@param rhs The vector to compare with
	@param tolerance The amount that each element of the vector may vary by
		and still be considered equal
	*/
	//inline bool positionEquals(const Vector3& rhs, float tolerance = 1e-03) const
	//{
	//	return Math::floatEqual(x, rhs.x, tolerance) &&
	//		Math::floatEqual(y, rhs.y, tolerance) &&
	//		Math::floatEqual(z, rhs.z, tolerance);

	//}

	/** Returns whether this vector is within a positional tolerance
		of another vector, also take scale of the vectors into account.
	@param rhs The vector to compare with
	@param tolerance The amount (related to the scale of vectors) that distance
        of the vector may vary by and still be considered close
	*/
	inline bool positionCloses(const Vector3& rhs, float tolerance = 1e-03f) const
	{
		return squaredDistance(rhs) <=
            (squaredLength() + rhs.squaredLength()) * tolerance;
	}

	/** Returns whether this vector is within a directional tolerance
		of another vector.
	@param rhs The vector to compare with
	@param tolerance The maximum angle by which the vectors may vary and
		still be considered equal
	@note Both vectors should be normalised.
	*/
	//inline bool directionEquals(const Vector3& rhs,
	//	const Radian& tolerance) const
	//{
	//	float dot = dotProduct(rhs);
	//	Radian angle = Math::ACos(dot);

	//	return Math::Abs(angle.valueRadians()) <= tolerance.valueRadians();

	//}

};