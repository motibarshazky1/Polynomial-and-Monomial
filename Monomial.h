#pragma once

#include <iostream>

using namespace std;


class Monomial {

	friend ostream &operator<<(ostream &, const Monomial &); // operator overloading for output //
	friend istream &operator>>(istream &, Monomial &); // operator overloading for input //

public:
	Monomial(); // optional constructor //
	Monomial(double); // optional constructor //
	Monomial(double, unsigned int); // optional constructor //
	static int getNumberOfMonomials();
	void print() const;
	~Monomial();
	Monomial operator=(const Monomial &); // m1=m2 : inserting m2 values into m1, using this //
	Monomial operator+(const Monomial &) const; // m1+m2 : m1,m2 will be const because they won't change //
	Monomial operator-(const Monomial &) const; // m1-m2 : m1,m2 will be const because they won't change //
	Monomial operator*(const Monomial &) const; // m1*m2 : m1,m2 will be const because they won't change //
	const Monomial& operator*=(const double); // m1=m1*num : m1 multiplied by a const number //
	const Monomial& operator+=(const Monomial &); // m2=m2+m1 : m2 changes, will now be (his original values+m1 vlaues) //
	const Monomial& operator-=(const Monomial &); // m2=m2-m1 : m2 changes, will now be (his original values-m1 vlaues) //
	bool operator!=(const Monomial &) const; // checking if the monomial is 0 - if so, return false. otherwise-return true //
	bool operator==(const Monomial &) const; // checking if the monomial is 0 - if so, return true. otherwise-return false //
	Monomial operator-() const; // unary operator - return the opposite of the monomial (values*(-1)) //
	double operator() (double) const; // m(r) returns the monomial value for r=x //
	double& getCoebyRef(); // returning the coefficient of the monomial by reference //
	static void ExtractCoeAndDegFromString(char*, double&, int &);
	friend class Polynomial;

private:
	double c;
	unsigned int d;
	static int Monocount;
};