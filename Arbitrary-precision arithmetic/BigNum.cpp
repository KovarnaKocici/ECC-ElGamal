#include "BigNum.h"
#include "Data.h"

#include <stdexcept>   
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

BigNum::BigNum() { _sign = '+'; }

BigNum::BigNum(char sign, vector<int> number) {
	_sign = sign;
	_number = number;
}

BigNum::BigNum(int number) { 
	BigNum bignumber = BigNum::convertToBigNum(number);
	_sign = bignumber._sign;
	_number = bignumber._number;
}

const std::vector<int> BigNum::zero = { 0 };
const std::vector<int>  BigNum::one = { 1 };
const std::vector<int>  BigNum::two = { 2 };
const int  BigNum::base = 10;

vector<int> BigNum::getNumber() {
	return (*this)._number;
}

char BigNum::getSign() {
	return (*this)._sign;
}

void BigNum::setSign(char sign) {
	(*this)._sign = sign;
}

void BigNum::neg() {
	if ((*this)._sign == '-')
		(*this)._sign = '+';
	else if ((*this)._sign == '+')
		(*this)._sign = '-';
}

BigNum BigNum::convertToBigNum(int n) {
	char sign;
	if (n >= 0) sign = '+';
	else {
		sign = '-';
		n = -n;
	}
	vector<int> number;
	if (n == 0)number.push_back(0);
	else 
		while (n != 0)
		{
			number.push_back(n%base);
			n = n / base;
		}
	return BigNum(sign, number);
}

BigNum BigNum::convertTo10Base(const string& input, int base)
{
	if (base < 2 || base > 36)
		return 0;

	bool isNegative = (input[0] == '-');

	int startIndex = input.length() - 1;
	int endIndex = isNegative ? 1 : 0;

	BigNum value = 0;
	BigNum digitValue = 1;

	for (int i = startIndex; i >= endIndex; --i)
	{
		char c = input[i];

		// Uppercase it - NOTE: could be done with std::toupper
		if (c >= 'a' && c <= 'z')
			c -= ('a' - 'A');

		// Convert char to int value - NOTE: could be done with std::atoi
		// 0-9
		if (c >= '0' && c <= '9')
			c -= '0';
		// A-Z
		else
			c = c - 'A' + 10;

		if (c >= base)
			return 0;
		int ch = (int)c;
		// Get the base 10 value of this digit    
	value = value + BigNum(ch) * digitValue;

		// Each digit has value base^digit position - NOTE: this avoids pow
		digitValue = digitValue*base;
	}

	if (isNegative)
		value.setSign('-');

	return value;
}

const void BigNum::SetAgrB(BigNum& aNew, BigNum& bNew, const BigNum& a, const BigNum& b) const {
	if (isGreater(a._number, b._number, '+') || isEqual(a._number, b._number))
	{
		aNew = a;
		bNew = b;
	}
	else
	{
		aNew = b;
		bNew = a;
	}
}

const bool BigNum::isGreater(const vector<int>& a, const vector<int>& b, char sign){
	if (sign == '+')
	{
		if (a.size() != b.size())
			return a.size() > b.size();
		for (int i = a.size() - 1; i >= 0; i--)
		{
			if (a[i] != b[i])
				return a[i] > b[i];
		}
	}
	if (sign == '-')
	{
		if (a.size() !=b.size())
			return a.size() < b.size();
		for (int i = a.size() - 1; i >= 0; i--)
		{
			if (a[i] != b[i])
				return a[i] < b[i];
		}
	}
	return false;
}

const bool BigNum::isEqual(const vector<int>& a, const vector<int>& b) {

		if (a.size() != b.size())
			return false;
		for (int i = a.size() - 1; i >= 0; i--)
		{
			if (a[i] != b[i])
				return false;
		}
	return true;
}

const bool BigNum::isEmpty() const {
	if ((*this)._number.size() == 0)
		return true;
	return false;
}

const bool BigNum::isPrime() const {
	if (prSolovayStrassen(*this))
		return true;
	return false;
}

const void BigNum::delInsignZero(vector<int>& number)
{
	while (number.size()>0 && number[number.size() - 1] == 0)
		number.pop_back();
}

const BigNum& BigNum::operator = (const BigNum& other) {
	if (this != &other)
	{
		_sign = other._sign;
		_number = other._number;
	}
	return *this;
}

std::istream& operator >> (std::istream& is, BigNum& n) {
	string line;
	if (getline(is, line))
	{
		stringstream number(line);
		char ch;
		number >> ch;
		if (ch == '-')
			n._sign = ch;
		else 
			if (isdigit(ch))
		{
			n._sign = '+';
			n._number.push_back(ch -'0');
		}

		while (number >> ch)
			n._number.push_back(ch - '0');
	}

	reverse(n._number.begin(), n._number.end());
	return is;
}

std::ostream& operator << (std::ostream& os, const BigNum& n)
{
	if(n._sign=='-')
		os << n._sign;
	for (int i = n._number.size()-1; i>=0; i--)
		cout << n._number[i];
	if (n._number.size() == 0)
		cout << 0;
	return os;
}

const bool BigNum::operator>(const BigNum& rhs) const {
	if ((*this)._sign == '+' && rhs._sign == '-')
		return true;
	if ((*this)._sign=='+' && rhs._sign=='+') 
		return  isGreater((*this)._number, rhs._number, '+');
	if ((*this)._sign == '-' && rhs._sign == '-') {
		return  isGreater((*this)._number, rhs._number, '-');
	}
	return false;
}

const bool BigNum::operator<(const BigNum& rhs) const {
	if (rhs > (*this)) return true;
	return false;
}

const bool BigNum::operator==(const BigNum& rhs) const {
	if (!((*this)<rhs || (*this)>rhs)) return true;
		return false;
}

const bool BigNum::operator!=(const BigNum& rhs) const {
	if ((*this)==rhs) return false;
	return true;
}

const bool BigNum::operator<=(const BigNum& rhs) const {
	if ((*this)<rhs || (*this)==rhs) return true;
	return false;
}

const bool BigNum::operator>=(const BigNum& rhs) const {
	if ((*this)>rhs || (*this) == rhs) return true;
	return false;
}

const vector<int> BigNum::Add(const vector<int>& a, const vector<int>& b) 
{
	vector<int> res = a;
	if (isEqual(a, zero)) return b;
	if (isEqual(b, zero)) return a;

	int temp = 0;
	int j = 0;
	for (; j < b.size(); j++)
	{
		res[j]+=b[j] + temp;
		if (res[j] >= base)
		{
			res[j] -= base;
			temp = 1;
		}
		else
			temp = 0;
	}

	while (temp != 0) {
		if (j < res.size())
		{
			res[j] += temp;
			if (res[j] >= base)
			{
				res[j] -= base;
				temp = 1;
				j++;
			}
			else
				temp = 0;
		}
		else {
			res.push_back(temp);
			temp = 0;
		}
	}

	return res;
}

BigNum BigNum::operator+(const BigNum& rhs) const{
	
	BigNum a , b;
	SetAgrB(a, b, *this, rhs);

	BigNum sum;
	if (a._sign == '-' && b._sign == '+' && a._number != b._number)
	{
		sum._sign = '-';
		sum._number = Substract(a._number, b._number);
	}
	else if (a._sign == '+' && b._sign == '-'  && a._number != b._number)
	{
		sum._sign = '+';
		sum._number = Substract(a._number, b._number);
	}
	else if(a._sign!=b._sign && a._number != b._number)
	{
		sum._sign = '+';
		sum._number = { 0 };
	}
	if (a._sign == '+' && b._sign == '+')
	{
		sum._sign = '+';
		sum._number = Add(a._number, b._number);
	}
	else if (a._sign == '-' && b._sign == '-')
	{
		sum._sign = '-';
		sum._number = Add(a._number, b._number);
	}

	return sum;
}

const vector<int> BigNum::Substract(const vector<int>& a, const vector<int>& b)
{
	vector<int> res = a;
	if (isEqual(b, zero)) return a;

	for (int i = 0; i< b.size(); i++)
	{
		res[i] -= b[i] ;
		if (res[i]<0){
			res[i] += base;
			res[i + 1]--;
		}
	}

	for (int i = b.size(); i < res.size() && res[i] < 0 ; i++)
	{
		res[i] += base;
		res[i + 1]--;
	}

	delInsignZero(res);
	return res;
}

BigNum BigNum::operator-(const BigNum& rhs) const {

	BigNum a, b;

	SetAgrB(a, b, *this, rhs);

	BigNum diff;
	
	if (a._sign == '+' && b._sign == '+' && a._number != b._number)
	{
		diff._sign = '+';
		diff._number = Substract(a._number, b._number);
	}
	else if (a._sign == '-' && b._sign == '-' && a._number != b._number)
	{
		diff._sign = '-';
		diff._number = Substract(a._number, b._number);
	}
	else if( a._sign==b._sign && a._number == b._number)
	{
		diff._sign = '+';
		diff._number = { 0 };
	}
	else if (a._sign == '-' && b._sign == '+')
	{
		diff._sign = '-';
		diff._number = Add(a._number, b._number);
	}
	else if (a._sign == '+' && b._sign == '-')
	{
		diff._sign = '+';
		diff._number = Add(a._number, b._number);
	}

	if (isGreater( rhs._number, (*this)._number, '+'))
		diff.neg();

	if (diff._number == zero)
		diff._sign = '+';
	return diff;
}

const vector<int> BigNum::Multiply(const vector<int>& a, const vector<int>& b){
	if (isEqual(a, zero) || isEqual(b, zero)) return zero;
	if (isEqual(a, one)) return b;
	if (isEqual(b, one)) return a;

	vector<int> res = vector<int>(a.size() + b.size() - 1);
	int temp = 0;

	for (int i = 0; i < a.size(); i++){
		for (int j = 0; j < b.size(); j++){
			res[i + j] += a[i] * b[j] + temp;
			temp = res[i + j] / base;
			res[i + j] -= temp*base;
		}
		if (temp != 0){
			if (i + b.size() <res.size())
				res[i + b.size()] += temp;
			else
				res.push_back(temp);
			temp = 0;
		}
	}

	delInsignZero(res);
	return res;
}

BigNum  BigNum::operator*(const  BigNum& rhs) const{
	BigNum a, b;
	SetAgrB(a, b, *this, rhs);
	
	BigNum product;

	if ((a._sign == '-' && b._sign == '+') || (a._sign == '+' && b._sign == '-'))
		product._sign = '-';
	else product._sign = '+';

	product._number = Multiply(a._number, b._number);

	return product;
}

const BigNum BigNum::Divide(const BigNum& a, const BigNum& b) {

	if (a == b) return BigNum('+',one);
	if (b == BigNum('+', zero)) throw new invalid_argument("Division by 0");
	if (b == BigNum('+', one)) return a;
	if (isGreater(b._number,a._number,'+')) return  BigNum('+', zero);

	BigNum res;
	BigNum curValue;

	for (int i = a._number.size() - 1; i >= 0; i--)
	{
		delInsignZero(curValue._number);
		curValue._number.insert(curValue._number.begin(), 0);
		curValue._number[0] = { a._number[i] };

		int x = 0;
		int l = 0, r = base;
		while (l <= r)
		{
			int m = (l + r) >> 1;

			BigNum cur = b*m;
			if (curValue > cur || curValue == cur)
			{
				x = m;
				l = m + 1;
			}
			else
				r = m - 1;
		}
		res._number.insert(res._number.begin(), x);
		curValue = curValue - b*x;
	}

	delInsignZero(res._number);
	return res;
}

BigNum  BigNum::operator/(const  BigNum& rhs) const {
	BigNum quotient;

	BigNum a = *this, b = rhs;
	if (a._sign == '-')
		a.neg();
	if (b._sign == '-')
		b.neg();
	quotient = Divide(a, b);
	if (((*this)._sign == '-' && rhs._sign == '+') || ((*this)._sign == '+' && rhs._sign == '-'))
		quotient._sign = '-';
	else quotient._sign = '+';

	return quotient;
}

const BigNum BigNum::Mod(const BigNum& a, const BigNum&  b) {
	if (b == BigNum('+', one)) return  BigNum('+', zero);
	BigNum mod = a - b*(a / b);
	BigNum pb = b;
	if (b._sign == '-')
		pb.neg();
	while (mod._sign == '-')
		mod = mod + pb;
	if (a._sign == '-' && a._sign == '-')return mod%b;

	if (mod._number == zero)
		mod._sign = '+';
	return mod;
}

BigNum BigNum::operator%(const  BigNum& rhs) const {

	return Mod(*this, rhs);
}

BigNum BigNum::ModINV(BigNum& n, BigNum& m) {
	BigNum res, x = 1, y = 1;
	BigNum g = eGCD(n, m, x, y);
	if (!isEqual(g.getNumber(),one))
		cout << "Inverse doesn't exist" << endl;
	else
		res = x%m;

	return res;

}

BigNum BigNum::Abs(BigNum & number)
{
	if (number.getSign() == '-')
	{
		BigNum abs = number;
		abs.setSign('+');
		return abs;
	}
	return number;
}

BigNum BigNum::Pow(const BigNum& number, const int& degree) {
	BigNum power= number;
	if (degree == 0)
		return 1;

	for (int i = 1; i < degree; i++)
		power = power*number;

	return power;
}

BigNum BigNum::PowMOD(BigNum number, BigNum degree, const BigNum& mod){

	BigNum res = 1;  // Initialize result 

	number = number % mod;  // Update x if it is more than or 
				// equal to p 

	while (degree > 0)
	{
		// If y is odd, multiply x with result 
		if (degree%2==1)
			res = (res*number) % mod;

		// y must be even now 
		degree = degree/2; 
		number = (number*number) % mod;
	}
	return res;
}

BigNum BigNum::Sqrt(const BigNum& number){
	if (number._sign=='-') throw new invalid_argument("Negative number");

	BigNum res;
	BigNum x0 = number;
	BigNum x1 = (number + 1)/2;
	while (x0 > x1) {
		x0 = x1;
		x1= (x1 +(number/x1))/2;
	}

	return x0;
}

BigNum BigNum::GCD(const BigNum a, const BigNum b) {

	if (b == 0)
		return a;

	BigNum gcd = GCD(b, a%b);

	return gcd;
}

BigNum BigNum::eGCD(const BigNum a, const BigNum b, BigNum& x, BigNum& y) {

	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}

	BigNum x1, y1, gcd = eGCD(b, a%b, x1, y1);
	x = y1;
	y = x1 - ((a / b) * y1);

	return gcd;
}

BigNum BigNum::p0Pollard(const BigNum& number){
	int count, loop = 1, size = 2;
	BigNum factor = 1, x = 2, x_fixed = 2;

	while (factor == 1) {
		//cout << "---- loop " << loop << " ----" << endl;
		for (count = 1; (count <= size) && (factor <= 1); count++) {
			x = (x * x - 1) % number;
			factor = GCD(Abs(x - x_fixed), number);
			//cout << "count = " << count << "; x = " << x << "; factor = " << factor << endl;
		}
		size = 2 * size;
		x_fixed = x;
		loop = loop + 1;
	}
	//cout << "factor is " << factor << endl;

	return factor;
}

vector<BigNum> BigNum::Factorize(BigNum number) {
	BigNum res;
	vector<BigNum> factors;
	while (number!=1) {
		res = p0Pollard(number);
		factors.push_back(res);
		number = number / res;
	}

	return factors;
}

BigNum BigNum::stepBabyGiantLog(const BigNum& n, const BigNum& r, const BigNum& m) {
	//Baby-step giant-step algorithm
	BigNum k = Sqrt(m) + 1;

	map<BigNum, BigNum> value;

	// Store all values of n^(k*i) of LHS 
	for (BigNum i = n; i >= 1; i=i-1)
		value[PowMOD(n, i * k, m)] = i;

	for (BigNum j = 0; j < k; j=j+1)
	{
		// Calculate (n ^ j) * r and check for collision 
		BigNum cur = (PowMOD(n, j, m) * r) % m;

		// If collision occurs i.e., LHS = RHS 
		if (value[cur]!=BigNum())
		{
			BigNum res = value[cur] * k - j;
			// Check whether ans lies below m or not 
			if (res < m)
				return res;
		}
	}
	return -1;
}

BigNum BigNum::funcEuler(BigNum number)
{
	//counts the positive integers up to a given integer n that are relatively prime to n

	BigNum res = number; // Initialize result as n 

					// Consider all prime factors of n and subtract their 
					// multiples from result 
	for(BigNum p = 2; p * p <= number; p=p+1) {

		// Check if p is a prime factor. 
		if (number % p == 0) {

			// If yes, then update n and result 
			while (number % p == 0)
				number =  number/p;
			res = res - res / p;
		}
	}

	// If n has a prime factor greater than sqrt(n) 
	// (There can be at-most one such prime factor) 
	if (number > 1)
		res = res - res / number;
	return res;

}

BigNum BigNum::funcMobius(BigNum number)
{
	//1 if n is a square-free positive integer with an even number of prime factors.
	//−1 if n is a square-free positive integer with an odd number of prime factors.
	//0 if n has a squared prime factor.

	BigNum p = 0;

	// Handling 2 separately 
	if (number % 2 == 0)
	{
		number = number / 2;
		p=p+1;

		// If 2^2 also divides N 
		if (number % 2 == 0)
			return 0;
	}

	// Check for all other prine factors 
	for (BigNum i = 3; i <= Sqrt(number); i = i + 2)
	{
		// If i divides n 
		if (number%i == 0)
		{
			number = number / i;
			p=p+1;

			// If i^2 also divides N 
			if (number % i == 0)
				return 0;
		}
	}

	return (p % 2 == 0) ? -1 : 1;
}

BigNum BigNum::symbLegendre(BigNum a, BigNum n) {
	//cout << "a " << a << "; n " << n << endl;
	if (n < 2)  // prime test is expensive?
		throw new invalid_argument("n must not be < 2");
	if (a == 0)
	{
		return 0;
	}
	if (a == 1)
	{
		return 1;
	}
	BigNum res;
	if (a % 2 == 0)
	{
		res = symbLegendre(a / 2, n);
		if (n % 8 == 3 ||n % 8==5)
			res.neg();
	}
	else
	{
		res = symbLegendre(n % a, a);
		if (a % 4 == 3 && n % 4 == 3)
			res.neg();
	}
	//cout << "res " << res << endl;
	return res;
}

BigNum BigNum::symbJacobi(BigNum a, BigNum n) {

	if (a == 0)// (0/n) = 0 
		return a;

	BigNum res = 1;

	if (a < 0)
	{
		a.neg();// (a/n) = (-a/n)*(-1/n) 
		if (n % 4 == 3)
			res.neg();// (-1/n) = -1 if n = 3 (mod 4)
	}

	if (a == 1)// (1/n) = 1 
		return res;

	while (!(a == 0))
	{
		if (a < 0)
		{
			a.neg();// (a/n) = (-a/n)*(-1/n) 
			if (n % 4 == 3)
				res.neg();// (-1/n) = -1 if n = 3 (mod 4) 
		}
		while (a % 2 == 0)
		{
			a = a / 2;
			if (n % 8 == 3 || n % 8 == 5)
				res.neg();
		}
		swap(a, n);
		if (a % 4 == 3 && n % 4 == 3)
			res.neg();
		a = a % n;
		if (a > n / 2)
			a = a - n;
	}
	if (n == 1)
		return res;
	return 0;
}

bool BigNum::prSolovayStrassen(BigNum number) {
	int iterations = 50;
	if (number <= 2) return false;
	for (int i = 0; i < iterations; i++)
	{
		// Generate a random number a 
		BigNum a = BigNum(rand())%(number - 1) + 1;
		BigNum jacobian = (number + symbJacobi(a, number)) % number;
		BigNum mod = PowMOD(a, (number - 1) / 2, number);
		//long long mod = modulo(a, (p - 1) / 2, p);

		if (jacobian==0 || mod != jacobian)
			return false;
	}
	return true;
}

BigNum::~BigNum()
{
}
