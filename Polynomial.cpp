#include<iostream>
#include <iomanip>
#include "Monomial.h"
#include "Polynomial.h"
using namespace std;

Polynomial::Polynomial() // Constructor --> linked list with dummy //
{
	head = (Node *)malloc(sizeof(Node)); // dummy //
	assert(head);
	head->data = new Monomial(0);
	Monomial::Monocount--;
	head->next = NULL; // end of list //
}

void Polynomial::add(const Monomial &a)
{
	Node *curr = head->next;
	Node *prev = head;
	while (curr != NULL) {
		if (a.d > curr->data->d) // we need to add a new node //
			break;
		else if (a.d < curr->data->d)// if the degree is bigger than we want to continue searching on the list //
		{
			prev = curr;
			curr = curr->next;
		}
		else if (a.d == curr->data->d) // if they are equal we want to combine the coefficients //
		{
			curr->data->c += a.c;
			if (curr->data->c == 0)
			{
				delete curr->data;
				prev->next = curr->next; //we need to free curr because he had 0 //
				return;
			}
			return;
		}
	}
	prev->next = (Node *)malloc(sizeof(Node));//we need to add a new node with "a" values
	prev->next->data = new Monomial(a.c, a.d);
	prev->next->next = curr;
	return;
}

void Polynomial::print() const
{
	if (head->next == NULL || (head->next->data->c==0 && head->next->data->d==0)) // list is empty or has monomial=0 //
	{
		cout << "0";
		return;
	}

	Node *curr = head->next;
	while (curr != NULL)
	{
		curr->data->print(); // prints the monomial //
		curr = curr->next;
		if (curr != NULL)
			cout << "+";
	}
}

const Polynomial& Polynomial::operator+=(const Monomial &a) // adding a monomial to the polynomial(linked list) //
{
	(*this).add(a); // uses the add function --> which adds or removes a node from the linked list //
	return *this;
}

const Polynomial& Polynomial:: operator+=(const Polynomial &a) // operator += between 2 polynomials //
{
	Node* curr = this->head->next;
	Node* curra = a.head->next;
	while (curr != NULL && curra != NULL)
	{
		if (curr->data->d == curra->data->d) // if degrees are equal- reduce coeffiecients //
		{
			curr->data->c += curra->data->c;
			curr = curr->next;
			curra = curra->next;
		}
		else if (curr->data->d > curra->data->d)
		{
			curr = curr->next;
		}
		else if (curr->data->d < curra->data->d)
		{
			this->add(Monomial(curra->data->c, curra->data->d));
			curra = curra->next;
		}
	}
	return *this;
}

const Polynomial& Polynomial::operator-=(const Monomial &a) // adding a monomial to the polynomial with (-) before the node //
{
	Node *begin = head;
	Node *curr = head->next;
	while (curr != NULL)
	{
		if (a.d == curr->data->d)
		{
			curr->data->c = curr->data->c - a.c;

			if (curr->data->c == 0)
			{
				delete curr->data;// Monocount-- //
				begin->next = curr->next;
				return *this;
			}
			return *this;
		}
		else if (a.d > curr->data->d) 
		{
			break;
		}

		else if (a.d < curr->data->d)
		{
			curr->next = (Node*)malloc(sizeof(Node));
			curr->next->data = new Monomial(-a.c, a.d);
			curr->next->next = NULL;
			return *this;
		}
	}
	begin->next = (Node*)malloc(sizeof(Node));
	begin->next->data = new Monomial(-a.c, a.d);  // -a.c because of : (-=) //
	begin->next->next = curr;
	return *this;
}

const Polynomial& Polynomial:: operator-=(const Polynomial &a)  // operator -= between 2 polynomials //
{
	Node* curr = this->head->next;
	Node* curra = a.head->next;
	while (curr != NULL && curra != NULL)
	{
		if (curr->data->d == curra->data->d) // if degrees are equal- reduce coeffiecients //
		{
			curr->data->c -= curra->data->c;
			curr = curr->next;
			curra = curra->next;
		}
		else if (curr->data->d > curra->data->d)
		{
			curr = curr->next;
		}
		else if (curr->data->d < curra->data->d)
		{
			this->add(Monomial(curra->data->c * (-1), curra->data->d));
			curra = curra->next;
		}
	}
	return *this;
}

Polynomial Polynomial :: operator+(const Polynomial &a) const // operator + between 2 polynomials //
{
	Polynomial *newpoly = new Polynomial();
	Node *curra = a.head->next;
	Node *currthis = this->head->next;

	while (currthis != NULL)
	{
		newpoly->add(*currthis->data);
		currthis = currthis->next;
	}

	while (curra != NULL)
	{
		newpoly->add(*curra->data);
		curra = curra->next;
	}
	return *newpoly;
}

Polynomial Polynomial :: operator+(const Monomial &a) const // operator + between polynomial and monomial //
{
	Polynomial *temp = new Polynomial(); // new Polynomial //
	Node *curr = this->head->next;
	while (curr != NULL)
	{
		temp->add(*curr->data); // the new polynomial will be the same as the polynomial we used(this) //
		curr = curr->next;
	}
	temp->add(a); // adding the monomial to the new polynomial //
	return *temp;
}

Polynomial Polynomial::operator- (const Polynomial &a) const // operator - between 2 polynomials //
{
	Polynomial *newpoly = new Polynomial();
	Node *currthis = this->head->next;
	while (currthis != NULL)
	{
		newpoly->add(*currthis->data);
		currthis = currthis->next;
	}

	*newpoly -= a; // uses the -= operator function //
	return *newpoly;
}

Polynomial Polynomial::operator-(const Monomial &a) const // operator - between polynomial and monomial //
{
	Polynomial *temp = new Polynomial(); // new Polynomial //
	Node *curr = this->head->next;
	while (curr != NULL)
	{
		temp->add(*curr->data); // the new polynomial will be the same as the polynomial we used(this) //
		curr = curr->next;
	}
	temp->add(Monomial(a.c*(-1), a.d)); // adding the monomial to the new polynomial, but with a minus sign in the coefficient //
	return *temp;
}

Polynomial Polynomial:: operator= (const Polynomial &a) // operator = between 2 polynomials //
{
	Node *todelete = this->head->next;
	Node *curra = a.head->next;
	Node *curr = this->head->next;
	while (curr != NULL)
	{
		delete(todelete->data);
		todelete = curr;
		curr = curr->next;
	}
	this->head->next = NULL;
	while (curra != NULL)
	{
		this->add(*curra->data);
		curra = curra->next;
	}
	return *this;
}

bool Polynomial::operator==(const Polynomial &a) const // operator == between 2 polynomials //
{
	Node *curr = this->head->next;
	Node *curra = a.head->next;
	while (curr != NULL && curra != NULL)
	{
		if (curr->data->c != curra->data->c || curr->data->d != curra->data->d)
			return false;
		else
		{
			curra = curra->next;
			curr = curr->next;
		}
	}
	if (curr == NULL && curra == NULL) // for a case which we saw the same nodes and the lists are in the same length-->they are equal //
		return true;
	else
		return false; // for a case which we saw the same nodes but one list is longer than the other-->they are not equal //
}

bool Polynomial:: operator==(const Monomial &a) const // operator == between polynomial and monomial //
{
	Node *curr = this->head->next;
	if (curr == NULL)
		return false; // polynomial is an empty list -- therefore not equal to monomial a=0 //
	if (curr->data->d == a.d && curr->data->c == a.c) // polynomial is not empty --> we'll check if it is equal to monomial a=0 //
	{
		if (curr->next == NULL) // polynomial is a list with monomial a=0 and that is it //
			return true;
		else // polynomial has other nodes(monomials) in his list //
			return false;
	}
	else
		return false; // polynomial current node is different from monomial a=0 //
}

bool Polynomial:: operator!=(const Polynomial &a) const // operator != between 2 polynomials //
{
	return !(*this == a);
}

bool Polynomial:: operator!=(const Monomial &a) const // operator != between polynomial and monomial //
{
	return !(*this == a);
}

Polynomial Polynomial:: operator-() const// unary operator - return the opposite of the Polynomial (values*(-1)) //
{
	Polynomial *temp = new Polynomial;
	Node *thiscurr = this->head->next;
	while (thiscurr != NULL)
	{
		temp->add(Monomial(thiscurr->data->c * (-1), thiscurr->data->d));
		thiscurr = thiscurr->next;
	}
	return *temp;
}

double Polynomial::operator() (double r) const // p(r) returns the polynomial value for r=x //
{
	Node *curr = this->head->next;
	double sum = 0;
	while (curr != NULL)
	{
		if (curr->data->d != 0)
		{
			sum = sum + (*curr->data)(r); // every monomial in the polynomial will be checked for his value by m(r) //
		}
		else // degree is 0 , which mean there is no X in the monomial //
		{
			sum += curr->data->c;
		}
		curr = curr->next;
	}
	return sum;
}

double Polynomial:: operator[](unsigned int num) // p[d] returns the coefficient of x^d in polynomial p //
{
	Node *curr = this->head->next;
	double x = 0;
	if (curr == NULL)
		return x;
	while (curr != NULL)
	{
		if (curr->data->d == num) // degree is found //
			return (curr->data->getCoebyRef()); // returning the coefficient and therefore setting him to a new value which we decide // 
		else
			curr = curr->next; // keep searching for the degree //
	}

	return x; // degree not found //
}

ostream &operator<<(ostream &output, const Polynomial &a) // operator overloading for output //
{
	a.print(); // uses the print function -- which prints the linked list //
	return output;
}

istream &operator>>(istream &input, Polynomial &a) // operator overloading for output //
{

	Node *curr = a.head->next;
	Node *temp = curr;
	while (curr != NULL)
	{
		temp = curr;
		delete temp->data;
		curr = curr->next;
	}
	a.head->next = NULL; // empty list //
	int i, j = 0, d = 0;
	double c = 0;
	bool addMinus, isStringInsertedCorrectly = false;
	char *stringToRead = new char[100];
	while (!isStringInsertedCorrectly) {
		cin.getline(stringToRead, 100);
		if ((stringToRead[0] >= '0' && stringToRead[0] <= '9') || (stringToRead[0] == '-')) {
			isStringInsertedCorrectly = true;
		}
		else cout << "String wasn't inserted correctly, please enter a valid monomial." << endl;
	}
	addMinus = stringToRead[0] == '-' ? true : false;

	for (i = 0; stringToRead[i] != ',' && stringToRead[i] != '\0'; i++) {
		char *monomialStr = new char[100];
		if (addMinus == true) { // if this flag is true then the monomial is negative
			monomialStr[j] = '-';
			j++;
		}
		while (stringToRead[i] != '+' && stringToRead[i] != '-' && stringToRead[i] != ',' && stringToRead[i] != '\0') {
			monomialStr[j] = stringToRead[i];
			i++;
			j++;
		}
		if (stringToRead[i] == '-') addMinus = true; // flag next monomial as negative
		else addMinus = false; // flag next monomial as positive/non-exist
		monomialStr[j] = '\0';
		Monomial::ExtractCoeAndDegFromString(monomialStr, c, d); // get coe and deg from the string
		delete[]monomialStr;
		a.add(Monomial(c, d));
		c = d = j = 0; // Reseting all the needed variables
		if (stringToRead[i] == '\0') break; // Reached end of string
	}

	delete[]stringToRead;
	return input;
}

Polynomial::~Polynomial()
{
	Node *curr = head->next;
	Node *next = head->next;

	while (curr != NULL)
	{
		next = curr;
		curr = curr->next;
		delete next->data;
	}
}
