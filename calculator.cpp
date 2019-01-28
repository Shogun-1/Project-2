#include <iostream>
#include <cmath>
#include <sstream>
#include <exception>

using namespace std;

void CheckDen (const int& den) // Checking that denominator is not equal to zero
{
	if (den == 0)
	{
		throw runtime_error("Denominator must not be equal to zero");
	}
}

int NOD (int a, int b) // Finding the greatest common divisor
{
	a = abs (a);
	b = abs (b);
  	while (a > 0 && b > 0) {
    		if (a > b) 
		{
      			a %= b;
    		} 
		else 
		{
      			b %= a;
   	 	}
	}
	return a + b;
}

int NOK (int a, int b) // Finding the least common multiple
{
	a = abs (a);
	b = abs (b);
	int i = 1;
	while (i % a != 0 || i % b != 0)
	{
		i++;
	}
	return i;
}

class Rational {
public:
	friend istream& operator>> (istream& stream, Rational& rational);

	Rational() {
    	p = 0;
    	q = 1;
    }

    Rational(int numerator, int denominator) {
    	p = numerator;
    	q = denominator;
    	int nod = NOD(p, q);
    	if (p == 0)
    	{
    		q = 1;
    	}
    	else // // Fraction reduction
    	{
    		int result = abs (p / nod);
    		double p_double = p;
    		double q_double = q;
    		if (p_double / q_double < 0)
    		{
    			p = -result;
    		}
    		else
    		{
    			p = result;
    		}
    		result = abs (q / nod);
    		q = result;
    	}
    }

    int Numerator() const {
    	return p;
    }

    int Denominator() const {
    	return q;
    }
private:
    int p;
    int q;
};

// Operator overloadings for the Rational class
Rational operator+ (const Rational& lhs, const Rational& rhs)
{
	int nok = NOK (lhs.Denominator(), rhs.Denominator());
	int numerator = (lhs.Numerator() * (nok / lhs.Denominator())) +
			(rhs.Numerator() * (nok / rhs.Denominator()));
	Rational result (numerator, nok);
	return result;
}

Rational operator- (const Rational& lhs, const Rational& rhs)
{
	int nok = NOK (lhs.Denominator(), rhs.Denominator());
	int numerator = (lhs.Numerator() * (nok / lhs.Denominator())) -
			(rhs.Numerator() * (nok / rhs.Denominator()));
	Rational result (numerator, nok);
	return result;
}

bool operator== (const Rational& lhs, const Rational& rhs)
{
	if (lhs.Numerator() == rhs.Numerator() &&
			lhs.Denominator() == rhs.Denominator())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

Rational operator* (const Rational& lhs, const Rational& rhs)
{
	Rational result (lhs.Numerator() * rhs.Numerator(),
			lhs.Denominator() * rhs.Denominator());
	return result;
}

Rational operator/ (const Rational& lhs, const Rational& rhs)
{
	Rational result (lhs.Numerator() * rhs.Denominator(),
			lhs.Denominator() * rhs.Numerator());
	return result;
}

ostream& operator<< (ostream& stream, const Rational& rational)
{
	stream << rational.Numerator() << "/" << rational.Denominator();
	return stream;
}

istream& operator>> (istream& stream, Rational& rational)
{
	stream >> rational.p;
	stream.ignore(1);
	stream >> rational.q;
	return stream;
}

bool operator< (const Rational& lhs, const Rational& rhs)
{
	double num_lhs = lhs.Numerator();
	double den_lhs = lhs.Denominator();
	double num_rhs = rhs.Numerator();
	double den_rhs = rhs.Denominator();
	return (num_lhs / den_lhs < num_rhs / den_rhs);
}

int main()
{
	try {
	Rational n, d;
	string op;
	cin >> n >> op >> d;
	CheckDen (n.Denominator());
	CheckDen (d.Denominator());
	if (op == "+")
	{
		cout << n + d;
	}
	else if (op == "-")
	{
		cout << n - d;
	}
	else if (op == "*")
	{
		cout << n * d;
	}
	else if (op == "/")
	{
		CheckDen (d.Numerator());
		cout << n / d;
	} } catch (exception& ex) {
		cout << ex.what();
	}
	return 0;
}
