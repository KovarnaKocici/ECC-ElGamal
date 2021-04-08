#include "Cipolla.h"
#include <iostream>
C::C(BigNum num1, BigNum num2) {
	_numINf1 = num1;
	_numINf2 = num2;
}

BigNum C::getNumINf1() {
	return _numINf1;
}

BigNum C::getNumINf2() {
	return _numINf2;
}

// Multiplication in Fp2
C Cipolla::mult(C aa, C bb, BigNum finalOmega, BigNum m) {
	return C(
		(aa.getNumINf1() * bb.getNumINf1() + aa.getNumINf2() * bb.getNumINf2() * finalOmega) % m,
		(aa.getNumINf1() * bb.getNumINf2() + bb.getNumINf1() * aa.getNumINf2()) % m);
}

C Cipolla::calc(BigNum n, BigNum m) {
	//std::cout << n << std::endl<< m<<std::endl;
	// Step 0: validate arguments
	if (BigNum::symbLegendre(n, m) != 1)
		return C(0, 0);

	// Step 1: Find a, omega2
	BigNum a = 0;
	BigNum omega2;
	while (true) {
		omega2 = (a * a + m - n) % m;
		if (BigNum::symbLegendre(omega2, m) == -1) {
			break;
		}
		a = a + 1;
	}

	// Step 2: Compute power
	C r = C(1, 0);
	C s = C(a, 1);
	BigNum nn = ((m + 1) / 2) % m;
	while (nn > 0) {
		if (nn % 2 == 1) {
			r = mult(r, s, omega2, m);
		}
		s = mult(s, s, omega2, m);
		nn = nn / 2;
	}

	// Step 3: Check x in Fp
	if (r.getNumINf2() != 0)
		return C(0, 0);

	// Step 5: Check x * x = n
	if (r.getNumINf1() * r.getNumINf1() % m != n)
		return C(0, 0);

	// Step 4: Solutions
	return C(r.getNumINf1(), m - r.getNumINf1());
}