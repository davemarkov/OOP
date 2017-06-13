#ifndef SOLDIER_HEADER
#define SOLDIER_HEADER

class Soldier
{
protected:
	char* mSoldierName;
	int mAge;
	int mSkills;
	int mSalary; //златни монети

	static int allSoldierCnt;
	static int mageCnt;
	static int skillsCnt;
	static int salaryCnt;
	static int manaCnt;
	
public:
	Soldier();
	Soldier(char* name, int age, int skills, int salary);
	Soldier(const Soldier&);
	Soldier& operator= (const Soldier&);
	~Soldier();

	void copySoldier(const Soldier&);

	void setSoldierName(char* name);
	void setAge(int age);
	void setSkills(int skills);
	void setSalary(int salary);

	void createSoldier(char* name, int age, int skills, int salary);

	char* getSoldierName() const { return mSoldierName; }
	int getAge() const { return mAge; }
	int getSkills() const { return mSkills; }
	int getSalary() const { return mSalary; }

	int averigeSkill();
	int totalSkill() const;

	int averageMana();
	int totalMana() const;

	int totalSalary() const;

	bool higherSkills(int compare) const;
};

#endif//SOLDIER_HEADER