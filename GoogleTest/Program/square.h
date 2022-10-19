#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED

class Square{
	private:
		int length;
	public:
		Square();
		int getLength();
		void setLength(int sideLength);
		int getPeremeter();
		int getArea();
};
#endif