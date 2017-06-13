#include <iostream>
#include "line.h"
#include <fstream>

Line::Line(const Line& o) : stroke(nullptr),
x1Str("x1="), x2Str("x2="), y1Str("y1="), y2Str("y2="),
strokeStr("stroke=")
{
	copy(o);
}

Line& Line::operator= (const Line& o)
{
	if (this != &o)
	{
		delete[] stroke;
		copy(o);
	}
	return *this;
}

void Line::copy(const Line& o)
{
	Shape::operator= (o);
	if (o.stroke != nullptr)
		setStroke(o.stroke);
	x1 = o.x1;
	x2 = o.x2;
	y1 = o.y1;
	y2 = o.y2;
}

char* Line::getLine()
{
	createFig();
	return line;
}

void Line::createFig()
{
	char* num1 = intToChar(x1);
	char* num2 = intToChar(y1);
	char* num3 = intToChar(x2);
	char* num4 = intToChar(y2);
	char* colour = quotes(stroke);
	int baseLen =
		strlen("<line ") +
		strlen(x1Str) +
		strlen(x2Str) +
		strlen(y1Str) +
		strlen(y2Str) +
		strlen(strokeStr) +
		strlen(colour) +
		strlen(num1) +
		strlen(num2) +
		strlen(num3) +
		strlen(num4) +
		strlen(" />") + 1;
	
	line = new (std::nothrow) char[baseLen];
	
	strcpy(line, "<line ");
	strcat(line, x1Str);
	strcat(line, num1);
	strcat(line, y1Str);
	strcat(line, num2);
    strcat(line, x2Str);
	strcat(line, num3);
	strcat(line, y2Str);
	strcat(line, num4);
	strcat(line, strokeStr);
	strcat(line, colour);
	strcat(line, " />");

	delete[] num1;
	delete[] num2;
	delete[] num3;
	delete[] num4;
	delete[] colour;
}

void Line::print()
{
	std::cout << "Line"
		<< "  " << x1
		<< "  " << y1
		<< "  " << x2
		<< "  " << y2
		<< "  " << stroke
		<< "\n";
}

bool Line::withinCircle(int x, int y, int r)
{
	if (((x - r) > 0) && ((y - r) > 0))
	{
		int tempX = x1 - x;
		int tempY = y1 - y;
		int tempWhidth = x2 - x;
		int tempHeight = y2 - y;

		x = 0; y = 0;
		if ((r * r) <= ((tempX * tempX) + (tempY * tempY) &&
			(r * r) <= ((tempWhidth * tempWhidth) + (tempHeight * tempHeight))))
			return true;
	}
	return false;
}

bool Line::withinRectangle(int x, int y, int width, int height)
{
	if ((x1 < x && x1 > width) && (y1 < y && y1 > height) &&
		(x2 < x && x2 > width) && (y2 < y && y2 > height))
		return true;
	return false;
}

void Line::translate(int x, int y)
{
	x1 += x; x2 += x;
	y1 += y; y2 += y;
}

void Line::setX1(const char* text)
{
	setX1(charToInt(text));
}

void Line::setX2(const char* text)
{
	setX2(charToInt(text));
}

void Line::setY1(const char* text)
{
	setY1(charToInt(text));
}
void Line::setY2(const char* text)
{
	setY2(charToInt(text));
}

void Line::addData(const char* text)
{
	char* temp = nullptr;
	int x1Cnt = 0, y1Cnt = 0, x2Cnt = 0,
		y2Cnt = 0, strokeCnt = 0;
	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == ' ')
			continue;
		if (checkElement(text, x1Str, i) && x1Cnt == 0)
		{
			x1 = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			x1Cnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, y1Str, i) && y1Cnt == 0)
		{
			y1 = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			y1Cnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, x2Str, i) && x2Cnt == 0)
		{
			x2 = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			x2Cnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, y2Str, i) && y2Cnt == 0)
		{
			y2 = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			y2Cnt++;
			delete[] temp;
			continue;
		}
	    if (checkElement(text, strokeStr, i) && strokeCnt == 0)
		{
			setColour(extract(text, i, temp));
			i += nextElement(text, i);
			strokeCnt++;
			delete[] temp;
			continue;
		}
	}
}

void Line::setColour(char* colour)
{
	if (colourDetect(colour))
		setStroke(colour);
	else
		setStroke("black");
}

void Line::setStroke(const char* text)
{
	int len = strlen(text) + 1;
	stroke = new (std::nothrow) char[len];
	if (!stroke) throw;
	strcpy(stroke, text);
}
