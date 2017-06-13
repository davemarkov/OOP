#ifndef RECTANGLE_HEADER
#define RECTANGLE_HEADER

#include "shape.h"

class Rect : public Shape
{
protected:
	int mX;
	int mY;
	int mWidth;
	int mHeight;
	char* fill;
	char* strX;
	char* strY;
	char* strWidht;
	char* strHeight;
	char* strFill;
public:
	Rect() : fill(nullptr), mX(0), mY(0), mWidth(0), mHeight(0),
		strX("x="), strY("y="), strWidht("width="),
		strHeight("height="), strFill("fill=") {}
	Rect(int x, int y, int width, int height)
		: fill(nullptr), mX(x), mY(y), mWidth(width), mHeight(height),
		strX("x="), strY("y="), strWidht("width="),
		strHeight("height="), strFill("fill=") {}
	 
	Rect(const Rect&);
	Rect& operator= (const Rect&);
	void copy(const Rect&);
	Shape* clone() override { return new Rect(*this); }
	virtual ~Rect() { delete[] fill; }
	
	void setFill(const char* text);
	char* getLine() override;
	
	bool withinCircle(int x, int y, int r) override;
	bool withinRectangle(int x, int y, int width, int height) override;
	void translate(int x, int y) override;

	void addData(const char* text) override;
	void createFig();
	void print() override;
	
	void setColour(char* colour);
	void setX(const char* text);
	void setY(const char* text);
	void setWidth(const char* text);
	void setHeight(const char* text);
private:
	void setX(int x) { mX = x; }
	void setY(int y) { mY = y; }
	void setWidth(int width) { mWidth = width; }
	void setHeight(int height) { mHeight = height; }

};

#endif//RECTANGLE_HEADER