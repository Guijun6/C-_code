#include<iostream>
#include <assert.h>
#include"CommentConvert.h"

using namespace std;

enum State
{
	NULL_STATE,//��״̬
	C_STATE,//C״̬
	CPP_STATE,//C++״̬
	END_STATE,//����
};

enum State state = NULL_STATE;

void OnNullState(FILE* fin, FILE* fout)	// ��/* // ->
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
	else if (first == EOF)//�������EOF�����ļ�������
	{
		fputc(first, fout); //д��������ַ�
		state = END_STATE;//������ʱ��״ֵ̬Ϊ����״̬
	}
	else
	{
		fputc(first, fout);
	}
}

void OnCState(FILE* fin, FILE* fout)	// ��*/ -> NULL_STATE
{
	char first = getc(fin);
	if (first == '*')
	{
		char second = getc(fin);
		if (second == '/')		//��ȡ�ڶ����ַ������ж�
		{
			char third = fgetc(fin);
			state = NULL_STATE;
			if (third != '\n')		//�ٶ�ȡ�������ַ�
			{
				fputc('\n', fout);
				ungetc(third, fin);//�����޷�֪����һ���ַ���ʲô�����ֻ�ܽ����ַ��˻�
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

void OnCppState(FILE* fin, FILE* fout)	// �� \n -> NULL_STATE
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