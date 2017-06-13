#include <iostream>
#include "basketData.h"
#include "eggData.h"

void basketInput()
{
	std::cout << "new basket: \n";
	Basket basket;

	int num = 0;
	std::cin >> basket;
	std::cout << "Multiply all by: ";
	std::cin >> num;
	basket *= num;
	std::cin.ignore();
	std::cout << basket;
	std::cout << std::endl;
	
	std::cout << "new basket: \n";
	Basket basket1;
	std::cin >> basket1;
    std::cout << "Divide all by: ";
	std::cin >> num;
	basket1 /= num;
	std::cout << basket1;
	std::cout << std::endl;

	std::cin.ignore();
	
	std::cout << "Enter egg name to search for in " 
		<< basket1.getBasketOwner() << ": \n";
	char str[30];
	std::cin.getline(str, 30);
	std::cout << basket1[str];

	Basket basket3(basket1);

	std::cout << basket.getBasketOwner() << "==" <<
		basket3.getBasketOwner() << " ?\n";
	if (basket1 == basket3)
		std::cout << "equal\n";
	else
		std::cout << "not equal\n";

	std::cout << std::endl;
	std::cout << basket.getBasketOwner() << "!=" <<
		         basket3.getBasketOwner() << " ?\n";
	
	if (basket != basket3)
		std::cout << "not equal\n";
	else
		std::cout << "equal\n";
	std::cout << std::endl;

    Basket basket2 = basket + basket1;
	std::cout << basket.getBasketOwner() << "+" << basket1.getBasketOwner() << ": \n";
	std::cout << basket2;
	std::cout << std::endl;
	
	int index = 0;
	std::cout << "Enter index to search for in "
		<< basket2.getBasketOwner() << ": \n";
	std::cin >> index;
	std::cout << basket2[index];
	std::cout << std::endl;
	std::cin.ignore();

	std::cout << "new basket: \n";

	Basket basket5(basket1 % basket);
	std::cout << basket1.getBasketOwner() << "%" << basket.getBasketOwner() << ": \n";
	std::cout << basket5;
	std::cout << std::endl;

	basket.serialization();	
	basket1.serialization();
	basket2.serialization();
	basket3.serialization();
	

}

int main()
{
	basketInput();
	
	Basket basket;
	std::cout << "Deserialization: \n";
	basket.deserialization();
	std::cout << basket;
	std::cout << std::endl;
	basket.print();
		
	return 0;
}