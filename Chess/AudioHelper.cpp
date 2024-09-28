#include "AudioHelper.h"

#include "AudioHelper.h"
#include <iostream>

sf::SoundBuffer Audio::buf_cap;
sf::SoundBuffer Audio::buf_prom;
sf::SoundBuffer Audio::buf_check;
sf::SoundBuffer Audio::buf_move;
sf::SoundBuffer Audio::buf_cast;
sf::SoundBuffer Audio::buf_passant;

sf::Sound Audio::capture;
sf::Sound Audio::castle;
sf::Sound Audio::move;
sf::Sound Audio::check;
sf::Sound Audio::promote;
sf::Sound Audio::en_pasant;

Audio::Audio() {
	buf_cap.loadFromFile("assets/sounds/capture.mp3");
	capture.setBuffer(Audio::buf_cap);
	buf_check.loadFromFile("assets/sounds/move-check.mp3");
	check.setBuffer(Audio::buf_check);
	buf_move.loadFromFile("assets/sounds/move-self.mp3");
	move.setBuffer(Audio::buf_move);
	buf_cast.loadFromFile("assets/sounds/castle.mp3");
	castle.setBuffer(Audio::buf_cast);
	buf_prom.loadFromFile("assets/sounds/promote.mp3");
	promote.setBuffer(Audio::buf_move);
	buf_passant.loadFromFile("assets/sounds/en_passant.mp3");
	en_pasant.setBuffer(Audio::buf_passant);
}

void Audio::playCapture() {
	capture.play();
}

void Audio::playCastle() {
	castle.play();
}

void Audio::playCheck() {
	check.play();
}

void Audio::playMove() {
	move.play();
}

void Audio::playPromote() {
	promote.play();
}

void Audio::playEnPassant() {
	en_pasant.play();
}
