/**
 * Complex.cpp
 *
 *  Created on: May 14, 2025
 *      Author: mahmoud
 */
#ifndef INTEGER_HPP_
#define INTEGER_HPP_

#include <ostream>

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

	// Copy operator
	Integer &operator=(Integer &obj);

	// Move operator
	Integer &operator=(Integer &&obj);

	// Returns the value of the integer
	int GetValue() const;

	// Set the value of the integer
	void SetValue(int value);

	friend std::ostream &operator<<(std::ostream &os, const Integer &obj);

	// Destructor
	~Integer();
};

#endif // INTEGER_HPP_
