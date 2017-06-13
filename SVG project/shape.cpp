#include <iostream>
#include "shape.h"

Shape::Shape(const Shape& o) : line(nullptr)
{
	copy(o);
}

Shape& Shape::operator= (const Shape& o)
{
	if (this != &o)
	{
		delete[] line;
		copy(o);
	}
	return *this;
}

void Shape::copy(const Shape& o)
{
	if (o.line != nullptr)
	{
		int len = strlen(o.line) + 1;
		line = new (std::nothrow) char[len];
		strcpy(line, o.line);
	}
}

int Shape::digitCnt(int value)
{
	int cnt = 0;
	while (value > 0)
	{
		value /= 10;
		cnt++;
	}
	return cnt;
}

char* Shape::intToChar(int value)
{
	int digNum = digitCnt(value);
	char str1[] = "\"";
	int str1Len = 2*(strlen(str1));
	int len = digNum + str1Len + 2;
	char* newSet = new char[len];

	int div = 1;
	for (int i = 0; i < digNum - 1; i++)
		div *= 10;
	strcpy(newSet, "\"");
	for (int i = 0; i < digNum; i++)
	{
		int num = value;
		num /= div;
		num %= 10;
		div /= 10;

		if (num == 0)
			strcat(newSet, "0");
		if (num == 1)
			strcat(newSet, "1");
		if (num == 2)
			strcat(newSet, "2");
		if (num == 3)
			strcat(newSet, "3");
		if (num == 4)
			strcat(newSet, "4");
		if (num == 5)
			strcat(newSet, "5");
		if (num == 6)
			strcat(newSet, "6");
		if (num == 7)
			strcat(newSet, "7");
		if (num == 8)
			strcat(newSet, "8");
		if (num == 9)
			strcat(newSet, "9");
	}
	strcat(newSet, "\" ");
	return newSet;
}

char* Shape::extract(const char* text, int index, char* &temp)
{
	for (int i = index; text[i] != '\0'; i++)
	{
		if (text[i] == '\"')
		{
			i += 1;
			int len = 0;
			for (int j = i; text[j] != '\"'; j++)
				len++;

			temp = new (std::nothrow) char[len + 1];

			int pos = 0;
			for (; text[i] != '\"'; pos++, i++)
				temp[pos] = text[i];
			temp[pos] = '\0';

			return temp;
		}
	}
}

char* Shape::quotes(const char* text)
{
	char str[] = "\"";
	int strLen = 2 * (strlen(str));
	int len = strlen(text) + strLen + 2;
	char* temp = new (std::nothrow) char[len];
	strcpy(temp, str);
	strcat(temp, text);
	strcat(temp, str);
	return temp;
}

bool Shape::colourDetect(const char* text)
{
	if (strcmp(text, "white") == 0)
		return true;
	if (strcmp(text, "blue") == 0)
		return true;
	if (strcmp(text, "black") == 0)
		return true;
	if (strcmp(text, "red") == 0)
		return true;
	if (strcmp(text, "green") == 0)
		return true;
	if (strcmp(text, "yellow") == 0)
		return true;
	if (strcmp(text, "none") == 0)
		return true;
	return false;
  }

bool Shape::checkElement(const char* text, const char* elem, int index)
{
	int len = strlen(elem);
	for (int i = index; text[i] != '\"'; i++)
	{
		if (text[i] == elem[0])
		{
			if (text[i] == ' ')
				return false;
			int cnt = 0;
			for (int j = 0; elem[j] != '\0'; i++, j++)
			{
				if (text[i] != elem[j] || text[i] == '\"')
					break;
				cnt++;
			}
			if (len == cnt)
				return true;
		}
		if (text[i] == '>')
			return false;
	}
	return false;
}

bool Shape::ifNum(const char digit)
{
	return (digit >= '0' && digit <= '9');
}

int Shape::charToInt(const char* text)
{
	int len = strlen(text); 
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		if (!ifNum(text[i]))
			return 0;
		num *= 10;
		int dig = (int)text[i] - '0';
		num += dig;
	}
	return num;
}

int Shape::nextElement(const char* text, int index)
{
	int len = 0;
	for (int i = index, cnt = 0; text[i] != '>'; i++)
	{
		if (text[i] == '\"')
			cnt++;
		if (cnt == 2 || text[i] == '>')
			return len;
		len++;
	}
	return 0;
}