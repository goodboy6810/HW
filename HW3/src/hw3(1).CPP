#include <iostream>
#include<algorithm>
#include <string>
#include<vector>
#include <sstream>
#include<cmath>

using namespace std;

class Polynomial;

class Term {
	friend Polynomial;
public:
	float coef;//係數
	int exp;//次方數
};

class Polynomial {//多項式

	friend ostream& operator<<(ostream& o, const Polynomial& poly);

public:
	Polynomial();//建構子
	Polynomial(const Polynomial& poly);
	~Polynomial();//解構子
	Polynomial operator+ (const Polynomial& b) const;

	Polynomial operator- (const Polynomial& b) const;
	Polynomial  operator* (const Polynomial& b) const;
	float Eval(float x);//帶x得解
	void NewTerm(float coef, int exp);//添加格子,相同的話合併
private:
	std::vector<long double> coefficients;
	void insertTerm(const Term& term);
	Term* termArray;//係數空間
	int capacity = 10;//組數大小
	int terms = 0;//總共有幾項
};




Polynomial::Polynomial()
{
	this->terms = 0;
	this->capacity = 10;
	termArray = new Term[this->capacity];
}



Polynomial::Polynomial(const Polynomial& b)

{
	this->terms = 0;
	this->capacity = b.capacity;
	termArray = new Term[this->capacity];
	for (int i = 0; i < b.terms; i++) {
		NewTerm(b.termArray[i].coef, b.termArray[i].exp);
	}
}



Polynomial::~Polynomial()
{

	//delete[] termArray;

}



Polynomial Polynomial::operator+ (const Polynomial& b) const

{

	Polynomial c;

	int ac = 0;

	int bc = 0;

	while (ac < terms && bc < b.terms) {

		if (termArray[ac].exp == b.termArray[bc].exp) {

			float coef = termArray[ac].coef + b.termArray[bc].coef;

			if (coef)c.NewTerm(coef, termArray[ac].exp);

			ac++; bc++;

		}
		else if (termArray[bc].exp < b.termArray[bc].exp) {

			c.NewTerm(b.termArray[bc].coef, b.termArray[bc].exp);

			bc++;

		}
		else {

			c.NewTerm(termArray[ac].coef, termArray[ac].exp);

			ac++;

		}

	}

	while (ac < terms) {

		c.NewTerm(termArray[ac].coef, termArray[ac].exp);

		ac++;

	}

	while (bc < b.terms) {

		c.NewTerm(b.termArray[bc].coef, b.termArray[bc].exp);

		bc++;

	}

	return c;

}

Polynomial Polynomial::operator- (const Polynomial& b) const

{

	Polynomial c;

	int ac = 0;

	int bc = 0;

	while (ac < terms && bc < b.terms) {

		if (termArray[ac].exp == b.termArray[bc].exp) {

			float coef = termArray[ac].coef - b.termArray[bc].coef;

			if (coef)c.NewTerm(coef, termArray[ac].exp);

			ac++; bc++;

		}
		else if (termArray[bc].exp < b.termArray[bc].exp) {

			c.NewTerm(b.termArray[bc].coef, b.termArray[bc].exp);

			bc++;

		}
		else {

			c.NewTerm(termArray[ac].coef, termArray[ac].exp);

			ac++;

		}

	}

	while (ac < terms) {

		c.NewTerm(termArray[ac].coef, termArray[ac].exp);

		ac++;

	}

	while (bc < b.terms) {

		c.NewTerm(b.termArray[bc].coef, b.termArray[bc].exp);

		bc++;

	}

	return c;

}



Polynomial Polynomial::operator* (const Polynomial& b) const

{

	Polynomial c;

	for (int i = 0; i < terms; i++) {

		for (int j = 0; j < b.terms; j++) {

			float coef = termArray[i].coef * b.termArray[j].coef;

			int exp = termArray[i].exp + b.termArray[j].exp;

			c.NewTerm(coef, exp);

		}

	}

	return c;

}

void Polynomial::NewTerm(float coef, int exp)

{

	if (terms == capacity) {

		capacity *= 2;

		Term* tmp = new Term[capacity];

		copy(termArray, termArray + terms, tmp);

		delete[] termArray;

		termArray = tmp;

	}

	Term ATerm;

	ATerm.coef = coef; ATerm.exp = exp;

	insertTerm(ATerm);

}

void Polynomial::insertTerm(const Term& term)

{

	int i;

	for (i = 0; i < terms && term.exp < termArray[i].exp; i++) {

	}

	if (term.exp == termArray[i].exp) {

		termArray[i].coef += term.coef;

		if (!termArray[i].coef) {

			for (int j = i; j < terms - 1; j++)

				termArray[j] = termArray[j + 1];

			terms--;

		}

	}
	else {

		for (int j = terms - 1; j >= i; j--)

			termArray[j + 1] = termArray[j];

		termArray[i] = term;

		terms++;

	}

}



float Polynomial::Eval(float x)

{

	float sum = 0;

	for (int i = 0; i < terms; i++) {

		sum += termArray[i].coef * pow(x, termArray[i].exp);

	}

	return sum;

}



ostream& operator<<(ostream& o, const Polynomial& poly)

{

	for (int i = 0; i < poly.terms - 1; i++) {

		o << poly.termArray[i].coef << "x^" << poly.termArray[i].exp << " + ";

	}

	o << poly.termArray[poly.terms - 1].coef << "x^" << poly.termArray[poly.terms - 1].exp;

	return o;

}



int main()

{

	Polynomial a;

	cout << "輸入a多像式係數和X的次方 ex : 5x ^ 2請輸入 5 2 注意:輸入0 0 停止" << endl;
	int y;
	float x;
	cin >> x >> y;
	while (x != 0 || y != 0)
	{
		a.NewTerm(x, y);
		cin >> x >> y;
	}



	Polynomial b;

	cout << "輸入b多項式係數和X的次方 ex : 5x ^ 2請輸入 5 2 注意:輸入0 0 停止" << endl;
	int j;
	float i;
	cin >> i >> j;
	while (i != 0 || j != 0)
	{
		b.NewTerm(i, j);
		cin >> i >> j;
	}



	cout << "(" << a << ") + (" << b << ") = " << a + b << endl; //a+b輸出
	cout << "(" << a << ") - (" << b << ") = " << a - b << endl; //a+b輸出
	cout << "(" << a << ") * (" << b << ") = " << a * b << endl;//a*b輸出
	cout << "請輸入x數值" << endl;
	int x2;
	cin >> x2; //輸入x數值
	cout << "相加後F(x=" << x2 << ") = " << (a + b).Eval(x2) << endl;//輸出相加後帶入x後計算結果

}
