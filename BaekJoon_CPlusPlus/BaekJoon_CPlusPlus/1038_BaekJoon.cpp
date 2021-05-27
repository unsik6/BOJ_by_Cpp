// 백준 1038번 감소하는 수

#include <iostream>
#include <cmath>
using namespace std;

int CheckDigit(unsigned long long);
int DigitNumber(unsigned long long, int, int);
long long DecreaseNumber(int);

int main()
{
	int n;
	cin >> n;
	cout << DecreaseNumber(n) << endl;
	return 0;
}

long long DecreaseNumber(int n)
{
	unsigned long long num = 0;
	int count = 0;
	while (count <= n)
	{
		if (num > 9876543210)
			return -1;
		int digit = CheckDigit(num);
		int escapeDigit = -1;
		for (int i = digit; i > 1; i--)
		{
			if (DigitNumber(num, digit, i) <= DigitNumber(num, digit, i - 1))
			{
				escapeDigit = i;
				break;
			}
		}

		if (escapeDigit == -1)
		{
			if (count == n)
				return num;
			count++;
			num++;
		}
		else
		{
			int tmp1 = DigitNumber(num, digit, escapeDigit - 1);
			tmp1 = 10 - tmp1;
			tmp1 = tmp1 * pow(10, escapeDigit - 2);
			num += tmp1;
			escapeDigit == -1;
		}
	}
	return num;
}

int DigitNumber(unsigned long long num, int digit, int curdigit)
{
	for (int i = digit; i >= curdigit; i--)
	{
		unsigned long long tmp = pow(10, i);
		num %= tmp;
	}
	unsigned long long tmp = pow(10, curdigit - 1);
	num /= tmp;

	return num;
}

int CheckDigit(unsigned long long num)
{
	int digit = 0;
	while (num > 0)
	{
		num /= 10;
		digit++;
	}

	return digit;
}