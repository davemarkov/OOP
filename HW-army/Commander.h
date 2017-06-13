#ifndef COMMANDER_HEADER
#define COMMANDER_HEADER

#include "Soldier.h"
#include "Mage.h"

class Commander : public Soldier
{
protected:
	char* mMageReport;
	Mage* mMage;
	int mMageSize;
	int mMageCapacity;
public:
	Commander();
	Commander(char* name, int age, int skills, int salary);
	Commander(const Commander&);
	Commander& operator= (const Commander&);
	~Commander();

	void copyCommander(const Commander&);

	Commander& operator+= (const Mage&);
	friend std::ostream& operator<< (std::ostream& out, Commander& o);

	void addMage(char* name, int age, int skills, int salary);
	void resize(int value);

	void createArmy();
	
	void mageReport();
	void setMageReport(const char* name);
	char* getReport() const { return mMageReport; }
};

std::ostream& operator<< (std::ostream& out, Commander& o);

#endif//COMMANDER_HEADER