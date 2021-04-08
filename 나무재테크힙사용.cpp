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
	
	// ���� ���� ���� ������ �߰�
		heap[++heap_count] = data; // heap_count == 1 
		
		// �Ʒ��� ������ child�� parent�� ���ϸ鼭 �˸��� ��ġ�� �ϳ��� �ø��� �κ�
		
		int child = heap_count;
		int parent = child / 2;
		while (child > 1 && heap[parent] > heap[child]) {
			
			swap(&heap[parent], &heap[child]);
			
			child = parent;
			
			parent = child / 2;
			
		}
	
	}
	
	int heap_pop() {
	
		// ���� ���� ù��° ���Ҹ� ��ȯ
		// ���� ���� �ո� ���� �ִ�!
		int result = heap[1];
		
		// ù��° ���Ҹ� ���� ���� ���� ���ҿ� �ٲٰ�
		// ���� ���� ���� ���� ���� �����̴� heap_count�� �����ش�.
		swap(&heap[1], &heap[heap_count]);
		heap_count--;
		
		// �Ʒ��� ������ child�� parent�� ���ϸ鼭 �˸��� ��ġ�� �ϳ��� ������ �κ�
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
// heap�� ������ ������ ��Ÿ���� ���ÿ� �迭�� ���� �� ���Ҹ� ��Ÿ���� heap�� ���� ��Ÿ���⵵ �մϴ�.
int dy[8] = {0,0,-1,1,-1,-1,1,1}; ///���� ����  
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
				// �� Ǫ���Ǹ� ����� ��� �޶����Ƿ� �����ϴ� �����鸸 ������.
				
				int age = arr[i][j].heap_pop();
				
				if(E[i][j] >= age){
					E[i][j] -= age;
					temp.heap_push( age + 1 );
				}
				
				else {
					sum += (age/2); // �� ĭ�� ���� �������� ���̸� �� ��Ƽ� �Ѳ����� ������� �ش�. 
				} 
	
			}
			//������ ����� �����ֹǷ� �Ѳ����� ó�����ش�. �ٷ� ���⼭
			E[i][j] +=sum;  // �Ѳ����� ������� �ش�. 
			while(temp.size()){ // �� ������ �ѹ����ؼ� �׷��Ű��� ������ �������� 10���������� ��ΰɸ��� �ð� �ʰɸ���. 
				int age2  = temp.heap_pop();
				//cout << "��ǥ y : " << i << " ��ǥ x : " << j << " " << "���� : " << age << endl;
				arr[i][j].heap_push(age2);
				 // ����ִ� ���� �ٽ� �����ɾ��ش�. ���̰� �ϳ� ������ ��������  
			}
		
		}
	}
}
void fall(){
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			HEAP temp;
			int size = arr[i][j].size(); // �̷��� ������ �ι������ʿ����.   
			for(int t=1;t<=size;++t){ // �����͸� ������ ��� ������ ������ ����Ƿ� ���� ����� ���س��� �������� 
				int age = arr[i][j].heap[t];
				if((age % 5) == 0){ // 5�� ����� �ƴϸ� �׳� �ڱ��ڽ��� �ִ� �״�� ������ 5�ǹ���̸� ������ ���� �����Ѵ�. 
					for(int k=0;k < 8;++k){
						int ny = i + dy[k];
						int nx = j + dx[k];
						if( ny < 0 || nx < 0 || ny >= N || nx >= N ) continue;
						arr[ny][nx].heap_push(1); // ���⼭ ���� �������� �ӽú����� ���� �־�����ȴ� �׷� �ᱹ �����ڸ��� ������ ���ܳ��ԵǴ� ���̴�. 
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
