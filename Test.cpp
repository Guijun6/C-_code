#include<iostream>
#include<assert.h>

#include"CommentConvert.h"

using namespace std;



int main()
{
	//以读的方式打开一个文件名为input.cpp的文件
	FILE *pRead = fopen("input.cpp", "r");
	if (pRead == NULL)
	{
		perror("open file for read");
		exit(EXIT_FAILURE);
	}

	//写入新创建的"output.c"文件;  
	FILE *pWrite = fopen("output.cpp", "w");
	if (pWrite == NULL)
	{
		fclose(pRead);
		perror("open file for write");
		exit(EXIT_FAILURE);
	}

	//调用操作选项函数;  
	_StartConvert(pRead, pWrite);

	//关闭已经打开的文件;  
	fclose(pRead);
	fclose(pWrite);

	return 0;
}