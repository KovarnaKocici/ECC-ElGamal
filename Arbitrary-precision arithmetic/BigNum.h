#include <vector>
#include <string>
#pragma once

class BigNum
{
private:
	std::vector<int> _number;
	char _sign;

	static const void delInsignZero(std::vector<int>& number);
	static const bool isGreater(const std::vector<int>& a, const std::vector<int>& b, char sign);
	const void SetAgrB(BigNum& aNew, BigNum& bNew, const BigNum& a, const BigNum& b) const;

	static const std::vector<int> Add(const std::vector<int>& a, const std::vector<int>& b); //a>b, a>=0, b>=0
	static const std::vector<int> Substract(const std::vector<int>& a, const std::vector<int>& b) ; //a>b, a>=0, b>=0
	static const std::vector<int> Multiply(const std::vector<int>& a, const std::vector<int>& b) ; //a>=b, a>=0, b>=0
	static const BigNum Divide(const BigNum& a, const BigNum& b); //a>=b, a>=0, b>0
	static const BigNum Mod(const BigNum& a, const BigNum& b);

public:
	static const std::vector<int> zero;
	static const std::vector<int> one;
	static const std::vector<int> two;
	static const int base;

	BigNum();
	BigNum(char sign, std::vector<int> number);
	BigNum::BigNum(int number);
	static BigNum convertToBigNum(int n);
	static BigNum convertTo10Base(const std::string& input, int base);

	std::vector<int> getNumber();
	char getSign();
	void setSign(char sign);
	void neg();

	static const bool isEqual(const std::vector<int>& a, const std::vector<int>& b);
	const bool isEmpty() const;
	const bool isPrime() const;

	const BigNum& operator = (const BigNum& other);

	friend std::istream& operator >> (std::istream& is, BigNum& number);
	friend std::ostream& operator << (std::ostream& os, const BigNum& number);

	const bool operator>(const BigNum& rhs) const;
	const bool operator<(const BigNum& rhs) const;
	const bool operator==(const BigNum& rhs) const;
	const bool operator!=(const BigNum& rhs) const;
	const bool operator<=(const BigNum& rhs) const;
	const bool operator>=(const BigNum& rhs) const;

	BigNum operator+(const BigNum& rhs) const;
	BigNum operator-(const BigNum& rhs) const;
	BigNum operator*( const BigNum& rhs) const;
	BigNum  operator/(const BigNum& rhs) const;
	BigNum operator%(const BigNum& rhs) const;
	
	static BigNum ModINV(BigNum& n, BigNum& m);
	static BigNum Abs(BigNum& number);
	static BigNum Pow(const BigNum& number, const int& degree);
	static BigNum PowMOD(BigNum number, BigNum degree, const BigNum& mod);
	static BigNum Sqrt(const BigNum& number);
	static BigNum GCD(const BigNum a, const BigNum b);
	static BigNum eGCD(const BigNum a, const BigNum b, BigNum& x, BigNum& y);
	static BigNum p0Pollard(const BigNum& number);
	static std::vector<BigNum> Factorize(BigNum number);
	static BigNum stepBabyGiantLog(const BigNum& n, const BigNum& r, const BigNum& m);
	static BigNum funcEuler(BigNum number);
	static BigNum funcMobius(BigNum number);
	static BigNum symbLegendre(BigNum a, BigNum);
	static BigNum symbJacobi(BigNum a, BigNum n);
	static bool prSolovayStrassen(BigNum number);

	~BigNum();
};

