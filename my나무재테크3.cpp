#include <iostream>
#include <algorithm>

#include <vector>

// ���� �ð��ʰ����. for������ ������ �������̴�. �ε����� �����ؾ��Ѵ�. // ����?? �� �ð��ʰ� �Ȼ���� ???
 
using namespace std;

int N,M,K;

int soil[10][10] =  {0,}; // �Ӿ� 5�� ������ �ȵǳ� �׳� �������� �����ߵȴ�. 
int A[10][10] = {0,};

vector <int> arr[10][10]; // ���̸� ��´� ��ĭ�� ���� ������ ��´�.  

int dy[8] = {0,0,-1,1,-1,-1,1,1}; ///���� ����  
int dx[8] = {1,-1,0,0,-1,1,-1,1};

vector <int> dead[10][10]; // ������������ ��Ƴ���  

int ans = 0;

bool compare(int a, int  b){
	if(a < b){
		return true;
	}
	return false;

}
void winter(){
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			soil[i][j] += A[i][j]; // �ܿ￡�� ����� �߰����ش�. 
		}
	}
}
void fall(){
	// ����ִ� �������� �������� �ɾ��ִ� �۾��̴�.
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(arr[i][j].empty())continue;
			for(int t=0;t < arr[i][j].size();++t){
				if(arr[i][j][t] %5 !=0) continue; // 5�� ��� ���̰� �ƴ� ������ ���  
	
		 		for(int k=0;k < 8;++k){ // �� ���⿡ ������ �ɾ��ش�. 
		 			int ny = i + dy[k]; // �̷��� ��� �����ִ� ���� �Ǽ��� �߽ɿ��� �������Ѵ�. 
		 			int nx = j + dx[k];
		 			if(ny<0||nx<0||ny>=N||nx>=N)continue; // ���� �������� �����ؾ��Ѵ� ny nny nnx nx 
					arr[ny][nx].push_back(1);
		 		}
	
			}
			
		}
	}

}
void summer(){
	
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(dead[i][j].empty())continue;
			for(int k=0;k<dead[i][j].size();++k){
				 // �̷��� �Ź� �� ĭ���� ������������ �� ������ ã�Ƴ����Ѵ�.�ƴϸ� ���������鵵 �Ȱ��� 2�����迭�ʿ� �� ĭ�� �ɾ��ش�. 
				soil[i][j] += dead[i][j][k]/2;
				//���� �־������� ��������  
			}
			dead[i][j].clear(); 
		}
	}
	/*for(int i=0;i<dead.size();++i){
		tree cur = dead[i];
		int ny = cur.y;
		int nx = cur.x;
		soil[ny][nx] += cur.z/2;
		
	}
	// ���� �������� ��� ������� ��� ������ ���� ���� �������� ���� �������Ѵ�.
	dead.clear(); */
}
void spring(){ // ���� ������ �ٷ� ��翡 ���ϸ�ǹǷ� �׳� ������ �Բ� �����Ѵ�. 
		for(int i=0;i<N;++i){
			for(int j=0;j<N;++j){ // ��� �����Ǽ� ���� �̷��� ���� Ʋ���� ������ϴµ����ص� �ð� �����ɸ���. 
				int sum = 0; 
				vector <int> alive;
				if(arr[i][j].empty())continue; // �ش�ĭ�� ������ �ƿ����ٸ� �Ѿ��. 
				sort(arr[i][j].begin(),arr[i][j].end(),compare);
				for(int k=0;k < arr[i][j].size();++k){ //�� �ش�ĭ�� ���� ������ŭ �����Ѵ�.
		 		
		        // ������ ������� ���� �ڸ��� �ִ� �������� �� ����ؾ��ϹǷ� ��翡 ����� ���ϴ°� ����������� �ٸ�Ƽ� �Ѳ����� �����־�� �Ѵ�. 
					if(soil[i][j] >= arr[i][j][k]){
						soil[i][j] -= arr[i][j][k]; // ����ִ� ������ ��и԰� ���̸԰� ���. 
						alive.push_back(arr[i][j][k]+1); // ����� ���� ������ ���� �ѻ��� ���԰� ���. 
					}
					else {  
						dead[i][j].push_back(arr[i][j][k]);  // �� ĭ�� ���� ������ ����صд�.  
					}
					
				}
				arr[i][j].clear(); // ��� �з����������� �������Ѵ�.������ ���� ��ǥ�� ������ �� �����ԵǹǷ� ������ �ȴ�. 
				for(int t = 0; t <  alive.size(); ++t){ // ��ĭ�� ���½��Ѽ� ��Ƴ��� �������� ����ָ� �� ĭ�� �۾��� ���� ����. 
					arr[i][j].push_back(alive[t]); // ����ִ� �������� ����ִ� ĭ�� �ٳ־��ָ� �ȴ�.
				}
			}
		}
}
	

int main(){
	cin >> N >>  M >> K;
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			cin >> A[i][j];        //  �Է��� �������� �Է¸� �޴´�. 
		}
	}	
	
	for(int i=0;i < M;++i){
		int y,x,z;
		cin >> y >> x >> z;
		--y;
		--x;
		arr[y][x].push_back(z);   // �� 2�����迭������ �������̰� ��� ������ ����  
	}
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			soil[i][j] = 5;
		}
	}
	while(K--){
		spring();
		summer(); 
		fall();
		winter();
	}
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(arr[i][j].empty()) continue;
			ans += arr[i][j].size();
		}
	}
	cout << ans;
	
}
