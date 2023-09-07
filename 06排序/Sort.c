#include"Sort.h"
#include"stack.h"

void PrintArray(int* a, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
void Swap(int* a, int* b)
{
	int tmp = *b;
	*b = *a;
	*a = tmp;
}

//直接插入排序
// 最好：O(N)    顺序有序
// 最坏：O(N^2)  逆序
void InsertSort(int* a, int n)
{
	for (int i = 1; i < n; i++)
	{
		int tmp = a[i];
		int end = i - 1;
		while (end >=0)
		{
			if (tmp < a[end])
			{
				a[end + 1] = a[end];
				--end;
			}
			else
			{
				break;
			}
		}
		a[end + 1] = tmp;
	}
}

//希尔排序O(N^1.3)
void ShellSort(int* a, int n)
{
	//如何选取合适的gap
	// gap > 1 预排序
	// gap == 1 直接插入排序

	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;

		for (int i = 0; i < n - gap; i++)
		{
			int end = i;
			int tmp = a[i + gap];
			while (end >= 0)
			{
				if (tmp < a[end])
				{
					a[end + gap] = a[end];
					end -= gap;
				}
				else
				{
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}
}

//最坏 O(N^2)
//最好 O(N^2)
void SelectSort(int* a, int n)
{
	//记录最小值和最大值的位置
	int left = 0, right = n - 1;
	while (left < right)
	{
		//将最左边的值认为是最大的，最右边的值认为是最小的
		//如果有比它还小的数 更新下标
		int mini = left, maxi = right;
		for (int i = left+1; i <= right; i++)
		{
			if (a[i] < a[mini])
			{
				mini = i;
			}
			if (a[i] > a[maxi])
			{
				maxi = i;
			}
			
		}
		if (left == maxi)//如果i==maxi， 交换后要修正一下
		{
			maxi = mini;
		}
		Swap(&a[left], &a[mini]);
		Swap(&a[right], &a[maxi]);
		++left;
		--right;
	}
}

void AdjustDown(int* a,int n,int parent)
{
	int child = parent * 2 + 1;
	while (child < n)
	{
		// 选出左右孩子中大的那一个
		if (child + 1 < n && a[child + 1] > a[child])
		{
			++child;
		}

		if (a[child] > a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}
void HeapSort(int* a, int n)
{
	// 建堆 -- 向下调整建堆 -- O(N)
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDown(a, n, i);
	}

	// 自己先实现 -- O(N*logN)
	int end = n - 1;
	while (end > 0)
	{
		Swap(&a[end], &a[0]);
		AdjustDown(a, end, 0);

		--end;
	}
}

//最坏 O(N^2)
//最好 O(N)
void BubbleSort(int* a, int n)
{
	int flag = 0;
	for (int j = 0; j < n - 1; j++)
	{
		for (int i = 1; i < n-j; i++)
		{
			if (a[i] < a[i - 1])
			{
				Swap(&a[i], &a[i - 1]);
				flag = 1;
			}
		}

		if (flag == 0)
		{
			break;
		}
	}
}
int GetMidNumi(int* a, int left, int right)
{
	int midi = (right - left) / 2;
	if (a[left] > a[midi])
	{
		if (a[midi] > a[right])
		{
			return midi;
		}
		else if (a[left] > a[right])
		{
			return right;
		}
		else
		{
			return left;
		}
	}
	else//a[left] < a[midi]
	{
		if (a[midi] < a[right])
		{
			return midi;
		}
		else if (a[right] > a[left])
		{
			return right;
		}
		else
		{
			return left;
		}
	}
}

//三数取中法
int PartSort1(int* a, int left, int right)
{
	//当数组为顺序有序时，时间复杂度为O(N^2) 
	//因此选择keyi，让它变为无序

	//随机选keyi(但仍有几率为顺序数组)
	//int randi = left + rand() % (right - left);
	//Swap(&a[left], &a[randi]);
	
	//三数取中
	int midi = GetMidNumi(a, left, right);
	Swap(&a[left], &a[midi]);

	int keyi = left;
	while (left < right)
	{
		//左边找小
		while (left < right && a[right] >= a[keyi])
		{
			--right;
		}
		//右边找大
		while (left < right && a[left] <= a[keyi])
		{
			++left;
		}

		Swap(&a[left], &a[right]);
	}
	Swap(&a[left], &a[keyi]);
	keyi = left;

	return keyi;
}

//挖坑法
int PartSort2(int* a, int left, int right)
{
	int begin = left, end = right;

	int midi = GetMidNumi(a, left, right);
	Swap(&a[left], &a[midi]);

	int key = a[left];//记录key的值
	int holei = left;//记录坑的位置
	while (left < right)
	{
		//左边找小
		while (left < right && a[right] >= key)
		{
			--right;
		}
		a[holei] = a[right];
		holei = right;
		//右边找大
		while (left < right && a[left] <= key)
		{
			++left;
		}
		a[holei] = a[left];
		holei = left;
	}
	a[holei] = key;//一定在空的坑位相遇

	return holei;
}

//前后下标法
int PartSort3(int* a, int left, int right)
{
	//三数取中
	int midi = GetMidNumi(a, left, right);
	Swap(&a[left], &a[midi]);

	int key = a[left];
	int prev = left, cur = left + 1;
	while (cur <= right)
	{
		if (a[cur] < key && ++prev!=cur)
		{
			Swap(&a[prev], &a[cur]);
		}
		++cur;
	}
	Swap(&a[left], &a[prev]);

	return prev;
}

//快速排序的递归实现
void QuickSort(int* a, int left, int right)
{
	if (left >= right)
		return;
	
	int keyi = PartSort3(a, left, right);
	QuickSort(a, left,keyi-1);
	QuickSort(a, keyi+ 1,right);
}

//非递归实现
void QuickSortNonR(int* a, int left, int right)
{
	ST st;
	STInit(&st);

	STPush(&st, right);
	STPush(&st, left);

	while (!STEmpty(&st))
	{
		int begin = STTop(&st);
		STPop(&st);
		int end = STTop(&st);
		STPop(&st);
		
		int keyi = PartSort3(a, begin, end);

		if (keyi + 1 < end)
		{
			STPush(&st, end);
			STPush(&st, keyi + 1);
		}
		if (begin < keyi - 1)
		{
			STPush(&st, keyi - 1);
			STPush(&st, begin);
		}
	}
	STDestroy(&st);
}

void _MergeSort(int* a, int begin, int end, int* tmp)
{
	if (begin >= end)
		return;

	int mid = (end+begin) / 2;
	//[begin , mid] [mid+1 , end]
	_MergeSort(a, begin, mid, tmp);
	_MergeSort(a, mid+1, end, tmp);

	int begin1 = begin, end1 = mid;
	int begin2 = mid + 1, end2 = end;
	int i = begin;
	while (begin1 <= end1 && begin2 <=end2)
	{
		if (a[begin1] < a[begin2])
		{
			tmp[i++] = a[begin1++];
		}
		else
		{
			tmp[i++] = a[begin2++];
		}
	}
	while (begin1 <= end1)
	{
		tmp[i++] = a[begin1++];
	}
	while (begin2<= end2)
	{
		tmp[i++] = a[begin2++];
	}

	memcpy(a + begin, tmp + begin, sizeof(int)*(end-begin+1));
}
void MergeSort(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		perror("malloc fail\n");
	}
	
	_MergeSort(a, 0, n - 1, tmp);

	free(tmp);
}
void MergeSortNonR(int* a, int n)
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	if (tmp == NULL)
	{
		perror("malloc failed");
		return;
	}

	int gap = 1;
	while (gap < n)
	{
		for (int i = 0; i < n; i+=2*gap)
		{
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			/*if (end1 > n-1)
			{
				end1 = n-1;
				begin2 = n;
				end2 = n-1;
			}
			else if (begin2 > n - 1)
			{
				begin2 = n;
				end2 = n - 1;
			}
			else if (end2 > n - 1)
			{
				end2 = n - 1;
			}*/
			if (end1 > n - 1 || begin2 > n - 1)
			{
				break;
			}
			if (end2 > n - 1)
			{
				end2 = n - 1;
			}
			printf("[%d][%d],[%d][%d]  ", begin1, end1, begin2, end2);
			int j = i;
			while (begin1 <= end1 && begin2 <= end2)
			{
				if (a[begin1] < a[begin2])
				{
					tmp[j++] = a[begin1++];
				}
				else
				{
					tmp[j++] = a[begin2++];
				}
			}
			while (begin1 <= end1)
			{
				tmp[j++] = a[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[j++] = a[begin2++];
			}

			memcpy(a+i , tmp+i, sizeof(int)*(end2-i+1));//归并一部分，拷贝回去一部分

		}
		printf("\n");
		//memcpy(a , tmp, sizeof(int) * n);//全部归并完拷贝
		gap *= 2;
	}

	free(tmp);
}

void CountSort(int* a, int n)
{
	//找出最大值和最小值
	int max = a[0], min = a[0];
	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
		if (a[i] < min)
		{
			min = a[i];
		}
	}
	int range = max - min + 1;//闭区间  countA的数组大小

	//计数
	int* countA = (int*)calloc(range, sizeof(int));
	if (countA == NULL)
	{
		perror("calloc fail");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		countA[a[i] - min]++;
	}

	//排序
	int j = 0;
	for (int i = 0; i < range; i++)
	{
		while (countA[i]--)
		{
			a[j++] = i + min;
		}
	}
}