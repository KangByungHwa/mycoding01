#include <stdio.h>
#include <vector>
#pragma warning(disable:4996)

using namespace std;

// ¼­, ³², µ¿, ºÏ
int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { -1, 0, 1, 0 };

int mdx[4][10] = { {-1, 1, -1, 1, -2, 2, -1, 1, 0, 0}, {-1, -1, 0, 0, 0, 0, 1, 1, 2, 1}
				, {-1, 1, -1, 1, -2, 2, -1, 1, 0, 0}, {1, 1, 0, 0, 0, 0, -1, -1, -2, -1} };
int mdy[4][10] = { {1, 1, 0, 0, 0, 0, -1, -1, -2, -1}, {-1, 1, -1, 1, -2, 2, -1, 1, 0, 0}
				, {-1, -1, 0, 0, 0, 0, 1, 1, 2, 1}, {-1, 1, -1, 1, -2, 2, -1, 1, 0, 0} };
int mp[9] = { 1, 1, 7, 7, 2, 2, 10, 10, 5 };

int N = 0;
vector<vector<int>> map;
pair<int, int> wizard_shark;
int answer = 0;

void magic(int r, int c, int d) {
	int val = map[r][c];

	for (int i = 0; i < 9; i++) {
		if (r + mdx[d][i] >= 0 && r + mdx[d][i] < N && c + mdy[d][i] >= 0 && c + mdy[d][i] < N) {
			int temp = map[r][c] * mp[i] / 100;
			map[r + mdx[d][i]][c + mdy[d][i]] += temp;
			val -= temp;
		}
		else {
			int temp = map[r][c] * mp[i] / 100;
			answer += temp;
			val -= temp;
		}
	}

	map[r][c] = 0;

	if (r + mdx[d][9] >= 0 && r + mdx[d][9] < N && c + mdy[d][9] >= 0 && c + mdy[d][9] < N) {
		map[r + mdx[d][9]][c + mdy[d][9]] += val;
	}
	else {
		answer += val;
	}
}

void moving() {
	int d = -1;

	for (int step = 1; step <= N; step++) {
		for (int cnt = 0; cnt < 2 * step; cnt++) {
			if (cnt == 0 || cnt == step) {
				d += 1;

				if (d == 4) {
					d = 0;
				}
			}

			int nR = wizard_shark.first + dx[d];
			int nC = wizard_shark.second + dy[d];

			if (nR == 0 && nC == -1) {
				break;
			}
			else {
				magic(nR, nC, d);
				wizard_shark = make_pair(nR, nC);
			}
		}
	}

	printf("%d", answer);
}

int main() {
	scanf("%d", &N);

	wizard_shark = make_pair(N/2, N/2);

	map.resize(N);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int a = 0;
			scanf("%d", &a);
			map[i].push_back(a);
		}
	}

	moving();

	return 0;
}
