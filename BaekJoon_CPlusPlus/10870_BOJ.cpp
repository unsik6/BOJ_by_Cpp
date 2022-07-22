// 백준 10870번 피보나치 수 5

// input: 0 <= n <= 20 : 자연수 또는 0

int fibonacci(int n)
{
	if (n == 0) return 0;
	else if (n < 2) return 1;
	else return fibonacci(n - 1) + fibonacci(n - 2);
}

#include <iostream>

int main()
{
	int n;
	std::cin >> n;
	std::cout << fibonacci(n);
}