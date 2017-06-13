#include <iostream>
#include "SpellBook.h"

SpellBook::SpellBook() : mSpell(nullptr),
mSpellCapacity(1), mSpellSize(0) 
{
	createBook();
}

void SpellBook::createBook()
{
	mSpell = new (std::nothrow) Spell[mSpellCapacity];
	if (!mSpell) throw;
}

SpellBook::SpellBook(const SpellBook& o) : mSpell(nullptr)
{
	copySpellBook(o);
}

SpellBook& SpellBook::operator= (const SpellBook& o)
{
	if (this != &o)
	{
		delete[] mSpell;
		copySpellBook(o);
	}
	return *this;
}

void SpellBook::copySpellBook(const SpellBook& o)
{
	mSpellSize = o.mSpellSize;
	mSpellCapacity = o.mSpellCapacity;
	
	mSpell = new (std::nothrow) Spell[mSpellCapacity];
	if (!mSpell) throw;
	
	for (int i = 0; i < mSpellSize; i++)
		mSpell[i] = o.mSpell[i];
}

SpellBook::~SpellBook()
{
	delete[] mSpell;
}

void SpellBook::addSpell(SpellType newSpell, int requiredMana)
{
	mSpell[mSpellSize].createSpell(newSpell, requiredMana);
	
	mSpellSize++;
	mSpellCapacity++;
	resize();
}

void SpellBook::removeSpell(int index)
{
	for (int i = index + 1; i < mSpellSize; i++, index++)
		mSpell[index] = mSpell[i];
	
	mSpellSize--;
	mSpellCapacity--;
	resize();
}

void SpellBook::sort() //from small to big
{
	Spell tempSpell;
	for (int i = 0; i < mSpellSize - 1; i++)
	{
		if (mSpell[i].getRequiredMana() > mSpell[i + 1].getRequiredMana())
		{
			tempSpell = mSpell[i];
			mSpell[i] = mSpell[i + 1];
			mSpell[i + 1] = tempSpell;
		}
	}
}

int SpellBook::possibleSpells(int mana)
{
	sort();
	int manaMeter = 0;
	int cnt = 0;
	for (int i = 0; i < mSpellSize; i++)
	{
		if (manaMeter <= mana)
		{
			manaMeter += mSpell[i].getRequiredMana();
			cnt++;
			if (manaMeter > mana)
			{
				cnt--;
				break;
			}
		}
    }
	return cnt;
}

void SpellBook::resize()
{
	Spell* newSet = new (std::nothrow) Spell[mSpellCapacity];
	if (!newSet) throw;
	
	for (int i = 0; i < mSpellSize; i++)
		newSet[i] = mSpell[i];
	
	delete[] mSpell;
	mSpell = newSet;
}

SpellType SpellBook::getSpell(int index) const
{
	return mSpell[index].getSpell();
}

int SpellBook::getRequiredMana(int index) const
{
	return mSpell[index].getRequiredMana();
}