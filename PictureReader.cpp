#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "PictureReader.h"

bool PictureReader::openBMP(const std::string& fileName)
{
	std::ifstream fs(fileName, std::ios::binary);
	if(!fs.is_open())
        return false; // не открыли

    //Прочитать головы
	BMPHeader head;
	BMPInfoHeader infoHead;
	fs.read((char*)&head,sizeof(BMPHeader));
	fs.read((char*)&infoHead,sizeof(BMPInfoHeader));

    width = infoHead.biWidth;
    height = infoHead.biHeight;
	int pixelCount = width * height;
	int sizeImage = infoHead.biSizeImage;
    
    // создать все буферы
	buf.resize(sizeImage);
	colors.resize(pixelCount);

    //перейти на начало изображения, прочитать и закрыть
	fs.seekg(head.bfOffBits);
	fs.read(buf.data(),sizeImage);
	fs.close();

    // для отбора лишней информации из картинки (padding)
	int temp = infoHead.biWidth * 3;
	int line = temp + infoHead.biWidth % 4;

    // Достать информацию о цветах. (255,255,255) - белый, остальное черное
	int a = 0;
	int i = 0;
	while(i<sizeImage)
	{

		if (i >= temp && (i % line) >= temp)
		{//buf[i] это padding, пропускаем
			i++; 
			continue;
		}
		u_int8_t r = buf[i];		
		i++;
		u_int8_t g = buf[i];
		i++;
		u_int8_t b = buf[i];
		i++;

		if(r==255 &&
		g==255 &&
		b==255)
			colors[a] = true;
		else
			colors[a] = false;
		a++;
	}

    //Пометить об успешном открытии в классе 
    opennedFile = fileName;
    opened = true;

	return true;
}

bool PictureReader::displayBMP()
{
    if(!opened || colors.size()<height*width)
        return false;
    // Изображение перевернутое, ибо bmp
	for(int y=height-1;y>=0;y--)
	{
		std::cout << "\n";
		for(int x=0;x<width;x++)
		{
			if(colors[x + y * width])
				std::cout<<"00";// 2 символа/пиксель делают картинку не настолько искажённой
			else
				std::cout<<"  ";
		}
	}
	std::cout<<"\n";
    return true;
}

bool PictureReader::closeBMP()
{
    width = -1;
    height = -1;
    opennedFile = "";

    // С этим можно имплементировать проверку и выдавать ошибку в случае если ничего небыло открыто до этого
    // но в данном случае я реализовал закрытие как просто отчистку класса обратно в норму, даже если он сломан/удалено пару буферов
    opened = false; 


    return true;
}