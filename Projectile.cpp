#include "stdafx.h"
#include "Projectile.h"
#include "BasicEnemy.h"
#include "Game.h"
#include "MainHUD.h"

Projectile::Projectile() :
_velocity(500.f),
_timeBetweenShots(1.f),
shouldDestroy(false)
{
	Load("playerlaserbeam.png");
	assert(IsLoaded());
}

Projectile::~Projectile(){}

void Projectile::Draw(sf::RenderWindow &rw)
{
	VisibleGameObject::Draw(rw);
}

void Projectile::Update(float elapsedTime)
{

	sf::Vector2f movement(0.f, 0.f);

	movement.y -= _velocity;

	GetSprite().move(movement * elapsedTime);

	//check for collision with enemies.
	for  (auto item : Game::GetGameObjectManager().GetAll())
	{
		BasicEnemy* enemy = dynamic_cast<BasicEnemy*>(item.second);
		if (enemy != NULL)
		{
			if (enemy->GetBoundingRect().contains(GetSprite().getPosition()))
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

bool Projectile::Destroy()
{
	return shouldDestroy;
}

