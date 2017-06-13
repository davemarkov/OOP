#include <iostream>
#include <fstream>
#include "basketData.h"

char* Basket::fileNameGen()
{
	char str1[] = "report_";
	char str2[] = ".txt";
	int newLen = strlen(str1) + strlen(str2) + strlen(basketOwner) + 1;
	try
	{
		fileName = new (std::nothrow) char[newLen];
	}
	catch (std::bad_alloc&)
	{
		std::cout << "mem alloc failed\n";
	}
	strcpy(fileName, str1);
	strcat(fileName, basketOwner);
	strcat(fileName, str2);

	return fileName;
}

void Basket::print()
{
	std::ofstream report(fileNameGen(), std::ios::out);
	if (report.is_open())
	{
		report << "Basket owner: " << basketOwner << "\n";
		for (int i = 0; i < size; i++)
			report << "Egg name: " << egg[i].getName() << " "
			<< " Size: " << egg[i].getSize() << "\n";
		report.close();
		std::cout << "Report file created for owner: " << basketOwner << "\n";
	}

	clearFileName();
}
