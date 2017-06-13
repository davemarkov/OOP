#include <iostream>
#include "eggData.h"


Egg::Egg() : eggName(nullptr), eggSize(0) {}

Egg::Egg(const Egg& o) : eggName(nullptr), eggSize(0)
{
	objectEggCopy(o);
}

Egg& Egg::operator= (const Egg& p)
{
	if (this != &p)
		objectEggCopy(p);
	return *this;
}

void Egg::objectEggCopy(const Egg& s)
{
	setName(s.eggName);
	eggSize = s.eggSize;
}


Egg::~Egg()
{
	clear();
}

void Egg::clear()
{
	delete[] eggName;
}

std::ostream& operator<< (std::ostream& out, Egg& o)
{
	out << "Egg name: " << o.getName() << "    Size: " << o.getSize() << "\n";
	return out;
}

Egg& Egg::operator+= (const char* text)
{
	int newLen = strlen(getName()) + strlen(text) + 1;
	char* newName = new char[newLen];
	strcpy(newName, eggName);
	strcat(newName, text);

	delete eggName;
	eggName = newName;
	return *this;
}

Egg& Egg::operator*=(const int multi)
{
		int newSize = getSize();
		setSize(newSize * multi);
	return *this;
}

Egg& Egg::operator/=(const int div)
{
		int newSize = getSize();
		setSize(newSize / div);
	return *this;
}

void Egg::addition()
{
	int newSize = getSize();
	setSize(newSize + 1);
}

Egg& Egg::operator++ (int) //B++
{
	addition();
	return *this;
}

Egg& Egg::operator++ () //++B
{
	addition();
	return *this;
}

void Egg::removal()
{
	int newSize = getSize();
	if (newSize > 0)
		setSize(newSize - 1);
}

Egg& Egg::operator-- (int)
{
	removal();
	return *this;
}

Egg& Egg::operator-- ()
{
	removal();
	return *this;
}

bool operator== (const Egg& o, const Egg& p)
{
	if (strcmp(o.getName(), p.getName()) != 0)
		return false;
	return true;
}

bool operator!= (const Egg& o, const Egg& p)
{
	if (o == p)
		return false;
	return true;
}

bool operator<  (const Egg& o, const Egg& p)
{
	if (strcmp(o.getName(), p.getName()) == -1)
		return false;
	return true;
}

bool operator>  (const Egg& o, const Egg& p)
{
	if (o < p)
		return false;
	return true;
}

void Egg::initializeName(int len)
{
	try
	{
		eggName = new (std::nothrow) char[len];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
}

void Egg::setName(char* newEggName)
{
	int len = strlen(newEggName) + 1;
	initializeName(len);
	strcpy(eggName, newEggName);
}

void Egg::setSize(double newSize)
{
	eggSize = newSize;
}