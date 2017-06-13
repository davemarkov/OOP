#include <iostream>
#include "Mage.h"

Mage::Mage() : mSergeantReport(nullptr), mSergeant(nullptr),
mMana(0), mSergeantSize(0), mSergeantCapacity(1) 
{
	createBattalion();
}

Mage::Mage(char* name, int age, int skills, int salary, int mana)
: Soldier(name, age, skills, salary), mSergeantReport(nullptr),
mSergeant(nullptr), mMana(mana), mSergeantSize(0), mSergeantCapacity(1)
{
	createBattalion();
	sergeantReport();
	manaCnt += mMana;   
	mageCnt++;
}

void Mage::createBattalion()
{
	mSergeant = new (std::nothrow) Sergeant[mSergeantCapacity];
	if (!mSergeant) throw;
}

Mage::Mage(const Mage& o)
{
	copyMage(o);
}

Mage& Mage::operator=(const Mage& o)
{
	if (this != &o)
	{
		delete[] mSergeantReport;
		delete[] mSergeant;
		copyMage(o);
	}
	return *this;
}

void Mage::copyMage(const Mage& o)
{
	Soldier::operator= (o);

	setSergeantReport(o.mSergeantReport);
	
	mMana = o.mMana;
	mSergeantSize = o.mSergeantSize;
	mSergeantCapacity = o.mSergeantCapacity;

	mSpellBook = o.mSpellBook;

	mSergeant = new (std::nothrow) Sergeant[mSergeantCapacity];
	if (!mSergeant) throw;

	for (int i = 0; i < mSergeantSize; i++)
		mSergeant[i] = o.mSergeant[i];
}

void Mage::setSergeantReport(const char* name)
{
	int len = strlen(name) + 1;
	mSergeantReport = new (std::nothrow) char[len];
	if (!mSergeantReport) throw;
	strcpy(mSergeantReport, name);
}

Mage& Mage::operator+= (const Sergeant& o)
{
	if (higherSkills(o.getSkills()))
	{
		mSergeant[mSergeantSize] = o;
		mSergeantSize++;
		resize(1);
	}
	else
	    std::cout << "Mage's skills must be higher than Sergeant's!"
		          << std::endl;
	return *this;
}

std::ostream& operator<< (std::ostream& out, Mage& o)
{
	for (int i = 0; i < o.mSergeantSize; i++)
	{
		out << o.mSergeant[i].getSoldierName() 
			<< "  (Sergeant)" << std::endl;
	}
	return out;
}

Mage::~Mage()
{
	delete[] mSergeantReport;
	delete[] mSergeant;
}

void Mage::useSpell(SpellType newSpell)
{
	int size = mSpellBook.getSize();
	for (int i = 0; i < size; i++)
	{ 
		if (mSpellBook.getSpell(i) == newSpell && enoughMana(i))
		{
			mSpellBook.removeSpell(i);
			mMana -= mSpellBook.getRequiredMana(i);
		}
	}
	std::cout << "Spell used!" << std::endl;

}

bool Mage::enoughMana(int index) const
{
	if (mMana < mSpellBook.getRequiredMana(index))
		return false;
	return true;
}

void Mage::createSpell(SpellType newSpell, int requiredMana)
{
	mSpellBook.addSpell(newSpell, requiredMana);
}

int Mage::getMaxSpells() 
{
	std::cout << "Num of spells that can be used: ";
	return mSpellBook.possibleSpells(mMana);
}

void Mage::addSergeant(char* name, int age, int skills, int salary)
{
	mSergeant[mSergeantSize].createSoldier(name, age, skills, salary);
	mSergeantSize++;
	if (mSergeantSize >= mSergeantCapacity)
		resize(1);
}

void Mage::resize(int value)
{
	mSergeantCapacity += value;
	Sergeant* newSet = new (std::nothrow) Sergeant[mSergeantCapacity];
	for (int i = 0; i < mSergeantSize; i++)
		newSet[i] = mSergeant[i];
	delete[] mSergeant;
	mSergeant = newSet;
}

void Mage::sergeantReport()
{
	char str1[] = "'s Battalion";
	int len = strlen(mSoldierName) + strlen(str1) + 1;
	mSergeantReport = new (std::nothrow) char[len];
	strcpy(mSergeantReport, mSoldierName);
	strcat(mSergeantReport, str1);
	std::cout << mSergeantReport << "  (Mage)" << std::endl;
}


