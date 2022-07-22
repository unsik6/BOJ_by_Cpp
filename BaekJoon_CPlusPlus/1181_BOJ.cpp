// 백준 1181번 단어정렬

// input: 1 <= N = 단어 개수 <= 20,000
//		  |string| <= 50

// condition: first) lenght increasing order / second) order in dictionary

#include <iostream>
#include <vector>
using namespace std;

vector<string> merge(vector<string>& _v1, vector<string>& _v2)
{
	vector<string> tmpV;
	int size1 = _v1.size();
	int size2 = _v2.size();
	int size = size1 + size2;
	
	int curIdx1 = 0, curIdx2 = 0;
	int i = 0;
	while (curIdx1 < size1 || curIdx2 < size2)
	{
		if (curIdx1 == size1)
		{
			tmpV.push_back(_v2[curIdx2]);
			curIdx2++;
			i++;
			continue;
		}
		else if (curIdx2 == size2)
		{
			tmpV.push_back(_v1[curIdx1]);
			curIdx1++;
			i++;
			continue;
		}
		else
		{
			if (_v1[curIdx1].length() < _v2[curIdx2].length())
			{
				tmpV.push_back(_v1[curIdx1]);
				curIdx1++;
				i++;
				continue;
			}
			else if (_v1[curIdx1].length() > _v2[curIdx2].length())
			{
				tmpV.push_back(_v2[curIdx2]);
				curIdx2++;
				i++;
				continue;
			}
			else
			{
				bool isChanged = false;
				for (int j = 0; j < _v1[curIdx1].length(); j++)
				{
					if (_v1[curIdx1][j] < _v2[curIdx2][j])
					{
						tmpV.push_back(_v1[curIdx1]);
						curIdx1++;
						i++;
						isChanged = true;
						break;
					}
					else if (_v1[curIdx1][j] > _v2[curIdx2][j])
					{
						tmpV.push_back(_v2[curIdx2]);
						curIdx2++;
						i++;
						isChanged = true;
						break;
					}
				}

				if (!isChanged)
				{
					tmpV.push_back(_v1[curIdx1]);
					curIdx1++;
					curIdx2++;
					i++;
				}
			}			
		}
	}
	return tmpV;
}

vector<string> mergeSort(vector<string>& _v)
{
	int size = _v.size();
	if (size == 1)
	{
		return _v;
	}
	else
	{
		int m = size / 2;
		vector<string> v1, v2;
		for (int i = 0; i < size; i++)
		{
			if (i < m) v1.push_back(_v[i]);
			else if (i >= m) v2.push_back(_v[i]);
		}
		
		mergeSort(v1);
		mergeSort(v2);
		_v = merge(v1, v2);
		
		return _v;
	}
}


int main()
{
	int N;
	cin >> N;
	vector<string> v;
	for (int i = 0; i < N; i++)
	{
		string input;
		cin >> input;
		v.push_back(input);
	}

	mergeSort(v);

	for (string i : v) cout << i << '\n';
}


// using QuickSort : timelimit

//#include <iostream>
//#include <ctime>
//using namespace std;
//
//
//void swapStr(string& _a, string& _b)
//{
//	string tmp = _a;
//	_a = _b;
//	_b = tmp;
//}
//
//int Randomized_partition(string* _strArr, int _pIdx, int _rIdx)
//{
//	int i = _pIdx - 1;
//	srand((unsigned int)time(NULL));
//	int pivot = rand() % (_rIdx - _pIdx + 1) + _pIdx;
//	swapStr(_strArr[_rIdx], _strArr[pivot]);
//
//	for (int j = _pIdx; j < _rIdx; j++)
//	{
//		if (_strArr[j].length() < _strArr[_rIdx].length())
//		{
//			swapStr(_strArr[++i], _strArr[j]);
//		}
//		else if (_strArr[j].length() == _strArr[_rIdx].length())
//		{
//			for (int f = 0; f < (unsigned int)_strArr[j].length(); f++)
//			{
//				if (_strArr[j][f] < _strArr[_rIdx][f])
//				{
//					swapStr(_strArr[++i], _strArr[j]);
//					break;
//				}
//			}
//		}
//	}
//    swapStr(_strArr[i + 1], _strArr[_rIdx]);
//	return i + 1;
//}
//
//void Randomized_quickSort(string* _strArr, int _pIdx, int _rIdx)
//{
//	if (_pIdx < _rIdx)
//	{
//		int pivot = Randomized_partition(_strArr, _pIdx, _rIdx);
//		Randomized_quickSort(_strArr, _pIdx, pivot - 1);
//		Randomized_quickSort(_strArr, pivot + 1, _rIdx);
//	}
//}
//
//int main()
//{
//	int N;
//	cin >> N;
//	string* strArr = new string[N];
//	for (int i = 0; i < N; i++)
//	{
//		cin >> strArr[i];
//	}
//
//	Randomized_quickSort(strArr, 0, N - 1);
//
//	for (int i = 0; i < N; i++)
//	{
//		cout << strArr[i] << '\n';
//	}
//	delete[] strArr;
//}






