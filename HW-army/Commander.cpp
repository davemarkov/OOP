#include <iostream>
#include "Commander.h"

Commander::Commander() : mMageReport(nullptr), mMage(nullptr),
mMageSize(0), mMageCapacity(1)
{
	createArmy();
}

Commander::Commander(char* name, int age, int skills, int salary)
: Soldier(name, age, skills, salary),
mMageReport(nullptr), mMage(nullptr), 
mMageSize(0), mMageCapacity(1) 
{
	createArmy();
	mageReport();
}

void Commander::createArmy()
{
	mMage = new (std::nothrow) Mage[mMageCapacity];
	if (!mMage) throw;
}

Commander::Commander(const Commander& o)
{
	copyCommander(o);
}

Commander& Commander::operator= (const Commander& o)
{
	if (this != &o)
	{
		delete[] mMageReport;
		delete[] mMage;
		copyCommander(o);
	}
	return *this;
}

void Commander::copyCommander(const Commander& o)
{
	Soldier::operator= (o);

	setMageReport(o.mMageReport);

	mMageSize = o.mMageSize;
	mMageCapacity = o.mMageCapacity;

	mMage = new (std::nothrow) Mage[mMageCapacity];
	if (!mMage) throw;

	for (int i = 0; i < mMageSize; i++)
		mMage[i] = o.mMage[i];

}

void Commander::setMageReport(const char* name)
{
	int len = strlen(name) + 1;
	mMageReport = new (std::nothrow) char[len];
	if (!mMageReport) throw;
	strcpy(mMageReport, name);
}

Commander::~Commander()
{
	delete[] mMageReport;
	delete[] mMage;
}

Commander& Commander::operator+= (const Mage& o)
{
	if (higherSkills(o.getSkills()))
	{
		mMage[mMageSize] = o;
		mMageSize++;
		resize(1);
	}
	else
	std::cout << "Commander's skills must be higher than mage's!"
		<< std::endl;
	return *this;
}

std::ostream& operator<< (std::ostream& out, Commander& o)
{
	for (int i = 0; i < o.mMageSize; i++)
	{
		out << o.mMage[i].getSoldierName() 
			<< "  (Mage)"<< std::endl;
	}
	return out;
}

void Commander::addMage(char* name, int age, int skills, int salary)
{
	mMage[mMageSize].createSoldier(name, age, skills, salary);
	mMageSize++;
	if (mMageSize >= mMageCapacity)
		resize(1);
}

void Commander::resize(int value)
{
	mMageCapacity += value;
	Mage* newSet = new (std::nothrow) Mage[mMageCapacity];
	if (!newSet) throw;
	for (int i = 0; i < mMageSize; i++)
		newSet[i] = mMage[i];
	delete[] mMage;
	mMage = newSet;
}

void Commander::mageReport()
{
	char str1[] = "'s Army";
	int len = strlen(mSoldierName) + strlen(str1) + 1;
	mMageReport = new (std::nothrow) char[len];
	if (!mMageReport) throw;
	strcpy(mMageReport, mSoldierName);
	strcat(mMageReport, str1);
	std::cout << mMageReport << "  (Commander)" << std::endl;
}

