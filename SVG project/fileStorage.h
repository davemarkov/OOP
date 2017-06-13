#ifndef FILE_STORAGE_HEADER
#define FILE_STORAGE_HEADER

class FileStorage
{
	char** data;
	int capacity;
	int size;
	bool inLine;
public:
	FileStorage() : data(nullptr), inLine(0), size(0), capacity(1) 
	{
		createSpace();
	}

	~FileStorage()
	{
		clear();
	}

	void clear()
	{
		for (int i = 0; i < size; i++)
		{
			delete[] data[i];
			data[i] = nullptr;
		}
		delete[] data;
		data = nullptr;
		capacity = 1;
		size = 0;
		inLine = 0;
	}
	void createSpace();
	void removeLine(int index);
	void addLine(char* text);
	void printLines();
	char* getLine(int index) { return data[index]; }
	int getSize() { return size; }
private:
	int lineLen(int index, const char* text);
	bool ifLine(const char* text);
	void resizeLine(int value);
	void resize(int value);
	
};

#endif//FILE_STORAGE_HEADER