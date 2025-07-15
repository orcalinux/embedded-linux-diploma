#include <Fraction.hpp>
#include <iostream>
#include <numeric>

Fraction::Fraction(int num, int den)
  : num_(num), den_(den)
{
	if(!den_) {
		std::cerr << "Invalid argument" << std::endl;
		den_ = 1;
	}
	simplify();
}

void Fraction::setNumerator(int num) {
	num_ = num;
}

void Fraction::setDenominator(int den) {
	if (!den)
		return;
	den_ = den;
}

int Fraction::getNumerator() const {
	return num_;
}

int  Fraction::getDenominator() const {
	return den_;
}

Fraction Fraction::operator+(const Fraction& other) {
	int l = std::lcm(den_, other.den_);
	int x = l/den_, y = l/other.den_;
	return Fraction{num_ * x + other.num_ * y, l};
}

Fraction& Fraction::operator+=(const Fraction& other) {
	return *this = *this + other;
}

Fraction Fraction::operator-(const Fraction& other) {
	int l = std::lcm(den_, other.den_);
	int x = l/den_, y = l/other.den_;
	return Fraction{num_ * x - other.num_ * y, l};
}

Fraction& Fraction::operator-=(const Fraction& other) {
	return *this = *this - other;
}

Fraction Fraction::operator*(const Fraction& other) {
	return Fraction{num_ * other.num_, den_ * other.den_};
}

Fraction& Fraction::operator*=(const Fraction& other) {
	num_ *= other.num_;
	den_ *= other.den_;
	simplify();
	return *this;
}

Fraction& Fraction::operator++() {
	num_ += den_;
	simplify();
	return *this;
}

Fraction Fraction::operator++(int) {
	Fraction tmp{num_, den_};
	num_ += den_;
	simplify();
	return tmp;
}

Fraction& Fraction::operator--() {
	num_ -= den_;
	simplify();
	return *this;
}

Fraction Fraction::operator--(int) {
	Fraction tmp = *this;
	--*this;
	return tmp;
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) {
	return os << f.num_ << '/' << f.den_;
}

std::istream& operator>>(std::istream& is, Fraction& f) {
	int n, d;
	char sep;
	if(is >> n >> sep >> d && sep == '/') {
		f = Fraction(n, d);
	} else {
		 is.setstate(std::ios::failbit);
	}
	return is;
}

void Fraction::simplify() {
	int g = std::gcd(num_ < 0 ? -num_ : num_, den_);

	num_ /= g;
	den_ /= g;

	if (den_ < 0) {
		den_ = - den_;
		num_ = -num_;
	}
}
