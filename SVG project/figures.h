#ifndef SHAPE_HEADER
#define SHAPE_HEADER

#include "rectangle.h"
#include "circle.h"
#include "line.h"
#include "fileStorage.h"
#include "commandsInput.h"

class Figures : public Commands
{
protected:
	Shape** shape;
	FileStorage lines;
	int size;
	int capacity;
	char* newFileName;
	bool openFile;
	char* circleTag;
	char* lineTag;
	char* rectangleTag;
public:
	Figures() : shape(nullptr), newFileName(nullptr),
		openFile(false), size(0), capacity(1),
		circleTag("<circle "), lineTag("<line "), rectangleTag("<rect ")
	{
		newFigSet();
	}
	
	virtual ~Figures() 
	{
		for (int i = 0; i < size; i++)
			delete[] shape[i];
		delete[] shape;
		delete[] newFileName;
	}

	void open(InputStorrage&) override;
	void close() override;
	void save() override;
	void saveAs(InputStorrage&) override;
	void saveInfile(const char* fileName);
	
	void create(InputStorrage&) override;
	void erase(InputStorrage &) override;
	void print() override;
	void translate(InputStorrage&) override;
	void within(InputStorrage&) override;
	void withinCircle(int x, int y, int r);
	void withinRectangle(int x, int y, int width, int height);
private:
	void newFigSet();
	void addFig(Shape*);
	void getData(const char* text, Shape*);
private:
	char* validPath(char* text);
	bool ifValid(int value, InputStorrage& o);
	bool ifFig(char* command,const char* text);
	bool figCheck(const char* text);
	void resize(int value);
private:
	void setFileName(const char* text);
	void createCircle(InputStorrage&);
	void createLine(InputStorrage&);
	void createRect(InputStorrage&);
};

#endif//SHAPE_HEADER