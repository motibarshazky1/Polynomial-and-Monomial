#ifndef Polynomial_H
#define Polynomial_H
#include "Monomial.h"
#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <assert.h>
using namespace std;

class Monomial; // because Monomial is a friend of Polynomial //

struct Node //our linked list struct 
{
	Monomial* data;//every node will point to a Monomial object
	Node* next;
};
class Polynomial {

	friend ostream &operator<<(ostream &, const Polynomial &); // operator overloading for output //
	friend istream &operator>>(istream &, Polynomial &); // operator overloading for input //

private:
	Node *head;//first node of the linked list
public:
	Polynomial();//constructer-> creating Node linked list that every node points to a monomial object
	void add(const Monomial &);//adding a Monomial object to the linked list
	void print()const;//printing a linked list
	~Polynomial();//destructer

	const Polynomial& operator+=(const Monomial &); // operator += between monomial and polynomial //
	const Polynomial& operator+=(const Polynomial &); // operator += between 2 polynomials //
	const Polynomial& operator-=(const Monomial &);  // operator -= between monomial and polynomial //
	const Polynomial& operator-=(const Polynomial &);  // operator -= between monomial and polynomial //
	Polynomial operator+ (const Polynomial &) const; // operator + between 2 polynomials //
	Polynomial operator+(const Monomial &)const; // operator + between polynomial and monomial //
	Polynomial operator- (const Polynomial &) const; // operator + between 2 polynomials //
	Polynomial operator-(const Monomial &)const; // operator + between polynomial and monomial //
	Polynomial operator= (const Polynomial &); // operator = between 2 polynomials //
	bool operator==(const Polynomial &) const; // operator == between 2 polynomials //
	bool operator==(const Monomial &) const; // operator == between polynomial and monomial //
	bool operator!=(const Polynomial &) const; // operator != between 2 polynomials //
	bool operator!=(const Monomial &) const; // operator != between polynomial and monomial //
	Polynomial operator-() const; // unary operator - return the opposite of the Polynomial (values*(-1)) //
	double operator() (double) const; // p(r) returns the polynomial value for r=x //
	double operator[](unsigned int); // p[d] returns the coefficient of x^d in polynomial p //
};

#endif

