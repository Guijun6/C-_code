#include<iostream>
#include <assert.h>
#include"CommentConvert.h"

using namespace std;

enum State
{
	NULL_STATE,//空状态
	C_STATE,//C状态
	CPP_STATE,//C++状态
	END_STATE,//结束
};

enum State state = NULL_STATE;

void OnNullState(FILE* fin, FILE* fout)	// 找/* // ->
{
	char first = fgetc(fin);
	if (first == '/')
	{
		char second = fgetc(fin);
		if (second == '*')
		{
			state = C_STATE;
		}
		else if (second = '/')
		{
			state = CPP_STATE;
		}
		fputs("//", fout);
	}
	else if (first == EOF)//如果遇到EOF，则文件结束，
	{
		fputc(first, fout); //写入读到的字符
		state = END_STATE;//并将此时的状态值为结束状态
	}
	else
	{
		fputc(first, fout);
	}
}

void OnCState(FILE* fin, FILE* fout)	// 找*/ -> NULL_STATE
{
	char first = getc(fin);
	if (first == '*')
	{
		char second = getc(fin);
		if (second == '/')		//读取第二个字符进行判断
		{
			char third = fgetc(fin);
			state = NULL_STATE;
			if (third != '\n')		//再读取第三个字符
			{
				fputc('\n', fout);
				ungetc(third, fin);//由于无法知道下一个字符是什么，因此只能将次字符退回
			}
			else
			{
				fputc(third, fout);
			}
		}
		else
		{
			fputc(first, fout);
			ungetc(second, fin);
		}
	}
	else if (first == '\n')
	{
		fputc(first, fout);
		fputs("//", fout);
	}
	else if (first == EOF)
	{
		fputc(first, fout);
		state = END_STATE;
	}
	else
	{
		fputc(first, fout);
	}
}

void OnCppState(FILE* fin, FILE* fout)	// 找 \n -> NULL_STATE
{
	char first = fgetc(fin);
	if (first == '\n')
	{
		fputc(first, fout);
		state = NULL_STATE;
	}
	else if (first == EOF)
	{
		fputc(first, fout);
		state = END_STATE;
	}
	else
	{
		fputc(first, fout);
	}
}

void _StartConvert(FILE* fin, FILE* fout)
{
	while (state != END_STATE)
	{
		switch (state)
		{
		case NULL_STATE:
			OnNullState(fin, fout);
			break;
		case C_STATE:
			OnCState(fin, fout);
			break;
		case CPP_STATE:
			OnCppState(fin, fout);
			break;
		case END_STATE:
			break;
		default:
			assert(false);
			break;
		}
	}
}