#include <iostream>
#include <time.h>
using namespace std;

void printSolution(int**, int, int);
double mcm(int* _arrP, int _sizeP)
{
	clock_t start, end;
	int n = _sizeP - 1;
	int** m = new int* [n + 1];
	int** s = new int* [n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		m[i] = new int[n + 1];
		s[i] = new int[n + 1];
		m[i][i] = 0;
	}
	
	start = clock();
	for (int l = 2; l <= n; l++)
	{
		for (int i = 1; i <= n - l + 1; i++)
		{
			int j = i + l - 1;
			m[i][j] = -1;
			for (int k = i; k < j; k++)
			{
				int q = m[i][k] + m[k + 1][j] + _arrP[i - 1] * _arrP[k] * _arrP[j];
				if (m[i][j] == -1 || q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
	end = clock();
	/*if(n >= 2) cout << "min = " << m[1][n] << '\n';*/

	/*printSolution(s, 1, n);*/

	for (int i = 0; i < n + 1; i++)
	{
		delete[] m[i];
		delete[] s[i];
	}

	return (double)(end - start);
}

void printSolution(int** _s, int _i, int _j)
{
	if (_i == _j)
	{
		cout << 'A' << _i << ' ';
	}
	else
	{
		cout << "(" << ' ';
		printSolution(_s, _i, _s[_i][_j]);
		printSolution(_s, _s[_i][_j] + 1, _j);
		cout << ")" << ' ';
	}
}

int naiveMCM(int* _arrP, int _strIdx, int _endIdx)
{
	if (_strIdx == _endIdx)
	{
		return 0;
	}
	else
	{
		int min = -1;
		for (int k = _strIdx; k <= _endIdx - 1; k++)
		{
			int cur = naiveMCM(_arrP, _strIdx, k) * naiveMCM(_arrP, k + 1, _endIdx)
				+ _arrP[_strIdx - 1] * _arrP[k] * _arrP[_endIdx];
			if (min == -1 || min > cur)
			{
				min = cur;
			}
		}
		return min;
	}
}

int main()
{
	clock_t  nStart, nEnd;
	int N = 10;
	while (N < 1001)
	{
		cout << "Å©±â: " << N << ' ';
		clock_t sum = 0, nSum = 0;
		int* p = new int[N + 1];
		for (int i = 0; i < 1000; i++)
		{
			srand(time(NULL) + i);
			for (int i = 0; i < N + 1; i++)
			{
				/*cin >> p[i];*/
				p[i] = rand() % N + 1;
			}

			sum += mcm(p, N + 1);

			nStart = clock();
			naiveMCM(p, 1, N);
			nEnd = clock();

			
			clock_t diffNaive = nEnd - nStart;
			nSum += diffNaive;
			/*cout << "\nTEST : " << i << " // " << (double)difference << '\n' << sum << '\n';*/
		}
		cout << "DP = " << (double)sum / 1000 << " // "
			<< "Naive = " << (double)nSum/1000 << '\n';



		int head = N / 10;
		if (N < 20) N++;
		else if (N == 20) N = 50;
		else if (head != 1) N *= 2;
		else N *= 5;
	}	
}