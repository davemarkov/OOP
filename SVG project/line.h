#ifndef LINE_HEADER
#define LINE_HEADER

#include "shape.h"

class Line : public Shape
{
protected:
	int x1;
	int x2;
	int y1;
	int y2;
	char* stroke;
	char* x1Str;
	char* x2Str;
	char* y1Str;
	char* y2Str;
	char* strokeStr;
public:
	Line() : stroke(nullptr), x1(0), x2(0), y1(0), y2(0),
	x1Str("x1="), x2Str("x2="), y1Str("y1="), y2Str("y2="),
	strokeStr("stroke=") {}

	Line(const Line&);
	Line& operator= (const Line&);
	void copy(const Line&);
	virtual ~Line() { delete[] stroke; }

	Shape* clone() override { return new Line(*this); }


	void addData(const char* text) override;

	bool withinCircle(int x, int y, int r) override;
	bool withinRectangle(int x, int y, int width, int height) override;
	void translate(int x, int y) override;
	
	void createFig();
	void print() override;
	
	int getX1() { return x1; }
	char* getColour() { return stroke; }
	char* getLine() override;
	
	void setX1(const char* text);
	void setX2(const char* text);
	void setY1(const char* text);
	void setY2(const char* text);
	void setColour(char* colour);
	void setStroke(const char* text);
	
private:
	void setX1(int newX1) { x1 = newX1; }
	void setX2(int newX2) { x2 = newX2; }
	void setY1(int newY1) { y1 = newY1; }
	void setY2(int newY2) { y2 = newY2; }

	

};

#endif//LINE_HEADER