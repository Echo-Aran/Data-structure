#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//��̬˳����������˲����ã��������˷�
//
//typedef int SLDataType;  //���������������
//#define N 100
//struct SeqList
//{
//	SLDataType a[N];
//	int size;
//};

typedef int SLDataType;
#define Init_Capacity 4   //��ʼ���ռ�����Ϊ4

//��̬���ݱ������ͣ�������������
typedef struct SeqList
{
	SLDataType* a;  //˳������飩
	int size;       //��Ч���ݸ���
	int capacity;    //�ռ�����
}SL;

//��ɾ���
void SLInit(SL* ps);       //��ʼ��
void SLDestroy(SL* ps);    //����
void SLPrint(SL* ps);      //��ӡ

void SLPushBack(SL* ps);
void SLPopBack(SL* ps);
void SLPushFront(SL* ps);
void SLPopFront(SL* ps);   //���ݵ�ַ


