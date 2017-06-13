#ifndef __BASKETDATA_H__
#define __BASKETDATA_H__

#include "eggData.h"

enum State
{
	OWNER,
	EGG,
};

class Basket
{
	char* basketOwner;
	int capacityCnt;
	int size;
	char* fileName;
	char* saveFileName;
public:
	Basket();
	Basket(const Basket&);
	Basket& operator= (const Basket&);
	void objectBasketCopy(const Basket&);
	~Basket();
	void clear();
	void clearBasketOwner();

	Egg* egg;

	void setbasketOwner(char* newName);
	char* getBasketOwner() const { return basketOwner; }
	void eggInput(char* newName, double newEggSize);

	void nameInput(int state);
	void checkName(char* name, double newEggSize);
	void addEgg(char* eggName, double newEggSize);
	void removeEgg(char* eggName);
	void resize();
	
	void setSaveFileName();
	char* getSaveFileName() const { return saveFileName; }
	void clearSavefileName();
	
	void serialization();
	void deserialization();

	char* fileNameGen();
	void print();
	void clearFileName();

	Egg& operator[] (const int index);
	Egg& operator[] (const char* name);

	Basket& operator+= (const Basket&);
	Basket& operator+= (const char* text);
	Basket& operator*= (const int multi);
	Basket& operator/= (const int div);
	void addition();
	Basket& operator++ (int);
	Basket& operator++ ();
	void removal();
	Basket& operator-- (int);
	Basket& operator-- ();

	friend std::ostream& operator<< (std::ostream& out, Basket&);
	friend std::istream& operator>> (std::istream&  in, Basket&);

	void setSize(int newSize) { size = newSize; }
	int getSize() const { return size; }
	
	void setCapacity(int newCapacity) { capacityCnt = newCapacity; }
	int getCapacity() const { return capacityCnt; }
};

Basket operator+ (const Basket&, const Basket&);
Basket operator% (const Basket&, const Basket&);

std::ostream& operator<< (std::ostream& out, Basket&);
std::istream& operator>> (std::istream&  in, Basket&);
	
bool operator== (const Basket&, const Basket&);
bool operator!= (const Basket&, const Basket&);
bool operator>= (const Basket&, const Basket&);
bool operator<= (const Basket&, const Basket&);
bool operator<  (const Basket&, const Basket&);
bool operator>  (const Basket&, const Basket&);

#endif //__BASKETDATA_H__
