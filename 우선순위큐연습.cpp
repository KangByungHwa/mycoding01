#include <bits/stdc++.h>
using namespace std;

void heapsort(vector <int> &arr){
	priority_queue<int> h;
	for(int i=0;i<arr.size();++i){
		h.push(-arr[i]); // �����δ� ���������� ����� �ٲ�� ������������ �ȴ�. 
	}
	while(!h.empty()){
		cout << -h.top(); // �ٽ� �ѹ� ����� �ٲٸ� ������������ �ٲ۴�. 
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
