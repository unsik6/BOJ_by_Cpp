#include <iostream>
#include <vector>
#include <stack>
#include <utility>
using namespace std;

int N;

int rings[3]{ 0 };

// output
int cnt = 0;
vector<pair<int, int>> seq;

void moveTower(int _n, int _s, int _w, int _d)
{
	if (_n > 1)
	{
		moveTower(_n - 1, _s, _d, _w);
	}

	rings[_s]--;
	rings[_d]++;

	// output
	if(N <= 20)	seq.push_back({ _s + 1, _d + 1 });
	cnt++;

	if (_n > 1)
	{
		moveTower(_n - 1, _w, _s, _d);
	}
}

int main()
{
	cin >> N;
	if (N <= 20)
	{
		moveTower(N, 0, 1, 2);
		cout << cnt << '\n';
		for (int i = 0; i < seq.size(); i++)
			cout << seq[i].first << ' ' << seq[i].second << '\n';
	}
	else
	{
		string ans = "1";
		for (int i = 2; i <= N; i++)
		{
			char over = '0';
			bool first = true;
			for (int j = ans.length() - 1; j >= 0; j--)
			{
				int digit = (ans[j] - '0') * 2;

				if (first)
				{
					digit++;
					first = false;
				}
					

				if (over != '0')
					digit += over - '0';

				ans[j] = (char)(digit % 10 + '0');

				over = (char)(digit / 10 + '0');
			}
			if (over != '0')
				ans.insert(ans.begin(), over);
		}

		cout << ans;
	}
}