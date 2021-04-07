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
// top�� ���� ���� ���� �ö�´�.
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

	// ������ �ִ� ������ ���̰� ���� �������� ����� �Դ´�.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (pq[i][j].empty()) continue;
			int x = i; int y = j;
			priority_queue<int, vector<int>, greater<int>> temp; // ������ Ŀ���� ���������̴�. 
			int food = 0;

			// �ִ� ��� ������ ����� �������� �õ�
			while (!pq[x][y].empty())
			{
				// ����� ���� �� ������ 
				if (map[x][y] - pq[x][y].top() >= 0)
				{
					// �Դ´�
					map[x][y] -= pq[x][y].top();

					// �������� ������ ��ġ
					if ((pq[x][y].top() + 1) % 5 == 0)
					{
						born.push_back(make_pair(x, y));
					}
					// ���̰� 1 �����ѻ��·� �ٸ� �켱���� ť�� ����
					temp.push(pq[x][y].top() + 1);
				}
				else {
					// ������ ����� �� ������
					food += (pq[x][y].top() / 2);
					// ���� �� ������ ���� ������.
				}
				pq[x][y].pop();
			}

			// pq[x][y]�� ���� ����� ����, ����ִ� ������ �ٽ� �ִ´�.
			while (!temp.empty())
			{
				pq[x][y].push(temp.top());
				temp.pop();
			}
			// ����
			map[x][y] += food;
		}
	}
}

void FallWinter()
{
	// ����
	// ������ ������
	for (auto tree : born)
	{
		int x = tree.first;
		int y = tree.second;

		for (int k = 0; k < 8; k++)
		{
			int nx = x + dx[k];
			int ny = y + dy[k];
			// ���� ����� out
			if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
			// �ȹ���� ���� 1¥�� ���� �߰�
			pq[nx][ny].push(1);
		}
	}

	// �ܿ�
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			// ��� �߰�
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
