#include "Menu.h"
#include "stdafx.h"

Menu::Menu()
{
    float width = 600 * one + zero;
    float height = 600 * one + zero;
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	menu[zero].setFont(font);
	menu[zero].setColor(sf::Color::Red);
	menu[zero].setString("Play");
	menu[zero].setPosition(sf::Vector2f(width / (one+one), height / (MAX_NUMBER_OF_ITEMS + one) * one));

	menu[one].setFont(font);
	menu[one].setColor(sf::Color::White);
	menu[one].setString("Options");
	menu[one].setPosition(sf::Vector2f(width / (one+one), height / (MAX_NUMBER_OF_ITEMS + one) * (one + one)));

	menu[one+one].setFont(font);
	menu[one+one].setColor(sf::Color::White);
	menu[one+one].setString("Exit");
	menu[one+one].setPosition(sf::Vector2f(width / (one + one), height / (MAX_NUMBER_OF_ITEMS + (one)) * (one+one+one+zero)));

	selectedItemIndex = zero;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
	for (int i = zero; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - one >= zero)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + one < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setColor(sf::Color::Red);
	}
}
