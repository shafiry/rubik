#ifndef GUARD_Cube_H
#define GUARD_Cube_H

#include <vector>
#include <array>
#include <algorithm>
#include <string>

enum Adj { //Defines adjacent colors that make up a piece, making searching the cube much easier for particular piece
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

class cube
{
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

	
	//constants
	const static int N = 3; // NxNxN cube
	const static int COOR = N + 2; // coordinates will be from 0, N+2
	int moves; //keeps tracks of how many moves are done

private:
	box cub; //cube
	void setadj(Adj, int, int, int, int, int, int, int, int, int);
	void setadj(Adj, int, int, int, int, int, int);
	void swapfours(piece&, piece&, piece&, piece&);
	std::array<int, 3> findpiece(int, Adj);

public:
	cube(); //constructs cube
	void reset_cube(); //resets cube to completed
	void showcube();
	void shuffle_cube(int NumOfMoves = 100);
	void solve_cube();

	//moves
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
	void movecubeleft();

	// algorithm to solve

	//topcross
	void settopcross();
	void dotopcrossmove(int, Adj);
	void dotopcornermove(int, Adj);

	//top corners
	void settopcorners();

	//mid sides

	void dobtor();
	void dobtol();
	void placemids(int, Adj);
	void setmidpieces();

	//bottom corners
	void horswitchbotcorn();
	bool checktopcornsdone();
	std::array<int,4> checktopcorns();
	void setbottomcorners();
	
	//finishcube
	bool checkit(int, int, int, int, int, int, int, int, int, int, int, int);
	bool isHorF();
	void overandover();
	void setupbottom();
	void fixbmids();
	void movebedges();
	bool isbedges();
	void finishcube();

};


#endif
