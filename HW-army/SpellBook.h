#ifndef SPELL_BOOK_HEADER
#define SPELL_BOOK_HEADER

#include "Spell.h"

class SpellBook
{
protected:
	Spell* mSpell;
	int mSpellCapacity;
	int mSpellSize;
public:
	SpellBook();
	SpellBook(const SpellBook&);
	SpellBook& operator= (const SpellBook&);
	~SpellBook();

	void copySpellBook(const SpellBook&);

	void createBook();
	
	void addSpell(SpellType newSpell, int requiredMana);
	void removeSpell(int index);
	
	void sort();
	int possibleSpells(int mana);

	SpellType getSpell(int index) const;
	int getRequiredMana(int index) const;
	int getSize() const { return mSpellSize; }
	
	void resize();
	
};

#endif//SPELL_BOOK_HEADER