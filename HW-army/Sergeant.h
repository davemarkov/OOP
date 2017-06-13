#ifndef SERGEANT_HEADER
#define SERGEANT_HEADER

#include "Soldier.h"

class Sergeant : public Soldier
{
protected:
	char* mSoldierReport;
	Soldier* mSoldier;
	int mSoldierSize;
	int mSoldierCapacity;
public:
	Sergeant();
	Sergeant(char* name, int age, int skills, int salary);
	Sergeant(const Sergeant&);
	Sergeant& operator= (const Sergeant&);
	~Sergeant();

	Sergeant& operator+= (const Soldier&);
	friend std::ostream& operator<< (std::ostream& out, Sergeant& o);

	void copySergent(const Sergeant&);

	void createSquad();
	int getSize() const { return mSoldierSize; }
	int getCapacity() const { return mSoldierCapacity; }

	void addSoldier(char* name, int age, int skills, int salary);

	void soldierReport();
	void setSoldierReport(const char* name);
	char* getReport() const { return mSoldierReport; }

	void resize(int value);
	void newSoldierReport();
};

std::ostream& operator<< (std::ostream& out, Sergeant& o);

#endif//SERGEANT_HEADER