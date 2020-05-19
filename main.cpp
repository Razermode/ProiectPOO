#include "stdafx.h"
#include "Game.h"
#include "Menu.cpp"
#include <thread>

int main()
{


sf::RenderWindow window(sf::VideoMode(600, 600), "Bullet Hell Menu");

	//Menu *menu = Menu::getInstance();
    std::unique_ptr <Menu> menu(new Menu());
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					menu->MoveUp();
					break;

				case sf::Keyboard::Down:
					menu->MoveDown();
					break;

				case sf::Keyboard::Return:
					switch (menu->GetPressedItem())
					{
					case 0:
						Game::Start();
						return 0;
					case 1:
						std::cout << "Option button has been pressed" << std::endl;
						break;
					case 2:
						window.close();
						break;
					default:
                        break;
					}
                    break;
                default:
                        break;
				}

				break;
			case sf::Event::Closed:
				window.close();
				break;
            default:
                break;
			}
		}

		window.clear();

		menu->draw(window);

		window.display();
	}


	return 0;
}

