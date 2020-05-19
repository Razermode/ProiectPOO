#include "stdafx.h"
#include "BasicEnemy.h"
#include "Game.h"
#include "EnemyProjectile.h"
#include "Player.h"
#include <thread>

BasicEnemy::BasicEnemy() :
_velocity(200.f),
_timeBetweenShots(0.f)
{
	Load("basicenemy.png");
	assert(IsLoaded());
}

BasicEnemy::~BasicEnemy(){}

void BasicEnemy::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

void BasicEnemy::Update(float elapsedTime)
{
	_timeBetweenShots += elapsedTime;
	sf::Vector2f movement(0.f, 0.f);

	if (_timeBetweenShots > 1.f)
	{
		//std::cout << "fire projectile" << std::endl;

		EnemyProjectile *shot = new EnemyProjectile();

		auto posX = [](auto first, auto second, auto third) {
            return first + second/2 - third/2;
		};
		auto posY = [](auto first, auto second) {
            return first + second/2;
		};

		shot->SetPosition(posX(GetSprite().getPosition().x, GetSprite().getGlobalBounds().width, shot->GetWidth()),
            posY(GetSprite().getPosition().y, GetSprite().getGlobalBounds().height));


		Game::GetGameObjectManager().Add("enemy_projectile_" + std::to_string(rand()), shot);

		_timeBetweenShots = 0.f;
	}

	movement.y += _velocity;
	GetSprite().move(movement * elapsedTime);


	//check for collision with player.
	Player *player = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player"));
	if (player != NULL)
	{
		if (!player->IsPlayerHit() && player->GetBoundingRect().intersects(GetSprite().getGlobalBounds()))
		{
			player->HitPlayer();
		}
	}
}

