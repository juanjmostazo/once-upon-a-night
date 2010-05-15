/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/* Original author: John C. Hare
 * Date: June 26, 1996 (although I've had these around for at least 6 years)
 * Adapted to C++ by W.J. van der Laan 2004
 */
#ifndef H_Q_Julia
#define H_Q_Julia

#include <cmath>

namespace OUAN
{
	struct Quat {
		float r,i,j,k;
	};

	inline void qadd(Quat &a, const Quat &b)
	{
		a.r += b.r;
		a.i += b.i;
		a.j += b.j;
		a.k += b.k;
	}

	inline void qmult(Quat &c, const Quat &a, const Quat &b) 
	{
		c.r = a.r*b.r - a.i*b.i - a.j*b.j - a.k*b.k;
		c.i = a.r*b.i + a.i*b.r + a.j*b.k - a.k*b.j;
		c.j = a.r*b.j + a.j*b.r + a.k*b.i - a.i*b.k;
		c.k = a.r*b.k + a.k*b.r + a.i*b.j - a.j*b.i;
	}

	inline void qsqr(Quat &b, const Quat &a) 
	{
		b.r = a.r*a.r - a.i*a.i - a.j*a.j - a.k*a.k;
		b.i = 2.0f*a.r*a.i;
		b.j = 2.0f*a.r*a.j;
		b.k = 2.0f*a.r*a.k;
	}

	class Julia 
	{
	private:
		float global_real, global_imag, global_theta;
		Quat oc,c,eio,emio;

	public:
		Julia();
		Julia(float global_real, float global_imag, float global_theta);
		float eval(float x, float y, float z);
	};
}

#endif
