
#include <iostream>
#include "NVList.hpp"

using std::cout;

int main(){
	ArrayList <int> list({5, 6, 8, 3, 7});
	//cout << list.length;
//	for(int i = 0; i < list.size(); i++){
//		cout << i << " ";
//		list[i] = i+2;
//	}
	for(int i = 0; i < list.length; i++){
		int p = list[i];
		cout << i << "=" << p << "\n";
	}
	list.resize(20);
	cout << "\n";
	for(int x = 0; x < list.length; x++){
		list[x] = rand()%40;
	}
	for(int i = 0; i < list.length; i++){
		int p = list[i];
		cout << i << "=" << p << "\n";
	}
	return 0;
}
