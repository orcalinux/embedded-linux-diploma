#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <iostream>

class Fraction {
public:
	Fraction(int num = 0, int den = 1);

	void setNumerator(int num);
	void setDenominator(int den);

	int getNumerator() const;
	int getDenominator() const;

	Fraction  operator+(const Fraction& other);
	Fraction& operator+=(const Fraction& other);

	Fraction  operator-(const Fraction& other);
	Fraction& operator-=(const Fraction& other);

	Fraction  operator*(const Fraction& other);
	Fraction& operator*=(const Fraction& other);

	Fraction& operator++();
	Fraction  operator++(int);

	Fraction& operator--();
	Fraction  operator--(int);

	friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
	friend std::istream& operator>>(std::istream& is, Fraction& f);

private:
	int num_;
	int den_;

	void simplify();
};

#endif // FRACTION_HPP
