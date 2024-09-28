#include "Rook.h"

Rook::Rook() :Piece() {
}

Rook::Rook(int colour) :Piece(colour, pt::ROOK) {

}

void Rook::possible_moves(int y_pos, int x_pos, Piece* board[8][8]) {

	bool found_piece = false;

	//left to right movement ->
	for (int i = x_pos; i < 7 && !found_piece; i++) {

		if (board[y_pos][i + 1] != nullptr && get_colour() == board[y_pos][i + 1]->get_colour()) {
			break;
		}
		if (board[y_pos][i + 1] != nullptr && get_colour() != board[y_pos][i + 1]->get_colour()) {
			found_piece = true;
			board[y_pos][i + 1]->make_Capturable();
		}

		add_to_moves(y_pos, i + 1);


	}
	found_piece = false;

	//right to left ->
	for (int i = x_pos; i > 0 && !found_piece; i--) {

		if (board[y_pos][i - 1] != nullptr && get_colour() == board[y_pos][i - 1]->get_colour()) {
			break;
		}
		if (board[y_pos][i - 1] != nullptr && get_colour() != board[y_pos][i - 1]->get_colour()) {
			found_piece = true;
			board[y_pos][i - 1]->make_Capturable();
		}

		add_to_moves(y_pos, i - 1);
	}


	found_piece = false;

	//up
	for (int i = y_pos; i < 7 && !found_piece; i++) {

		if (board[i + 1][x_pos] != nullptr && get_colour() == board[i + 1][x_pos]->get_colour()) {
			break;
		}
		if (board[i + 1][x_pos] != nullptr && board[i + 1][x_pos]->get_colour() != get_colour()) {
			found_piece = true;
			board[i + 1][x_pos]->make_Capturable();
		}

		add_to_moves(i + 1, x_pos);
	}
	found_piece = false;

	//down
	for (int i = y_pos; i > 0 && !found_piece; i--) {
		
		if (board[i - 1][x_pos] != nullptr && get_colour() == board[i - 1][x_pos]->get_colour()) {
				break;
		}
		if (board[i - 1][x_pos] != nullptr && get_colour() != board[i - 1][x_pos]->get_colour()) {
			found_piece = true;
			board[i - 1][x_pos]->make_Capturable();
		}
		add_to_moves(i - 1, x_pos);
	}
}

Piece* Rook::clone() {
	return new Rook(*this);
}

