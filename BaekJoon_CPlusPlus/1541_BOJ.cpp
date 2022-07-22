// 백준 1541번 잃어버린 괄호

// input: 숫자와 +, -로만 이루어진 식 (길이 <=50)
//		  연속해서 두 개 이상의 연산자가 나타나지 않으며, 5자리보다 많은 숫자는 없다.

// condition: 괄호를 적절히 쳐서 이 식의 값을 최소로 만들어야 한다.

// 식의 값이 최소가 되려면 - 값이 가장 커야한다.
// 즉, 연산자 -를 만나면 다음 -가 나올 때까지 +연산을 하고 그 값을 -한다.
// -(a + b + c + ...) -

#include <iostream>
using namespace std;

void initiateArrForMakingNum(int* _arr, int _size = 5)
{
	for (int i = 0; i < _size; i++)
		_arr[i] = -1;
}

int powInt(int _x, int _y)
{
	int result = 1;
	for (int i = 0; i < _y; i++)
		result *= _x;
	return result;
}

int main()
{
	string formula;
	cin >> formula;


	int total = 0;
	int tempSumForSubproblem = 0;

	// making number
	int number = 0;
	int numberCnt = -1;
	int arrForMakingNum[5];
	initiateArrForMakingNum(arrForMakingNum);

	for (int i = formula.length() - 1; i >= 0; i--)
	{
		if (formula[i] >= '0' && formula[i] <= '9')
		{
			arrForMakingNum[++numberCnt] = formula[i] - '0';

			if (i == 0) // first Number
			{
				for (int i = 0; i <= numberCnt; i++)
				{
					number += powInt(10, i) * arrForMakingNum[i];
				}
				total += (number + tempSumForSubproblem);
			}
		}
		else  // operator
		{
			for (int i = 0; i <= numberCnt; i++)
			{
				number += powInt(10, i) * arrForMakingNum[i];
			}

			if (formula[i] == '+')
				tempSumForSubproblem += number;
			else
			{
				total -= (tempSumForSubproblem + number);
				tempSumForSubproblem = 0;
			}


			initiateArrForMakingNum(arrForMakingNum);
			number = 0;
			numberCnt = -1;
		}
	}
	
	cout << total;
}