#ifndef CIRCLE_HEADER
#define CIRCLE_HEADER

#include "shape.h"

class Circle : public Shape
{
	int cx;
	int cy;
	int cr;
	char* fill;
	char* strCY;
	char* strR;
	char* strCX;
	char* strFill;
public:
	Circle() : fill(nullptr), cx(0), cy(0), cr(0),
		strCY("cy="), strR("r="), strCX("cx="), strFill("fill=") {}
	Circle(int x, int y, int r) : fill(nullptr), cx(x), cy(y), cr(r),
		strCY("cy="), strR("r="), strCX("cx="), strFill("fill=") {}

	Circle(const Circle&);
	Circle& operator= (const Circle&);
	virtual ~Circle() { delete[] fill; }
	void copy(const Circle&);

	Shape* clone() override { return new Circle(*this); }
	void createFig();
	void addData(const char* text) override;
	void print() override;
	
	void translate(int x, int y) override;
	bool withinCircle(int x, int y, int r) override;
	bool withinRectangle(int x, int y, int width, int height) override;

	void setX(const char* text);
	void setY(const char* text);
	void setR(const char* text);
	void setColour(char* colour);
private:
	char* getLine() override;
	char* getColour() { return fill; }
	int getX() { return cx; }

private:	
	void setX(int x) { cx = x; }
	void setY(int y) { cy = y; }
	void setR(int r) { cr = r; }
	void setFill(const char* text);

};

#endif//CIRCLE_HEADER