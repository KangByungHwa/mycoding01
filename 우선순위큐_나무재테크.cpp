#include <iostream>
#include <vector>
#include <queue>
#define MAX 11
using namespace std;



int n, m, k;
int map[MAX][MAX];
int A[MAX][MAX];
int dx[] = { 1, -1, 0, 0, 1, -1,1 ,-1 };
int dy[] = { 0, 0, 1, -1, 1, -1, -1, 1 };
// top에 가장 작은 수가 올라온다.
priority_queue<int, vector<int>, greater<int>> pq[MAX][MAX];


vector<pair<int, int>> v;
vector<pair<int, int>> born;
void Input()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{

			scanf("%d", &A[i][j]);
			map[i][j] = 5;
		}
	}
	for (int i = 0; i < m; i++)
	{
		int x, y, age;
		scanf("%d %d %d", &x, &y, &age);
		pq[x][y].push(age);
	}

}

void SpringSummer()
{

	// 나무가 있는 곳들은 나이가 적은 나무부터 양분을 먹는다.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pq[i][j].empty()) continue;
			int x = i; int y = j;
			priority_queue<int, vector<int>, greater<int>> temp; // 갈수록 커진다 오름차순이다. 
			int food = 0;

			// 있는 모든 나무가 양분을 먹으려고 시도
			while (!pq[x][y].empty())
			{
				// 양분을 먹을 수 있으면 
				if (map[x][y] - pq[x][y].top() >= 0)
				{
					// 먹는다
					map[x][y] -= pq[x][y].top();

					// 나무들이 번식할 위치
					if ((pq[x][y].top() + 1) % 5 == 0)
					{
						born.push_back(make_pair(x, y));
					}
					// 나이가 1 증가한상태로 다른 우선순위 큐에 저장
					temp.push(pq[x][y].top() + 1);
				}
				else {
					// 여름에 양분이 될 나무들
					food += (pq[x][y].top() / 2);
					// 먹을 수 없으면 전부 빼낸다.
				}
				pq[x][y].pop();
			}

			// pq[x][y]는 전부 비어진 상태, 살아있는 나무를 다시 넣는다.
			while (!temp.empty())
			{
				pq[x][y].push(temp.top());
				temp.pop();
			}
			// 여름
			map[x][y] += food;
		}
	}
}

void FallWinter()
{
	// 가을
	// 번식할 나무들
	for (auto tree : born)
	{
		int x = tree.first;
		int y = tree.second;

		for (int k = 0; k < 8; k++)
		{
			int nx = x + dx[k];
			int ny = y + dy[k];
			// 범위 벗어나면 out
			if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
			// 안벗어나면 나이 1짜리 나무 추가
			pq[nx][ny].push(1);
		}
	}

	// 겨울
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// 양분 추가
			map[i][j] += A[i][j];
		}
	}
}

void Output()
{
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (!pq[i][j].empty())
			{
				ans += pq[i][j].size();
			}
		}
	}
	printf("%d", ans);
}
int main()
{
	Input();
	while (k--)
	{
		born.clear();
		SpringSummer();
		FallWinter();
	}
	Output();

	return 0;
}
