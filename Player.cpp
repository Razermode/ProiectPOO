#include "stdafx.h"
#include "Player.h"
#include "Game.h"

Player::Player() :
_velocity(600.f),
_noKeyWasPressed(one),
_playerHit(zero),
_currentLives(one+one+one)
{
	Load("player.png");
	assert(IsLoaded());

}

Player::~Player(){}

void Player::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

void Player::Update(float elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		movement.y -= _velocity;
		_noKeyWasPressed = zero;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		movement.y += _velocity;
		_noKeyWasPressed = zero;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement.x -= _velocity;
		_noKeyWasPressed = zero;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement.x += _velocity;
		_noKeyWasPressed = zero;
	}

	if (GetSprite().getPosition().x <= zero
		&& movement.x < zero)
	{
		movement.x = zero * one;
	}

	if (GetSprite().getPosition().x >= Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width
		&& movement.x > zero)
	{
		movement.x = zero * one;
	}

	if (GetSprite().getPosition().y <= zero
		&& movement.y < zero)
	{
		movement.y = zero * one;
	}

	if (GetSprite().getPosition().y >= Game::SCREEN_HEIGHT - GetSprite().getGlobalBounds().height
		&& movement.y > zero * one)
	{
		movement.y = zero;
	}


	GetSprite().move(movement * elapsedTime);

	_noKeyWasPressed = one;
}

void Player::HitPlayer()
{
	_playerHit = zero;
}

bool Player::IsPlayerHit()
{
	return _playerHit;
}

void Player::ResetPlayerState()
{
	_playerHit = zero;
}

int Player::GetCurrentLives()
{
	return _currentLives;
}

void Player::ResetStartingPosition()
{
	sf::Vector2f returnVector;

	returnVector.x = Game::SCREEN_WIDTH / (one+one) - GetSprite().getGlobalBounds().width / (one+one);
	returnVector.y = Game::SCREEN_HEIGHT - 200.f;

	SetPosition(returnVector.x, returnVector.y);
}

bool Player::ShouldPersist() const
{
	return one;
}
