#include <bits/stdc++.h>
using namespace std;

int r,c,t;
int house[50][50] = { 0, }; 

int dir_y[4] = {-1,0,1,0}; // 방향순서를 바꿔서 순서대로 읽어들이는 방법이있고 
int dir_x[4] = {0,-1,0,1};
// 인덱스를 조작해서 하는 방법이 있다. 가령 시계방향은 위의 방향변수에서 3 2 1 0 순이고 반시계방향의 인덱스는 3012 순이다.
int c[4]  = {3,2,1,0}; // 이 배열은 방향 인덱스들을 모아놓은 것이다. 그래서 방향이 바뀔 때 이 배열의 값을 넣어주기만하면 차례로 인덱스가 증가하면 방향을 시계 혹은 반시계 90도로 돌아간다. 
int rc[4] = {3,0,1,2};//  반시계 방향 인덱스들을 모아놓은 것이다.  
int temp[50][50] = {0,};
int temp1[50][50] = {0,};
int temp2[50][50] = {0,};
struct info{
	int y,x;
};
vector <info> aircon;
void spread_dust(int y,int x){
	
	int cur_y = y;
	int cur_x = x;
	int cnt= 0;
	int m = house[cur_y][cur_x] / 5;
	for(int i=3;i>=0;i--){
		int ny = cur_y +dir_y[i];
		int nx = cur_x + dir_x[i];
		if(ny< 0 || nx < 0 || ny >=r || nx >= c || house[ny][nx] == -1)continue;
		temp[ny][nx] +=m;
		cnt++;
	}
	temp[cur_y][cur_x] += house[cur_y][cur_x] - ( m * cnt);
	
}
void On_Aircon1(){
  	int cur_y = aircon[0].y ;
    int cur_x = aircon[0].x + 1;  
	for(int i=0;i<4;i++){
		while(1){
			
			int ny = cur_y + dir_y[rc[i]];
	      	int nx = cur_x + dir_x[rc[i]];
	      	if(ny < 0 || nx < 0 || ny >= r || nx >=c) break;
	    	if(temp[ny][nx] == -1) 
	    	{
	    		temp1[ny][nx] = -1;
	    		break;
			}
			temp1[ny][nx] = temp[cur_y][cur_x]; // 아.. 이러면 기존에 있던 원본 집을 옮기는 꼴;;;;; 새로운 임시배열에다가 먼지가 퍼져있던 배열가지고 해야하는데...이런실수...
			 // 아니면 temp임시변수를 참조변수로해서 계속  
		
			cur_y = ny;
			cur_x = nx;
		}
	}
}
void On_Aircon2(){
  	int cur_y = aircon[1].y ;
    int cur_x = aircon[1].x + 1;  
	for(int i=0;i<4;i--){  
		while(1){
			
			int ny = cur_y + dir_y[c[i]];// 변수 하나로 두개의 방식으로 나눠지는 
	      	int nx = cur_x + dir_x[c[i]];
	      	if(ny < 0 || nx < 0 || ny >= r || nx >=c) break;
	    	if(temp[ny][nx] == -1) 
	    	{
	    		temp1[ny][nx] = -1;
	    		break;
			}
			temp1[ny][nx] = temp[cur_y][cur_x]; // 아.. 이러면 기존에 있던 원본 집을 옮기는 꼴;;;;; 새로운 임시배열에다가 먼지가 퍼져있던 배열가지고 해야하는데...이런실수...
			 // 아니면 temp임시변수를 참조변수로해서 계속  
		
			cur_y = ny;
			cur_x = nx;
		}
	}
}
void solve(){
	for(int i = 0; i <  r ; i++){
		for(int j = 0; j < c ; j++){
			if(house[i][j]){
				spread_dust(i,j);
			}
			if(house[i][j] == -1)temp[i][j] = -1; 
			
		}
	}
	//memcpy(house,temp,sizeof(house));
	//memcpy(temp,temp1,sizeof(temp)); // 이런 복사 시간을 줄이고 메모리 공간을 확보해서 하는 것이 좋다. 
	
	On_Aircon1();
	On_Aircon2();
	for(int i=1;i<aircon[0].y;i++){
		for(int j=1;j<c-1;j++){
			temp1[i][j] = temp[i][j];			
		}
	}
	for(int i=aircon[1].y+1;i<r-1;i++){
		for(int j=1;j<c-1;j++){
			temp1[i][j] = temp[i][j];			
		}
	}
	memcpy(house,temp1,sizeof(house)); // 마지막 집에 있는 미세먼지들을 셋팅하고 그 뒤에 임시변수들은 리셋해주어야 다음 계산을 또 먼지퍼지게하고 공기청정기작동해서 미세먼지를 밀어낸다. 
	memcpy(temp,temp2,sizeof(temp2)); // 모두 초기화시켜줘야한다. 
	memcpy(temp1,temp2,sizeof(temp2)); // temp변수는 계속 비워줘야한다. 계속 동시에 퍼지는 것을 정보훼손으로 방지하기 위해 houes원본을 임시변수로 옮겨야한다. 
}

int main(){
	int sum= 0;
	cin >> r >> c >> t;
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			cin >> house[i][j];	
			if(house[i][j] == -1){
				aircon.push_back({i,j});
			}
		}
	}
	while(t--){
		solve();
	}
	//cout << endl << endl;
	
	
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			//cout << house[i][j] << " ";
			if(house[i][j] == -1) continue;
			sum += house[i][j];			
		}
		//cout << endl;
	}
	//cout << endl ;
	
	cout << sum;
}
