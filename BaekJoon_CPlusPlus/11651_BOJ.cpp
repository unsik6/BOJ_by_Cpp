// 백준 11651번 좌표 정렬하기

// input: N = 좌표의 수 <= 100,000
//        -100,000 <= xi, yi = integer <= 100,000 (distinct)

// y좌표 증가순 + y가 같으면 x좌표 증가순

// using HeapSort


#include <iostream>
#include <utility>
using namespace std;

void swapPair(pair<int, int>& _pair1, pair<int, int>& _pair2)
{
	pair<int, int> temp = _pair1;
	_pair1 = _pair2;
	_pair2 = temp;
}

class HeapInPair
{
private:
	pair<int, int>* m_arr;
	int m_lastIdx;

	int m_capacity;
	int m_heapSize;

public:
	HeapInPair(int _size = 0)
	{
		this->m_capacity = _size;
		this->m_heapSize = 0;
		this->m_lastIdx = 0;
		this->m_arr = new pair<int, int>[_size];
	}
	~HeapInPair() { delete[] m_arr; }


	void upHeap()
	{
		int curIdx = this->m_lastIdx;
		while (curIdx / 2 > 0)
		{
			if (this->m_arr[curIdx].second < this->m_arr[curIdx / 2].second ||
				(this->m_arr[curIdx].second == this->m_arr[curIdx / 2].second
					&& this->m_arr[curIdx].first < this->m_arr[curIdx / 2].first))
			{
				swapPair(this->m_arr[curIdx], this->m_arr[curIdx / 2]);
			}
			curIdx /= 2;
		}
	}

	void downHeap()
	{
		int curIdx = 1;
		while (curIdx * 2 <= this->m_heapSize)
		{
			int minIdx = curIdx;
			if (this->m_arr[minIdx].second > this->m_arr[curIdx * 2].second ||
				(this->m_arr[minIdx].second == this->m_arr[curIdx * 2].second
					&& this->m_arr[minIdx].first > this->m_arr[curIdx * 2].first))
			{
				minIdx = curIdx * 2;
			}
			if (curIdx * 2 + 1 <= this->m_heapSize)
			{
				if (this->m_arr[minIdx].second > this->m_arr[curIdx * 2 + 1].second ||
					(this->m_arr[minIdx].second == this->m_arr[curIdx * 2 + 1].second
						&& this->m_arr[minIdx].first > this->m_arr[curIdx * 2 + 1].first))
				{
					minIdx = curIdx * 2 + 1;
				}
			}

			if (minIdx == curIdx) return;
			else
			{
				swapPair(m_arr[curIdx], m_arr[minIdx]);
			}
			curIdx = minIdx;
		}
	}


	void insert(pair<int, int> _pair)
	{
		if (this->m_heapSize == this->m_capacity)
		{
			cerr << "Full\n";
			return;
		}
		this->m_arr[++this->m_lastIdx] = _pair;

		this->upHeap();

		this->m_heapSize++;
	}

	pair<int, int> removeMin()
	{
		if (this->m_heapSize < 1)
		{
			return make_pair(-100001, -100001);
		}
		pair<int, int> result = this->m_arr[1];
		this->m_arr[1] = this->m_arr[this->m_lastIdx--];
		this->m_heapSize--;
		this->downHeap();

		return result;
	}


	void printAll()
	{
		for (int i = 1; i <= this->m_heapSize; i++)
			cout << this->m_arr[i].first << ' ' << this->m_arr[i].second << '\n';
	}
};


int main()
{
	int N;
	cin >> N;
	HeapInPair* heap = new HeapInPair(N + 1);
	for (int i = 0; i < N; i++)
	{
		int x, y;
		cin >> x >> y;
		heap->insert(make_pair(x, y));
	}

	/*heap->printAll();*/


	for (int i = 0; i < N; i++)
	{
		pair<int, int> min = heap->removeMin();

		cout << min.first << ' ' << min.second << '\n';
	}
}