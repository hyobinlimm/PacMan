#include <stdio.h>
#include <string.h>
#include "GameInterface.h"

#pragma warning(disable:4996)

void TitleInit()
{
	
	/*
	FILE* folderName = fopen("TitleArt.txt", "rb");


	char TitleMapArr[100][101] = {0, }; // �������� \n �� ���� 101 ĭ���� �߽��ϴ�.

	for (int i = 0; i < 100; i++)
	{
		fgets(TitleMapArr[i], 101, folderName);
	}

	TitleExit(folderName);

	for (int i = 0; i < 100; i++)
	{
		printf("%s", TitleMapArr[i]);
	}
	*/


}

void TitleExit(FILE* fd)
{
	if (fd != NULL)
	{
		fclose(fd);
	}
}