/* 백준 7469 k번째 수
*
* Input: 배열의 크기 n과 쿼리 수행 횟수 m (1 <= n <= 100,000, 1 <= m <= 5,000)
*		 arr[i] (0 <= i < n, |arr[i]| < 1e9)
*		 쿼리에 사용할 인자 i, j, k (1<=i<=j<=n, 1<=k<=j-i+1)

* Output: 각 쿼리의 리턴값: arr[i..j]를 정렬했을 때, k번째 수
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define N_MAX 100000

// input
int N, M;
int arr[N_MAX];

// Merge Sort Tree
// 노드에 정렬된 구간이 들어가므로 vector의 배열을 사용
// 사실 엄밀히 따지면 노드의 개수는 2^(ceil(logn)+1)-1이지만
// 보통 낭낭하게 4*N으로 한다고 함 (세그먼트 트리도 동일)
vector<int> tree[N_MAX * 4];

// Merge Sort Tree 만들기
void construct_Merge_Sort_Tree(int _node, int _left, int _right)
{
	// base case
	if (_left == _right)
	{
		tree[_node].push_back(arr[_left]);
	}
	else
	{
		// 현재 구간을 반으로 나눠서 양쪽 서브트리 생성
		int mid = (_left + _right) / 2;
		construct_Merge_Sort_Tree(_node * 2, _left, mid);
		construct_Merge_Sort_Tree(_node * 2 + 1, mid + 1, _right);

		// 현재 노드를 채워야 하므로 사이즈 만들어두기
		tree[_node].resize(tree[_node * 2].size() + tree[_node * 2 + 1].size());

		// algorithm 헤더에 있는 merge 함수
		// merge(first1, last1, first2, last2, output)
		// 각 인자는 Iterator이며, 각 first, last는 합칠 두 구간에 대한 Iter이다. => [first#, last#)
		// outputIterator는 합쳐서 저장할 자료구조의 맨 앞 Iterator
		merge(tree[_node * 2].begin(), tree[_node * 2].end(),
			tree[_node * 2 + 1].begin(), tree[_node * 2 + 1].end(), tree[_node].begin());
	}
}


// 푸는 방법
// 
// 임의의 값에 대하여Merge Sort Tree를 순회하면서
// [i..j]가 조각나는 경우 모든 조각들에서 대하여 그 값이 얼마나 큰지 센다.
// 
// 만약 임의의 값의 순위가 k와 다르면 이분 탐색으로 임의의 값을 찾아간다.
// (임의의 값이 쿼리의 정해와 다르면 순위가 무조건 k와 달라진다.)
// 
// _node: 현재 탐색 중인 노드
// _left, _right: 그 노드의 범위
int query(int _node, int _left, int _right, int _i, int _j, int _mid)
{
	if (_j < _left || _i > _right)	// 범위 초과 (문제와 무관)
		return 0;

	// 찾고자 하는 범위 안에 있는 조각
	if (_i <= _left && _right <= _j)
	{
		return upper_bound(tree[_node].begin(), tree[_node].end(), _mid) - tree[_node].begin();
	}
	
	// 아직도 찾고자 하는 범위를 잘라야 할 때
	int mid_of_Interval = (_left + _right) / 2;
	int leftSide = query(_node * 2, _left, mid_of_Interval, _i, _j, _mid);
	int rightSide = query(_node * 2 + 1, mid_of_Interval + 1, _right, _i, _j, _mid);

	return leftSide + rightSide;
}

int main()
{
	cin >> N >> M;
	for (int n = 0; n < N; n++)
		cin >> arr[n];

	construct_Merge_Sort_Tree(1, 0, N - 1);

	int i, j, k;
	for (int m = 0; m < M; m++)
	{
		cin >> i >> j >> k;
		
		// 임의의 값 범위 (입력값의 범위)
		int left = -1e9, right = 1e9;
		while (left <= right)
		{
			int mid = (left + right) / 2;	// 넣어볼 임의의 값
			
			if (query(1, 0, N - 1, i - 1, j - 1, mid) < k)	// 임의의 값이 더 작다.
				left = mid + 1;
			else // 임의의 값이 찾고자 하는 값보다 크다.
				right = mid - 1;
		}

		cout << left << '\n';
	}
	return 0;
}
