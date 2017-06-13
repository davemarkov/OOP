#include <iostream>
#include "Soldier.h"

int Soldier::allSoldierCnt = 0;
int Soldier::mageCnt = 0;
int Soldier::skillsCnt = 0;
int Soldier::salaryCnt = 0;
int Soldier::manaCnt = 0;


Soldier::Soldier()
: mSoldierName(nullptr), mAge(0), mSkills(0), mSalary(0) {}

Soldier::Soldier(char* name, int age, int skills, int salary)
:  mSoldierName(nullptr), mAge(age), mSkills(skills), mSalary(salary)
{
	setSoldierName(name);
	allSoldierCnt++;
	skillsCnt += mSkills;
	salaryCnt += mSalary;
}

Soldier::Soldier(const Soldier& o)
{
	copySoldier(o);
}
Soldier& Soldier::operator= (const Soldier& o)
{
	if (this != &o)
	{
		delete[] mSoldierName;
		copySoldier(o);
	}
	return *this;
}

void Soldier::copySoldier(const Soldier& o)
{
	setSoldierName(o.mSoldierName);

	mAge = o.mAge;
	mSkills = o.mSkills;
	mSalary = o.mSalary;
}

Soldier::~Soldier()  
{ 
	delete[] mSoldierName; 
}

void Soldier::setSoldierName(char* name)
{
	int len = strlen(name) + 1;
	mSoldierName = new (std::nothrow) char[len];
	if (!mSoldierName) throw;
	strcpy(mSoldierName, name);
}

void Soldier::setAge(int age)
{
	mAge = age;
}

void Soldier::setSkills(int skills)
{
	mSkills = skills;
	skillsCnt += mSkills;
}

void Soldier::setSalary(int salary)
{
	mSalary = salary;
	salaryCnt = mSalary;
}

void Soldier::createSoldier(char* name, int age, int skills, int salary)
{
	setSoldierName(name);
	setAge(age);
	setSkills(skills);
	setSalary(salary);
}

int Soldier::averigeSkill()
{
	return skillsCnt / allSoldierCnt;
}
int Soldier::totalSkill() const
{
	return skillsCnt;
}

int Soldier::averageMana()
{
	return totalMana() / mageCnt;
}

int Soldier::totalMana() const
{
	return manaCnt;
}

int Soldier::totalSalary() const
{
	return salaryCnt;
}

bool Soldier::higherSkills(int compare) const
{
	if (mSkills > compare)
		return true;
	return false;
}