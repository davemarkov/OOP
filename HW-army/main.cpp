#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Commander.h"

int main()
{
	std::cout << "------------------------------" << std::endl;
	Sergeant sergeant1("Ivo", 23, 70, 50);
	{
		Soldier soldier1("Travis", 28, 34, 50);
		Soldier soldier2("Dave", 20, 40, 50);
		Soldier soldier3("Chrlie", 40, 32, 50);

		sergeant1 += soldier1;
		sergeant1 += soldier2;
		sergeant1 += soldier3;
	}
	sergeant1.getReport();
	std::cout << sergeant1;

	std::cout << "------------------------------" << std::endl;

	Sergeant sergeant2("Boiko", 48, 70, 50);
	{
		Soldier soldier4("Edi", 35, 35, 50);
		Soldier soldier5("Stoicho", 33, 56, 50);
		Soldier soldier6("Riko", 26, 36, 50);

		sergeant2 += soldier4;
		sergeant2 += soldier5;
		sergeant2 += soldier6;
	}
	sergeant2.getReport();
	std::cout << sergeant2;

	std::cout << "------------------------------" << std::endl;

	Sergeant sergeant3("Slavi", 50, 70, 50);
	{
		Soldier soldier7("Santa", 50, 50, 50);
		Soldier soldier8("Gecata", 32, 43, 50);
		Soldier soldier9("Marto", 29, 45, 50);

		sergeant3 += soldier7;
		sergeant3 += soldier8;
		sergeant3 += soldier9;
	}
	sergeant3.getReport();
	std::cout << sergeant3;

	std::cout << "------------------------------" << std::endl;

	Mage mage1("Ezio", 38, 80, 50, 100);
	mage1 += sergeant1;
	mage1 += sergeant2;
	mage1.getReport();
	std::cout << mage1;

	mage1.createSpell(PHYSICAL, 40);
	mage1.createSpell(FIRE, 30);
	mage1.createSpell(HOLY, 50);
	mage1.createSpell(FROST, 60);

	std::cout << mage1.getMaxSpells() << std::endl;

	mage1.useSpell(PHYSICAL);
	mage1.useSpell(FROST);

	std::cout << "------------------------------" << std::endl;

	Mage mage2("CJ", 33, 80, 50, 130);
	mage2 += sergeant3;
	mage2.getReport();
	std::cout << mage2;

	mage2.createSpell(NATURE, 50);
	mage2.createSpell(SHADOW, 20);
	mage2.createSpell(ARCANE, 70);
	mage2.createSpell(FROST, 40);

	std::cout << mage2.getMaxSpells() << std::endl;

	mage2.useSpell(ARCANE);
	mage2.useSpell(SHADOW);

	std::cout << "------------------------------" << std::endl;

	Commander commander("Sweet", 35, 90, 50);
	commander += mage1;
	commander += mage2;
	commander.getReport();
	std::cout << commander;

	std::cout << "------------------------------" << std::endl;

	std::cout << "Total skills: ";
	std::cout << commander.totalSkill() << std::endl;

	std::cout << "Average skills: ";
	std::cout << commander.averigeSkill() << std::endl;

	std::cout << "Total salary: ";
	std::cout << commander.totalSalary() << std::endl;

	std::cout << "Total mana: ";
	std::cout << commander.totalMana() << std::endl;

	std::cout << "Average mana: ";
	std::cout << commander.averageMana() << std::endl;

	return 0;
}