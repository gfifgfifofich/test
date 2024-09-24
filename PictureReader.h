#pragma once


class PictureReader
{
public:
    // состояние
    bool opened = false;
    std::string opennedFile = "";

    //буферы
	std::vector<char> buf;
	std::vector<bool> colors;

    //полезная информация об изображении
    int width = -1;
    int height = -1;

    //Расчитан на 24 битные bmp (RGB)
    bool openBMP(const std::string& fileName);
    bool displayBMP();
    bool closeBMP();

};

// Сделать выравнивание по 2 байта, а не 4 (так как в структурах есть полный int)
#pragma pack(push, 2)

// Этот хеадер общий во всех bmp
struct BMPHeader
{
	u_int16_t bfType = 0;
	unsigned int bfSize = 0;
	u_int16_t bfReserved1 = 0;
	u_int16_t bfReserved2 = 0;
	unsigned int bfOffBits = 0;
};

// 32-битный, версия 3 (BITMAPINFOHEADER) https://ru.wikipedia.org/wiki/BMP
struct BMPInfoHeader
{
	unsigned int biSize = 0;
	unsigned int biWidth = 0;
	unsigned int biHeight = 0;
	u_int16_t	biPlanes = 0;
	u_int16_t	biBitCount = 0;
	unsigned int biCompression = 0;
	unsigned int biSizeImage = 0;
	unsigned int biXPelsPerMeter = 0;
	unsigned int biYPelsPerMeter = 0;
	unsigned int biClrUsed = 0;
	unsigned int biClrImportant = 0;
};
#pragma pack(pop)