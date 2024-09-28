#pragma once

#include <SFML/Graphics.hpp>

class Image {
private:
	sf::Vector2u image_measurements;
	sf::Texture captured_pieces;
	sf::Texture pieces;
	sf::RectangleShape piece;
	sf::RectangleShape c_piece;
	sf::Texture possible_move_texture;
	sf::RectangleShape possible_move;
public:
	Image();
	void draw_piece(int type, int y_pos, int colour, int x_pos, sf::RenderWindow& window);
	void draw_capturable_piece(int type, int colour, int y_pos, int x_pos, sf::RenderWindow& window);
	void draw_possible_move(int y,int x, sf::RenderWindow& window);
};



