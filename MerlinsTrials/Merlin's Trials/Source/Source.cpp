#include"ATestClass.h"
#include<iostream>

int main()
{
	ATestClass testC;

	if (testC.importModel("Map1_V1.obj") != nullptr)
	{
		std::cout << "NOT NULLPTR" << std::endl;
	}
	else
	{
		std::cout << "NULLPTR" << std::endl;
	}
	system("PAUSE");

	return 0;
}


