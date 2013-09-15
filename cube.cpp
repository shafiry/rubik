#include "cube.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <random>
#include <string>

using namespace std;


//do piece

cube::piece::piece(){}

cube::piece::piece(const piece& other) : color(other.color), adj(other.adj){ }

cube::piece& cube::piece::operator=(const cube::piece& other){
	if (this != &other){
		this->color = other.color;
		this->adj = other.adj;
	}
	return *this;
}

bool cube::piece::operator==(const piece& other){
	if(color == other.color && adj == other.adj){
		return true;
	} else {
		return false;
	}
}

bool cube::piece::operator!=(const piece& other){
	return !(*this == other);
}


cube::cube(){
	for(int x = 0; x < COOR; x++){
		vector<vector<piece>> lev2;
		for(int y = 0; y < COOR; y++){
			vector<piece> lev3;
			for(int z = 0; z < COOR; z++){
				piece push;
				push.color = 0;
				push.adj = NA;
				lev3.push_back(push);
			}
			lev2.push_back(lev3);
		}
		cub.push_back(lev2);
	}
	reset_cube();
}

cube::~cube(){
}

cube::cube(const cube &other) : cub(other.cub){

}

cube& cube::operator=(const cube& other){
	if (this != &other){
		cub = other.cub;
	}
	return *this;
}

void cube::setadj(Adj _adj, int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3){
	cub[x1][y1][z1].adj = cub[x2][y2][z2].adj = cub[x3][y3][z3].adj = _adj;
}

void cube::setadj(Adj _adj, int x1, int y1, int z1, int x2, int y2, int z2){
	cub[x1][y1][z1].adj = cub[x2][y2][z2].adj = _adj;
}

int cube::moves = 0;

void cube::reset_cube(){
	for(int x = 0; x < COOR; x++){
		for(int y = 0; y < COOR; y++){
			for(int z = 0; z < COOR; z++){
				// white side
				if(x == 0){
					cub[x][y][z].color = WHITE;
				} 
				// yellow side
				else if(x == 4){
					cub[x][y][z].color = YELLOW;
				}
				// green side
				else if(y == 0){
					cub[x][y][z].color = GREEN;
				}
				// blue side
				else if(y == 4){
					cub[x][y][z].color = BLUE;
				}
				// red side
				else if(z == 0){
					cub[x][y][z].color = RED;
				}
				// orange side
				else if(z == 4){
					cub[x][y][z].color = ORANGE;
				}
			}
		}
	}
	setadj(WOG,0,1,3,1,1,4,1,0,3);
	setadj(WOB, 0,3,3,1,4,3,1,3,4);
	setadj(WBR,0,3,1,1,4,1,1,3,0);
	setadj(WRG,0,1,1,1,1,0,1,0,1);
	setadj(YRB,3,4,1,3,3,0,4,3,1);
	setadj(YRG,3,1,0,4,1,1,3,0,1);
	setadj(YBO,3,3,4,3,4,3,4,3,3);
	setadj(YOG,3,1,4,3,0,3,4,1,3);
	setadj(WB,0,3,2,1,4,2);
	setadj(WR,0,2,1,1,2,0);
	setadj(WO,1,2,4,0,2,3);
	setadj(WG,0,1,2,1,0,2);
	setadj(OG,2,1,4,2,0,3);
	setadj(OB,2,3,4,2,4,3);
	setadj(BR,2,4,1,2,3,0);
	setadj(RG,2,0,1,2,1,0);
	setadj(YR,3,2,0,4,2,1);
	setadj(YO,3,2,4,4,2,3);
	setadj(YB,3,4,2,4,3,2);
	setadj(YG,3,0,2,4,1,2);


}



void cube::shuffle_cube(){
	int NumOfMoves = 100; // 50 arbitrarily chosen as amount of moves needed to shuffle cube
	for(int i = 0; i < NumOfMoves; i++){
		int move = rand() % 12;
		domove(move);
	}
}

void cube::showcube(){

	for(int i = 0; i < 3; i++){
		cout << setw(5);
		for(int j = 0; j < 3; j++){
			cout << cub[3-i][j+1][4].color;
		}
		cout << endl;
	}
	cout << endl;
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 9; j++){
			if( j < 3){
				cout << cub[3-j][0][3-i].color;
			} else if(j < 6){
				if(j == 3) cout << setw(2);
				cout << cub[0][j % 3 + 1][3-i].color;
			} else {
				if(j == 6) cout << setw(2);
				cout << cub[j%3 + 1][4][3-i].color;
			}
		}
		cout << endl;
	}
	cout << endl;
	for(int i = 0; i < 3; i++){
		cout << setw(5);
		for(int j = 0; j < 3; j++){
			cout << cub[i+1][j+1][0].color;
		}
		cout << endl;
	}
	cout << endl;
	for(int i = 0; i < 3; i++){
		cout << setw(5);
		for(int j = 0; j < 3; j++){
			cout << cub[4][j+1][i+1].color;
		}
		cout << endl;
	}
	cout << endl;
	cout << "--------------------------------------" << endl;
}



void cube::swapfours(piece& a, piece& b, piece& c, piece& d){
	piece temp = d;
	d = c;
	c = b;
	b = a;
	a = temp;
}

void cube::lu(){ //left upards
	for(int i = 0; i < 2; i++){
		swapfours(cub[3][0][1+i], cub[1+i][0][1], cub[1][0][3-i], cub[3-i][0][3]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[4][1][1+i], cub[1+i][1][0], cub[0][1][3-i], cub[3-i][1][4]);
	}
	moves++;
	//cout << "Left ^" << endl;
}

void cube::ld(){ //left downards
	for(int i = 0; i < 2; i++){
		swapfours(cub[3-i][0][3], cub[1][0][3-i], cub[1+i][0][1], cub[3][0][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][1][4], cub[0][1][3-i], cub[1+i][1][0], cub[4][1][1+i]);
	}
	moves++;
	//cout << "Left v" << endl;
}

void cube::ru(){//right upwards
	for(int i = 0; i < 2; i++){
		swapfours(cub[1+i][4][3], cub[3][4][3-i], cub[3-i][4][1], cub[1][4][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours( cub[4][3][1+i],cub[1+i][3][0], cub[0][3][3-i], cub[3-i][3][4]);
	}
	moves++;//cout << "Right ^"<< endl;
}

void cube::rd(){//right downwards
	for(int i = 0; i < 2; i++){
		swapfours(cub[1][4][1+i],  cub[3-i][4][1],cub[3][4][3-i],cub[1+i][4][3] );
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][3][4], cub[0][3][3-i], cub[1+i][3][0], cub[4][3][1+i]);
	}
	moves++;//cout << "Right v"<< endl;
}

void cube::nl(){ //north left
	for(int i = 0; i < 2; i++){
		swapfours(cub[0][1+i][3], cub[0][3][3-i], cub[0][3-i][1], cub[0][1][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[1][1+i][4], cub[1][4][3-i], cub[1][3-i][0], cub[1][0][1+i]);
	}
	moves++;//cout << "Top <-"<< endl;
}

void cube::nr(){ //north right
	for(int i = 0; i < 2; i++){
		swapfours(cub[0][1][1+i], cub[0][3-i][1], cub[0][3][3-i],cub[0][1+i][3]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[1][0][1+i], cub[1][3-i][0], cub[1][4][3-i], cub[1][1+i][4]);
	}
	moves++;//cout << "Top ->"<< endl;
}

void cube::sr(){ //south right
	for(int i = 0; i < 2; i++){
		swapfours(cub[4][3-i][1], cub[4][3][3-i], cub[4][1+i][3],  cub[4][1][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours( cub[3][3-i][0], cub[3][4][3-i], cub[3][1+i][4], cub[3][0][1+i]);
	}
	moves++;//cout << "Bottom ->"<< endl;
}

void cube::sl(){ //south left
	for(int i = 0; i < 2; i++){
		swapfours( cub[4][1][1+i], cub[4][1+i][3],cub[4][3][3-i], cub[4][3-i][1]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3][0][1+i], cub[3][1+i][4], cub[3][4][3-i], cub[3][3-i][0]);
	}
	moves++;//cout << "Bottom <-"<< endl;
}

void cube::fc(){ //front clockwise
	for(int i = 0; i < 2; i++){
		swapfours(cub[1][1+i][0], cub[1+i][3][0], cub[3][3-i][0], cub[3-i][1][0]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[0][1+i][1], cub[1+i][4][1], cub[4][3-i][1], cub[3-i][0][1]);
	}
	moves++;//cout << "Front clockwise" << endl;
}

void cube::fa(){ //front counterclockwise
	for(int i = 0; i < 2; i++){
		swapfours( cub[3-i][1][0], cub[3][3-i][0], cub[1+i][3][0], cub[1][1+i][0]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][0][1],  cub[4][3-i][1],cub[1+i][4][1], cub[0][1+i][1]);
	}
	moves++;//cout << "Front counterclockwise" << endl;
}

void cube::ba(){ //back counterclockwise while facing front
	for(int i = 0; i < 2; i++){
		swapfours(cub[1][1+i][4], cub[1+i][3][4], cub[3][3-i][4], cub[3-i][1][4]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[0][1+i][3], cub[1+i][4][3], cub[4][3-i][3], cub[3-i][0][3]);
	}
	moves++;//cout << "Back counterclockwise (using front as reference for direction)" << endl;
}

void cube::bc(){ //back clockwise while facing front
	for(int i = 0; i < 2; i++){
		swapfours(cub[3-i][1][4], cub[3][3-i][4], cub[1+i][3][4], cub[1][1+i][4]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][0][3], cub[4][3-i][3], cub[1+i][4][3], cub[0][1+i][3]);
	}
	moves++;//cout << "Back clockwise (using front as reference for direction)" << endl;
}

void cube::mu(){//middle upwards
	for(int i = 0; i < 3; i++){
		swapfours(cub[4][2][3-i], cub[3-i][2][0], cub[0][2][1+i], cub[1+i][2][4]);
	}
	moves++;//cout << "Middle(between left and right) upwards" << endl;
}
void cube::md(){ //middle downwards
	for(int i = 0; i < 3; i++){
		swapfours(cub[1+i][2][4], cub[0][2][1+i], cub[3-i][2][0], cub[4][2][3-i]);
	}
	moves++;//cout << "Middle(between left and right) downwards" << endl;
}


void cube::el(){//equator left
	for(int i = 0; i < 3; i++){
		swapfours(cub[2][0][3-i], cub[2][3-i][4], cub[2][4][1+i], cub[2][1+i][0]);
	}
	moves++;//cout << "Equator(between top and bottom) leftwards" << endl;
}

void cube::er(){ //equator right
	for(int i = 0; i < 3; i++){
		swapfours(cub[2][1+i][0], cub[2][4][1+i], cub[2][3-i][4], cub[2][0][3-i]);
	}
	moves++;//cout << "Equator(between top and bottom) rightwards" << endl;
}

void cube::ic(){ //inbetween front and back clockwise
	for(int i = 0; i < 3; i++){
		swapfours(cub[0][1+i][2], cub[1+i][4][2], cub[4][3-i][2], cub[3-i][0][2]);
	}
	moves++;//cout << "inbetween (front and back) clockwise" << endl;
}
void cube::ia(){//inbetween counterclockwise
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][0][2], cub[4][3-i][2], cub[1+i][4][2], cub[0][1+i][2]);
	}
	moves++;//cout << "inbetween (front and back) counterclockwise" << endl;
}

void cube::domove(int b){
	switch(b){
	case(0):
		lu();
		break;
	case(1):
		ld();
		break;
	case(2):
		ru();
		break;
	case(3):
		rd();
		break;
	case(4):
		nl();
		break;
	case(5):
		nr();
		break;
	case(6):
		sl();
		break;
	case(7):
		sr();
		break;
	case(8):
		fc();
		break;
	case(9):
		fa();
		break;
	case(10):
		bc();
		break;
	case(11):
		ba();
		break;
	default:
		break;
	}
}





// algorithm to solve cube:


void cube::solve_cube(){
	settopcross();
	settopcorners();
	setmidpieces();
	setbottomcorners();
	setupbottom();
	finishcube();
}

array<int,3> cube::findpiece(int colour, Adj findadj){
	for(int i = 0; i < N+2; i++){
		for(int j = 0; j < N+2; j++){
			for(int k = 0; k < N+2; k++){
				if(cub[i][j][k].adj == findadj && cub[i][j][k].color == colour){
					array<int, 3> ret = {{i,j,k}};
					return ret;
				}
			}
		}
	}
	throw domain_error("no piece exists");
}



void cube::movecubeleft(){
	nl();el();sl();
}


void cube::dotopcrossmove(int color, Adj adj){
	int xto = 0, yto = 2, zto = 1;
	while(!(cub[xto][yto][zto].color == color && cub[xto][yto][zto].adj == adj)){
		array<int,3> coors = findpiece(color, adj);
		if(coors[0] == 0){ //on correct side
			if(coors[1] == 1){
				ld();
			} else if(coors[1] == 2){
				ba();
			} else if (coors[1] == 3){
				rd();
			}
		} else if(coors[0] == 1){ // upper row
			if(coors[1] == 2 && coors[2] == 0){
				md();sl();sl();mu();sl();md();sr();mu();
			} else if(coors[1] == 0){
				ld();
			} else if(coors[1] == 2){
				ba();
			} else if(coors[1] == 4){
				rd();
			}
		}
		else if(coors[0] == 2){ // middle row
			while(cub[2][3][0].adj != adj)
				el();
			if(cub[2][3][0].color == color){
				er();fc();el();fa();
			} else {
				er();fa();el();el();fc();
			}
		}
		else{
			while(cub[3][2][0].adj != adj)
				sl();
			if(cub[3][2][0].color == color){
				sl();md();sr();mu();
			} else {
				md();sl();sl();mu();
			}
		}
	}
}



void cube::settopcross(){
	dotopcrossmove(WHITE,WR);
	movecubeleft();
	dotopcrossmove(WHITE,WB);
	movecubeleft();
	dotopcrossmove(WHITE,WO);
	movecubeleft();
	dotopcrossmove(WHITE,WG);
	movecubeleft();
}

void cube::dotopcornermove(int color, Adj adj){
	int xto = 0, yto = 3, zto = 1;
	while(!(cub[xto][yto][zto].color == color && cub[xto][yto][zto].adj == adj)){
		array<int,3> coors = findpiece(color, adj);
		if(coors[0] == 0 || coors[0] == 1){ //on top corners
			if(cub[0][1][1].adj == adj){
				ld();sr();lu();
			} else if(cub[0][1][3].adj == adj){
				lu();sl();ld();
			} else if(cub[0][3][3].adj == adj){
				ru();sr();rd();
			}
		} else { // on bottom corners
			while(cub[3][3][0].adj != adj){
				sr();
			}
			if(cub[3][3][0].color == color){
				sl();rd();sr();ru();
			} else if(cub[4][3][1].color == color){
				rd();sr();ru();sr();sr();rd();sl();ru();
			} else{
				rd();sl();ru();
			}
		}
	}
}

void cube::settopcorners(){
	dotopcornermove(WHITE,WBR);
	movecubeleft();
	dotopcornermove(WHITE,WOB);
	movecubeleft();
	dotopcornermove(WHITE,WOG);
	movecubeleft();
	dotopcornermove(WHITE,WRG);
	movecubeleft();
}

void cube::dobtor(){
	sl();rd();sr();ru();sr();fc();sl();fa();
}

void cube::dobtol(){
	sr();ld();sl();lu();sl();fa();sr();fc();
}

void cube::placemids(int frontcol, Adj adj){
	while(cub[2][2][0].color != frontcol){
		el();
	}
	array<int,3> coors = findpiece(frontcol, adj);
	if(coors[0] == 2){
		while(cub[2][3][0].adj != adj){
			el();
		}
		dobtor();
		placemids(frontcol, adj);
	} else {
		while(cub[3][2][0].adj != adj){
			sl();
		}
		if(cub[3][2][0].color == frontcol){
			dobtor();
		} else {
			nl();el();dobtol();er();nr();
		}
	}
}

void cube::setmidpieces(){
	placemids(RED, BR);
	placemids(BLUE, OB);
	placemids(ORANGE, OG);
	placemids(GREEN, RG);

}

array<int, 4> cube::checktopcorns(){
	array<int, 4> ret;
	ret[0] = 1;
	cub[0][3][1].adj == YBO ? ret[1] = 1 : ret[1] = 0;
	cub[0][3][3].adj == YRB ? ret[2] = 1 : ret[2] = 0;
	cub[0][1][3].adj == YRG ? ret[3] = 1 : ret[3] = 0;
	return ret;
}

bool cube::checktopcornsdone(){
	bool ret = false;
	while(cub[0][1][1].adj != YOG){ // YOG -> YBO -> YBR -> YRG
		nl();
	}
	if(cub[0][3][1].adj == YBO && cub[0][3][3].adj == YRB && cub[0][1][3].adj == YRG){
		ret = true;
	}
	return ret;

}

void cube::horswitchbotcorn(){
	lu();nr();ld();fc();nl();fa();lu();nl();ld();nl();nl();
}


void cube::setbottomcorners(){
	lu();lu();mu();mu();ru();ru();
	while(!checktopcornsdone()){
		if(cub[0][3][1].adj != YBO){
			if(cub[0][3][3].adj == YBO){
				nl();
				horswitchbotcorn();
			} else {
				nl();
				nl();horswitchbotcorn();
			}
		} else {
			nl();nl();
			horswitchbotcorn();
			nl();nl();
		}
	}

	while(cub[2][2][0].color != ORANGE)
		el();
	while(cub[3][2][0].color != ORANGE)
		sl();
	while(cub[0][1][1].adj != YOG){
		nl();
	}

}

void cube::overandover(){
	lu();nr();ld();nr();lu();nr();nr();ld();nr();nr();
}

bool cube::checkit(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int x4, int y4, int z4){
	return (cub[x1][y1][z1].color == YELLOW && cub[x2][y2][z2].color == YELLOW && cub[x3][y3][z3].color == YELLOW && cub[x4][y4][z4].color == YELLOW);

}




bool cube::isHorF(){
	int missing = 0;
	for(int i = 1; i < 4; i++){
		for(int j = 1; j < 4; j++){
			if(cub[0][i][j].color != YELLOW){
				missing++;
			}
		}
	}
	if(missing == 2){
		return true;
	} else{
		return false;
	}
}



void cube::setupbottom(){
	int i = 0;
	while(!isHorF()){
		if(i % 16 == 0){
			overandover();nl();
		} else if(i % 4 == 0){
			overandover();
		}
		for(int j = 0; j < 3; j++){

			if(isHorF()){
				break;
			}
			overandover();
			i++;
		}
		nl();
		showcube();
	}

}

bool cube::isbedges(){
	return (cub[0][2][1].adj == YO && cub[0][3][2].adj == YB && cub[0][2][3].adj == YR && cub[0][1][2].adj == YG);
}

void cube::movebedges(){
	fc();fc();nl();rd();ld();fc();fc();lu();ru();nl();fc();fc();
}

void cube::fixbmids(){
	while(!isbedges()){
		if(cub[0][2][1].adj == YO){
			nl();nl();
		} else if(cub[0][3][2].adj == YB){
			nr();
		} else if(cub[0][2][1].adj == YG){
			nl();
		} 
		movebedges();



		while(cub[2][2][0].color != ORANGE)
			el();
		while(cub[3][2][0].color != ORANGE)
			sl();
		while(cub[0][1][1].adj != YOG){
			nl();
		}
	}
}

void cube::finishcube(){
	while(cub[0][3][2].color == YELLOW)
		nl();


	//check if in H or Fish pattern
	if(cub[0][1][2].color != YELLOW){
		//H pattern
		rd();el();rd();rd();el();el();rd();nr();nr();ru();er();er();rd();rd();er();ru();nr();nr();
	} else {
		//fish pattern
		if(cub[0][2][1].color == YELLOW){
			nl();nl();
		}
		fa();lu();rd();el();rd();rd();el();el();rd();nr();nr();ru();er();er();rd();rd();er();ru();nr();nr();ld();fc();
	}
	while(cub[2][2][0].color != ORANGE)
		el();
	while(cub[3][2][0].color != ORANGE)
		sl();
	while(cub[0][1][1].adj != YOG){
		nl();
	}

	fixbmids();

	lu();lu();mu();mu();ru();ru();
}
