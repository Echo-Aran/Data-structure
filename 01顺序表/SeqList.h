#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

//静态顺序表——开少了不够用，开多了浪费
//
//typedef int SLDataType;  //给数据类型起别名
//#define N 100
//struct SeqList
//{
//	SLDataType a[N];
//	int size;
//};

typedef int SLDataType;
#define Init_Capacity 4   //初始化空间容量为4

//动态数据表（的类型）——按需申请
typedef struct SeqList
{
	SLDataType* a;  //顺序表（数组）
	int size;       //有效数据个数
	int capacity;    //空间容量
}SL;

//增删查改
void SLInit(SL* ps);       //初始化
void SLDestroy(SL* ps);    //销毁
void SLPrint(SL* ps);      //打印

void SLPushBack(SL* ps);
void SLPopBack(SL* ps);
void SLPushFront(SL* ps);
void SLPopFront(SL* ps);   //传递地址


