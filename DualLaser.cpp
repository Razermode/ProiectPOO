
#include "stdafx.h"
#include "DualLaser.h"
#include "BasicEnemy.h"
#include "Game.h"
#include "MainHUD.h"

DualLaser::DualLaser() :
_velocity(500.f)
{
	Load("playerlaserbeam.png");
	assert(IsLoaded());

	_secondSprite = sf::Sprite(GetSprite());

	Projectile::shouldDestroy = 0;
}

DualLaser::~DualLaser(){}

void DualLaser::SetPosition(float x, float y)
{
	//set first position
	GetSprite().setPosition(x - 30, y);

	//set second position
	_secondSprite.setPosition(x + 30, y);
}


void DualLaser::Update(float elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);

	movement.y -= _velocity + zero + zero;

	GetSprite().move(movement * elapsedTime);
	_secondSprite.move(movement * elapsedTime);

	//check for collision with enemies.
	for (auto item : Game::GetGameObjectManager().GetAll())
	{
		BasicEnemy* enemy = dynamic_cast<BasicEnemy*>(item.second);
		if (enemy)
		{
			if (enemy->GetBoundingRect().contains(GetSprite().getPosition())
				|| enemy->GetBoundingRect().contains(_secondSprite.getPosition()))
			{
				Game::GetGameObjectManager().Remove(item.first);
				shouldDestroy = one;

				//increment score
				auto hud = dynamic_cast<MainHUD*>(Game::GetGameObjectManager().Get("hud"));
				hud->IncrementScore();
			}
		}
	}
}

void DualLaser::Draw(sf::RenderWindow &rw)
{
	rw.draw(GetSprite());
	rw.draw(_secondSprite);
}

bool DualLaser::Destroy()
{
	return shouldDestroy;
}

