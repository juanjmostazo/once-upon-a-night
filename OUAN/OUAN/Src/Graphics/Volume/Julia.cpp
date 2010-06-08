#include "OUAN_Precompiled.h"

#include "Julia.h"

using namespace OUAN;

Julia::Julia()
{

}

Julia::Julia(float global_real, float global_imag, float global_theta)
{
	this->global_real = global_real;
	this->global_imag = global_imag;
	this->global_theta = global_theta;

	oc.r = global_real;
	oc.i = global_imag;
	oc.j = oc.k = 0.0;

	eio.r = cos(global_theta);
	eio.i = sin(global_theta);
	eio.j = 0.0;
	eio.k = 0.0;

	emio.r = cos(-global_theta);
	emio.i = sin(-global_theta);
	emio.j = 0.0;
	emio.k = 0.0;

	/***
	 *** multiply eio*c only once at the beginning of iteration
	 *** (since q |-> sqrt(eio*(q-eio*c)))
	 *** q -> e-io*q^2 - eio*c
	 ***/

	qmult(c, eio,oc);
}

float Julia::eval(float x, float y, float z) {

	Quat q, temp;
	int i;

	q.r = x;
	q.i = y;
	q.j = z;
	q.k = 0.0;

	for (i = 30; i > 0; i--) {
		qsqr(temp, q);
		qmult(q, emio, temp);
		qadd(q, c);

		if (q.r*q.r + q.i*q.i + q.j*q.j + q.k*q.k > 8.0)
		{
			break;
		}
	}

	return((float)i);
}