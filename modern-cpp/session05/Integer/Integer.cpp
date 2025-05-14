/**
 * Complex.cpp
 *
 *  Created on: May 9, 2025
 *      Author: mahmoud
 */
#include "Integer.hpp"
#include <iostream>

Integer::Integer()
{
	std::cout << "Integer()" << std::endl;
	m_pInt = new int(0);
}

Integer::Integer(int value)
{
	std::cout << "Integer(int)" << std::endl;
	m_pInt = new int(value);
}

Integer::Integer(const Integer &obj)
{
	std::cout << "Integer(const Integer&)" << std::endl;
	m_pInt = new int{*obj.m_pInt};
}

Integer::Integer(Integer &&obj)
{
	std::cout << "Integer(int&&)" << std::endl;
	m_pInt = obj.m_pInt;
	obj.m_pInt = nullptr;
}

// Copy-assignment
Integer &Integer::operator=(const Integer &rhs)
{
	std::cout << "operator=(const Integer&)" << std::endl;
	if (this != &rhs)
	{
		// free old
		delete m_pInt;
		// deep-copy from rhs
		m_pInt = new int{*rhs.m_pInt};
	}
	return *this;
}

// Move-assignment
Integer &Integer::operator=(Integer &&rhs)
{
	std::cout << "operator=(Integer&&)" << std::endl;
	if (this != &rhs)
	{
		// free old
		delete m_pInt;
		// steal pointer, leave rhs in a valid state
		m_pInt = rhs.m_pInt;
		rhs.m_pInt = nullptr;
	}
	return *this;
}

int Integer::GetValue() const
{
	return *m_pInt;
}

void Integer::SetValue(int value)
{
	*m_pInt = value;
}

Integer::~Integer()
{
	std::cout << "~Integer()" << std::endl;
	delete m_pInt;
}
