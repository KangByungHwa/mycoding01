#include <cstdio>
#include <algorithm>
using namespace std;

struct COORD {
	COORD() {}
	COORD(int y_, int x_) :y(y_), x(x_) {}
	int y, x;
};
int n;
int A[500][500];
COORD cur;

const int dx[] = { -1,0,1,0 };	//W,S,E,N
const int dy[] = { 0,1,0,-1 };
int dir, dist, ans;

//y, W,S,E,N
const pair<COORD, int> spread[4][10] = 
{ {{COORD(-2,0),2},{COORD(-1,-1),10},{COORD(-1,0),7},{COORD(-1,1),1},{COORD(0,-2),5},{COORD(1,-1),10},{COORD(1,0),7},{COORD(1,1),1},{COORD(2,0),2},{COORD(0,-1),0}} ,
 {{COORD(-1,-1),1},{COORD(-1,1),1},{COORD(0,-2),2},{COORD(0,-1),7},{COORD(0,1),7},{COORD(0,2),2},{COORD(1,-1),10},{COORD(1,1),10},{COORD(2,0),5},{COORD(1,0),0}} ,
 {{COORD(-2,0),2},{COORD(-1,-1),1},{COORD(-1,0),7},{COORD(-1,1),10},{COORD(0,2),5},{COORD(1,-1),1},{COORD(1,0),7},{COORD(1,1),10},{COORD(2,0),2},{COORD(0,1),0}} ,
 {{COORD(1,-1),1},{COORD(1,1),1},{COORD(0,-2),2},{COORD(0,-1),7},{COORD(0,1),7},{COORD(0,2),2},{COORD(-1,-1),10},{COORD(-1,1),10},{COORD(-2,0),5},{COORD(-1,0),0}}
};

int main()
{
	scanf("%d", &n);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			scanf("%d", &A[i][j]);

	cur = COORD((1 + n) / 2, (1 + n) / 2);

	//move
	for (dist = 1; dist < n; ++dist) {

		int iter = 2;

		if (dist == n-1)
			iter = 3;

		for (int j = 1; j <= iter; ++j) {
			for (int k = 1; k <= dist; ++k) {

				COORD next;
				next.x = cur.x + dx[dir];
				next.y = cur.y + dy[dir];

				if (A[next.y][next.x] != 0) {
					//spread
					int sand = A[next.y][next.x];
					A[next.y][next.x] = 0;
					int sumofspreadsand = 0;
					COORD spread_sand;
					for (int i = 0; i < 10; ++i) {
						spread_sand.y = next.y + spread[dir][i].first.y;
						spread_sand.x = next.x + spread[dir][i].first.x;

						int amount = 0;
						if (i < 9) {
							amount = sand * spread[dir][i].second / 100;
							sumofspreadsand += amount;	//sand is blown
						}
						else {
							//for a
							amount = sand - sumofspreadsand;
						}

						if (spread_sand.y<1 || spread_sand.x<1 || spread_sand.y>n || spread_sand.x >n)
						{
							ans += amount;
							continue;
						}
						A[spread_sand.y][spread_sand.x] += amount;
					}
				}
				cur = next;
			}
			dir = (dir + 1) % 4;	//next dir
		}
	}
	
	printf("%d", ans);

	return 0;
}
