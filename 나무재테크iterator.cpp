#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 11
#define FOR(i,n) for(int i =1;i<=n;i++)

using namespace std;
int N;
int A[MAX][MAX]; //겨울마다 제공되는 양분 
vector<int> trees[MAX][MAX];
pair<int, int > dir[8] = { {-1,0},{0,1},{1,0},{0,-1},{-1,1},{-1,-1},{1,-1},{1,1} };

int go(int K) {
	vector<int> die[MAX][MAX];	//죽은 나무들 
	int food[MAX][MAX];  //현재 양분
	FOR(i, N)
		fill(food[i], food[i] + MAX, 5);
	while (K--) {
		//봄 : 양분 & 나이 먹기  
		FOR(i, N) {
			FOR(j, N) {
				if (trees[i][j].empty()) continue;
				sort(trees[i][j].begin(), trees[i][j].end());
					// 어린 나무들부터 양분을 먹는다고 하였으므로 이런 정렬을 이용한다.. 
				int& fd = food[i][j]; // (i,j)의 현재 양분
				for (auto it = trees[i][j].begin(); it != trees[i][j].end(); it++) {
					if (*it > fd) { // 벡터에서 죽는 나무들을 이렇게 한꺼번에 죽는것으로 표현하였다. 편리하다. 
						die[i][j].resize((int)distance(it, trees[i][j].end())); //die벡터에 메모리 할당 후, 죽은 나무들 복사
						copy(it, trees[i][j].end(), die[i][j].begin());
						trees[i][j].erase(it, trees[i][j].end());//erase 함수// 나머지 나무들은 지워버린다. 죽었으므로  
						break; // 나이순으로 작은것부터 정렬했으므로 더이상양분을 먹지 못하고 나머지 나무들은 죽으므로 그냥 한꺼번에 복붙해서 제동걸었다. 
					}
					fd -= *it;
					(*it)++;
				}
			}
		}

		//여름 : 죽은 나무들의 나이/2만큼 양분에 추가 
		FOR(i, N) {
			FOR(j, N) {
				if (die[i][j].empty()) continue;
				for (auto x : die[i][j]) {
					food[i][j] += x / 2;
				}
				die[i][j].clear();
			}
		}

		//가을 : 나무의 확장 
		FOR(i, N) {
			FOR(j, N) {
				for (auto x : trees[i][j]) {
					if (x % 5 == 0) {
						for (int k = 0; k < 8; k++) {
							int ni = i + dir[k].first;
							int nj = j + dir[k].second;
							if (ni <= 0 || nj <= 0 || ni > N || nj > N) continue;
							trees[ni][nj].push_back(1);
						}
					}
				}
			}
		}

		//겨울 : 양분 제공
		FOR(i, N) {
			FOR(j, N)
				food[i][j] += A[i][j];
		}
	}

	//살아 남은 나무 수 찾기
	int sum = 0;
	FOR(i, N) {
		FOR(j, N) {
			if (trees[i][j].empty()) continue;
			sum += trees[i][j].size();
		}
	}
	return sum;
}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int M, K;
	cin >> N >> M >> K;
	//양분 배열 입력 받음
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			cin >> A[i][j];
	}

	//각 나무 정보 입력 받음 
	for (int i = 1; i <= M; i++) {
		int r, c, old;
		cin >> r >> c >> old;
		trees[r][c].push_back(old);
	}

	cout << go(K) << endl;

	return 0;
}
