#include <iostream>
#include <fstream>
#include "basketData.h"
#include "eggData.h"

Basket::Basket() : basketOwner(nullptr), saveFileName(nullptr),
fileName(nullptr), capacityCnt(8), size(0), egg(nullptr)
{
	try
	{
		egg = new Egg[capacityCnt];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
}

Basket::Basket(const Basket& o) : basketOwner(nullptr), saveFileName(nullptr),
fileName(nullptr), capacityCnt(8), size(0), egg(nullptr)
{
	objectBasketCopy(o);
}

Basket& Basket::operator= (const Basket& p)
{
	if (this != &p)
	{
		clear();
		objectBasketCopy(p);
	}
	return *this;
}

void Basket::objectBasketCopy(const Basket& s)
{
	setbasketOwner(s.basketOwner);

	capacityCnt = s.capacityCnt;
	size = s.size;
	try
	{
		egg = new Egg[capacityCnt];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
	for (int i = 0; i < size; i++)
	{
		egg[i] = s.egg[i];
	}
}

Basket::~Basket()
{
	clear();
}

void Basket::clear()
{
	clearBasketOwner();
	delete[] egg;
}

void Basket::clearBasketOwner()
{
	delete[] basketOwner;
}


Egg& Basket::operator[] (const int index)
{
	if (index >= 0 && index < size)
		return egg[index];
	std::cout << "Invalid index! \n";
}

Egg& Basket::operator[] (const char* name)
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(egg[i].getName(), name) == 0)
			return egg[i];
	}
	std::cout << "No such name exists! \n";
}

Basket& Basket::operator*=(const int multi)
{
	for (int i = 0; i < size; i++)
		egg[i] *= multi;
	return *this;
}

Basket& Basket::operator/=(const int div)
{
	for (int i = 0; i < size; i++)
		egg[i] /= div;
	return *this;
}

void Basket::addition()
{
	for (int i = 0; i < size; i++)
		egg[i]++;
}

Basket& Basket::operator++ (int) //B++
{
	addition();
	return *this;
}

Basket& Basket::operator++ () //++B
{
	addition();
	return *this;
}

void Basket::removal()
{
	for (int i = 0; i < size; i++)
	{
		int newSize = egg[i].getSize();
		if (newSize > 0)
			egg[i]--;
	}
}

Basket& Basket::operator-- (int)
{
	removal();
	return *this;
}

Basket& Basket::operator-- ()
{
	removal();
	return *this;
}

Basket& Basket::operator+= (const char* text)
{
	for (int i = 0; i < size; i++)
	{
		egg[i] += text;
	}
	return *this;
}

Basket& Basket::operator+= (const Basket& o)
{
	char str1[] = "&";
	int newLen = strlen(str1) + strlen(getBasketOwner()) + strlen(o.getBasketOwner()) + 1;
	char* name;
	try
	{
		name = new char[newLen];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
	strcpy(name, getBasketOwner());
	strcat(name, str1);
	strcat(name, o.getBasketOwner());

	clearBasketOwner();
	setbasketOwner(name);
	delete[] name;
	int oSize = o.getSize();
	int oldSize = size;
	for (int i = 0; i < oSize; i++)
	{
		int cnt = 0;
		for (int j = 0; j < oldSize; j++)
		{
			if (size >= capacityCnt)
			{
				capacityCnt *= 2;
				resize();
			}
			if (egg[j] == o.egg[i])
				cnt++;
		}
		if (cnt == 0)
		{
			egg[size] = o.egg[i];
			size++;
		}
	}
	return *this;
}

Basket operator+ (const Basket& p, const Basket& o)
{
	Basket combine(p);
	combine += o;
	return combine;
}

Basket operator% (const Basket& o, const Basket& p)
{
	Basket section;
	section.setbasketOwner(o.getBasketOwner());
	int bigSize = o.getSize();
	int smallSize = p.getSize();
	if (o.getSize() < p.getSize())
	{
		bigSize = p.getSize();
		smallSize = o.getSize();
	}
	for (int i = 0; i < bigSize; i++)
	{
		for (int j = 0; j < smallSize; j++)
		{
			if (strcmp(o.egg[i].getName(), p.egg[j].getName()) == 0)
				section.checkName(o.egg[i].getName(), o.egg[i].getSize());
		}
	}

	return section;
}

std::ostream& operator<< (std::ostream& out, Basket& o)
{
	int size = o.getSize();

	out << "Owner: " << o.getBasketOwner() << "\n";
	for (int i = 0; i < size; i++)
	{
		out << "Egg name: " << o.egg[i].getName() 
			<< "    Size: " << o.egg[i].getSize() << "\n";
	}
	return out;
}

void Basket::nameInput(int state)
{
	const int buffer = 30;
	char newName[30];
	std::cin.getline(newName, buffer);
	if (state == EGG)
	{
		std::cout << "Egg size: ";
		double newEggSize = 0;
		std::cin >> newEggSize;
		eggInput(newName, newEggSize);
	}
	if (state == OWNER)
		setbasketOwner(newName);
	
}

std::istream& operator>> (std::istream&  in, Basket& o)
{
	std::cout << "Basket owner: ";
	o.nameInput(OWNER);
	
	for (int i = 0; i < 4; i++)
	{
		std::cout << "Egg name: ";
		o.nameInput(EGG);
		std::cin.ignore();
		std::cin.clear();
	}
	return in;
}

bool operator== (const Basket& o, const Basket& p)
{
	if (o.getSize() != p.getSize()) return false;
	int size = o.getSize();
	for (int i = 0; i < size; i++)
	{
		if (o.egg[i] != p.egg[i])
			return false;
	}
	return true;
}

bool operator!= (const Basket& o, const Basket& p)
{
	if (o == p)
		return false;
	return true;
}

bool operator<  (const Basket& o, const Basket& p)
{
	if (strcmp(o.getBasketOwner(), p.getBasketOwner()) == 1)
		return false;
	int smallSize = o.getSize();
	if (o.getSize() > p.getSize()) 
		smallSize = p.getSize();

	for (int i = 0; i < smallSize; i++)
	{
		if (o.egg[i] > p.egg[i])
			return false;
	}
	return true;
}

bool operator>  (const Basket& o, const Basket& p)
{
	if (o < p)
		return false;
	return true;
}


void Basket::clearFileName()
{
	delete[] fileName;
}

void Basket::setbasketOwner(char* newName)
{
	int len = strlen(newName) + 1;
	try
	{
		basketOwner = new (std::nothrow) char[len];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
	strcpy(basketOwner, newName);
}

void Basket::eggInput(char* newName, double newEggSize)
{
	checkName(newName, newEggSize);
}

//checks if the egg already exists
void Basket::checkName(char* name, double newEggSize)
{
	for (int i = 0; i < size; i++)
	{
		if (size == 0)    //if basket is empty
			continue;
		if (strcmp(egg[i].getName(), name) == 0)
		{
			removeEgg(name);       //if the egg exists , it is removed
			return;
		}
	}
	addEgg(name, newEggSize);  //if does not exist , it is added
}

void Basket::addEgg(char* eggName, double newEggSize)
{
	if (size == capacityCnt) //if array is too small
	{                        //it is enlarged
		capacityCnt = capacityCnt * 2;
		resize();
	}

	// and the egg is being added
	int len = strlen(eggName) + 1;
	egg[size].setName(eggName);

	egg[size].setSize(newEggSize);

	size++;
	std::cout << "New egg added!\n";

}

void Basket::removeEgg(char* eggName)
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(egg[i].getName(), eggName) == 0)   //we ara looking for the egg 
		{                                             //which we are about to remove
			for (int k = i + 1; k < size; k++)
				egg[i] = egg[k];                    //once found we copy the next object 
			break;                                  //to the current possition 
		}
	}

	size--;  // and finaly the size is reduced accordingly

	if (size < capacityCnt / 2)  //if array is too small
	{                            // it's capacity is reduced
		capacityCnt = capacityCnt / 2;
		resize();
	}
	std::cout << "Egg removed!\n";
}

//resize of array 
void Basket::resize()
{
	Egg* newSet;
	try
	{
		newSet = new (std::nothrow) Egg[capacityCnt];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
	for (int i = 0; i < size; i++)
		newSet[i] = egg[i];

	delete[] egg;
	egg = newSet;
	newSet = nullptr;
}

void Basket::setSaveFileName()
{
	char str1[] = "save_";
	char str2[] = ".dat";
	int newLen = strlen(str1) + strlen(str2) + strlen(basketOwner) + 1;
	delete[] saveFileName;
	try
	{
		saveFileName = new (std::nothrow) char[newLen];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
	strcpy(saveFileName, str1);
	strcat(saveFileName, basketOwner);
	strcat(saveFileName, str2);
}

void Basket::clearSavefileName()
{
	delete[] saveFileName;
}

void Basket::serialization()
{
	setSaveFileName();
	std::ofstream save(getSaveFileName(), std::ios::binary);
	if (save.is_open())
	{
		//save char length and then name
		int playerLen = strlen(basketOwner) + 1;
		save.write((char*)&playerLen, sizeof(int));
		save.write(basketOwner, playerLen);

		//save capcity and size of array
		save.write((char*)&capacityCnt, sizeof(int));
		save.write((char*)&size, sizeof(int));
		for (int i = 0; i < size; i++)
		{
			//save name length, name and eggSize of each egg
			int eggLen = strlen(egg[i].getName()) + 1;

			double eggSizeW = egg[i].getSize();
			save.write((char*)&(eggSizeW), sizeof(double));

			save.write((char*)&eggLen, sizeof(int));
			save.write(egg[i].getName(), eggLen);
		}
		save.close();
	}
	std::cout << "Basket saved!\n";
	clearSavefileName();
}

void Basket::deserialization()
{
	std::cout << "Basket owner: ";
	nameInput(OWNER);
	setSaveFileName();
	std::ifstream get(getSaveFileName(), std::ios::binary);
	if (get.is_open())
	{
		//read name length
		int playerLen = 0;
		get.read((char*)&playerLen, sizeof(int));
		//then the name itself
		basketOwner = new (std::nothrow) char[playerLen];
		get.read(basketOwner, playerLen);

		//read the capacity and size of array 
		//which is going to be created
		get.read((char*)&capacityCnt, sizeof(int));
		get.read((char*)&size, sizeof(int));

		delete[] egg;
		try
		{
			egg = new (std::nothrow) Egg[capacityCnt];
		}
		catch (std::bad_alloc&)
		{
			std::cout << "mem alloc failed\n";
		}
		for (int i = 0; i < size; i++)
		{
			//read length of egg name, egg name and egg size
			double eggSizeR = 0;
			get.read((char*)&eggSizeR, sizeof(double));
			egg[i].setSize(eggSizeR);

			int eggLen = 0;
			get.read((char*)&eggLen, sizeof(int));

			egg[i].initializeName(eggLen);
			get.read(egg[i].getName(), eggLen);
		}

		get.close();
	}
	std::cout << "Basket loaded!\n";
}