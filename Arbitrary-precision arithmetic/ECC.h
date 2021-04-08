#pragma once
#include "BigNum.h"
#include "Cipolla.h"

class Point
{
private:

	BigNum _x, _y;

public:
	Point();
	Point(BigNum x, BigNum y);

	BigNum getX();
	BigNum getY();

	void setX(BigNum x);
	void setY(BigNum y);

	const Point& operator = (const Point& other);
	const bool operator==(const Point& rhs) const;

	friend std::ostream& operator << (std::ostream& os, const Point& number);

	~Point();
};

class Curve
{
private:
	BigNum _a, _b, _p;
	Point _basePoint;

public:
	Curve();
	Curve(BigNum a, BigNum b, BigNum p);
	C at(BigNum x);
	Point neg(Point p);
	Point add(Point p, Point q);
	Point mul(Point point, BigNum t);
	~Curve();
};

class KeyFactory {
private:
	Curve _curve;
	BigNum _private;
	Point _public;

public:
	KeyFactory(Curve curve);

	BigNum getPrivate();
	Point getPublic();

	void generate(Point g, BigNum n);

};

class �ryptogram
{
private:
	Point _�1;
	Point _�2;

public:
	Point get�1();
	Point get�2();

	�ryptogram(Point �1, Point �2);
};

class ElGamal{
private:
	Curve _curve;
	Point _g;
	BigNum _n;

public:
	ElGamal(Curve curve, Point g, BigNum n);

	Point getG();
	BigNum getN();

	�ryptogram encrypt(Point publickey, BigNum m);
	Point decrypt(BigNum privatekey, Point C, Point D);
};

