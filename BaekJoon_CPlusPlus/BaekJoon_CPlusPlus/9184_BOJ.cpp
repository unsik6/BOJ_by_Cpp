// 백준 9184번 행렬 곱셈

// input: 한 줄씩 -50 <= a, b, c <= 50 입력 (a, b, c)는 정수들
//		  마지막 한줄은 -1, -1, -1; 마지막 한줄을 제외하면 -1, -1, -1은 없음

// condition: 각 줄에 대하여 w(a, b, c) = 결과값 출력
//
//if a <= 0 or b <= 0 or c <= 0, then w(a, b, c) returns:
//1
//
//if a > 20 or b > 20 or c > 20, then w(a, b, c) returns:
//w(20, 20, 20)
//
//if a < band b < c, then w(a, b, c) returns :
//    w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c)
//
//    otherwise it returns :
//w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1)


#include<iostream>
using namespace std;

int main()
{
	int*** cube = new int** [21];
	for (int a = 0; a < 21; a++)
	{
		cube[a] = new int* [21];
		for (int b = 0; b < 21; b++)
		{
			cube[a][b] = new int[21];
			for (int c = 0; c < 21; c++)
			{
				if(a <= 0 || b <= 0 || c <= 0) cube[a][b][c] = 1;
				else if (a < b && b < c)
				{
					cube[a][b][c] = cube[a][b][c - 1] + cube[a][b - 1][c - 1] - cube[a][b - 1][c];
				}
				else
				{
					cube[a][b][c] = cube[a - 1][b][c] + cube[a - 1][b - 1][c] + cube[a - 1][b][c - 1] - cube[a - 1][b - 1][c - 1];
				}
			}
		}
	}

	int a, b, c;
	cin >> a >> b >> c;

	while (!(a == -1 && b == -1 && c == -1))
	{
		cout << "w(" << a << ", " << b << ", " << c << ") = "; 
		if (a <= 0 || b <= 0 || c <= 0)
			a = b = c = 0;
		else if (a > 20 || b > 20 || c > 20)
			a = b = c = 20;
		cout << cube[a][b][c] << '\n';
		cin >> a >> b >> c;
	}

	for (int a = 0; a < 21; a++)
	{
		for (int b = 0; b < 21; b++)
		{
			delete[] cube[a][b];
		}
		delete[] cube[a];
	}
	delete[] cube;
}