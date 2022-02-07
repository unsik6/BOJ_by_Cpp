// 백준 2108번 수 정렬하기 2

// input: 1 <= N = 정수 개수 <= 500,000 (단, N은 홀수)
//		  N개의 줄에는 정수들이 주어짐. |i| < 4,000


#include <iostream>
using namespace std;

class Arr
{
private:
	int* m_arr;
	int m_capacity;
	int m_size;

public:
	Arr(int _size = 0)
	{
		this->m_arr = new int[_size];
		this->m_capacity = _size;
		this->m_size = 0;

		// the count of element is stored in m_arr[element + m_capacity / 2].
		for (int i = 0; i < m_capacity; i++)
		{
			this->m_arr[i] = 0;
		}
	}
	~Arr() { delete[] this->m_arr; }

	void insert(int _e)
	{
		if (_e >= this->m_capacity / 2 || _e <= this->m_capacity / 2 * -1)
		{
			return;
		}
		else
		{
			this->m_arr[_e + this->m_capacity / 2]++;
			this->m_size++;
		}
	}

	void printAll()
	{
		cout << "size is " << this->m_size << endl;
		for (int i = 0; i < this->m_capacity; i++)
		{
			if (this->m_arr[i] <= 0) continue;
			cout << i - this->m_capacity / 2 << ' ' << this->m_arr[i] << " / ";
		}
		cout << '\n';
	}

	void printStatistics()
	{
		int avg = 0;
		int mid = this->m_capacity, cntForMid = 0;;
		int* mode = new int[2];
		mode[0] = mode[1] = this->m_capacity;
		int modeCnt = 0;
		int min = this->m_capacity, max = this->m_capacity * -1;

		for (int i = 0; i < this->m_capacity; i++)
		{
			if (this->m_arr[i] < 1) continue;
			
			int realElem = i - this->m_capacity / 2;

			// avg
			avg += realElem * this->m_arr[i];

			// mid
			cntForMid += this->m_arr[i];
			if (mid == this->m_capacity && cntForMid > this->m_size / 2)
				mid = realElem;

			// mode
			if (this->m_arr[i] > modeCnt)
			{
				mode[0] = realElem;
				mode[1] = this->m_capacity;
				modeCnt = this->m_arr[i];
			}
			else if (this->m_arr[i] == modeCnt)
			{
				// realElem is increasing, we just need second min.
				if (mode[1] == this->m_capacity)
					mode[1] = realElem;
			}

			// range
			min = (min > realElem ? realElem : min);
			max = (max < realElem ? realElem : max);
		}

		// avg
		if (avg > 0)
		{
			if (avg % this->m_size > this->m_size / 2)
				avg = avg / this->m_size + 1;
			else avg = avg / this->m_size;
		}
		else if (avg < 0)
		{
			if (avg % this->m_size < this->m_size / 2 * -1)
				avg = avg / this->m_size - 1;
			else avg = avg / this->m_size;
		}

		// print
		cout << avg << '\n' << mid << '\n' << (mode[1] != this->m_capacity ? mode[1] : mode[0]) << '\n'
			<< max - min;

		delete[] mode;
	}
};

int main()
{
	Arr* arr = new Arr(80001);
	int N;
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int n;
		cin >> n;
		arr->insert(n);
		//arr->printAll();			// check
	}
	
	//arr->printAll();;				// check

	arr->printStatistics();
}

// 버려진 merge sort
void merge(int* _arrOrigin, int* _arrL, int _sizeL, int* _arrR, int _sizeR)
{
	int originSize = _sizeL + _sizeR;
	int LIdx = 0, RIdx = 0;

	for (int i = 0; i < originSize; i++)
	{
		if (LIdx >= _sizeL)
		{
			if (RIdx >= _sizeR)
			{
				break;
			}
			else
			{
				_arrOrigin[i] = _arrR[RIdx];
				RIdx++;
			}
		}
		else if (RIdx >= _sizeR)
		{
			_arrOrigin[i] = _arrL[LIdx];
			LIdx++;
		}
		else if (_arrL[LIdx] <= _arrR[RIdx])
		{
			_arrOrigin[i] = _arrL[LIdx];
			LIdx++;
		}
		else if (_arrL[LIdx] > _arrR[RIdx])
		{
			_arrOrigin[i] = _arrR[RIdx];
			RIdx++;
		}
	}
}

int* mergeSort(int* _arr, int _arrSize)
{
	if (_arrSize == 1)
	{
		return _arr;
	}
	else
	{
		int mid = _arrSize / 2;
		int* leftArr = new int[mid];
		int* rightArr = new int[_arrSize - mid];
		for (int i = 0; i < mid + 1; i++)
		{
			if (i < mid) leftArr[i] = _arr[i];
			if (i < _arrSize - mid) rightArr[i] = _arr[i + mid];
		}
		mergeSort(leftArr, mid);
		mergeSort(rightArr, _arrSize - mid);
		merge(_arr, leftArr, mid, rightArr, _arrSize - mid);


		delete[] leftArr;
		delete[] rightArr;
		return _arr;
	}
}