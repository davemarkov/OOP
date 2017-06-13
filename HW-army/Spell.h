#ifndef SPELL_HEADER
#define SPELL_HEADER

enum SpellType
{
	PHYSICAL,
	ARCANE,
	FIRE,
	FROST,
	NATURE,
	SHADOW,
	HOLY,
	NOT_SET
};

class Spell
{
protected:
	SpellType spell;
	int mRequiredMana;
public:
	Spell();
	Spell(SpellType newSpell, int requiredMana);
	Spell(const Spell&);
	Spell& operator= (const Spell&);
	//~Spell();

	void copySpell(const Spell&);

	void createSpell(SpellType newSpell, int requiredMana);
	SpellType getSpell() const { return spell; }
	int getRequiredMana() const { return mRequiredMana; }
};

#endif//SPELL_HEADER