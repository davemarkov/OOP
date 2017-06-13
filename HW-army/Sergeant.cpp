#include <iostream>
#include "Sergeant.h"

Sergeant::Sergeant() : mSoldierReport(nullptr), mSoldier(nullptr),
mSoldierSize(0), mSoldierCapacity(1)
{
	createSquad();
}

Sergeant::Sergeant(char* name, int age, int skills, int salary) 
: Soldier(name, age, skills, salary), mSoldierReport(nullptr),
mSoldier(nullptr), mSoldierCapacity(1), mSoldierSize(0) 
{
	createSquad();
	soldierReport();
}

void Sergeant::createSquad()
{
	mSoldier = new (std::nothrow) Soldier[mSoldierCapacity];
	if (!mSoldier) throw;
}

Sergeant::Sergeant(const Sergeant& o)
{
	copySergent(o);
}
Sergeant& Sergeant::operator= (const Sergeant& o)
{
	if (this != &o)
	{
		delete[] mSoldierReport;
		delete[] mSoldier;
		copySergent(o);
	}
	return *this;
}

void Sergeant::copySergent(const Sergeant& o)
{
	Soldier::operator= (o);

	setSoldierReport(o.mSoldierReport);
	
	mSoldierSize = o.mSoldierSize;
	mSoldierCapacity = o.mSoldierCapacity;

	mSoldier = new (std::nothrow) Soldier[mSoldierCapacity];
	for (int i = 0; i < mSoldierSize; i++)
		mSoldier[i] = o.mSoldier[i];
}

void Sergeant::setSoldierReport(const char* name)
{
	int len = strlen(name) + 1;
	mSoldierReport = new (std::nothrow) char[len];
	if (!mSoldierReport) throw;
	strcpy(mSoldierReport, name);
}

Sergeant& Sergeant::operator+= (const Soldier& o)
{
	if (higherSkills(o.getSkills()))
	{
		mSoldier[mSoldierSize] = o;
		mSoldierSize++;
		resize(1);
	}
	else
	std::cout << "Sergeant's skills must be higher than Soldier's!"
		<< std::endl;
	return *this;
}

std::ostream& operator<< (std::ostream& out, Sergeant& o)
{
	for (int i = 0; i < o.mSoldierSize; i++)
	{
		out << o.mSoldier[i].getSoldierName() 
			<< "  (Soldier)" << std::endl;
	}
	return out;
}

void Sergeant::addSoldier(char* name, int age, int skills, int salary)
{
	mSoldier[mSoldierSize].createSoldier(name, age, skills, salary);
	mSoldierSize++;
	if (mSoldierSize >= mSoldierCapacity)
		resize(1);
}

void Sergeant::soldierReport()
{
	char str1[] = "'s Squad";
	int len = strlen(mSoldierName) + strlen(str1) + 1;
	mSoldierReport = new (std::nothrow) char[len];
	strcpy(mSoldierReport, mSoldierName);
	strcat(mSoldierReport, str1);
	std::cout << mSoldierReport << "  (Sergeant)" << std::endl;
}

void Sergeant::resize(int value)
{
	mSoldierCapacity += value;
	Soldier* newSet = new (std::nothrow) Soldier[mSoldierCapacity];
	if (!newSet) throw;
	for (int i = 0; i < mSoldierSize; i++)
		newSet[i] = mSoldier[i];
	delete[] mSoldier;
	mSoldier = newSet;
}

Sergeant::~Sergeant()
{
	delete[] mSoldierReport;
	delete[] mSoldier;
}
