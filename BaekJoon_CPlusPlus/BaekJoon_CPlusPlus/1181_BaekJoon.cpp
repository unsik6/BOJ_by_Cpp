// 백준 2581번 소수

#include <iostream>
#include <string>
using namespace std;

void arrSwap(string a, string b)
{
	string tmp = a;
	a = b;
	b = tmp;
}

int main()
{
	int N;
	cin >> N;
	string* arr = new string[N];
	int lenOfS = 0;
	int lenOfL = 0;

	// 입력과 동시에 길이 별로 정렬
	for (int i = 0; i < N; i++)
	{
		cin >> arr[i];
		
		// 맨 앞 문자열의 길이
		lenOfS = arr[0].length();
		
		// 만약 맨 앞의 문자열보다 짧다면 arr[i]를 맨 앞으로 옮기고 나머지 한칸 씩 뒤로
		if (arr[i].length() <= lenOfS)
		{
			string tmp = arr[i];
			for (int f = i; f > 0; f--) arr[i] = arr[i-1];
			arr[0] = tmp;
		}
		// 만약 길이가 중간 정도라면
		else if (arr[i].length() < lenOfL && arr[i].length() > lenOfS)
		{
			// 길이가 같은 게 나올 때
			// 그 앞에 넣고 나머지 한 칸씩 뒤로
			for (int k = 0; k < i; k++)
			{
				if (arr[k].length() == arr[i].length())
				{
					string tmp = arr[i];
					for (int f = i; f > k; f--) arr[i] = arr[i - 1];
					arr[k] = tmp;
				}
			}
		}
		// 길이가 제일 길면 상관 없음

		// 맨뒤 길이 넣기
		lenOfL = arr[i].length();
	}

	
	

	for (int i = 0; i < N; i++) cout << arr[i] << endl;
}