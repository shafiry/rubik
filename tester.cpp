#include "cube.h"
#include <iostream>
#include <algorithm>
#include <tuple>
#include <string>
#include <ctime>
#include <sys/time.h>

using namespace std;

int main(){
	cube y;
	y.showcube();
	y.shuffle_cube();
	y.showcube();
	//time_t t = clock();
	timeval start, end;
        gettimeofday(&start, NULL);
	y.solve_cube();
	gettimeofday(&end, NULL);
	//t = clock() - t;
	y.showcube();
	cout << "Time to solve in milliseconds: " << ((end.tv_sec - start.tv_sec)*1000.0)+((end.tv_usec - start.tv_usec)/1000.0) << endl;
	cout << "Number of moves: " << y.moves << endl;
	
	return 0;
}
