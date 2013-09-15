#include "cube.h"
#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <ctime>

using namespace std;

int main(){
	cube y;
	y.showcube();
	y.shuffle_cube();
	y.showcube();
	time_t t = clock();
	y.solve_cube();
	t = clock() - t;
	y.showcube();
	cout << "Time to solve in milliseconds: " << t << endl;
	cout << "Number of moves: " << y.moves << endl;
	
	return 0;
}
