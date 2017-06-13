#ifndef __EGGDATA_H__
#define __EGGDATA_H__

class Egg
{
	char* eggName;
	double eggSize;
public:
	Egg();
	Egg(const Egg&);
	Egg& operator= (const Egg&);
	void objectEggCopy(const Egg&);
	~Egg();
	void clear();

	friend std::ostream& operator<< (std::ostream& out, Egg& o);
	friend std::istream& operator>> (std::istream& out, Egg&);

	Egg& operator+= (const char* text);
	Egg& operator*= (const int multi);
	Egg& operator/= (const int div);
	void addition();
	//increase/decrease each egg size with one
	Egg& operator++ (int);
	Egg& operator++ ();
	void removal();
	Egg& operator-- (int);
	Egg& operator-- ();

	void initializeName(int len);
	void setName(char* newName);
	void setSize(double size);
	char* getName() const { return eggName; }
	double getSize() const { return eggSize; }
};

std::ostream& operator<< (std::ostream& out, Egg&);
std::istream& operator>> (std::istream& out, Egg&);

bool operator== (const Egg&, const Egg&);
bool operator!= (const Egg&, const Egg&);
bool operator>= (const Egg&, const Egg&);
bool operator<= (const Egg&, const Egg&);
bool operator<  (const Egg&, const Egg&);
bool operator>  (const Egg&, const Egg&);
#endif //__EGGDATA_H__