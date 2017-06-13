#ifndef COMMANDS_INPUT_HEADER
#define COMMANDS_INPUT_HEADER

#include "inputStorage.h"

class Commands 
{
protected:
	virtual void save() = 0;
	virtual void saveAs(InputStorrage&) = 0;
	virtual void print() = 0;
	virtual void erase(InputStorrage&) = 0;
	virtual void open(InputStorrage&) = 0;
	virtual void create(InputStorrage&) = 0;
	virtual void close() = 0;
	virtual void translate(InputStorrage&) = 0;
	virtual void within(InputStorrage&) = 0;
public:
	bool input();
	bool ifSame(char* command, const char* text);
private:
	void checkCommand(char* text);
};

#endif//COMMANDS_INPUT_HEADER