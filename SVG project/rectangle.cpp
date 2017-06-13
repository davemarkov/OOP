#include <iostream>
#include "rectangle.h"

Rect::Rect(const Rect& o) : fill(nullptr),
strX("x="), strY("y="), strWidht("width="),
strHeight("height="), strFill("fill=")
{
	copy(o);
}

Rect& Rect::operator= (const Rect& o)
{
	if (this != &o)
	{
		delete[] fill;
		copy(o);
	}
	return *this;
}

void Rect::copy(const Rect& o)
{
	Shape::operator= (o);
	if (o.fill != nullptr)
		setFill(o.fill);
	mX = o.mX;
    mY = o.mY;
	mWidth = o.mWidth;
	mHeight = o.mHeight;
}

char* Rect::getLine()
{
	createFig();
	return line;
}

void Rect::createFig()
{
	char* num1 = intToChar(mX);
	char* num2 = intToChar(mY);
	char* num3 = intToChar(mWidth);
	char* num4 = intToChar(mHeight);
	char* colour = quotes(fill);
	int baseLen =
		strlen("<rect ") +
		strlen(strX) +
		strlen(strY) +
		strlen(strWidht) +
		strlen(strHeight) +
		strlen(strFill) +
		strlen(colour) +
		strlen(num1) +
		strlen(num2) +
		strlen(num3) +
		strlen(num4) +
		strlen(" />") + 1;
	
	line = new (std::nothrow) char[baseLen];

	strcpy(line, "<rect ");
	strcat(line, strX);
	strcat(line, num1);
	strcat(line, strY);
	strcat(line, num2);
	strcat(line, strWidht);
	strcat(line, num3);
	strcat(line, strHeight);
	strcat(line, num4);
	strcat(line, strFill);
	strcat(line, colour);
	strcat(line, " />");

	delete[] num1;
	delete[] num2;
	delete[] num3;
	delete[] num4;
	delete[] colour;
}

void Rect::print()
{
	std::cout << "Rectangle"
		<< "  " << mX
		<< "  " << mY
		<< "  " << mWidth
		<< "  " << mHeight
		<< "  " << fill
		<< "\n";
}

bool Rect::withinCircle(int x, int y, int r)
{
	if (((x - r) > 0) && ((y - r) > 0))
	{
		int tempX = mX - x;
		int tempY = mY - y;
		int tempWhidth = mWidth - x;
		int tempHeight = mHeight - y;

		x = 0; y = 0;
		if ((r * r) <= ((tempX * tempX) + (tempY * tempY) &&
			(r * r) <= ((tempWhidth * tempWhidth) + (tempHeight * tempHeight))))
			return true;
	}
	return false;
}

bool Rect::withinRectangle(int x, int y, int width, int height)
{
	if ((mX < x && mX > width) && (mY < y && mY > height) &&
		(mWidth < x && mWidth > width) && (mHeight < y && mHeight > height))
		return true;
	return false;
}

void Rect::translate(int x, int y)
{
	mX += x; mWidth += x;
	mY += y; mHeight += y;
}

void Rect::setX(const char* text)
{ 
	setX(charToInt(text));
}

void Rect::setY(const char* text)
{
	setY(charToInt(text));
}

void Rect::setWidth(const char* text)
{
	setWidth(charToInt(text));
}

void Rect::setHeight(const char* text)
{
	setHeight(charToInt(text));
}

void Rect::addData(const char* text)
{
	int cnt = 0;
	char* temp = nullptr;
	while (text[cnt] != ' ')
		cnt++;
	int xCnt = 0, yCnt = 0, widhtCnt = 0,
	    heightCnt = 0, fillCnt = 0;
	for (int i = cnt; text[i] != '>'; i++)
	{
		if (text[i] == ' ')
			continue;
		if (checkElement(text, strX, i) && xCnt == 0)
		{
			mX = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			xCnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, strY, i) && yCnt == 0)
		{
			mY = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			yCnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, strWidht, i) && widhtCnt == 0)
		{
			mWidth = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			widhtCnt++;
			delete[] temp;
			continue;
		}
		if (checkElement(text, strHeight, i) && heightCnt == 0)
		{
			mHeight = charToInt(extract(text, i, temp));
			i += nextElement(text, i);
			heightCnt++;
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

void Rect::setColour(char* colour)
{
	if (colourDetect(colour))
		setFill(colour);
	else
		setFill("black");
}

void Rect::setFill(const char* text)
{
	int len = strlen(text) + 1;
	fill = new (std::nothrow) char[len];
	if (!fill) throw;
	strcpy(fill, text);
}