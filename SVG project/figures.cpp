#include <iostream>
#include "figures.h"

#include <fstream>

void Figures::saveInfile(const char* fileName)
{
	std::ofstream write(fileName);
	if (write.is_open())
	{
		char header[] = "<?xml version=\"1.0\" standalone=\"no\"?>\n\
<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\
\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">  \n";
   
		char svgTag[] = "<svg width = \"12cm\" height = \"4cm\" viewBox = \"0 0 1200 400\"\n\
   xmlns = \"http://www.w3.org/2000/svg\" version = \"1.1\">\n ";
		
		write << header;

		int lSize = lines.getSize();
		for (int i = 0; i < lSize; i++)
		{
			if (ifSame("<svg", (lines.getLine(i))))
			{
				write << svgTag;
				for (int j = 0; j < size; j++)
					write << shape[j]->getLine() << "\n";
				for (int j = i + 1; j < lSize; j++)
				{
					if (ifSame("<\svg>", lines.getLine(j)))
						write << "<\svg> \n";
					write << lines.getLine(j) << "\n";
				}
				break;
			}
			i++;
		}
		std::cout << "File successfuly saved! \n";
		write.close();
	}
	else
		std::cout << "Error writing in file! \n";
}

void Figures::setFileName(const char* name)
{
	int len = strlen(name) + 1;
	newFileName = new (std::nothrow) char[len];
	strcpy(newFileName, name);
}

void Figures::save()
{
	if (openFile)
		saveInfile(newFileName);
	else
		std::cout << "You must open a file first! \n";
}

void Figures::saveAs(InputStorrage& o)
{
	if (size == 0)
	{
		std::cout << "You must open a file first! \n";
		return;
	}
	int elementsNum = 2;
	if (ifValid(elementsNum, o))
		return;
	saveInfile(o.getData(1));
}

bool Figures::ifValid(int value, InputStorrage& o)
{
	if (o.getSize() > value || o.getSize() < value)
	{
		std::cout << "Invalid data! \n";
		return true;
	}
	return false;
}

void Figures::create(InputStorrage& o)
{
	if (ifSame("circle", o.getData(1)))
		createCircle(o);
	else if (ifSame("rectangle", o.getData(1)))
		createRect(o);
	else if (ifSame("line", o.getData(1)))
		createLine(o);
	else
		std::cout << "Unknown figure! \n";
}

void Figures::createCircle(InputStorrage& o)
{
	int elementsNum = 6;
	if (ifValid(elementsNum, o))
		return;
	Circle c;
	c.setX(o.getData(2));
	c.setY(o.getData(3));
	c.setR(o.getData(4));
	c.setColour(o.getData(5));
	addFig(&c);
	std::cout << "Successfuly created circle (" << size << ") \n";
}

void Figures::createRect(InputStorrage& o)
{
	int elementsNum = 7;
	if (ifValid(elementsNum, o))
		return;
	Rect r;
	r.setX(o.getData(2));
	r.setY(o.getData(3));
	r.setWidth(o.getData(4));
	r.setHeight(o.getData(5));
	r.setColour(o.getData(6));
	addFig(&r);
	std::cout << "Successfuly created rectangle (" << size << ") \n";
}
void Figures::createLine(InputStorrage& o)
{
	int elementsNum = 7;
	if(ifValid(elementsNum, o))
		return;
	Line l;
	l.setX1(o.getData(2));
	l.setY1(o.getData(3));
	l.setX2(o.getData(4));
	l.setY2(o.getData(5));
	l.setColour(o.getData(6));
	addFig(&l);
	std::cout << "Successfuly created line (" << size << ") \n";
}

char* Figures::validPath(char* text)
{
	for (int i = 0; text[i] != '\0'; i++)
    {
		if (text[i] == '\\')
		text[i] = '/';
    }
	return text;
}

void Figures::open(InputStorrage& o)
{
	
	int elementsNum = 2;
	if (ifValid(elementsNum, o))
		return;
	if (openFile == true)
	{
		std::cout << "A file has alredy been opened! \n";
		return;
	}
	lines.clear();
	lines.createSpace();
	setFileName(validPath(o.getData(1)));
	std::ifstream read(newFileName, std::ios::in);
	if (read.is_open())
	{
		while (!read.eof())
		{
			char fileLine[2048] = { 0, };
			read.getline(fileLine, 2048);
			if (!read) break;
			lines.addLine(fileLine);
		}

		int lineSize = lines.getSize();
		for (int i = 0; i < lineSize; i++)
		{
			if (figCheck(lines.getLine(i)))
			{
				lines.removeLine(i);
				lineSize--;
				i--;
			}
		}
		std::cout << "File successfuly opened! \n";
		openFile = true;
		read.close();
	}
	else
	{
		std::ofstream newFile(newFileName);
		if (newFile.is_open())
		{
			std::cout << "New file created! \n";
			newFile.close();
		}
		else
			std::cout << "Couldn't create new file! \n";
	}
}

void Figures::close()
{
	if (openFile)
	{
		delete[] newFileName;
		newFileName = nullptr;
		openFile = false;
		std::cout << "File succesfuly closed! \n";
		return;
	}
	else
		std::cout << "Error closing file! \n";
}


bool Figures::figCheck(const char* text)
{
	for (int i = 0, j = 0; text[i] != '\0'; i++)
	{
		if (ifSame(circleTag, text))
		{
			Circle c;
			getData(text, &c);
			return true;
		}

		if (ifSame(rectangleTag, text))
		{
			Rect r;
			getData(text, &r);
			return true;
		}
		
		if (ifSame(lineTag, text))
		{
			Line l;
			getData(text, &l);
			return true;
		}
	}
	return false;
}

void Figures::getData(const char* text, Shape* o)
{
	o->addData(text);
	addFig(o);
}

void Figures::newFigSet()
{
	shape = new (std::nothrow) Shape*[capacity];
}

void Figures::addFig(Shape* o)
{
	shape[size] = o->clone();
	size++;
	resize(1);
}

void Figures::resize(int value)
{
	Shape** newSet = new Shape*[capacity + value];
	for (int i = 0; i < size; i++)
		newSet[i] = shape[i];
	delete[] shape;
	shape = newSet;
	capacity += value;
}

void Figures::erase(InputStorrage& o)
{
	if (size == 0)
	{
		std::cout << "No elements to erase! \n";
		return;
	}

	int elementsNum = 2;
	if (o.getSize() > elementsNum || o.getSize() < elementsNum)
	{
		std::cout << "Invalid data! \n";
		return;
	}

	int index = shape[0]->charToInt(o.getData(1)) - 1;
	if (index > size)
	{
		std::cout << "There is no figure number " << index << "! \n";
		return;
	}

	Shape* temp;
	for (int i = index; i < size - 1; i++)
	{
		temp = shape[i];
		shape[i] = shape[i + 1];
		shape[i + 1] = temp;
	}
	delete[] shape[size - 1];
	shape[size - 1] = nullptr;
	size--;
	resize(-1);
	std::cout << "Erased (" << index + 1 << ") \n";
}

void Figures::print()
{
	int cnt = 1;
	for (int i = 0; i < size; i++)
	{
		std::cout << cnt << ". ";
		shape[i]->print();
		cnt++;
	}
}

void Figures::translate(InputStorrage& o)
{

	int elementsNum = o.getSize();
	if (elementsNum < 5 || elementsNum > 6)
	{
		std::cout << "Invalid data! \n";
		return;
	}
	int x = 0, y = 0;
	int figNum = -1;

	for (int i = 1; i < elementsNum; i++)
	{
		if (ifSame("horizontal", o.getData(i)))
		{
			i++;
			x = shape[0]->charToInt(o.getData(i));
			continue;
		}
		if (ifSame("vertical", o.getData(i)))
		{
			i++;
			y = shape[0]->charToInt(o.getData(i));
			continue;
		}
		if (figNum == -1)
		{
			figNum = shape[0]->charToInt(o.getData(i));
			continue;
		}
	}

	if (figNum >= 0)
	{
		shape[figNum - 1]->translate(x, y);
		std::cout << "Figure ( " << figNum << " ) translated! \n";
	}
	else
	{
		for (int i = 0; i < size; i++)
			shape[i]->translate(x, y);
		std::cout << "Translated all figures! \n";
	}
}

void Figures::within(InputStorrage& o)
{
	int elementsNum = o.getSize();
	if (elementsNum < 5 || elementsNum > 6)
	{
		std::cout << "Invalid data! \n";
		return;
	}
	if (ifValid(elementsNum, o))
		return;
	if (size > 0)
	{
		if (elementsNum == 5 && ifSame("circle", o.getData(1)))
			withinCircle(shape[0]->charToInt(o.getData(2)),
			shape[0]->charToInt(o.getData(3)),
			shape[0]->charToInt(o.getData(4)));
		else if (elementsNum == 6 && 
			ifSame("rectangle", o.getData(1)))
			withinRectangle(
			shape[0]->charToInt(o.getData(2)),
			shape[0]->charToInt(o.getData(3)),
			shape[0]->charToInt(o.getData(4)),
			shape[0]->charToInt(o.getData(5)));
	}
	else
		std::cout << "No figures avaiable! \n";
}

void Figures::withinCircle(int x, int y, int r)
{
	int cnt = 0;
	for (int i = 0; i < size; i++)
	{
		if (shape[i]->withinCircle(x, y, r))
		{
			cnt++;
			std::cout << cnt << ". ";
			shape[i]->print();
		}
	}
}

void Figures::withinRectangle(int x, int y, int width, int height)
{
	int cnt = 0;
	for (int i = 0; i < size; i++)
	{
		if (shape[i]->withinRectangle(x, y, width, height))
		{
			cnt++;
			std::cout << cnt << ". ";
			shape[i]->print();
		}
	}
}