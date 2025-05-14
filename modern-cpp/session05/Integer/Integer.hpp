/**
 * Complex.cpp
 *
 *  Created on: May 14, 2025
 *      Author: mahmoud
 */
#ifndef INTEGER_HPP_
#define INTEGER_HPP_

class Integer
{
	int *m_pInt;

public:
	// Default constructor
	Integer();

	// Parameterized constructor
	Integer(int value);

	// Copy constructor
	Integer(const Integer &obj);

	// Move constructor
	Integer(Integer &&obj);

	// Copy-assignment
	Integer& operator=(const Integer& rhs);

	// Move-assignment
	Integer& operator=(Integer&& rhs);

	int GetValue() const;

	void SetValue(int value);

	~Integer();
};

#endif // INTEGER_HPP_