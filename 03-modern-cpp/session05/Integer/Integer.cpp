/**
 * Complex.cpp
 *
 *  Created on: May 14, 2025
 *      Author: mahmoud
 */
#include "Integer.hpp"
#include <iostream>
#include <ostream>

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
	this->m_pInt = obj.m_pInt;
	obj.m_pInt = nullptr;
}

Integer &Integer::operator=(Integer &obj)
{
	std::cout << "operator=(Integer&)" << std::endl;
	if (this != &obj)
	{
		if (m_pInt != nullptr)
		{
			delete m_pInt;
			m_pInt = new int(*(obj.m_pInt));
		}
	}
	return *this;
}

Integer &Integer::operator=(Integer &&obj)
{
	std::cout << "operator=(Integer&&)" << std::endl;
	if (this != &obj)
	{
		if (m_pInt != nullptr)
		{
			delete m_pInt;
			m_pInt = obj.m_pInt;
			obj.m_pInt = nullptr;
		}
	}
	return *this;
}

int Integer::GetValue() const
{
	return *m_pInt;
}

void Integer::SetValue(int value)
{
	if (!m_pInt)
		m_pInt = new int;
	*m_pInt = value;
}

std::ostream &operator<<(std::ostream &os, const Integer &obj)
{
	os << *obj.m_pInt;
	return os;
}

Integer::~Integer()
{
	std::cout << "~Integer()" << std::endl;
	delete m_pInt;
}
