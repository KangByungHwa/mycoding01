#include <bits/stdc++.h>
using namespace std;

int r,c,t;
int house[50][50] = { 0, }; 

int dir_y[4] = {-1,0,1,0}; // ��������� �ٲ㼭 ������� �о���̴� ������ְ� 
int dir_x[4] = {0,-1,0,1};
// �ε����� �����ؼ� �ϴ� ����� �ִ�. ���� �ð������ ���� ���⺯������ 3 2 1 0 ���̰� �ݽð������ �ε����� 3012 ���̴�.
int c[4]  = {3,2,1,0}; // �� �迭�� ���� �ε������� ��Ƴ��� ���̴�. �׷��� ������ �ٲ� �� �� �迭�� ���� �־��ֱ⸸�ϸ� ���ʷ� �ε����� �����ϸ� ������ �ð� Ȥ�� �ݽð� 90���� ���ư���. 
int rc[4] = {3,0,1,2};//  �ݽð� ���� �ε������� ��Ƴ��� ���̴�.  
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
			temp1[ny][nx] = temp[cur_y][cur_x]; // ��.. �̷��� ������ �ִ� ���� ���� �ű�� ��;;;;; ���ο� �ӽù迭���ٰ� ������ �����ִ� �迭������ �ؾ��ϴµ�...�̷��Ǽ�...
			 // �ƴϸ� temp�ӽú����� �����������ؼ� ���  
		
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
			
			int ny = cur_y + dir_y[c[i]];// ���� �ϳ��� �ΰ��� ������� �������� 
	      	int nx = cur_x + dir_x[c[i]];
	      	if(ny < 0 || nx < 0 || ny >= r || nx >=c) break;
	    	if(temp[ny][nx] == -1) 
	    	{
	    		temp1[ny][nx] = -1;
	    		break;
			}
			temp1[ny][nx] = temp[cur_y][cur_x]; // ��.. �̷��� ������ �ִ� ���� ���� �ű�� ��;;;;; ���ο� �ӽù迭���ٰ� ������ �����ִ� �迭������ �ؾ��ϴµ�...�̷��Ǽ�...
			 // �ƴϸ� temp�ӽú����� �����������ؼ� ���  
		
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
	//memcpy(temp,temp1,sizeof(temp)); // �̷� ���� �ð��� ���̰� �޸� ������ Ȯ���ؼ� �ϴ� ���� ����. 
	
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
	memcpy(house,temp1,sizeof(house)); // ������ ���� �ִ� �̼��������� �����ϰ� �� �ڿ� �ӽú������� �������־�� ���� ����� �� �����������ϰ� ����û�����۵��ؼ� �̼������� �о��. 
	memcpy(temp,temp2,sizeof(temp2)); // ��� �ʱ�ȭ��������Ѵ�. 
	memcpy(temp1,temp2,sizeof(temp2)); // temp������ ��� �������Ѵ�. ��� ���ÿ� ������ ���� �����Ѽ����� �����ϱ� ���� houes������ �ӽú����� �Űܾ��Ѵ�. 
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
