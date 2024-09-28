#pragma once
#include "Piece_types.h"
#include <vector>

class Piece
{
private:
	bool moved_once;
	int type;
	bool capturable;
	int colour;
	static bool King_safe;
	static std::vector<std::pair<int, int>> moves;
public:
	Piece();
	Piece(int type, int colour);//contructor

	int get_type();
	bool hasItMoved();
	int get_colour();
	bool is_capturabe();
	static std::vector<std::pair<int, int>>& getMoves();

	void itMoved();
	void make_Capturable();
	void make_safe();
	void add_to_moves(int y, int x);
	void clean();

	virtual void possible_moves(int y_pos, int x_pos, Piece* board[8][8]) = 0;
	virtual Piece* clone()=0;
	
	//functions to handle the king
	static bool getKingSafety();
	static void make_king_safe();
	static void KingIsINDanger();
};
