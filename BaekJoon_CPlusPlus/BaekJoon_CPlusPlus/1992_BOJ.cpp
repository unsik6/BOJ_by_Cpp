// 백준 1992번 쿼드트리

// input: N은 2의 제곱수, 1<= N <= 64

// condition: 쿼드트리 압축


#include <iostream>
using namespace std;

string compressQuadTree(string* _arr, int _strRowIdx, int _strColIdx, int _n)
{
	string result = "";
	if (_n == 1)
	{
		result += _arr[_strRowIdx][_strColIdx];
		return result;
	}
	else
	{
		char p = _arr[_strRowIdx][_strColIdx];
		for (int i = 0; i < _n; i++)
		{
			for (int j = 0; j < _n; j++)
			{
				if (_arr[_strRowIdx+i][_strColIdx+j] != p)
				{
					result += "(";
					result += compressQuadTree(_arr, _strRowIdx, _strColIdx, _n / 2);
					result += compressQuadTree(_arr, _strRowIdx, _strColIdx + _n / 2, _n / 2);
					result += compressQuadTree(_arr, _strRowIdx + _n / 2, _strColIdx, _n / 2);
					result += compressQuadTree(_arr, _strRowIdx + _n / 2, _strColIdx + _n / 2, _n / 2);
					result += ")";
					return result;
				}
			}
		}


	}
	result += _arr[_strRowIdx][_strColIdx];
	return result;
}


int main()
{
	int N;
	cin >> N;
	string* arr = new string[N];

	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
	}

	string compression = compressQuadTree(arr, 0, 0, N);
	cout << compression;

}