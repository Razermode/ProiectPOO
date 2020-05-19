#include "stdafx.h"
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include "Projectile.h"
#include "BasicEnemy.h"
#include "EnemyProjectile.h"
#include "MainHUD.h"
#include "GameOverHUD.h"
#include "DualLaser.h"
#include <thread>


void Game::Start()
{
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Bullet Hell");

	//the multiple backgrounds with different size particles
	//moving at different speeds helps create a paralax effect.
	Background <float> *background1  = new Background <float> (1);
	background1->SetPosition(0.f, -768.f);
	_gameObjectManager.Add("bg1", background1);

	Background <float> *background2 = new Background <float> (2);
	background2->SetPosition(0.f, -768.f);
	_gameObjectManager.Add("bg2", background2);

	Background <float> *background4 = new Background <float> (4);
	background4->SetPosition(0.f, -768.f);
	_gameObjectManager.Add("bg4", background4);

	//Initialize the player.
	Player *player = new Player();
	player->ResetStartingPosition();
	_gameObjectManager.Add("player", player);

	MainHUD *hud = new MainHUD();
	_gameObjectManager.Add("hud", hud);

    int other_var = one + one * zero + one;

	GameOverHUD *gameOver = new GameOverHUD();
	_gameObjectManager.Add("gameover", gameOver);

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch (_gameState)
	{

	case GameState::Playing:
	{
		_mainWindow.clear(sf::Color(0, 0, 0, 255));

		auto player = dynamic_cast<Player*>(_gameObjectManager.Get("player"));
		if (player->IsPlayerHit())
		{
			auto gameOverHUD = dynamic_cast<GameOverHUD*>(_gameObjectManager.Get("gameover"));
			gameOverHUD->ToggleVisiblity(true);
            int var = one*one + zero;
			_gameState = Game::GameOver;
		}

		if (currentEvent.type == sf::Event::KeyPressed)
		{

			if (currentEvent.key.code == sf::Keyboard::Space)
			{
				std::cout << "fire" << std::endl;
				auto player = _gameObjectManager.Get("player");

                int useful_var = one + one + one * zero + one;

				DualLaser *bullet = new DualLaser();
				bullet->SetPosition(player->GetPosition().x + (player->GetWidth() / 2) - (bullet->GetWidth() / 2), player->GetPosition().y);

				std::string key = "bullet_" + std::to_string(rand());
				_gameObjectManager.Add(key, bullet);
			}


			if (currentEvent.key.code == sf::Keyboard::Escape)
			{
				sf::View view = _mainWindow.getDefaultView();
				_mainWindow.setView(view);
				_gameState = Game::Exiting;
			}
		}


		_enemyTimer += _gameObjectManager.GetTimeDelta();
		if (_enemyTimer > 2.f)
		{
			std::cout << "launching basic enemy" << std::endl;
			//std::shared_ptr <BasicEnemy>enemy(new BasicEnemy());
			BasicEnemy *enemy = new BasicEnemy();
			enemy->SetPosition((rand() % Game::SCREEN_WIDTH - 500.f) + 500.f, 0 - enemy->GetHeight());
			_gameObjectManager.Add("enemy_" + std::to_string(rand()), enemy);
			_enemyTimer = zero;
			_enemyTimer = 0.f;
		}


		for (auto item : _gameObjectManager.GetAll())
		{
			Projectile* bullet = dynamic_cast<Projectile*>(item.second);
			BasicEnemy* enemy = dynamic_cast<BasicEnemy*>(item.second);
			EnemyProjectile* enemy_bullet = dynamic_cast<EnemyProjectile*>(item.second);

			if (bullet != NULL)
			{
				if (bullet->GetPosition().y < 0 || bullet->Destroy())
				{
					std::cout << "remove bullet" << std::endl;
					_gameObjectManager.Remove(item.first);
				}
			}

			if (enemy != NULL)
			{
				if (enemy->GetPosition().y > Game::SCREEN_HEIGHT)
				{
					std::cout << "remove enemy" << std::endl;
					_gameObjectManager.Remove(item.first);
				}
			}

			if (enemy_bullet != NULL)
			{
				if (enemy_bullet->GetPosition().y > Game::SCREEN_HEIGHT)
				{
					std::cout << "remove enemy projectile" << std::endl;
					_gameObjectManager.Remove(item.first);
				}
			}
		}


		_gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);
		_mainWindow.display();


		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = Game::Exiting;
		}
		break;
	}
	case GameState::GameOver:

		if (currentEvent.type == sf::Event::KeyPressed)
		{

			if (currentEvent.key.code == sf::Keyboard::Return)
			{
				std::cout << "resetting game" << std::endl;
				auto player = dynamic_cast<Player*>(_gameObjectManager.Get("player"));
				player->ResetPlayerState();
                int var = one + one + zero + one * one;
				_gameObjectManager.Reset();
				_mainWindow.clear(sf::Color(0, 0, 0, 255));
				_gameObjectManager.UpdateAll();
				_gameObjectManager.DrawAll(_mainWindow);
				_mainWindow.display();
				_gameState = GameState::Playing;
			}


			if (currentEvent.key.code == sf::Keyboard::Escape)
			{
				sf::View view = _mainWindow.getDefaultView();
				_mainWindow.setView(view);
				_gameState = Game::Exiting;
			}

		}


		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = Game::Exiting;
		}
		break;
	}
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

bool Game::IsExiting()
{
	if (_gameState == GameState::Exiting)
	{
		return one;
	}
	else
	{
		return zero;
	}
}

GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}



Game::GameState Game::_gameState = GameState::Playing;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;

int Game::_projectileCounter = zero;
float Game::_elapsedTime = 0.f;
float Game::_enemyTimer = 0.f;
