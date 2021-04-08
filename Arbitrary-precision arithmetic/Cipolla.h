#pragma once
#include "BigNum.h"

class C
{
private:
	BigNum _numINf1;
	BigNum _numINf2;

public:
	BigNum getNumINf1();
	BigNum getNumINf2();

	C(BigNum num1, BigNum num2);
};

static class Cipolla
{
	public:
		static C calc(BigNum n, BigNum m);
		static C mult(C aa, C bb, BigNum finalOmega, BigNum m);
};


