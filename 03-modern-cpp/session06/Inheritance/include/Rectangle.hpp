#ifndef INCLUDE_RECTANGLE_HPP_
#define INCLUDE_RECTANGLE_HPP_

class Rectangle {

private:
	int length;
	int breadth;

public:
	Rectangle();

	Rectangle(int l, int b);

	int getLength() const;

	int getBreadth() const;

	void setLength(int l);

	void setBreadth(int b);

	int area() const;

	int perimeter() const;


};

#endif /* INCLUDE_RECTANGLE_HPP_ */
