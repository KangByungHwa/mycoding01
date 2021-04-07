#include <iostream>
#include <vector>
#include <algorithm>
#define MAX 11
#define FOR(i,n) for(int i =1;i<=n;i++)

using namespace std;
int N;
int A[MAX][MAX]; //�ܿ︶�� �����Ǵ� ��� 
vector<int> trees[MAX][MAX];
pair<int, int > dir[8] = { {-1,0},{0,1},{1,0},{0,-1},{-1,1},{-1,-1},{1,-1},{1,1} };

int go(int K) {
	vector<int> die[MAX][MAX];	//���� ������ 
	int food[MAX][MAX];  //���� ���
	FOR(i, N)
		fill(food[i], food[i] + MAX, 5);
	while (K--) {
		//�� : ��� & ���� �Ա�  
		FOR(i, N) {
			FOR(j, N) {
				if (trees[i][j].empty()) continue;
				sort(trees[i][j].begin(), trees[i][j].end());
					// � ��������� ����� �Դ´ٰ� �Ͽ����Ƿ� �̷� ������ �̿��Ѵ�.. 
				int& fd = food[i][j]; // (i,j)�� ���� ���
				for (auto it = trees[i][j].begin(); it != trees[i][j].end(); it++) {
					if (*it > fd) { // ���Ϳ��� �״� �������� �̷��� �Ѳ����� �״°����� ǥ���Ͽ���. ���ϴ�. 
						die[i][j].resize((int)distance(it, trees[i][j].end())); //die���Ϳ� �޸� �Ҵ� ��, ���� ������ ����
						copy(it, trees[i][j].end(), die[i][j].begin());
						trees[i][j].erase(it, trees[i][j].end());//erase �Լ�// ������ �������� ����������. �׾����Ƿ�  
						break; // ���̼����� �����ͺ��� ���������Ƿ� ���̻����� ���� ���ϰ� ������ �������� �����Ƿ� �׳� �Ѳ����� �����ؼ� �����ɾ���. 
					}
					fd -= *it;
					(*it)++;
				}
			}
		}

		//���� : ���� �������� ����/2��ŭ ��п� �߰� 
		FOR(i, N) {
			FOR(j, N) {
				if (die[i][j].empty()) continue;
				for (auto x : die[i][j]) {
					food[i][j] += x / 2;
				}
				die[i][j].clear();
			}
		}

		//���� : ������ Ȯ�� 
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

		//�ܿ� : ��� ����
		FOR(i, N) {
			FOR(j, N)
				food[i][j] += A[i][j];
		}
	}

	//��� ���� ���� �� ã��
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
	//��� �迭 �Է� ����
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			cin >> A[i][j];
	}

	//�� ���� ���� �Է� ���� 
	for (int i = 1; i <= M; i++) {
		int r, c, old;
		cin >> r >> c >> old;
		trees[r][c].push_back(old);
	}

	cout << go(K) << endl;

	return 0;
}
