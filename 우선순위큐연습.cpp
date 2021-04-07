#include <bits/stdc++.h>
using namespace std;

void heapsort(vector <int> &arr){
	priority_queue<int> h;
	for(int i=0;i<arr.size();++i){
		h.push(-arr[i]); // 음수로는 내림차순이 양수로 바뀌면 오름차순으로 된다. 
	}
	while(!h.empty()){
		cout << -h.top(); // 다시 한번 양수로 바꾸면 오름차순으로 바꾼다. 
		h.pop();
	}
}
int main(){
	int n=3;
	vector <int> arr;
	for(int i=0;i<n;++i){
		int x;
		cin >> x;
		arr.push_back(x);
	}
	heapsort(arr);	
	
} 
