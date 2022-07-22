// 백준 10814번 단어정렬

// input: 1 <= N = 회원수 <= 100,000
//		  N개의 나이와 이름 입력 (입력 순은 가입 순)
//        1 <= 나이 = integer <= 200
//        이름: 알파벳 대소문자 |이름| <= 100

// condition: first) age, second) register date

// using countingSort

#include<iostream>
using namespace std;

struct info
{
	string name = "";
	int age = 0;
};

void swapInfo(info& _a, info& _b)
{
	info tmp = _a;
	_a = _b;
	_b = tmp;
}

void countingSort(info*& _arr, int _size, int _k)
{
	int* countingArr = new int[_k + 1];
	info* resultArr = new info[_size];

	for (int i = 0; i < _k + 1; i++)
	{
		countingArr[i] = 0;
	}
	for (int i = 1; i < _size; i++)
	{
		countingArr[_arr[i].age]++;
	}
	for (int i = 1; i < _k + 1; i++)
	{
		countingArr[i] += countingArr[i - 1];
	}
	for (int i = _size - 1; i >= 1; i--)
	{
		if (countingArr[_arr[i].age] == 0) continue;
		resultArr[countingArr[_arr[i].age]] = _arr[i];
		countingArr[_arr[i].age]--;
	}
	
	_arr = resultArr;
}




int main()
{
	int N;
	cin >> N;
	int size = N + 1;
	info* arr = new info[size];
	for (int i = 1; i < size; i++)
	{
		int age;
		string name;
		cin >> age >> name;
		arr[i].age = age;
		arr[i].name = name;
	}

	countingSort(arr, size, 200);

	for (int i = 1; i < size; i++)
	{
		cout << arr[i].age << ' ' << arr[i].name << '\n';
	}

	delete[] arr;
}