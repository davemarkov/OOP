#include <iostream>
#include "inputStorage.h"

InputStorrage::InputStorrage(const char* text, int index)
: data(nullptr), capacity(1), size(0)
{
	createSpace();
	addData(text, index);
}

void InputStorrage::createSpace()
{
	data = new (std::nothrow) char*[capacity];
	if (!data) throw;
}

bool InputStorrage::isLetter(const char letter)
{
	return (letter >= 'a' && letter <= 'z') ||
		(letter >= 'A' && letter <= 'Z') ||
		(letter >= '0' && letter <= '9') ||
		letter == '.' || letter == ':' ||
		letter == '\\' || letter == '/';
}

void InputStorrage::addData(const char* text, int index)
{
	for (int i = index; text[i] != '\0'; i++)
	{
		if (text[i] != ' ')
		{
			int len = 0;
			for (int j = i; isLetter(text[j]); ++j)
				len++;
			data[size] = new (std::nothrow) char[len + 1];
			int pos = 0;
			for (; pos < len; pos++, i++)
				data[size][pos] = text[i];
			data[size][pos] = '\0';
			size++;
			resizeData();
		}
	}
}

void InputStorrage::resizeData()
{
	char** newSet = new (std::nothrow) char*[capacity + 1];
	for (int i = 0; i < capacity; i++)
		newSet[i] = data[i];  // копира само адресите!
	delete[] data;//трябва да изтрива само записите на адресите 
	data = newSet;
	capacity++;

}

char* InputStorrage::getData(int index)
{
	return data[index];
}

