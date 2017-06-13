#ifndef INPUT_STORRAGE_HEADER
#define INPUT_STORRAGE_HEADER

class InputStorrage
{
	char** data;
	int size;
	int capacity;
public:

	InputStorrage(const char* text) : data(nullptr), capacity(1), size(0)
	{
		createSpace();
		addData(text, 0);
	}
	InputStorrage(const char* text, int index);
	virtual ~InputStorrage()
	{
		for (int i = 0; i < size; i++)
			delete[] data[i];
		delete[] data;
	}

	int getSize() { return size; }
	void createSpace();
	void addData(const char* text, int index);
	char* getData(int index);
	
private:
	void resizeData();
	bool isLetter(const char letter);
};

#endif//INPUT_STORRAGE_HEADER