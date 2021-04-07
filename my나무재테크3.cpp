#include <iostream>
#include <algorithm>

#include <vector>

// 역시 시간초과뜬다. for문으로 돌리면 무조건이다. 인덱스로 접근해야한다. // 머지?? 왜 시간초과 안생길까 ???
 
using namespace std;

int N,M,K;

int soil[10][10] =  {0,}; // 머야 5가 리셋이 안되네 그냥 이중포문 돌려야된다. 
int A[10][10] = {0,};

vector <int> arr[10][10]; // 나이를 담는다 한칸에 나무 여러개 담는다.  

int dy[8] = {0,0,-1,1,-1,-1,1,1}; ///번식 방향  
int dx[8] = {1,-1,0,0,-1,1,-1,1};

vector <int> dead[10][10]; // 죽은나무들을 담아놓음  

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
			soil[i][j] += A[i][j]; // 겨울에는 양분을 추가해준다. 
		}
	}
}
void fall(){
	// 살아있는 나무들을 여러곳에 심어주는 작업이다.
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(arr[i][j].empty())continue;
			for(int t=0;t < arr[i][j].size();++t){
				if(arr[i][j][t] %5 !=0) continue; // 5의 배수 나이가 아닌 나무는 통과  
	
		 		for(int k=0;k < 8;++k){ // 각 방향에 나무를 심어준다. 
		 			int ny = i + dy[k]; // 이러면 계속 더해주는 꼭이 되서어 중심에서 돌려야한다. 
		 			int nx = j + dx[k];
		 			if(ny<0||nx<0||ny>=N||nx>=N)continue; // 변수 조심하자 변경해야한다 ny nny nnx nx 
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
				 // 이러면 매번 그 칸에서 죽은나무들을 다 뒤져셔 찾아내야한다.아니면 죽은나무들도 똑같은 2차원배열맵에 그 칸에 심어준다. 
				soil[i][j] += dead[i][j][k]/2;
				//이제 넣어줬으면 비워줘야지  
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
	// 죽은 나무들이 모두 양분으로 들어 갔으면 이제 죽은 나무들의 통을 비워줘야한다.
	dead.clear(); */
}
void spring(){ // 죽은 나무는 바로 토양에 더하면되므로 그냥 여름봄 함께 진행한다. 
		for(int i=0;i<N;++i){
			for(int j=0;j<N;++j){ // 계속 변수실수 많다 이러면 완전 틀린다 디버깅하는데만해도 시간 오래걸린다. 
				int sum = 0; 
				vector <int> alive;
				if(arr[i][j].empty())continue; // 해당칸에 나무가 아예없다면 넘어간다. 
				sort(arr[i][j].begin(),arr[i][j].end(),compare);
				for(int k=0;k < arr[i][j].size();++k){ //그 해당칸의 나무 개수만큼 조사한다.
		 		
		        // 고정된 양분으로 같은 자리에 있는 나무들이 다 흡수해야하므로 토양에 양분을 더하는건 죽은나무들거 다모아서 한꺼번에 더해주어야 한다. 
					if(soil[i][j] >= arr[i][j][k]){
						soil[i][j] -= arr[i][j][k]; // 살수있는 나무는 양분먹고 나이먹고 산다. 
						alive.push_back(arr[i][j][k]+1); // 양분을 먹은 나무는 나이 한살을 더먹고 산다. 
					}
					else {  
						dead[i][j].push_back(arr[i][j][k]);  // 그 칸에 죽은 나무를 기억해둔다.  
					}
					
				}
				arr[i][j].clear(); // 모든 분류가끝났으면 비워줘야한다.다음에 같은 좌표가 나오면 또 돌리게되므로 비워줘야 된다. 
				for(int t = 0; t <  alive.size(); ++t){ // 한칸을 리셋시켜서 살아남은 나무들을 담아주면 그 칸은 작업이 끝이 났다. 
					arr[i][j].push_back(alive[t]); // 살아있는 나무들은 비어있는 칸에 다넣어주면 된다.
				}
			}
		}
}
	

int main(){
	cin >> N >>  M >> K;
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			cin >> A[i][j];        //  입력을 받을때는 입력만 받는다. 
		}
	}	
	
	for(int i=0;i < M;++i){
		int y,x,z;
		cin >> y >> x >> z;
		--y;
		--x;
		arr[y][x].push_back(z);   // 그 2차원배열공간에 나무나이가 담긴 나무를 심음  
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
