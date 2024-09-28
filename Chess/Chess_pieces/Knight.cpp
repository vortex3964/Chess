#include "Knight.h"

Knight::Knight() :Piece() {

}

Knight::Knight(int colour) :Piece(colour, pt::KNIGHT) {

}

void Knight::possible_moves(int y_pos, int x_pos, Piece* board[8][8]) {
	std::vector<std::pair<int, int>> moves = {
		{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
		{1, 2}, {1, -2}, {-1, 2}, {-1, -2}
	};

	for (auto move : moves) {
		int newy = y_pos + move.first;
		int newx = x_pos + move.second;
		if (newx >= 0 && newx < 8 && newy >= 0 && newy < 8) {
			if (board[newy][newx] != nullptr && board[newy][newx]->get_colour() == get_colour()) continue;
			if (board[newy][newx] != nullptr && board[newy][newx]->get_colour() != get_colour()) {
				board[newy][newx]->make_Capturable();
			}
			board[newy][newx]->add_to_moves(newy, newx);
		}
	}
}

Piece* Knight::clone() {
	return new Knight(*this);
}