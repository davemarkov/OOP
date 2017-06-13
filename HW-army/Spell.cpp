#include <iostream>
#include "Spell.h"

Spell::Spell() : spell(NOT_SET), mRequiredMana(0) {}

Spell::Spell(SpellType newSpell, int requiredMana)
: spell(newSpell), mRequiredMana(requiredMana) {}

Spell::Spell(const Spell& o)
{
	copySpell(o);
}

Spell& Spell::operator= (const Spell& o)
{
	if (this != &o)
		copySpell(o);
	return *this;
}

void Spell::copySpell(const Spell& o)
{
	spell = o.spell;
	mRequiredMana = o.mRequiredMana;
}

void Spell::createSpell(SpellType newSpell, int requiredMana)
{
	spell = newSpell;
	mRequiredMana = requiredMana;
}

