// 백준 2750번 수 정렬하기 2

// input: 1 <= N = 정수 개수 <= 1,000,000
//		  |x| <= 1,000,000 (중복 안됨)

// using Merge Sort Algorithm

#include<iostream>
using namespace std;

void merge(int* arr, int* arr1, int* arr2, int size1, int size2)
{
	int i = 0, i1 = 0, i2 = 0;
	while (i < size1 + size2)
	{
		if (i2 >= size2)
		{
			arr[i] = arr1[i1];
			i++;
			i1++;
			continue;
		}
		else if (i1 >= size1)
		{
			arr[i] = arr2[i2];
			i++;
			i2++;
			continue;
		}
		if (arr1[i1] >= arr2[i2])
		{
			arr[i] = arr2[i2];
			i2++;
		}
		else
		{
			arr[i] = arr1[i1];
			i1++;
		}
		i++;
	}
}

void mergeSort(int* arr, int size)
{
	if (size == 1) return;

	int size1 = size / 2;
	int* arr1 = new int[size1];
	int size2 = size - size1;
	int* arr2 = new int[size2];
	for (int i = 0; i < size; i++)
	{
		if (i < size1) arr1[i] = arr[i];
		else arr2[i - size1] = arr[i];
	}
	mergeSort(arr1, size1);
	mergeSort(arr2, size2);
	merge(arr, arr1, arr2, size1, size2);
}

int main()
{
	int N;
	cin >> N;
	int* arr = new int[N];
	for (int i = 0; i < N; i++) cin >> arr[i];
	mergeSort(arr, N);
	for (int i = 0; i < N; i++) cout << arr[i] << '\n';
}