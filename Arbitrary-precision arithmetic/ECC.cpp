#include "ECC.h"
#include <iostream>
#include "time.h"

using namespace std;

Point::Point(){}

Point::Point(BigNum x, BigNum y) {
	_x = x;
	_y = y;
}

BigNum Point::getX() { return _x; }
BigNum Point::getY() { return _y; }

void Point::setX(BigNum x) { _x = x; }
void Point::setY(BigNum y) { _y = y; }

const Point& Point::operator = (const Point& other) {
	if (this != &other)
	{
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

const bool Point::operator==(const Point& rhs) const {
	if ((*this)._x == rhs._x && (*this)._y == rhs._y) return true;
		return false;
}

std::ostream& operator << (std::ostream& os, const Point& p) {
	cout << "( " << p._x << ", " << p._y << " )";
	return os;
}

Point::~Point()
{}


Curve::Curve()
{
	_a = BigNum();
	_b = BigNum();
	_p = BigNum();
	_basePoint = Point();

}

Curve::Curve(BigNum a, BigNum b, BigNum p){
	_a = a;
	_b = b;
	_p = p;
	_basePoint = Point(0, 0);
}

C Curve::at( BigNum x) {
	return Cipolla::calc((BigNum::PowMOD(x, 3, _p) + _a * x + _b) % _p, _p);
}

Point Curve::neg(Point p) {
	BigNum negY = p.getY();
	negY.neg();
	return Point(p.getX(), negY % _p);
}

Point Curve::add(Point p, Point q) {

	if (p == _basePoint)
		return q;
	if (q == _basePoint)
		return p;
	if (p.getX() == q.getX() && (p.getY() != q.getY() || p.getY() == 0))
		return _basePoint;

	BigNum l;
	if (p.getX() == q.getX())
		l = (p.getX() * 3 * p.getX() + _a) * BigNum::ModINV(p.getY() * 2, _p) % _p;
	else
		l = (q.getY() - p.getY()) * BigNum::ModINV(q.getX() - p.getX(), _p) % _p;
	BigNum x = (l * l - p.getX() - q.getX()) % _p;
	BigNum y = (l * (p.getX() - x) - p.getY()) % _p;
	return Point(x, y);
}

Point Curve::mul(Point point, BigNum t) {
	Point res = _basePoint;
	while (t > 0) {
		if (t % 2 == 1)
			res = add(res, point);
		t = t / 2;
		point = add(point, point);
	}
		return res;
}

Curve::~Curve()
{
}

KeyFactory::KeyFactory(Curve curve) {
	_curve = curve;
	_private =NULL;
	_public = Point();
}

BigNum KeyFactory::getPrivate() { return _private; }
Point KeyFactory::getPublic() { return _public; }

void KeyFactory::generate(Point g, BigNum n) {
	srand(time(NULL));

	BigNum min = 1;
	BigNum max = n-1;
	BigNum x = (min + (BigNum(rand()) % (max - min + 1)));
	Point y = _curve.mul(g, x);

	_private = x;
	_public = y;
}

—ryptogram::—ryptogram(Point Ò1, Point Ò2) {
	_Ò1 = Ò1;
	_Ò2 = Ò2;
}

Point —ryptogram::get—1() {
	return _Ò1;
}

Point —ryptogram::get—2() {
	return  _Ò2;
}

ElGamal::ElGamal(Curve curve, Point g, BigNum n) {
	_curve = curve;
	_g = g;
	_n = n;
}

Point ElGamal::getG() {
	return _g;
}

BigNum ElGamal::getN() {
	return _n;
}

—ryptogram ElGamal::encrypt(Point publickey, BigNum m) {
	srand(time(NULL));

	BigNum  min = 1;
	BigNum max = _n - 1;
	BigNum  k = (min + (BigNum(rand()) % (max - min + 1)));
	Point C1 = _curve.mul(_g, k);
	Point C_ = _curve.mul(publickey, k);
	Point Pm = Point(m, _curve.at(m).getNumINf1());
	Point C2 = _curve.add(C_, Pm);
	
	return —ryptogram(C1, C2);
}

Point ElGamal::decrypt(BigNum privatekey, Point C, Point D) {
	Point C_ = _curve.mul(C, privatekey);
	Point Pm =_curve.add(D, _curve.neg(C_));
	return Pm;
}