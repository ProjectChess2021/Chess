#include "player.h"

Player::Player( const int &id ) : score{ 0 }, id{ id } { }

int Player::getScore() { return score; }

int Player::getId() { return id; }

Player::~Player() { }