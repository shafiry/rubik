#include "cube.h"
#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <ctime>

using namespace std;

int main(){
	cube *y = new cube();
	y->showcube();
	y->shuffle_cube();
	y->showcube();
	time_t t = clock();
	y->solve_cube();
	t = clock() - t;
	y->showcube();
	cout << t << endl;
	cout << y->moves;
	
	return 0;
}