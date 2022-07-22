// 백준 1780번 종이의 개수

// input: 전체 종이의 한변의 길이 N은 3의 거듭제곱 1<= N <= 3^7
//        가로 윗줄부터 차례로 -1, 0, 1

// condition: 만약 색종이가 같은 색들로만 이루어져 있지 않다면 전체를 1/9한다.


#include <iostream>
using namespace std;

struct paperNum
{
	int neg = 0;
	int zero = 0;
	int one = 0;
};

paperNum& operator+=(paperNum& _a, const paperNum& _b)
{
	_a.neg += _b.neg;
	_a.zero += _b.zero;
	_a.one += _b.one;
	return _a;
}

ostream& operator<<(ostream& _os, const paperNum _pn)
{
	_os << _pn.neg << '\n' << _pn.zero << '\n' << _pn.one;
	return _os;
}


paperNum computeNumberOfPapers(int** _arr, int _startRowIdx, int _startColumnIdx, int _n)
{
	paperNum result;
	if (_n == 1)
	{
		if (_arr[_startRowIdx][_startColumnIdx] == -1)
			result.neg++;
		else if (_arr[_startRowIdx][_startColumnIdx] == 0)
			result.zero++;
		else
			result.one++;

		return result;
	}
	else
	{
		int p = _arr[_startRowIdx][_startColumnIdx];
		for (int i = 0; i < _n; i++)
		{
			for (int j = 0; j < _n; j++)
			{
				if (_arr[_startRowIdx + i][_startColumnIdx + j] != p)
				{
					for (int k = 0; k < 3; k++)
					{
						for (int f = 0; f < 3; f++)
						{
							result += computeNumberOfPapers(_arr, _startRowIdx + _n / 3 * k,
								_startColumnIdx + _n / 3 * f, _n / 3);
						}
					}
					return result;
				}
			}
		}
		if (_arr[_startRowIdx][_startColumnIdx] == -1)
			result.neg++;
		else if (_arr[_startRowIdx][_startColumnIdx] == 0)
			result.zero++;
		else
			result.one++;

		return result;
	}
}

int main()
{
	int N;
	cin >> N;
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
	{
		arr[i] = new int[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> arr[i][j];
		}
	}

	paperNum result = computeNumberOfPapers(arr, 0, 0, N);
	cout << result;

	for (int i = 0; i < N; i++)
	{
		delete[] arr[i];
	}
	delete[] arr;

}