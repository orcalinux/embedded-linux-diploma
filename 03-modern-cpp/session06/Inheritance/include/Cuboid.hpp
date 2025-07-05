#ifndef INCLUDE_CUBOID_HPP_
#define INCLUDE_CUBOID_HPP_

#include "Rectangle.hpp"

class Cuboid : public Rectangle {
private:
	int height;

public:

	Cuboid();

	Cuboid(int l, int b, int h);

	int getHeight() const;

	void setHeight(int h);

	int volume() const;

};


#endif /* INCLUDE_CUBOID_HPP_ */
