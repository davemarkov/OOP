#include <iostream>
#include "commandsInput.h"

bool Commands::input()
{
	std::cout << "> ";
	char buffer[64] = { 0, };
	std::cin.getline(buffer, 63);
	if (ifSame("exit", buffer)) return false;
	checkCommand(buffer);
	return true;
}

bool Commands::ifSame(char* command, const char* text)
{
	for (int i = 0; command[i] != '\0'; i++)
		if (text[i] != command[i])
			return false;
	return true;
}

void Commands::checkCommand(char* text)
{
	InputStorrage storrage(text);
	if (ifSame("open", storrage.getData(0)))
		open(storrage);
	else if (ifSame("close", storrage.getData(0)))
		close();
	else if (ifSame("print", storrage.getData(0)))
		print();
	else if (ifSame("saveas", storrage.getData(0)))
		saveAs(storrage);
	else if (ifSame("save", storrage.getData(0)))
		save();
	else if (ifSame("erase", storrage.getData(0)))
		erase(storrage);
	else if (ifSame("create", storrage.getData(0)))
		create(storrage);
	else if (ifSame("translate", storrage.getData(0)))
		translate(storrage);
	else if (ifSame("within", storrage.getData(0)))	
		within(storrage);
	else
		std::cout << "Unknown command! \n";
}