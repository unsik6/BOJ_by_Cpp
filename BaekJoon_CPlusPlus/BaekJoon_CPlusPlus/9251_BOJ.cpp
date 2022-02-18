// 백준 9251번 LCS (Long Common Subsequence)

// input: 첫째줄과 둘째둘에 두 문자열이 주어진다. 길이가 최대 1000글자이다.


#include <iostream>
using namespace std;

int main()
{
	string str1, str2;
	cin >> str1 >> str2;
	int len1 = str1.length();
	int len2 = str2.length();

	int** mat = new int* [len1 + 1];
	for (int i = 0; i < len1 + 1; i++)
	{
		mat[i] = new int[len2 + 1];

		if (i == 0)
			for (int f = 0; f < len2 + 1; f++)
				mat[0][f] = 0;
		mat[i][0] = 0;
	}

	for (int i = 1; i < len1 + 1; i++)
	{
		for (int f = 1; f < len2 + 1; f++)
		{
			if (str1[i - 1] == str2[f - 1])
			{
				mat[i][f] = mat[i - 1][f - 1] + 1;
			}
			else if (mat[i - 1][f] >= mat[i][f - 1])
			{
				mat[i][f] = mat[i - 1][f];
			}
			else
				mat[i][f] = mat[i][f - 1];
		}
	}

	cout << mat[len1][len2];


	for (int i = 0; i < len1 + 1; i++)
		delete[] mat[i];
	delete[] mat;
}