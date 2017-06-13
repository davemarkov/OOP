#ifndef MAGE_HEADER
#define MAGE_HEADER

#include "Soldier.h"
#include "Sergeant.h"
#include "SpellBook.h"

class Mage : public Soldier
{
protected:
	char* mSergeantReport;
	Sergeant* mSergeant;
	SpellBook mSpellBook;
	int mMana;
	
	int mSergeantSize;
	int mSergeantCapacity;
public:
	Mage();
	Mage(char* name, int age, int skills, int salary, int mana);
	Mage(const Mage&);
	Mage& operator=(const Mage&);
	~Mage();

	void copyMage(const Mage&);

	Mage& operator+= (const Sergeant&);
	friend std::ostream& operator<< (std::ostream& out, Mage&);

	void useSpell(SpellType newSpell);
	bool enoughMana(int index) const;
	void createSpell(SpellType newSpell, int requiredMana);

	int getMaxSpells();

	void createBattalion();
	void addSergeant(char* name, int age, int skills, int salary);
	void resize(int value);

	void sergeantReport();
	void setSergeantReport(const char* name);
	char* getReport() const { return mSergeantReport; }

};

std::ostream& operator<< (std::ostream& out, Mage& o);

#endif//MAGE_HEADER