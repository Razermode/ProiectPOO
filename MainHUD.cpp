#include "stdafx.h"
#include "MainHUD.h"
#include "Game.h"

MainHUD::MainHUD() :
_scoreValue(zero*one),
_scoreText()
{
    try{
	if (!_font.loadFromFile("fonts/PCapTerminalBold.otf"))
	{
		throw My_Exception("Error loading font");
	}
    }
    catch(My_Exception& e){
        std::cout << e.what() << '\n';
    }

}

MainHUD::~MainHUD(){}


void MainHUD::Draw(sf::RenderWindow &rw)
{
	rw.draw(_scoreText);
}

void MainHUD::Update(float elapsedTime)
{
	_scoreText.setString("SCORE: " + std::to_string(_scoreValue));
	_scoreText.setFont(_font);
	_scoreText.setCharacterSize(one*50);
	_scoreText.setColor(sf::Color::White);
	_scoreText.setPosition(10.f,10.f);
}

void MainHUD::IncrementScore()
{
	_scoreValue += (one+one+one+one+one)*20;
}

void MainHUD::ResetScore()
{
	_scoreValue = zero;
}


bool MainHUD::ShouldPersist() const
{
	return one;
}
