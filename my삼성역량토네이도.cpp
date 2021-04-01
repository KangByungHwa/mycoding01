#include <iostream>
#include <algorithm>
using namespace std;
#define max 500
int n;
int startx = 0;
int starty = 0;
int dir = 0;
int  sum = 0; 
int sand[max][max] = {0,};
// 이런 2차원배열로 말고 이것도 좌표의 이동으로 나타내면된다.
// 비율이 0인거 말고 나머지 비율은 총 10개 이것을 각방향마다 중심에서 이동하는 인덱스 이동값으로 나타내면된다. 
double spread[5][5] = { // 퍼지는 모래의 비율을 2차원 배열 통째로 담았다. 
{0,     0,    0.02,   0,   0}, // 0.02의 인덱스는 중심에서 -2 , 0이다. 0.07은 -1,0이다. 여튼 이렇게 많은것도 1차원 배열로 담아서 하는 것이 좋다. 
{0,    0.1,   0.07 , 0.01, 0},
{0.05,  0,     0,     0,   0}, // 가운데가 현재 이동해서 도착한 지점이다. 즉 2,2의 위치가. 2,1의 위치는 퍼지고 나머지 모래양이다. 
{0,    0.1,   0.07,  0.01, 0},
{0,     0,    0.02,   0,   0}
}; // 이렇게하면 꼬이긴한다;;;
 
int dy[4] = {0,1,0,-1}; // 첫스타트는 왼쪽 
int dx[4] = {-1,0,1,0};
void input(){
	cin >> n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin >> sand[i][j];
		}
	}	
}
void turn(int d){ // 90 반시계회전. dir은 방향이고 dir에 따라 90도 반시계 회전 횟수가 결정된다. 
//왠만하면 복잡하니 따로 변수를 생성해주는 것이 좋다. 예를 들어 총 모래의 양은 int sand = sand[starty][startx]; 
	int total = sand[starty][startx]; 
	
	if(sand[starty][startx] == 0) return; //모래의 양이 0이면 그냥 더 볼 필요도 없다. 
	double spread1[5][5] = {0,};
	double temp1[5][5] = {0,}; 
	int temp2[max][max] = {0,};
	memcpy(spread1,spread,sizeof(spread)); // 비율을 따로 저장해둔다.
	for(int k=0;k<d;k++){ // 이거 잘못됫다. 
		if(d == 0)break; // 방행이 0이면 안돌리고 그냥 바로 비율계산한다;
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				temp1[i][j] = spread1[j][4-i];
			
			}
		}
		memcpy(spread1,temp1,sizeof(spread1)); // 한번돌리고 난 후 다시 돌리려면 그 값을 저장해놓아야한다. 
	}// 방향대로 돌린다. 90도 반시계회전.
	
	// 머야 쓰레기값이 들어가네. ->  자료형을 맞추어야한다.!!!!!!! double형은 double형이 들어가야한다. 
	
	
	
	int ny = starty-2; // 현재좌표는 모래가 있는 중심이기에 모래비율은 5x5이고 그중심은 2,2 이므로 2를 빼주엇다. 
	int nx = startx-2; 
	// 이제 돌린 걸로 계산시작해서 더한다. 
	
	int plus = 0;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if( i + ny < 0 || j + nx < 0||i + ny >= n || j + nx >= n ){ // 밖으로 나간 모래양도 빼주어야한다. 
				sum += total*spread1[i][j];// 밖으로 벗어난 모래들은 따로 담아준다. 
				plus += total*spread1[i][j];
				continue; // 범위를 벗어나는 모래들은 따로 저장해두고 넘긴다..  더하지못하기 때문이다.
				//비율이 적히지 않고 범위를 벗어난 모래의 이동임. 
			}
			plus += sand[starty][startx]*spread1[i][j];
			temp2[i+ny][j+nx] = total*spread1[i][j]; // 비율이 적힌칸으로 모래가 이동했음 
			sand[i+ny][j+nx] += temp2[i+ny][j+nx];
				
		}
	}
	// total_sum 은 모래가 일정한 비율로 다 퍼진 양의 총합이다.
	if(d ==0 && starty>=0 && startx - 1>=0 && starty < n && startx - 1 < n){ // 아 이건 왼쪽방향만 그런거고;;; 
		sand[starty][startx-1] += sand[starty][startx] - plus; // 남은 모래의 양 계산. 
	}
	else if(d ==1 && starty+1>=0 && startx>=0 && starty+1 < n && startx  < n){ 
		sand[starty+1][startx] += sand[starty][startx] - plus;
	}
	else if(d ==2 && starty>=0 && startx + 1>=0 && starty < n && startx + 1 < n){ 
		sand[starty][startx+1] += sand[starty][startx] - plus;
	}
	else if(d ==3 && starty-1>=0 && startx >=0 && starty-1 < n && startx  < n){  
		sand[starty-1][startx] += sand[starty][startx] - plus;
	}
	else{ // 위의 경우 전부 아니라면 나머지양도 벗어난것이므로 결과값에 더해주어야한다. 
		sum += sand[starty][startx] - plus;
	} 
	sand[starty][startx]  = 0; // 리셋 시켜줘야한다;;;;; 
}
void spread_sand(int d){

	if(d == 0){ // 방향이 왼쪽이면 턴할 필요없이 계산해서 추가한다.
		turn(d);
	}
	else if(d == 1){
		turn(d);
	}
	else if(d == 2){
		turn(d);
	}
	else if(d ==3){
		turn(d);
	}
}
void move(int cnt){// cnt는 몇칸을 이동하느냐이고 한칸이동시 모래가 바로 퍼진다. 
	int ndir = dir%4;
	for(int i=0;i<cnt;i++){
	
		starty += dy[ndir];
		startx += dx[ndir];
		spread_sand(ndir); 
	}
} 
void solve(){
	for(int i=1;i < n;i++){
		move(i); // 맵이 5x5라면 2,2에서 방향이 0부터 시작해서, 1칸이동부터 시작한다. 
		dir++; 
	
		move(i);
		dir++;

	}
	move(n-1);
}
int main(){
	input();
	starty = n/2;
	startx = n/2; // 맵의 중간에서부터 시작한다.

	solve(); 

	cout << sum << endl; 
}
