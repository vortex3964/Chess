#pragma once
#include <SFML/Audio.hpp>

class Audio {
private:
    static sf::SoundBuffer buf_cap;
    static sf::SoundBuffer buf_prom;
    static sf::SoundBuffer buf_cast;
    static sf::SoundBuffer buf_move;
    static sf::SoundBuffer buf_check;
    static sf::SoundBuffer buf_passant;

    static sf::Sound capture;
    static sf::Sound castle;
    static sf::Sound promote;
    static sf::Sound check;
    static sf::Sound move;
    static sf::Sound en_pasant;
public:
    Audio();
    static void playMove();
    static void playCheck();
    static void playPromote();
    static void playCastle();
    static void playCapture();
    static void playEnPassant();
};

