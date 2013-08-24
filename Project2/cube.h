                                                                     
                                                                     
                                                                     
                                             
#ifndef GUARD_Cube_H
#define GUARD_Cube_H

#include <vector>
#include <tuple>
#include <algorithm>
#include <map>
#include <string>

enum Adj { //Defines quality of each piece with what are adjacent to them, making searching the cube much easier for particular piece
	//use this as reference
	WOG,
	WOB,
	WBR,
	WRG,
	YRB,
	YRG,
	YBO,
	YOG,
	WB,
	WR,
	WO,
	WG,
	OG,
	OB,
	BR,
	RG,
	YR,
	YB,
	YO,
	YG,


	NA //none
};


const int WHITE		=	0;
const int RED		=	1;
const int GREEN		=	2;
const int YELLOW	=	3;
const int ORANGE	=	4;
const int BLUE		=	5;

const int TOP		=	0;
const int FRONT		=	1;
const int LEFT		=	2;
const int BOTTOM	=	3;
const int BACK		=	4;
const int RIGHT		=	5;

class cube
{
//constants
public:
	struct piece{
		int color;
		Adj adj; //adjacent pieces
		piece();
		piece(const piece&);
		piece& operator=(const piece&);
		bool operator==(const piece&);
		bool operator!=(const piece&);
		friend void reset_cube(); //friend so that it can set s, r, c
	};

	typedef std::vector<std::vector<std::vector<piece>>> box;

	const static int N = 3; // NxNxN cube
	const static int COOR = N + 2; // coordinates will be from 0, N+2
	const static int SIDES = 6;
	std::map<std::string, int> movements;

private:
	box cub; //cube

public:

	cube(); //constructs cube
	~cube();
	cube(const cube &other);
	cube& operator=(const cube& other);
	void setadj(Adj, int, int, int, int, int, int, int, int, int);
	void setadj(Adj, int, int, int, int, int, int);
	void reset_cube(); //resets cube to completed
	void set_movements();
	void showcube();
	void showcubeadj();
	void shuffle_cube();
	void swapfours(piece&, piece&, piece&, piece&);
	void cwise(int);
	void ccwise(int);
	bool checkpiece(int, int, int, int);
	int getcolor(int, int, int);
	piece& findpiece(int, Adj);
	piece& getpiece(int, int, int);

	//moves
	void topc(); //top slice clockwise
	void froc(); //front slice clockwise
	void rigc(); //right slice clockwise
	void botc(); //bottom slice clockwise
	void bacc(); //back slice clockwise
	void lefc(); //left slice clockwise


	void lu(); //left upwards
	void ld(); //left downwards
	void mu(); //middle upwards
	void md(); //middle downwards
	void ru(); //right upwards
	void rd(); //right upwards
	void nl(); //north left
	void nr(); //north right
	void el(); //equator left
	void er(); //equator right
	void sl(); //south right
	void sr(); //south left
	void fc(); //front clockwise
	void fa(); //front counterclockwise
	void ic(); //inbetween clockwise
	void ia(); //inbetween counterclockwise
	void bc(); //back clockwise
	void ba(); //back counterclockwise


	void domove(int);
	void domove(std::string);


	// algorithm to solve

	void bottomcross();
	void settopcross();
	void settopcorners();
	

};


#endif
