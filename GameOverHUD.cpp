#include "stdafx.h"
#include "GameOverHUD.h"
#include "Game.h"
#include "VisibleGameObject.h"
#include "My_Exception.h"

GameOverHUD::GameOverHUD()
{
	ToggleVisiblity(zero);
    try{
	if (!_font.loadFromFile("fonts/PCapTerminalBold.otf"))
	{

		throw My_Exception("Error loading font");
	}
    }
    catch(My_Exception& e){
        std::cout<<e.what()<<'\n';
    }

	_gameOverText.setString("GAME OVER");
	_gameOverText.setFont(_font);
	_gameOverText.setCharacterSize(one*100);
	_gameOverText.setColor(sf::Color::Red);
	_gameOverText.setPosition(Game::SCREEN_WIDTH / (one+one) - _gameOverText.getGlobalBounds().width / (one+one), Game::SCREEN_HEIGHT / (one + one));
}

GameOverHUD::~GameOverHUD(){}

void GameOverHUD::Draw(sf::RenderWindow &rw)
{
	if (VisibleGameObject::ShouldDraw())
	{
		rw.draw(_gameOverText);
	}
}

void GameOverHUD::Update(float elapsedTime)
{

}

bool GameOverHUD::ShouldPersist() const
{
	return one;
}
