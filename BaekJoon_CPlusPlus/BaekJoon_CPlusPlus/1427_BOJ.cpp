// 백준 1427번 소트 인사이드

// input: N = 정렬하고자 하는 자연수 <= 1,000,000,000

// using original QuickSort

#include <iostream>
using namespace std;

void swapInt(int& _a, int& _b)
{
	int temp = _a;
	_a = _b;
	_b = temp;
}

int partitionOfQucikSort(int* _arr, int _pIdx, int _rIdx)
{
	int i = _pIdx - 1;
	for (int j = _pIdx; j < _rIdx; j++)
	{
		// decreasing order
		if (_arr[j] >= _arr[_rIdx])
		{
			i++;
			swapInt(_arr[j], _arr[i]);
		}
	}
	swapInt(_arr[i + 1], _arr[_rIdx]);

	return i + 1;
}

void quickSort(int* _arr, int _pIdx, int _rIdx)
{
	if(_pIdx < _rIdx)
	{
		int pivot = partitionOfQucikSort(_arr, _pIdx, _rIdx);
		quickSort(_arr, _pIdx, pivot - 1);
		quickSort(_arr, pivot + 1, _rIdx);
	}
}


int main()
{
	int N;
	cin >> N;
	int temp = N, size = 0;
	while (temp > 0)
	{
		temp /= 10;
		size++;
	}
	int* arr = new int[size];
	for(int i = 0; i < size; i++)
	{
		arr[i] = N % 10;
		N /= 10;
	}

	quickSort(arr, 0, size - 1);

	for (int i = 0; i < size; i++)
	{
		cout << arr[i];
	}

	delete[] arr;
}