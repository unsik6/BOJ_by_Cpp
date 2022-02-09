// 백준 18870번 단어정렬

// input: 1 <= N = 수직선상 좌표 수 <= 1,000,000
//		  |Xi| <= 10^9

// condition: Xi' = the number of distinct numbers, Xj that is less than Xi.

#include <iostream>
#include <utility>
using namespace std;

#define none -1

class MinHeap
{
private:
	pair<int, int>* m_arr;

	int m_capacity;
	int m_heapSize;

	int m_lastIdx;

public:
	MinHeap(int _size = 0)
	{
		this->m_capacity = _size + 1;
		this->m_heapSize = 0;
		this->m_lastIdx = 0;
		this->m_arr = new pair<int, int>[_size + 1];
		for (int i = 0; i < m_capacity; i++)
		{
			m_arr[i].first = none;
			m_arr[i].second = -1;
		}
	}
	~MinHeap() { delete[] this->m_arr; }

	bool isEmpty()
	{
		return this->m_heapSize == 0;
	}



	int getCapacity()
	{
		return this->m_capacity;
	}

	int getHeapSize()
	{
		return this->m_heapSize;
	}

	void upHeap()
	{
		int tempIdx = this->m_lastIdx;
		while (tempIdx / 2 > 0)
		{
			if (this->m_arr[tempIdx].first < this->m_arr[tempIdx / 2].first)
			{
				pair<int, int> temp = this->m_arr[tempIdx];
				this->m_arr[tempIdx] = this->m_arr[tempIdx / 2];
				this->m_arr[tempIdx / 2] = temp;

				tempIdx /= 2;
			}
			else break;
		}
	}

	void downHeap()
	{
		int tempIdx = 1;
		while (tempIdx * 2 <= this->m_heapSize)
		{
			int minIdx = tempIdx;
			if (this->m_arr[tempIdx].first > this->m_arr[tempIdx * 2].first)
			{
				minIdx = tempIdx * 2;
			}
			if (tempIdx * 2 + 1 <= this->m_heapSize
				&& this->m_arr[minIdx].first > this->m_arr[tempIdx * 2 + 1].first)
			{
				minIdx = tempIdx * 2 + 1;
			}

			if (minIdx == tempIdx) return;
			else
			{
				pair<int, int> temp = this->m_arr[tempIdx];
				this->m_arr[tempIdx] = this->m_arr[minIdx];
				this->m_arr[minIdx] = temp;
			}
			tempIdx = minIdx;
		}
	}

	void insertHeap(pair<int, int> _e)
	{
		// check for isFull
		if (this->m_heapSize >= this->m_capacity)
		{
			return;
		}
		else
		{
			this->m_arr[++this->m_lastIdx] = _e;
			this->upHeap();
			this->m_heapSize++;
		}
	}

	pair<int, int> removeMin()
	{
		if (isEmpty())
		{
			return make_pair(none, -1);
		}
		else
		{
			pair<int, int> min = this->m_arr[1];
			this->m_arr[1] = this->m_arr[this->m_lastIdx--];
			this->m_heapSize--;
			this->downHeap();

			return min;
		}
	}

	void printAll()
	{
		for (int i = 1; i <= m_heapSize; i++)
		{
			cout << this->m_arr[i].first << ' ';
		}
		cout << '\n';
	}
};


int main()
{
	int N;
	cin >> N;
	pair<int, int>* arr = new pair<int, int>[N];
	int* arr2 = new int[N];
	MinHeap* heap = new MinHeap(N);
	for (int i = 0; i < N; i++)
	{
		int input;
		cin >> input;
		arr[i].first = input;
		arr[i].second = i;
		heap->insertHeap(arr[i]);
	}
	for (int i = 0; i < N; i++) arr[i] = heap->removeMin();


	int curValue = arr[0].first;
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		if (curValue == arr[i].first)
			arr2[arr[i].second] = cnt;
		else
		{
			arr2[arr[i].second] = ++cnt;
			curValue = arr[i].first;
		}
	}

	for (int i = 0; i < N; i++) cout << arr2[i] << ' ';
}