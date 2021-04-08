#include <iostream>
#include <vector>
#include <exception>
#include "BigNum.h"
#include "Cipolla.h""
#include "ECC.h"
#include "Data.h"

using namespace std;

struct MenuItem
{
	int num; 
	const char *choice;
};

void outputMenu(MenuItem m[], int n);
int findChoice(MenuItem m[], int n, int choice);

void binaryOperations();
void binaryModOperations();
void comparisons();
void sqrt();
BigNum findMinX(vector<BigNum> mod, vector<BigNum> rem, int k);
void chineseRemainderTheorem();

void factorization();
void logarithm();
void calcEuler();
void calcMobius();
void calcLegendre();
void calcJacobi();
void primality();
void solveCipolla();
void encryptElGamal();

void lab1();
void lab2();


int main(int argc, char **argv)
{
	while (true) {
		lab2();
	}
}

void outputMenu(MenuItem m[], int n)
{
	cout << "\n Select option:\n";
	for (int i = 0; i < n; i++)
	{
		cout << " " << m[i].num << m[i].choice;
	}
}

int findChoice(MenuItem m[], int n, int choice)
{
	for (int i = 0; i < n; ++i)
	{
		if (choice == m[i].num) return choice;
	}
	choice = -1;
	return choice;
}

void binaryOperations() {
	int choice = 0, choice_user;
	MenuItem opt[] = { { 1, ") a * b\n" },
	{ 2, ") a + b\n" },
	{ 3, ") a - b\n" },
	{ 4, ") a / b\n" },
	{ 5, ") a % b\n" },
	{ 6, ") a ^ n\n" } };

	int nopt = sizeof(opt) / sizeof(MenuItem);
	outputMenu(opt, nopt);

	input_user(choice_user);
	choice = findChoice(opt, nopt, choice_user);

	BigNum a, b;
	int n;

	switch (choice)
	{
	case 1: {
		cout << " Your choice is a*b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << a*b;
		break;
	}
	case 2: {
		cout << " Your choice is a+b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << a + b;
		break;
	}
	case 3: {
		cout << " Your choice is a-b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << a - b;
		break;
	}
	case 4: {
		cout << " Your choice is a/b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << a / b;
		break;
	}
	case 5: {
		cout << " Your choice is a%b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << a % b;
		break;
	}
	case 6: {
		cout << " Your choice is a^n where " << endl;
		cout << " a = "; cin >> a;
		cout << " n = ";
		string temp;
		getline(cin, temp);
		n = stof(temp);
		cout << " Result is " << BigNum::Pow(a, n);
		break;
	}
	case -1: cout << " INVALID INSTRUCTION\n"; break;
	}
}

void binaryModOperations() {
	int choice = 0, choice_user;
	MenuItem opt[] = { { 1, ") (a * b)mod c\n" },
	{ 2, ") (a + b)mod c\n" },
	{ 3, ") (a - b)mod c\n" },
	{ 4, ") (a / b)mod c\n" },
	{ 5, ") (a % b)mod c\n" },
	{ 6, ") (a ^ n)mod c\n" } };

	int nopt = sizeof(opt) / sizeof(MenuItem);
	outputMenu(opt, nopt);

	input_user(choice_user);
	choice = findChoice(opt, nopt, choice_user);

	BigNum a; BigNum b; BigNum c;
	int n;

	switch (choice)
	{
	case 1: {
		cout << " Your choice is (a*b)modc where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " с = "; cin >> c;
		cout << " Result is " << (a * b) % c;
		break;
	}
	case 2: {
		cout << " Your choice is (a+b)modc where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " с = "; cin >> c;
		cout << " Result is " << (a + b) % c;
		break;
	}
	case 3: {
		cout << " Your choice is (a-b)modc where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " с = "; cin >> c;
		cout << " Result is " << (a - b) % c;
		break;
	}
	case 4: {
		cout << " Your choice is (a/b)modc where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " с = "; cin >> c;
		cout << " Result is " << (a / b) % c;
		break;
	}
	case 5: {
		cout << " Your choice is (a%b)modc where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " с = "; cin >> c;
		cout << " Result is " << (a % b) % c;
		break;
	}
	case 6: {
		cout << " Your choice is (a^n)modc where " << endl;
		cout << " a = "; cin >> a;
		cout << " n = "; cin >> n;
			cout << " с = "; cin >> c;
		//string temp;
		//getline(cin, temp);
		//n = stof(temp);
		cout << " Result is " << BigNum::PowMOD(a, n, c);
		break;
	}
	case -1: cout << " INVALID INSTRUCTION\n"; break;
	}
}

void comparisons() {
	int choice = 0, choice_user;
	MenuItem opt[] = { { 1, ") a > b\n" },
	{ 2, ") a < b\n" },
	{ 3, ") a == b\n" } };

	int nopt = sizeof(opt) / sizeof(MenuItem);
	outputMenu(opt, nopt);

	input_user(choice_user);
	choice = findChoice(opt, nopt, choice_user);

	BigNum a, b;

	switch (choice)
	{
	case 1: {
		cout << " Your choice is a>b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << (a>b);
		break;
	}
	case 2: {
		cout << " Your choice is a<b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << (a<b);
		break;
	}
	case 3: {
		cout << " Your choice is a==b where " << endl;
		cout << " a = "; cin >> a;
		cout << " b = "; cin >> b;
		cout << " Result is " << (a == b);
		break;
	}
	case -1: cout << " INVALID INSTRUCTION\n"; break;
	}
}

void sqrt() {
	BigNum a;
	cout << " Your choice is sqrt(a) where " << endl;
	cout << " a = "; cin >> a;
	cout << " Result is " << BigNum::Sqrt(a);
}

BigNum findMinX(vector<BigNum> mod, vector<BigNum> rem, int k)
{
	// Assumption: Numbers in mod[] are pairwise coprime 
	// (gcd for every pair is 1) 

	// Compute product of all numbers 
	BigNum M = BigNum('+', BigNum::one);
	for (int i = 0; i < k; i++)
		M = M*mod[i];

	// Initialize result 
	BigNum res = BigNum('+', BigNum::zero);

	// Apply above formula 
	for (int i = 0; i < k; i++)
	{
		BigNum mm = M / mod[i];
		BigNum plus = rem[i] * BigNum::ModINV(mm, mod[i]) * mm;
		//cout << plus << " " << endl;
		res = res + plus;
	}

	cout << res % M << "( mod" << M << " )";

	return res % M;
}

void chineseRemainderTheorem() {
	cout << " Input a sequence of congruence equations, having the form xi=ri(mod mi)" << endl;
	cout << " Number of equations is ";
	int k;
	cin >> k;
	clean();
	vector<BigNum> mod;
	vector<BigNum> rem;
	cout << " Input ri and mi of equations " << endl;
	for (int i = 0; i < k; i++) {
		BigNum r, m;
		cin >> r;
		rem.push_back(r);
		cin >> m;
		mod.push_back(m);
		cout << " equation is x = " << r << "(mod " << m << ")" << endl;
	}
	findMinX(mod, rem, k);

}

void factorization() {
	BigNum number;
	cout << " Input to factorize "<< endl; 
	cout << " number = "; cin >> number;

	vector<BigNum> factors = BigNum::Factorize(number);
	cout << " Result is " << number << " =";
	for (int i = 0; i < factors.size(); i++)
	{
		cout << " "<< factors[i];
		if (i != factors.size() - 1)
			cout << " *";
	}
}

void logarithm() {
	BigNum n, r, m;
	cout << " Input to calculate n^k=r(mod m) where" << endl;
	cout << " n = "; cin >> n;
	cout << " r = "; cin >> r;
	cout << " m = "; cin >> m;

	cout << " Result is " << BigNum::stepBabyGiantLog(n, r, m);
}

void calcEuler() {
	BigNum number;
	cout << " Input to calculate Euler`s Totient function" << endl;
	cout << " number = "; cin >> number;

	cout << " Result is " << BigNum::funcEuler(number);
}

void calcMobius() {
	BigNum number;
	cout << " Input to calculate Mobius function " << endl;
	cout << " number = "; cin >> number;

	cout << " Result is " << BigNum::funcMobius(number);
}

void calcLegendre() {
	BigNum a, n;
	cout << " Input Legendre symbol (a/n) where " << endl;
	cout << " a = "; cin >> a;
	cout << " n = "; cin >> n;

	cout << " Result is " << BigNum::symbLegendre(a, n);
}

void calcJacobi() {
	BigNum a, n;
	cout << " Input Jacobi symbol (a/n) where " << endl;
	cout << " a = "; cin >> a;
	cout << " n = "; cin >> n;

	cout << " Result is " << BigNum::symbJacobi(a, n);
}

void primality() {
	cout << " Input to check primality " << endl;
	BigNum n;
	cout << " number = "; cin >> n;

	cout << " Result is " << n.isPrime();
}

void solveCipolla() {
	BigNum r, m;
	cout << " Input a congruence equation, having the form x^2=r(mod m) where" << endl;
	cout << " r = "; cin >> r;
	cout << " m = "; cin >> m;
	C res = Cipolla::calc(r, m);
	cout << " Result is ";
	if (res.getNumINf1() == 0)
		cout << "No solution";
	else
		cout << res.getNumINf1() << "(mod "<< m <<") or " << res.getNumINf2() << "(mod " << m << ")";
}

void encryptElGamal() {

	string pHEXA = "FFFFFFFDFFFFFFFFFFFFFFFFFFFFFFFF",
		aHEXA = "FFFFFFFDFFFFFFFFFFFFFFFFFFFFFF",
		bHEXA = "E87579C11079F43DD824993C2CEE5E",
		gXHEXA = "161FF7528B899B2D0C28607CA52C5B",
		nHEXA = "FFFFFFFE0000000075A30D1B9038A1";
			
		BigNum a, b, p, g, gx, gy, n;
		cout << "Elliptic Curve General Form y^2 mod p = (x^3  + A*x + B) mod p \n";

		a = BigNum::convertTo10Base(aHEXA, 16);
		b = BigNum::convertTo10Base(bHEXA, 16);
		p = BigNum::convertTo10Base(pHEXA, 16);
		gx = BigNum::convertTo10Base(gXHEXA, 16);
		n = BigNum::convertTo10Base(nHEXA, 16);

		Curve curve = Curve(a, b, p);
		KeyFactory factory = KeyFactory(curve);
		gy = curve.at(gx).getNumINf1();
		cout << "x: " << gx << endl << "y: " << gy << endl;
		Point G = Point(gx, gy);
		factory.generate(Point(gx, gy), n);
		cout << "Private key: " << factory.getPrivate() << endl << "Public key: " << factory.getPublic()<<endl;

		BigNum message;
		cout << "Input to encrypt" << endl;
		cin >> message;
		ElGamal cr = ElGamal(curve, G, n);
		Сryptogram crypt = cr.encrypt(factory.getPublic(), message);
		cout << "Cryptogram: " << endl << "C1: "<< crypt.getС1() << endl << "C2: " << crypt.getС2()<<endl;
		
		cout << "Decrypt" << endl;
		cout<<cr.decrypt(factory.getPrivate(), crypt.getС1(), crypt.getС2()).getX();
	
}

void lab1() {
	int choice = 0, choice_user;
	MenuItem opt[] = { { 1, ") binary operations\n" },
	{ 2, ") binary modulo operations\n" },
	{ 3, ") comparison of two numbers\n" },
	{ 4, ") [sqrt(a)]\n" },
	{ 5, ") solve a system of congruence equations\n" } };

	int nopt = sizeof(opt) / sizeof(MenuItem);
	outputMenu(opt, nopt);

	try {
		input_user(choice_user);
		choice = findChoice(opt, nopt, choice_user);

		switch (choice)
		{
		case 1:binaryOperations(); break;
		case 2:binaryModOperations(); break;
		case 3:comparisons(); break;
		case 4:sqrt(); break;
		case 5:chineseRemainderTheorem(); break;
		case -1: cout << " INVALID INSTRUCTION\n";
		}
		cout << endl;
		system("pause");
	}

	catch (exception& Ex)
	{
		cout << Ex.what();
	}
}

void lab2() {
	int choice = 0, choice_user;
	MenuItem opt[] = { { 1, ") factorization (Pollard's p0 algorithm)\n" },
	{ 2, ") discrete logarithm (Baby-step giant-step algorithm)\n" },
	{ 3, ") Euler's function\n" },
	{ 4, ") Mobius function\n" },
	{ 5, ") Legendre symbol\n" },
	{ 6, ") Jacobi symbol\n" },
	{ 7, ") Cipolla's algorithm\n" },
	{ 8, ") Primality test (Solovay-Strassen primality test)\n" },
	{ 9, ") ElGamal encryption\n" }, };

	int nopt = sizeof(opt) / sizeof(MenuItem);
	outputMenu(opt, nopt);

	try {
		input_user(choice_user);
		choice = findChoice(opt, nopt, choice_user);

		switch (choice)
		{
		case 1: factorization(); break;
		case 2: logarithm(); break;
		case 3: calcEuler(); break;
		case 4: calcMobius(); break;
		case 5: calcLegendre(); break;
		case 6: calcJacobi(); break;
		case 7: solveCipolla(); break;
		case 8: primality(); break;
		case 9: encryptElGamal(); break;
		case -1: cout << " INVALID INSTRUCTION\n";
		}
		cout << endl;
		system("pause");
	}

	catch (exception& Ex)
	{
		cout << Ex.what();
	}
}