#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "PictureReader.h"

int main(int argc, char* argv[])
{
	// Проверить ввод
	if (argc < 2) {
		std::cout<<"usage:\n "<< argv[0] <<" ./file.bmp\n";
		return 1;
	}
	
	//Прочитать файл
	PictureReader pr;
	if(!pr.openBMP(argv[1]))
	{
		std::cout<<"Cant open BMP: " <<argv[1]<<"\n";
		return 1;		
	}

	std::cout<<"Picture size: " << pr.width <<"x"<< pr.height <<"\n";

	//отобразить
	if(!pr.displayBMP())
	{
		std::cout<<"Something went wrong while displaying image: " <<pr.opennedFile<<"\n";
		return 1;
	}

	//Закрыть все
	pr.closeBMP();
	return 0;
}