#include<iostream>
#include<assert.h>

#include"CommentConvert.h"

using namespace std;



int main()
{
	//�Զ��ķ�ʽ��һ���ļ���Ϊinput.cpp���ļ�
	FILE *pRead = fopen("input.cpp", "r");
	if (pRead == NULL)
	{
		perror("open file for read");
		exit(EXIT_FAILURE);
	}

	//д���´�����"output.c"�ļ�;  
	FILE *pWrite = fopen("output.cpp", "w");
	if (pWrite == NULL)
	{
		fclose(pRead);
		perror("open file for write");
		exit(EXIT_FAILURE);
	}

	//���ò���ѡ���;  
	_StartConvert(pRead, pWrite);

	//�ر��Ѿ��򿪵��ļ�;  
	fclose(pRead);
	fclose(pWrite);

	return 0;
}