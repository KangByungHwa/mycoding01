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
// �̷� 2�����迭�� ���� �̰͵� ��ǥ�� �̵����� ��Ÿ����ȴ�.
// ������ 0�ΰ� ���� ������ ������ �� 10�� �̰��� �����⸶�� �߽ɿ��� �̵��ϴ� �ε��� �̵������� ��Ÿ����ȴ�. 
double spread[5][5] = { // ������ ���� ������ 2���� �迭 ��°�� ��Ҵ�. 
{0,     0,    0.02,   0,   0}, // 0.02�� �ε����� �߽ɿ��� -2 , 0�̴�. 0.07�� -1,0�̴�. ��ư �̷��� �����͵� 1���� �迭�� ��Ƽ� �ϴ� ���� ����. 
{0,    0.1,   0.07 , 0.01, 0},
{0.05,  0,     0,     0,   0}, // ����� ���� �̵��ؼ� ������ �����̴�. �� 2,2�� ��ġ��. 2,1�� ��ġ�� ������ ������ �𷡾��̴�. 
{0,    0.1,   0.07,  0.01, 0},
{0,     0,    0.02,   0,   0}
}; // �̷����ϸ� ���̱��Ѵ�;;;
 
int dy[4] = {0,1,0,-1}; // ù��ŸƮ�� ���� 
int dx[4] = {-1,0,1,0};
void input(){
	cin >> n;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cin >> sand[i][j];
		}
	}	
}
void turn(int d){ // 90 �ݽð�ȸ��. dir�� �����̰� dir�� ���� 90�� �ݽð� ȸ�� Ƚ���� �����ȴ�. 
//�ظ��ϸ� �����ϴ� ���� ������ �������ִ� ���� ����. ���� ��� �� ���� ���� int sand = sand[starty][startx]; 
	int total = sand[starty][startx]; 
	
	if(sand[starty][startx] == 0) return; //���� ���� 0�̸� �׳� �� �� �ʿ䵵 ����. 
	double spread1[5][5] = {0,};
	double temp1[5][5] = {0,}; 
	int temp2[max][max] = {0,};
	memcpy(spread1,spread,sizeof(spread)); // ������ ���� �����صд�.
	for(int k=0;k<d;k++){ // �̰� �߸��̴�. 
		if(d == 0)break; // ������ 0�̸� �ȵ����� �׳� �ٷ� ��������Ѵ�;
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				temp1[i][j] = spread1[j][4-i];
			
			}
		}
		memcpy(spread1,temp1,sizeof(spread1)); // �ѹ������� �� �� �ٽ� �������� �� ���� �����س��ƾ��Ѵ�. 
	}// ������ ������. 90�� �ݽð�ȸ��.
	
	// �Ӿ� �����Ⱚ�� ����. ->  �ڷ����� ���߾���Ѵ�.!!!!!!! double���� double���� �����Ѵ�. 
	
	
	
	int ny = starty-2; // ������ǥ�� �𷡰� �ִ� �߽��̱⿡ �𷡺����� 5x5�̰� ���߽��� 2,2 �̹Ƿ� 2�� ���־���. 
	int nx = startx-2; 
	// ���� ���� �ɷ� �������ؼ� ���Ѵ�. 
	
	int plus = 0;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if( i + ny < 0 || j + nx < 0||i + ny >= n || j + nx >= n ){ // ������ ���� �𷡾絵 ���־���Ѵ�. 
				sum += total*spread1[i][j];// ������ ��� �𷡵��� ���� ����ش�. 
				plus += total*spread1[i][j];
				continue; // ������ ����� �𷡵��� ���� �����صΰ� �ѱ��..  ���������ϱ� �����̴�.
				//������ ������ �ʰ� ������ ��� ���� �̵���. 
			}
			plus += sand[starty][startx]*spread1[i][j];
			temp2[i+ny][j+nx] = total*spread1[i][j]; // ������ ����ĭ���� �𷡰� �̵����� 
			sand[i+ny][j+nx] += temp2[i+ny][j+nx];
				
		}
	}
	// total_sum �� �𷡰� ������ ������ �� ���� ���� �����̴�.
	if(d ==0 && starty>=0 && startx - 1>=0 && starty < n && startx - 1 < n){ // �� �̰� ���ʹ��⸸ �׷��Ű�;;; 
		sand[starty][startx-1] += sand[starty][startx] - plus; // ���� ���� �� ���. 
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
	else{ // ���� ��� ���� �ƴ϶�� �������絵 ������̹Ƿ� ������� �����־���Ѵ�. 
		sum += sand[starty][startx] - plus;
	} 
	sand[starty][startx]  = 0; // ���� ��������Ѵ�;;;;; 
}
void spread_sand(int d){

	if(d == 0){ // ������ �����̸� ���� �ʿ���� ����ؼ� �߰��Ѵ�.
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
void move(int cnt){// cnt�� ��ĭ�� �̵��ϴ����̰� ��ĭ�̵��� �𷡰� �ٷ� ������. 
	int ndir = dir%4;
	for(int i=0;i<cnt;i++){
	
		starty += dy[ndir];
		startx += dx[ndir];
		spread_sand(ndir); 
	}
} 
void solve(){
	for(int i=1;i < n;i++){
		move(i); // ���� 5x5��� 2,2���� ������ 0���� �����ؼ�, 1ĭ�̵����� �����Ѵ�. 
		dir++; 
	
		move(i);
		dir++;

	}
	move(n-1);
}
int main(){
	input();
	starty = n/2;
	startx = n/2; // ���� �߰��������� �����Ѵ�.

	solve(); 

	cout << sum << endl; 
}
