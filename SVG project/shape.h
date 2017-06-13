#ifndef FIGURE_HEADER
#define FIGURE_HEADER

class Shape 
{
protected:
	char* line;
public:
	Shape() : line(nullptr) {}
	Shape(const Shape&);
	Shape& operator= (const Shape&);
	virtual ~Shape() { delete[] line; }

	virtual Shape* clone() = 0;
	
	void copy(const Shape&);
	void createFig();
	void createFileLine();
	
	virtual bool withinCircle(int x, int y, int r) = 0;
	virtual bool withinRectangle(int x, int y, int width, int height) = 0;
	virtual void translate(int x, int y) = 0;
	virtual void print() = 0;
	virtual void addData(const char* text) = 0;
	virtual char* getLine() = 0;
	
	int charToInt(const char* text);
	int nextElement(const char* text, int index);
	char* intToChar(int value);
	char* quotes(const char* text);
	bool colourDetect(const char* text);
	int digitCnt(int value);
	bool ifNum(const char);
	char* extract(const char* text, int index, char* &temp);
	bool checkElement(const char* text, const char* elem, int index);
};

#endif//FIGURE_HEADER