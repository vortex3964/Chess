#include "Promotion.h"


void Promotion::promote(Piece* &board) {
	sf::RenderWindow window(sf::VideoMode(400, 100), "Promote your pawn", sf::Style::Titlebar); //player cant close the window just read the title bar

	sf::Texture image;
	sf::RectangleShape pick_piece;
	//Piece* piece=nullptr;
	int colour = board->get_colour();
	if (colour) image.loadFromFile("assets/images/promotion_white.png");
	else image.loadFromFile("assets/images/promotion_black.png");

	pick_piece.setTexture(&image);
	pick_piece.setSize(sf::Vector2f(400, 100));
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == e.MouseButtonPressed) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i choice = sf::Mouse::getPosition(window);
					delete board;
					board = nullptr;
					
					switch (choice.x / 100) {
					case 0:
						board = new Queen(colour);
						break;
					case 1:
						board = new Bishop(colour);
						break;
					case 2:
						board = new Knight(colour);
						break;
					case 3:
						board = new Rook(colour);
						break;
					}
					window.close();
				}
			}
		}
		window.clear(sf::Color::Cyan);
		window.draw(pick_piece);
		window.display();
	}
	
}
