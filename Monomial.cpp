#include "Monomial.h"
#include <iostream>
using namespace std;

int Monomial::Monocount = 0; // setting our static variable for counting the number od monomials we create //	


Monomial::Monomial() // default constructor --> d=0 in this monomial, and we will increase the counter as well //
{
	d = 0;
	c = 1;
	Monocount++;
}

Monomial::Monomial(double coefficient) // d=0 in this monomial, c gets the number we sent(the coefficient), increasing the counter //
{
	d = 0;
	c = coefficient;
	Monocount++;
}

Monomial::Monomial(double coefficient, unsigned int degree) // c is the coefficient (the first number we sent), d is the degree of the monomial, increasing the counter //
{
	d = degree;
	c = coefficient;
	Monocount++;
}



int Monomial::getNumberOfMonomials() // returns the static variable-Monocount //
{
	return Monocount;
}

void Monomial::print() const // prints each object //
{
	if (c != 0)
	{
		if (d == 0)
			cout << c;
		else if (c == 1)
		{
			if (d != 1)
				cout << "x^" << d;
			else
				cout << "x";
		}
		else if (d != 1)
			cout << c << "*x^" << d;
		else
			cout << c << "*x";
	}
}



Monomial Monomial::operator=(const Monomial &a) // m1=m2 : inserting m2 values into m1, using this //
{
	this->d = a.d;
	this->c = a.c;
	return *this;
}

Monomial Monomial::operator+(const Monomial &a) const // m1+m2 : m1,m2 will be const because they won't change //
{
	Monomial* temp = new Monomial;
	if (this->d == a.d) // add coedffiecients only if degrees are equal //
	{
		temp->c = this->c + a.c;
		temp->d = a.d;
		return *temp;
	}
	else
		return *this; // otherwise, return the same monomial //
}

Monomial Monomial::operator-(const Monomial &a) const // m1-m2 : m1,m2 will be const because they won't change //
{
	Monomial* temp = new Monomial;
	if (this->d == a.d)// substract coedffiecients only if degrees are equal //
	{
		temp->c = this->c - a.c;
		temp->d = a.d;
		return *temp;
	}
	else
		return *this; // otherwise, return the same monomial //
}

Monomial Monomial::operator*(const Monomial &a) const // m1*m2 : m1,m2 will be const because they won't change //
{
	return Monomial(this->c * a.c, d + a.d);
}

const Monomial& Monomial::operator*=(const double num) // m1=m1*num : m1 multiply by a const number //
{
	this->c *= num;
	return *this;
}

const Monomial& Monomial::operator+=(const Monomial &a) // m2=m2+m1 : m2 changes, will now be (his original values+m1 vlaues) //
{
	if (this->d == a.d) // add coeffiecients only if degrees are equal //
	{
		this->c += a.c;
		return *this;
	}
	else
		return *this; // otherwise, return the same monomial //
}

const Monomial& Monomial::operator-=(const Monomial &a) // m2=m2-m1 : m2 changes, will now be (his original values-m1 vlaues) //
{
	if (this->d == a.d) // add coedffiecients only if degrees are equal //
	{
		this->c -= a.c;
		return *this;
	}
	else
		return *this; // otherwise, return the same monomial //
}

bool Monomial::operator==(const Monomial &a) const // checking if the monomial is equal to 0 - if so, return true. otherwise-return false //
{
	return (this->c == a.c && this->d == a.d);
}

bool Monomial::operator!=(const Monomial &a) const // checking if the monomial is 0 - if so, return false. otherwise-return true //
//  the checking is with the help of operator== which we defined before //
{
	return !(this->c == a.c);
}


ostream &operator<<(ostream &output, const Monomial &a) // operator overloading for output //
{
	if (a.c == 0) // monomial is 0 //
		output << "0";
	else if (a.c == 1)
	{
		if (a.d == 0)
			output << "1";
		else if (a.d == 1)
			output << "x";
		else // degree is at least 2 //
			output << "x^" << a.d;
	}
	else if (a.c == -1)
	{
		if (a.d == 0)
			output << "-1";
		else if (a.d == 1)
			output << "-x";
		else // degree is at least 2 //
			output << "-x^" << a.d;
	}
	else // coefficient is not 0 and 1 and -1 //
	{
		if (a.d == 1)
			output << a.c << "*x";
		else if (a.d == 0)
			output << a.c;
		else //degree is at least 2 //
			output << a.c << "*x^" << a.d;
	}
	return output;
}

istream &operator>>(istream &input, Monomial &a) // operator overloading for input //
{
	double c = 0;
	int d = 0;
	char *stringToRead = new char[100];
	cin.getline(stringToRead, 100);
	a.ExtractCoeAndDegFromString(stringToRead, c, d);
	delete[]stringToRead;
	a.c = c;
	a.d = d;
	return input;
}

Monomial Monomial::operator-() const // unary operator - return the opposite of the monomial (values*(-1)) //
{
	Monomial* opposite = new Monomial;
	opposite->c = -c;
	opposite->d = this->d;
	return *opposite;
}

double Monomial::operator()(double r) const // m(r) returns the monomial value for r=x //
{
	double result = 1;
	if (this->c == 0)
		return 0;
	else if (this->c == 1)
	{
		if (this->d == 0)
			return 1;
		else if (this->d == 1)
			return r;
		else
		{
			for (unsigned int i = 1; i <= this->d; i++) // unsigned because we compare d(unsigned int) to i //
				result = result * r;
			return result;
		}
	}
	else // c >=2
	{
		if (this->d == 0)
			return this->c;
		else if (this->d == 1)
			return (this->c*r);
		else
		{
			for (unsigned int i = 0; i < this->d; i++)// unsigned because we compare d(unsigned int) to i //
			{
				result = result * r;
			}
			return (this->c*result);
		}
	}
}

double& Monomial::getCoebyRef() // returning the coefficient of the monomial by reference //
{
	return c;
}

void Monomial::ExtractCoeAndDegFromString(char* StringToRead, double &c, int &d)
{
	int i;
	bool checkCoefficient = true, turnToNegative = false;
	if (StringToRead[0] == '-') turnToNegative = true;
	for (i = 0; StringToRead[i] != '\0'; i++)
	{
		if (checkCoefficient == true && (StringToRead[i] >= '0' && StringToRead[i] <= '9')) // add to coefficient//
		{
			c = c * 10 + (StringToRead[i] - '0');
		}
		else if (StringToRead[i] == 'x')
		{
			checkCoefficient = false; // start checking degree
		}
		else if (checkCoefficient == false && StringToRead[i] != '^' && StringToRead[i] != ' ')
		{
			d = d * 10 + (StringToRead[i] - '0');
		}
	}
	if (checkCoefficient == false && d == 0) d = 1; // no exponent after x //
	if (turnToNegative == true) c *= -1; // first char was '-' //
}

Monomial::~Monomial() // destructor for each object we created by the consructor //
{
	Monocount--;
}