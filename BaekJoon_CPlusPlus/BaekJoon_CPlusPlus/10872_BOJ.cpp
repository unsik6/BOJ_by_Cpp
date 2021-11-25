// 백준 10872번 팩토리얼

// input: 0<= N <= 12

// N! = 479,001,600이므로 int로 해도 된다.

#include <iostream>
using namespace std;
int factorial(int n)
{
	if (n <= 1) return 1;
	else return n * factorial(n - 1);
}
int main()
{
	int n;
	cin >> n;
	cout << factorial(n);
}