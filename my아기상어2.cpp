// 안되는 프로그램이다. 무엇이 문제인가. 


#include <iostream>
#include <queue> 
using namespace std;

int n;
struct FISH{
	int y;
	int x;
	int size;
	int d; 
};
struct SHARK{
	int y;
	int x;
	int size;
	int eat_cnt;
	int d; // 이건 필요없다  
};

SHARK baby;

int sea[21][21] = {0,};
int dy[4] = {0,1,0,-1};
int dx[4] = {1,0,-1,0};

int ans = 0;

int flag  = 1;

void find_fish(){ // 물고기 찾아서 먹는거  
	bool  visited[21][21] = {false,};
	queue <SHARK> q;
	SHARK cur = {baby.y,baby.x,baby.size,baby.eat_cnt,baby.d};
	q.push(cur);
	visited[baby.y][baby.x] = true;
	vector <FISH> candi;
	while(!q.empty()){
		cur = q.front();
		q.pop();
		if(sea[cur.y][cur.x] >=1 && sea[cur.y][cur.x]<=6 && sea[cur.y][cur.x] < baby.size){
			candi.push_back({cur.y,cur.x,sea[cur.y][cur.x],cur.d});
		}
		for(int i=0;i<4;i++){
			
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];
			
			if(ny < 0 || nx < 0 || ny >= n || nx >= n || visited[ny][nx] || sea[ny][nx] > baby.size) continue;
			visited[ny][nx] = true;
			SHARK next = {ny,nx,baby.size,baby.eat_cnt,cur.d+1};
			q.push(next);
			
		}
	}
	if(candi.size() == 0)
	{
		flag = 0;
		return;
	}
	FISH  final_fish = { 0, 0, 0, 987654321 };

	for(int i=0;i<candi.size();i++){ // 여기서 문젠데 무슨 문젠거지.....하...발견;;;; 
	
	
		if(final_fish.d > candi[i].d){ 
		
			final_fish = {candi[i].y,candi[i].x,candi[i].size,candi[i].d};
			
		}
		
		else if(final_fish.d == candi[i].d){
			
			if(final_fish.y > candi[i].y){
			
				final_fish = {candi[i].y,candi[i].x,candi[i].size,candi[i].d};
				
			}
			else if(final_fish.y == candi[i].y && final_fish.x > candi[i].x){
			
				final_fish = {candi[i].y,candi[i].x,candi[i].size,candi[i].d};
				
			}
		}
	}
	sea[baby.y][baby.x] = 0;
	baby.y = final_fish.y;
	baby.x = final_fish.x;
	baby.eat_cnt++;
	
	if(baby.eat_cnt == baby.size){
		baby.size++;
		baby.eat_cnt = 0;
	}	
	
	ans += final_fish.d;
	
	sea[baby.y][baby.x] = 9;
	
	return;
}

int main(){
	cin >> n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin >> sea[i][j];
			if(sea[i][j] == 9){
				baby = {i,j,2,0,0};
			}
		}
	}
	while(flag){
		find_fish();
	} 
	cout << ans ;
	
}
