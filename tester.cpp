#include "cube.h"
#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>

using namespace std;

int main(){
	cube *y = new cube();
	y->showcube();
	y->shuffle_cube();
	//y->settopcross();
	y->showcube();
	string b;
	cin >> b;
	while(b != "q"){
		y->domove(b);
		y->showcube();
		cin >> b;
	}
	
	return 0;
}