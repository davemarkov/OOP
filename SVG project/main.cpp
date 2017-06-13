#include <iostream>
#include "figures.h"

int main()
{
	Figures f;
	Commands* figure = &f;
	while (true)
		if (!figure->input())
			break;
	return 0;
}