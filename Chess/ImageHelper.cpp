#include "ImageHelper.h"
#include "ImageHelper.h"

Image::Image() {

	captured_pieces.loadFromFile("assets/images/captured.png");
	pieces.loadFromFile("assets/images/Chess_Pieces.png");

	c_piece.setTexture(&captured_pieces);
	piece.setTexture(&pieces);


	image_measurements = pieces.getSize();
	image_measurements.x = image_measurements.x / 6;
	image_measurements.y = image_measurements.y / 2;

	piece.setSize(sf::Vector2f(100, 100));
	c_piece.setSize(sf::Vector2f(100, 100));

	possible_move_texture.loadFromFile("assets/images/Red_circle_frame_transparent.svg.png");
	possible_move.setTexture(&possible_move_texture);
	possible_move.setSize(sf::Vector2f(30, 30));
}

void Image::draw_piece(int type, int colour, int y_pos, int x_pos, sf::RenderWindow& window) {
	int y = (colour) ? y = 0 : y = 1;
	type = abs(type);
	type--;

	piece.setPosition(y_pos * 100, x_pos * 100);
	piece.setTextureRect(sf::IntRect(type * image_measurements.x, y * image_measurements.y, image_measurements.x, image_measurements.y));
	window.draw(piece);
}

void Image::draw_capturable_piece(int type, int colour, int y_pos, int x_pos, sf::RenderWindow& window) {
	int y = (colour) ? y = 0 : y = 1;
	type = abs(type);
	type--;

	c_piece.setPosition(y_pos * 100, x_pos * 100);
	c_piece.setTextureRect(sf::IntRect(type * image_measurements.x, y * image_measurements.y, image_measurements.x, image_measurements.y));
	window.draw(c_piece);
}

void Image::draw_possible_move(int y,int x,sf::RenderWindow& window) {
	possible_move.setPosition(x * 100+35 , y * 100+35);
	window.draw(possible_move);
}

