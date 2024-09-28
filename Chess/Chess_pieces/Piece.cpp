#include "Piece.h"

std::vector<std::pair<int, int>> Piece::moves = {};
bool Piece::King_safe = true;

Piece::Piece()
{
	type = pt::EMPTY;
	capturable = false;
	moved_once = false;
	this->colour = col::WHITE;
}

Piece::Piece(int colour, int type) {
	capturable = false;
	moved_once = false;
	this->colour = colour;
	this->type = type;
}

int Piece::get_type() {
	return type;
}

bool Piece::hasItMoved() {
	return moved_once;
}

int Piece::get_colour() {
	return	colour;
}

bool Piece::is_capturabe() {
	return capturable;
}

void Piece::itMoved() {
	moved_once = true;
}

void Piece::make_Capturable() {
	capturable = true;
}

void Piece::make_safe() {
	capturable = false;
}

std::vector<std::pair<int, int>>& Piece::getMoves() {
	return moves;
}

void Piece::add_to_moves(int y,int x) {
	moves.emplace_back(y,x);
}

void Piece::clean() {
	moves.clear();
}

bool Piece::getKingSafety() {
	return King_safe;
}

 void Piece::make_king_safe() {
	 King_safe = true;
}

 void Piece::KingIsINDanger() {
	 King_safe = false;
}

