#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

#define HEAP_SIZE 50000

struct HEAP{
	int heap[HEAP_SIZE];
	int heap_count = 0;
	
	void swap(int * a, int * b) {
		int tmp = *a; *a = *b; *b = tmp;
	}
	
	void init() {
		heap_count = 0;
	}
	
	int size() {
		return heap_count;
	}

	void heap_push(int data) {
	
	// 힙의 가장 끝에 데이터 추가
		heap[++heap_count] = data; // heap_count == 1 
		
		// 아래의 과정은 child를 parent와 비교하면서 알맞은 위치로 하나씩 올리는 부분
		
		int child = heap_count;
		int parent = child / 2;
		while (child > 1 && heap[parent] > heap[child]) {
			
			swap(&heap[parent], &heap[child]);
			
			child = parent;
			
			parent = child / 2;
			
		}
	
	}
	
	int heap_pop() {
	
		// 힙의 가장 첫번째 원소를 반환
		// 힙의 가장 앞만 보고 있다!
		int result = heap[1];
		
		// 첫번째 원소를 힙의 가장 끝에 원소와 바꾸고
		// 가장 끝은 이제 쓰지 않을 예정이니 heap_count를 내려준다.
		swap(&heap[1], &heap[heap_count]);
		heap_count--;
		
		// 아래의 과정은 child를 parent와 비교하면서 알맞은 위치로 하나씩 내리는 부분
		int parent = 1;
		int child = parent * 2;
		if (child + 1 <= heap_count) {
			child = (heap[child] < heap[child + 1]) ? child : child + 1;
		}
		
		while (child <= heap_count && heap[parent] > heap[child]) {
			swap(&heap[parent], &heap[child]);
		
			parent = child;
			child = child * 2;
			if (child + 1 <= heap_count) {
				child = (heap[child] < heap[child + 1]) ? child : child + 1;
				}
		}
		
		return result;
	} 
};


HEAP arr[10][10];

 // max heap
// heap의 원소의 갯수를 나타냄과 동시에 배열의 가장 끝 원소를 나타내며 heap의 끝을 나타내기도 합니다.
int dy[8] = {0,0,-1,1,-1,-1,1,1}; ///번식 방향  
int dx[8] = {1,-1,0,0,-1,1,-1,1};

int E[10][10];
int A[10][10];

int N,M,K;

void springANDsummer(){
	
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(arr[i][j].size() == 0) continue;
			HEAP temp;
			int sum = 0;
			while(arr[i][j].size()) {
				// 또 푸쉬되면 사이즈가 계속 달라지므로 현존하는 나무들만 돌린다.
				
				int age = arr[i][j].heap_pop();
				
				if(E[i][j] >= age){
					E[i][j] -= age;
					temp.heap_push( age + 1 );
				}
				
				else {
					sum += (age/2); // 그 칸에 죽은 나무들의 나이를 다 모아서 한꺼번에 양분으로 준다. 
				} 
	
			}
			//여름에 양분을 더해주므로 한꺼번에 처리해준다. 바로 여기서
			E[i][j] +=sum;  // 한꺼번에 양분으로 준다. 
			while(temp.size()){ // 이 연산을 한번더해서 그런거같다 나무가 같은곳에 10만개있으면 배로걸리면 시간 너걸린다. 
				int age2  = temp.heap_pop();
				//cout << "좌표 y : " << i << " 좌표 x : " << j << " " << "나이 : " << age << endl;
				arr[i][j].heap_push(age2);
				 // 비어있는 땅에 다시 나무심어준다. 나이가 하나 증가한 나무들을  
			}
		
		}
	}
}
void fall(){
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			HEAP temp;
			int size = arr[i][j].size(); // 이렇게 돌리면 두번돌릴필요없다.   
			for(int t=1;t<=size;++t){ // 데이터를 넣으면 계속 갯수는 변동이 생기므로 따로 사이즈를 정해놓고 돌려야함 
				int age = arr[i][j].heap[t];
				if((age % 5) == 0){ // 5의 배수가 아니면 그냥 자기자신이 있는 그대로 끝나고 5의배수이면 인접한 곳에 번식한다. 
					for(int k=0;k < 8;++k){
						int ny = i + dy[k];
						int nx = j + dx[k];
						if( ny < 0 || nx < 0 || ny >= N || nx >= N ) continue;
						arr[ny][nx].heap_push(1); // 여기서 나온 나무들을 임시변수에 같이 넣어줘버렸다 그럼 결국 같은자리에 나무가 생겨나게되는 것이다. 
					}
				}
			}
			
		}
	}
}
void winter(){
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			E[i][j] +=A[i][j];
			
		}
	}
}

int main(){
	int ans = 0;
	cin >> N >> M >> K;
	
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
		 	cin >> A[i][j];
		 	E[i][j] = 5;
		}
	}
	int y,x,z;
	for(int i=0;i<M;++i){
		cin >> y >> x >> z;
		--y;
		--x;
		
		arr[y][x].heap_push(z);
		
	}
	while(K--){
		springANDsummer();
		fall();
		winter();
	}
	for(int i = 0;i < N; ++i){
		for(int j = 0; j < N; ++j){
			ans += arr[i][j].size();
		}
	}
	cout << ans;
	return 0;

	
}
