                                                                     
                                                                     
                                                                     
                                             
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
	set_movements();
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


void cube::set_movements(){
	movements["lu"] = 0;
	movements["ld"] = 1;
	movements["mu"] = 2;
	movements["md"] = 3;
	movements["ru"] = 4;
	movements["rd"] = 5;
	movements["nl"] = 6;
	movements["nr"] = 7;
	movements["el"] = 8;
	movements["er"] = 9;
	movements["sl"] = 10;
	movements["sr"] = 11;
	movements["fc"] = 12;
	movements["fa"] = 13;
	movements["ic"] = 14;
	movements["ia"] = 15;
	movements["bc"] = 16;
	movements["ba"] = 17;
}


void cube::shuffle_cube(){
	int NumOfMoves = 100; // 50 arbitrarily chosen as amount of moves needed to shuffle cube
	for(int i = 0; i < NumOfMoves; i++){
		int move = rand() % 18;
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
//	printf(
//"\
//\
//%8i %i %i\n\
//%8i %i %i\n\
//%8i %i %i\n\n\
//\
//%i %i %i  %i %i %i  %i %i %i\n\
//%i %i %i  %i %i %i  %i %i %i\n\
//%i %i %i  %i %i %i  %i %i %i\n\n\
//\
//%8i %i %i\n\
//%8i %i %i\n\
//%8i %i %i\n\n\
//\
//%8i %i %i\n\
//%8i %i %i\n\
//%8i %i %i\n\n\n\n\
//",
//getcolor(3,1,4),getcolor(3,2,4),getcolor(3,3,4),
//getcolor(2,1,4),getcolor(3,1,4),getcolor(3,1,4),
//getcolor(3,1,4),getcolor(3,1,4),getcolor(3,1,4),;
}

void cube::showcubeadj(){

	for(int i = 0; i < 3; i++){
		cout << setw(10) << "";
		for(int j = 0; j < 3; j++){
			cout << setw(3) << cub[3-i][j+1][4].adj;
		}
		cout << endl;
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 9; j++){
			if( j < 3){
				cout << setw(3) << cub[3-j][0][3-i].adj;
			} else if(j < 6){
				if(j == 3) cout << setw(1) << "";
				cout << setw(3) << cub[0][j % 3 + 1][3-i].adj;
			} else {
				if(j == 6) cout << setw(1) << "";
				cout << setw(3) << cub[j%3 + 1][4][3-i].adj;
			}
		}
		cout << endl;
	}
	for(int i = 0; i < 3; i++){
		cout << setw(10) << "";
		for(int j = 0; j < 3; j++){
			cout << setw(3) << cub[i+1][j+1][0].adj;
		}
		cout << endl;
	}
	for(int i = 0; i < 3; i++){
		cout << setw(10) << "";
		for(int j = 0; j < 3; j++){
			cout << setw(3) << cub[4][j+1][i+1].adj;
		}
		cout << endl;
	}
}

#pragma region Movements

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
	cout << "Left ^" << endl;
}

void cube::ld(){ //left downards
	for(int i = 0; i < 2; i++){
		swapfours(cub[3-i][0][3], cub[1][0][3-i], cub[1+i][0][1], cub[3][0][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][1][4], cub[0][1][3-i], cub[1+i][1][0], cub[4][1][1+i]);
	}
	cout << "Left v" << endl;
}

void cube::ru(){//right upwards
	for(int i = 0; i < 2; i++){
		swapfours(cub[1+i][4][3], cub[3][4][3-i], cub[3-i][4][1], cub[1][4][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours( cub[4][3][1+i],cub[1+i][3][0], cub[0][3][3-i], cub[3-i][3][4]);
	}
	cout << "Right ^"<< endl;
}

void cube::rd(){//right downwards
	for(int i = 0; i < 2; i++){
		swapfours(cub[1][4][1+i],  cub[3-i][4][1],cub[3][4][3-i],cub[1+i][4][3] );
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][3][4], cub[0][3][3-i], cub[1+i][3][0], cub[4][3][1+i]);
	}
	cout << "Right v"<< endl;
}

void cube::nl(){ //north left
	for(int i = 0; i < 2; i++){
		swapfours(cub[0][1+i][3], cub[0][3][3-i], cub[0][3-i][1], cub[0][1][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[1][1+i][4], cub[1][4][3-i], cub[1][3-i][0], cub[1][0][1+i]);
	}
	cout << "Top <-"<< endl;
}

void cube::nr(){ //north right
	for(int i = 0; i < 2; i++){
		swapfours(cub[0][1][1+i], cub[0][3-i][1], cub[0][3][3-i],cub[0][1+i][3]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[1][0][1+i], cub[1][3-i][0], cub[1][4][3-i], cub[1][1+i][4]);
	}
	cout << "Top ->"<< endl;
}

void cube::sr(){ //south right
	for(int i = 0; i < 2; i++){
		swapfours(cub[4][3-i][1], cub[4][3][3-i], cub[4][1+i][3],  cub[4][1][1+i]);
	}
	for(int i = 0; i < 3; i++){
		swapfours( cub[3][3-i][0], cub[3][4][3-i], cub[3][1+i][4], cub[3][0][1+i]);
	}
	cout << "Bottom ->"<< endl;
}

void cube::sl(){ //south left
	for(int i = 0; i < 2; i++){
		swapfours( cub[4][1][1+i], cub[4][1+i][3],cub[4][3][3-i], cub[4][3-i][1]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3][0][1+i], cub[3][1+i][4], cub[3][4][3-i], cub[3][3-i][0]);
	}
	cout << "Bottom <-"<< endl;
}

void cube::fc(){ //front clockwise
	for(int i = 0; i < 2; i++){
		swapfours(cub[1][1+i][0], cub[1+i][3][0], cub[3][3-i][0], cub[3-i][1][0]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[0][1+i][1], cub[1+i][4][1], cub[4][3-i][1], cub[3-i][0][1]);
	}
	cout << "Front clockwise" << endl;
}

void cube::fa(){ //front counterclockwise
	for(int i = 0; i < 2; i++){
		swapfours( cub[3-i][1][0], cub[3][3-i][0], cub[1+i][3][0], cub[1][1+i][0]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][0][1],  cub[4][3-i][1],cub[1+i][4][1], cub[0][1+i][1]);
	}
	cout << "Front counterclockwise" << endl;
}

void cube::ba(){ //back counterclockwise while facing front
	for(int i = 0; i < 2; i++){
		swapfours(cub[1][1+i][4], cub[1+i][3][4], cub[3][3-i][4], cub[3-i][1][4]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[0][1+i][3], cub[1+i][4][3], cub[4][3-i][3], cub[3-i][0][3]);
	}
	cout << "Back counterclockwise (using front as reference for direction)" << endl;
}

void cube::bc(){ //back clockwise while facing front
	for(int i = 0; i < 2; i++){
		swapfours(cub[3-i][1][4], cub[3][3-i][4], cub[1+i][3][4], cub[1][1+i][4]);
	}
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][0][3], cub[4][3-i][3], cub[1+i][4][3], cub[0][1+i][3]);
	}
	cout << "Back clockwise (using front as reference for direction)" << endl;
}

void cube::mu(){//middle upwards
	for(int i = 0; i < 3; i++){
		swapfours(cub[4][2][3-i], cub[3-i][2][0], cub[0][2][1+i], cub[1+i][2][4]);
	}
	 cout << "Middle(between left and right) upwards" << endl;
}
void cube::md(){ //middle downwards
	for(int i = 0; i < 3; i++){
		swapfours(cub[1+i][2][4], cub[0][2][1+i], cub[3-i][2][0], cub[4][2][3-i]);
	}
	 cout << "Middle(between left and right) downwards" << endl;
}


void cube::el(){//equator left
	for(int i = 0; i < 3; i++){
		swapfours(cub[2][0][3-i], cub[2][3-i][4], cub[2][4][1+i], cub[2][1+i][0]);
	}
	 cout << "Equator(between top and bottom) leftwards" << endl;
}

void cube::er(){ //equator right
	for(int i = 0; i < 3; i++){
		swapfours(cub[2][1+i][0], cub[2][4][1+i], cub[2][3-i][4], cub[2][0][3-i]);
	}
	 cout << "Equator(between top and bottom) rightwards" << endl;
}

void cube::ic(){ //inbetween front and back clockwise
	for(int i = 0; i < 3; i++){
		swapfours(cub[0][1+i][2], cub[1+i][4][2], cub[4][3-i][2], cub[3-i][0][2]);
	}
	 cout << "inbetween (front and back) clockwise" << endl;
}
void cube::ia(){//inbetween counterclockwise
	for(int i = 0; i < 3; i++){
		swapfours(cub[3-i][0][2], cub[4][3-i][2], cub[1+i][4][2], cub[0][1+i][2]);
	}
	 cout << "inbetween (front and back) counterclockwise" << endl;
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
			mu();
			break;
		case(3):
			md();
			break;
		case(4):
			ru();
			break;
		case(5):
			rd();
			break;
		case(6):
			nl();
			break;
		case(7):
			nr();
			break;
		case(8):
			el();
			break;
		case(9):
			er();
			break;
		case(10):
			sl();
			break;
		case(11):
			sr();
			break;
		case(12):
			fc();
			break;
		case(13):
			fa();
			break;
		case(14):
			ic();
			break;
		case(15):
			ia();
			break;
		case(16):
			bc();
			break;
		case(17):
			ba();
			break;
		default:
			break;
		}
}

void cube::domove(string mover){
	map<string, int>::iterator b = movements.find(mover); //comes from the map<string, int> and goes to movements. Can't put string in switch statement
	if(b != movements.end()){
		domove(b->second);
	}
	else
		cout << "unsuccessful attempt" << endl << endl;
}


#pragma endregion



// algorithm to solve cube:


int cube::getcolor(int x, int y, int z){
	return cub[x][y][z].color;
}

cube::piece& cube::findpiece(int colour, Adj findadj){
	for(int i = 0; i < SIDES; i++){
		for(int j = 0; j < N; j++){
			for(int k = 0; k < N; k++){
				if(cub[i][j][k].adj == findadj && cub[i][j][k].color == colour){
					return cub[i][j][k];
				}
			}
		}
	}
	throw domain_error("no piece exists");
}

cube::piece& cube::getpiece(int s, int r, int c){
	return cub[s][r][c];
}



void cube::bottomcross(){
	//piece *dest = &getpiece(TOP, 2, 1);
	//piece *from = &findpiece(WHITE, WR);
	//while(*dest != *from){
	//	cout << from->side << from->row << from->col << endl;
	//	if(from->side == TOP){
	//		while(*dest != *from){
	//			nl();
	//		}
	//	} else if(from->side == BOTTOM){
	//		//find whether row or column is the edge
	//		while(from->row != 0 && from->col != 1){
	//			sl();
	//		}
	//		md();sl();sl();mu();
	//	} else {
	//		if(from->row == 2){
	//			while(from->side != RED){
	//				sl();
	//			}
	//			sl(); md(); sr(); mu(); //alg to move from adj face up
	//		} else if(from->row == 1){
	//			while(from->side != RED){
	//				el();
	//				showcube();
	//				cout << from->side << endl;
	//			}
	//			if(from->col == 2){ //appears on right side of face
	//				er();fa();el();el();fc();
	//			} else { // appears on left side of face
	//				er();er();fc();el();fa();
	//			}
	//		} else { // appears adjacent to where it has to be
	//			while(from->side != RED){
	//				nl();
	//			}
	//			md(); sl(); sl(); mu(); sl(); md(); sr(); mu();
	//		}
	//	}
	//}
}



void cube::settopcross(){
	bottomcross();
}


void cube::settopcorners(){


}