#include <iostream>
#include "fileStorage.h"

void FileStorage::createSpace()
{
	data = new (std::nothrow) char*[capacity];
	if (!data) throw;
}

int FileStorage::lineLen(int index, const char* text)
{
	int cnt = 0;
	for (int i = index; text[i] != '\0'; i++)
	{
		while (text[i] != '\0')
		{
			inLine = 1;
			cnt++;
			if (text[i] == '>')
			{
				inLine = 0;
				return cnt += 1;
			}
			i++;
		}
	}
	return cnt += 1;
}

void FileStorage::addLine(char* text)
{
	if (!ifLine(text))
		return;
	int allLen = strlen(text) + 1;
	for (int i = 0; text[i] != '\0'; i++)
	{
		if (inLine == 1)
		{ 
			int tempLineLen = lineLen(i, text);
			int len = strlen(data[size]) + tempLineLen;
			resizeLine(tempLineLen + 1);
			for (int pos = len - tempLineLen; pos < len; pos++, i++)
				data[size][pos] = text[i];
			if (inLine == 0)
			{
				data[size][len] = '\0';
				size++;
				resize(1);
			}
			i -= 2;
		}

		if (text[i] == '<')
		{
			int tempLineLen = lineLen(i, text);
			data[size] = new (std::nothrow) char[tempLineLen + 1];
			for (int pos = 0; pos < tempLineLen; pos++, i++)
				data[size][pos] = text[i];

			if (inLine == 0)
			{
				data[size][tempLineLen] = '\0';
				size++;
				resize(1);
			}
			i -= 2;
		}
	}
}

void FileStorage::removeLine(int index)
{
	char* temp;
	for (int i = index; i < size - 1; i++)
	{
		temp = data[i];
		data[i] = data[i + 1];
		data[i + 1] = temp;
	}
	delete[] data[size - 1];
	data[size - 1] = nullptr;
	size--;
	resize(-1);
}

void FileStorage::resizeLine(int value)
{
	int len = strlen(data[size]);
	char* newSet = new (std::nothrow) char[len + value + 1];
	for (int i = 0; i < len; i++)
		newSet[i] = data[size][i];
	delete[] data[size];
	data[size] = newSet;
}

void FileStorage::resize(int value)
{
	char** newSet = new char*[capacity + value];
	for (int i = 0; i < size; i++)
		newSet[i] = data[i];
	delete[] data;
	data = newSet;
	capacity += value;
}

void FileStorage::printLines()
{
	for (int i = 0; i < size; i++)
		std::cout << data[i] << "\n";
}

bool FileStorage::ifLine(const char* text)
{
	if (text[0] == '\0')
		return false;
	return true;
}
