#include <iostream>
#include "circle.h"
#include <fstream>

Circle::Circle(const Circle& o) : fill(nullptr),
strCY("cy="), strR("r="), strCX("cx="), strFill("fill=")
{
	copy(o);
}

Circle& Circle::operator= (const Circle& o)
{
	if (this != &o)
	{
		delete[] fill;
		copy(o);
	}
	return *this;
}

void Circle::copy(const Circle& o)
{
	Shape::operator=(o);
	if (o.fill != nullptr)
		setFill(o.fill);
	cx = o.cx;
	cy = o.cy;
	cr = o.cr;
}

char* Circle::getLine()
{
	createFig();
	return line;
}

void Circle::createFig()
{
	char* num1 = intToChar(cx);
	char* num2 = intToChar(cy);
	char* num3 = intToChar(cr);
	char* colour = quotes(fill);
	int baseLen =
		strlen("<circle ") +
		strlen(strCY) +
		strlen(strCX) +
		strlen(strR) +
		strlen(strFill) +
		strlen(colour) +
		strlen(num1) +
		strlen(num3) +
		strlen(num2) + 
		strlen( " />") + 1;

	line = new (std::nothrow) char[baseLen];
	strcpy(line, "<circle ");
	strcat(line, strCX);
	strcat(line, num1);
	strcat(line, strCY);
	strcat(line, num2);
	strcat(line, strR);
	strcat(line, num3);
	strcat(line, strFill);
	strcat(line, colour);
	strcat(line, " />");
	
	delete[] num1;
	delete[] num2;
	delete[] num3;
	delete[] colour;
}

void Circle::print()  
{
	std::cout << "Circle"
		<< "  " << cx
		<< "  " << cy
		<< "  " << cr
		<< "  " << fill
		<< "\n";
}

bool Circle::withinRectangle(int x, int y, int width, int height)
{
	int x1 = cx + cr;
	int x2 = cx - cr;
	int y1 = cy + cr;
	int y2 = cy - cr;

	if ((x1 < x && x1 > width) && (x2 < x  && x2 > width) &&
		(y1 < y && y1 > height) && (y2 < y && y2 > height))
		return true;
	return false;
}

bool Circle::withinCircle(int x, int y, int r)
{
	int x1 = cx + cr;
	int x2 = cx - cr;
	int y1 = cy + cr;
	int y2 = cy - cr;

	int compX1 = x + r;
	int compX2 = x - r;
	int compY1 = y + r;
	int compY2 = y - r;

	if ((x1 < compX1 && x1 > compX2) && (x2 < compX1  && x2 > compX2) &&
		(y1 < compY1 && y1 > compY2) && (y2 < compY1 && y2 > compY2))
		return true;
	return false;
}

void Circle::translate(int x, int y)
{
	cx += x;
	cy += y;
}

void Circle::setX(const char* text)
{
	setX(charToInt(text));
}

void Circle::setY(const char* text)
{
	setY(charToInt(text));
}

void Circle::setR(const char* text)
{
	setR(charToInt(text));
}

void Circle::addData(const char* text)
{
	char* temp = nullptr;
	int xCnt = 0, yCnt = 0, rCnt = 0,
		 fillCnt = 0;
	for (int i = 0; text[i] != '\0'; i++)
	{
		if (text[i] == ' ')
			continue;
		if (checkElement(text, strCX, i) && xCnt == 0)
		{
			cx = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			xCnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, strCY, i) && yCnt == 0)
		{
			cy = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			yCnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, strR, i) && rCnt == 0)
		{
			cr = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			rCnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, strFill, i) && fillCnt == 0)
		{
			setColour(extract(text, i, temp));
			i += nextElement(text, i);
			fillCnt++;
			delete[] temp;
			continue;
		}
	}
}

void Circle::setColour(char* colour)
{
	if (colourDetect(colour))
		setFill(colour);
	else
		setFill("black");
}

void Circle::setFill(const char* text)
{
	int len = strlen(text) + 1;
	fill = new (std::nothrow) char[len];
	if (!fill) throw;
	strcpy(fill, text);
}