#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void Swap(int* a, int* b);
void PrintArray(int* a, int n);
void InsertSort(int* a, int n);
void ShellSort(int* a, int n);
void SelectSort(int* a, int n);
void BubbleSort(int* a, int n);
void AdjustDown(int* a, int n, int parent);
void HeapSort(int* a, int n);

int GetMidNumi(int* a, int left, int right);
int PartSort1(int* a, int left, int right);
int PartSort2(int* a, int left, int right);
int PartSort3(int* a, int left, int right);
void QuickSort(int* a, int left, int right);
void QuickSortNonR(int* a, int left, int right);
void MergeSort(int* a, int n);
void _MergeSort(int* a, int begin, int end, int* tmp);
void MergeSortNonR(int* a, int n);
void CountSort(int* a, int n);
