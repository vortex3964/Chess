//chess game
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "AudioHelper.h"
#include "ImageHelper.h"
#include "Chess_Pieces/chess_pieces.h"
#include "Promotion.h"

//just en peassant left


void render_pieces(Piece* board[8][8], sf::RenderWindow& window);//renders the pieces on the board
void normalise(sf::Vector2i& mousepos);
bool matches_players_colour(Piece* piece);
void clean();
void print_move(int oldy, int oldx, int newy, int newx, int type,int colour);
void move(int piece_y,int piece_x,int new_y,int new_x);
bool isValidMove(int y, int x);
bool can_capture_opponents_king();
void make_valid_move(Piece* piece,int selected_y , int selected_x);
bool make_the_move(Piece* temp[8][8], int move_y, int move_x, int selected_y, int selected_x);
bool has_moves_left();
void declare_winner();
bool can_castle(int y, int x);

//global variables
bool white_to_move = true;
bool can_move = false;
sf::Vector2i selected_piece;
int total_pieces = 32;//to check if the players are down to just their kings
int fifty_move_rule = 0; //to track the fifty move rule

//helper classes
Audio* audio = new Audio();
Image* image = new Image();

Piece* board[8][8] = {
	{new Rook(col::WHITE),new Knight(col::WHITE),new Bishop(col::WHITE),new Queen(col::WHITE),new King(col::WHITE),new Bishop(col::WHITE),new Knight(col::WHITE),new Rook(col::WHITE)},
	{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},//filled with white pawn later in main
	{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
	{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
	{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
	{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},
	{nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr},//filled with black pawn later in main
	{new Rook(col::BLACK),new Knight(col::BLACK),new Bishop(col::BLACK),new Queen(col::BLACK),new King(col::BLACK),new Bishop(col::BLACK),new Knight(col::BLACK),new Rook(col::BLACK)}
};

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 800), "chess", sf::Style::Close | sf::Style::Titlebar);//create the window

	for (int i = 0; i < 8; i++) {//add the pawns to the board
		board[6][i] = new Pawn(col::BLACK);
		board[1][i] = new Pawn(col::WHITE);
	}
	
	std::cout << "chess moves:\n";
	std::cout << "===============\n";

	sf::Texture chess_board;
	chess_board.loadFromFile("assets/images/Chess_Board.png");
	sf::Sprite sboard;
	sboard.setTexture(chess_board);//the chess board

	sf::Image game_icon;
	game_icon.loadFromFile("assets/images/chess-icon-style-free-vector.jpg");
	window.setIcon(game_icon.getSize().x, game_icon.getSize().y, game_icon.getPixelsPtr());//load the games icon
	
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == e.Closed) {
				window.close();
			}

			if (e.type == e.MouseButtonPressed) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i new_move = sf::Mouse::getPosition(window);
					normalise(new_move);
					if (can_move && isValidMove(new_move.y, new_move.x)) {
						move(selected_piece.y, selected_piece.x, new_move.y, new_move.x);
						Piece::make_king_safe();
						can_move = false;
						clean();//clean after making a move
						if (fifty_move_rule == 50) goto end;
					}
					else if (can_move && selected_piece.x == new_move.x && selected_piece.y == new_move.y) {
						clean();//clean when pressing the same selected piece again
						selected_piece.x = 8;
						selected_piece.y = 8;
						can_move = false;                                                         
					}
					else if (board[new_move.y][new_move.x] != nullptr && matches_players_colour(board[new_move.y][new_move.x])) {
						clean();
						selected_piece.x = new_move.x;
						selected_piece.y = new_move.y;
						
						
						if (!has_moves_left()) goto end;//end the game the lossing side must press on one of their  pieces to triger this 
						make_valid_move(board[new_move.y][new_move.x],new_move.y,new_move.x);//exclude all the illegall moves
						
						if (total_pieces == 2) goto end;
						can_move = true;
					}
					else if (can_move && !isValidMove(new_move.y, new_move.x)) {
						can_move = false;
						clean();//clean when making an inavalid move
					}
					else if (board[new_move.y][new_move.x]==nullptr 
						&& (((new_move.y == 0 && new_move.x == 6) || (new_move.y == 0 && new_move.x == 2))
						|| ((new_move.y == 7 && new_move.x == 6) || (new_move.y == 7 && new_move.x == 2)))
						&& can_castle(new_move.y,new_move.x)) 
					{
						
						int colour = board[new_move.y][4]->get_colour();
						delete board[new_move.y][4];
						board[new_move.y][4] = nullptr;
						if (new_move.x > 4) {
							board[new_move.y][5] = new Rook(colour);
							delete board[new_move.y][7];
							board[new_move.y][7] = nullptr;
							board[new_move.y][6] = new King(colour);
							board[new_move.y][6]->itMoved();
						}
						else {
							board[new_move.y][3] = new Rook(colour);
							delete board[new_move.y][0];
							board[new_move.y][0] = nullptr;
							board[new_move.y][2] = new King(colour);
							board[new_move.y][2]->itMoved();
						}
						audio->playCastle();
						white_to_move = !white_to_move;
					}
					else if (board[new_move.y][new_move.x] == nullptr) {
						clean();//clean when tapping an empty square
						can_move = false;
					}
				}
			}
			
		}
		//draw the window
		window.clear();
		window.draw(sboard);
		render_pieces(board, window);
		window.display();
	}

end:
	//free the allocated memory
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete board[i][j];
		}
	}

	delete audio;
	delete image;
	
	declare_winner();

	std::cout<<("Press Enter to exit...\n");
	getchar(); // wait for user to press enter then exit

	return 0;
}

bool can_castle(int y,int x) {
	
	if (board[y][4]->hasItMoved()) return false;
	int colour = board[y][4]->get_colour();
	
	if (x>4) {
		if (board[y][7] ==nullptr||board[y][7]->hasItMoved()) return false;
		for (int i = 1; i < 3; i++) {
			if (board[y][4 + i] != nullptr) return false;
		}
	}
	else {
		if (board[y][0]==nullptr ||board[y][0]->hasItMoved()) return false;
		for (int i = 1; i < 4; i++) {
			if (board[y][4 - i] != nullptr) return false;
		}
	}

	//its logic is broken
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr && !matches_players_colour(board[i][j])) {
				board[i][j]->possible_moves(i,j,board);
			}
		}
	}

	//bool can_castle = true;
	if (x > 4) {
		for (auto move : Piece::getMoves()) {
			if ((move.first == y && move.second == 5) || (move.first == y && move.second == 6)) {
				clean();
				return false;
			}
		}
	}
	else 
	{
		for (auto move : Piece::getMoves()) {
			if ((move.first == y && move.second == 3) || (move.first == y && move.second == 2) || (move.first == y && move.second == 1)) {
				clean();
				return false;
			}
		}
	}
	
	clean();
	return true;
}

void declare_winner() {
	std::cout << "game ended\n======================================\n";
	if (total_pieces == 2) std::cout << "draw insuficient matterial\n";
	else if (fifty_move_rule == 50) std::cout << "its a draw by 50 move rule\n";
	else if (Piece::getKingSafety()) (white_to_move) ? std::cout << "black won\n" : std::cout << "white won\n";
	else if (!Piece::getKingSafety()) std::cout << "stalemate\n";
}

bool has_moves_left() {
	bool has_a_move = false;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]!=nullptr && matches_players_colour(board[i][j]) ) {
				make_valid_move(board[i][j],i,j);
				if (Piece::getMoves().size() > 0) {
					Piece::getMoves().clear();
					has_a_move = true;
					break;
				}
			}
		}
	}
	return has_a_move;
}

void make_valid_move(Piece* piece, int selected_y, int selected_x) {

	Piece* temp[8][8];

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) {
				temp[i][j] = board[i][j]->clone();
			} 
			else{
				temp[i][j] = nullptr;
			}
		}
	}//create a new board

	temp[selected_y][selected_x]->possible_moves(selected_y, selected_x, temp);//make all the possible moves for that piece
	std::vector<std::pair<int, int>> moves;

	for (auto move : Piece::getMoves()) {
		moves.emplace_back(move);//store all the new moves
	}
	Piece::getMoves().clear();

	for (auto& move : moves) {
		if (!make_the_move(temp,move.first,move.second,selected_y,selected_x)) {
			move = { -1,-1 };
		}//the move is not considered
	}

	// Remove invalid moves and reset the flags of the pieces
	moves.erase(std::remove(moves.begin(), moves.end(), std::make_pair(-1, -1)), moves.end());

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) board[i][j]->make_safe();
		}
	}

	// Replace the valid moves in the piece's move list and if a piece is capturable mark it 
	Piece::getMoves() = moves;
	for (auto move : moves) {
		if (board[move.first][move.second] != nullptr && !matches_players_colour(board[move.first][move.second])) {
			board[move.first][move.second]->make_Capturable();
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete temp[i][j];
		}
	}//free the allocated memory
}

bool make_the_move(Piece* temp[8][8], int move_y, int move_x,int selected_y,int selected_x) {
	bool saved_the_king = true;
	Piece* captured = nullptr;

	if (temp[move_y][move_x] != nullptr) {
		captured = temp[move_y][move_x]->clone();
		delete temp[move_y][move_x];
		temp[move_y][move_x] = nullptr;
	}

	temp[move_y][move_x] = temp[selected_y][selected_x];
	temp[selected_y][selected_x] = nullptr;
	delete temp[selected_y][selected_x];

	Piece::getMoves().clear();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (temp[i][j] != nullptr && !matches_players_colour(temp[i][j])) {
				temp[i][j]->possible_moves(i, j, temp);
			}
		}
	}

	//Check if moving the selected piece puts the king in danger
	for (auto move : Piece::getMoves()) {
		if (temp[move.first][move.second] != nullptr &&
			temp[move.first][move.second]->get_type() == pt::KING &&
			matches_players_colour(temp[move.first][move.second])) {

			saved_the_king = false; // The king is in check
			break; // Exit the loop since we found a check
		}
	}
	
	temp[selected_y][selected_x] = temp[move_y][move_x];// Restore the move

	if (captured != nullptr) {
		temp[move_y][move_x] = captured; // Restore the captured piece
	}
	else {
		temp[move_y][move_x] = nullptr; // Set to null if nothing was captured
	}
	return	saved_the_king;
}

bool can_capture_opponents_king() {
	bool val = false;
	Piece::getMoves().clear();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] !=nullptr && matches_players_colour(board[i][j])) {
				switch (board[i][j]->get_type()) {
				case pt::KING:
					break;//a king could never capture an enemy king
				default:
					board[i][j]->possible_moves(i, j, board);
					break;
				}
			}
		}
	}

	for (auto& move : Piece::getMoves()) {
		if (board[move.first][move.second] != nullptr && board[move.first][move.second]->get_type() == pt::KING && !matches_players_colour(board[move.first][move.second])) {
			val = true;
			Piece::KingIsINDanger();
			audio->playCheck();
			break;
		}
	}
	Piece::getMoves().clear();
	return val;
}

void print_move(int oldy, int oldx, int newy, int newx, int type,int colour) {
	char col = (colour) ? col = 'w' : col = 'b';
	std::string move;
	move+= col;
	switch (type) {
	case pt::KING:
		move += 'K';
		break;
	case pt::ROOK:
		move += 'R';
		break;
	case pt::BISHOP:\
		move += 'B';
		break;
	case pt::QUEEN:
		move += 'Q';
		break;
	case pt::KNIGHT:
		move += "Kn";
		break;
	}

	switch (oldx) {
	case 0:
		move += "a";
		break;
	case 1:
		move += "b";
		break;
	case 2:
		move += "c";
		break;
	case 3:
		move += "d";
		break;
	case 4:
		move += "e";
		break;
	case 5:
		move += "f";
		break;
	case 6:
		move += "g";
		break;
	case 7:
		move += "h";
		break;
	}
	move += std::to_string(oldy+1);
	move += " ";
	switch (newx) {
	case 0:
		move += "a";
		break;
	case 1:
		move += "b";
		break;
	case 2:
		move += "c";
		break;
	case 3:
		move += "d";
		break;
	case 4:
		move += "e";
		break;
	case 5:
		move += "f";
		break;
	case 6:
		move += "g";
		break;
	case 7:
		move += "h";
		break;
	}
	move += std::to_string(newy+1);
	std::cout << move << "\n";
}

bool isValidMove(int y,int x) {
	bool exists = false;
	int i = 0;
	while (!exists && i < Piece::getMoves().size()) {
		if (Piece::getMoves().at(i).first == y && Piece::getMoves().at(i).second == x) {
			exists = true;
		}
		i++;
	}
	return exists;
}

void move(int piece_y, int piece_x, int new_y, int new_x) {
	
	if (board[selected_piece.y][selected_piece.x]!=nullptr && Pawn::exists &&
		board[selected_piece.y][selected_piece.x]->get_type() == pt::PAWN &&
		(new_y==Pawn::y+1||new_y==Pawn::y-1)&&(new_x == Pawn::x))
	{
		delete board[Pawn::y][Pawn::x];
		board[Pawn::y][Pawn::x] = nullptr;
	    audio->playEnPassant();
		total_pieces--;
		fifty_move_rule = 0;
	}
	else if (board[new_y][new_x] != nullptr) {
		delete board[new_y][new_x];
		board[new_y][new_x]=nullptr;
		audio->playCapture();
		total_pieces--;
		fifty_move_rule = 0;
	}
	else {
		audio->playMove();
		fifty_move_rule++;
	}
	
	Pawn::colour = -1;
	Pawn::x = -1;
	Pawn::y = -1;//erase the pawn from memory
	Pawn::exists = false;

	board[new_y][new_x] = board[piece_y][piece_x];
	board[piece_y][piece_x] = nullptr;
	board[new_y][new_x]->itMoved();
	
	//problematic section
	if (board[new_y][new_x]!=nullptr && board[new_y][new_x]->get_type() == pt::PAWN && abs(new_y - piece_y) == 2 && ((board[new_y][new_x - 1] !=nullptr && board[new_y][new_x-1]->get_type() == pt::PAWN) 
		|| (board[new_y][new_x + 1]!=nullptr && board[new_y][new_x + 1]->get_type() == pt::PAWN))) {
		Pawn::colour = board[new_y][new_x]->get_colour();
		Pawn::x = new_x;
		Pawn::y = new_y;
		Pawn::exists = true;
	}
	can_capture_opponents_king();
	white_to_move = !white_to_move;//change turns 
	print_move(piece_y, piece_x, new_y, new_x, board[new_y][new_x]->get_type(), board[new_y][new_x]->get_colour());
}

void clean() {
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) board[i][j]->make_safe();
		}
	}
	
	Piece::getMoves().clear();
}

bool matches_players_colour(Piece*piece) {
	return (white_to_move && piece->get_colour()==col::WHITE) || (!white_to_move && piece->get_colour()==col::BLACK);
}

void normalise(sf::Vector2i& mousepos) {
	mousepos.x /= 100;
	mousepos.y /= 100;
}

void render_pieces(Piece* board[8][8], sf::RenderWindow& window) {
	for (int i = 0; i < 8; i++) {
		if (board[0][i] != nullptr && board[0][i]->get_type() == pt::PAWN) { 
			Promotion::promote(board[0][i]); 
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		if (board[7][i] != nullptr && board[7][i]->get_type() == pt::PAWN) {
			Promotion::promote(board[7][i]);
			audio->playPromote();
			break;
		}
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr)
			{
				if (board[i][j]->is_capturabe()) image->draw_capturable_piece(board[i][j]->get_type(), board[i][j]->get_colour(), j, i, window);
				else image->draw_piece(board[i][j]->get_type(), board[i][j]->get_colour(), j, i, window);
			}

			for (std::pair<int,int> marker : Piece::getMoves()) {
				if (board[marker.first][marker.second]!=nullptr&& board[marker.first][marker.second]->is_capturabe()) continue;
				image->draw_possible_move(marker.first, marker.second, window);
			}
		}
	}
}