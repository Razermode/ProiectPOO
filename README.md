# ProiectPOO

Put all the SFML files + DLL's + codeblocks project (linked) so it can be downloaded and compiled for testing. School project for OOP. All fonts taken from the internet.


## The project tasks: 

##### Interfața grafica (în SDL, SFML, Qt, etc) cu API pentru C++
```
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
sf::Font font;
sf::Text menu[MAX_NUMBER_OF_ITEMS];
```

##### RTTI
```
Player *player = dynamic_cast<Player*>(Game::GetGameObjectManager().Get("player"));
auto hud = dynamic_cast<MainHUD*>(Game::GetGameObjectManager().Get("hud"));
```

##### Abstract Classes
```
class VisibleGameObject
{
public: 
/* Some Methods */
virtual void Update(float elapsedTime) = 0; // Pure Virtual Class
```

##### Operatori 
```
		void operator()(const std::pair<std::string, VisibleGameObject*> & p) const
		{
			delete p.second;
		}
```

##### Heap Memory Allocation
```
EnemyProjectile *shot = new EnemyProjectile();
Background <float> *background1  = new Background <float> (1);
```

##### Exceptions (de extins std::exception)
```
class My_Exception: public std::logic_error
{
    public:
        My_Exception(const char *s);
        ~My_Exception();
};
```

##### STL
```
static std::map<std::string, sf::Texture> _images;
std::map<std::string, sf::Texture> VisibleGameObject::_images; //basic image cache
```

##### Lambda expressions
```
		auto posX = [](auto first, auto second, auto third) {
            return first + second/2 - third/2;
		};
		auto posY = [](auto first, auto second) {
            return first + second/2;
		};
```

##### Templates 
```
template <typename T>
class Background : public VisibleGameObject
{ /* Some Methods */

private:
	T _velocity;
};
```

##### Smart pointers (minim 1 tip / proiect)
```
std::unique_ptr <Menu> menu(new Menu());
```

##### Design Patterns (2 patternuri)
1. [Iterator](https://refactoring.guru/design-patterns/iterator) 
```
	auto iterator = _gameObjects.begin();
	while (iterator != _gameObjects.end())
	{
      /* some code */
	}
```
2. [State](https://refactoring.guru/design-patterns/state) 
```
static GameState _gameState;
switch (_gameState)
	{
	case GameState::Playing:
    //  Some Code Here
		break;
	
	case GameState::GameOver:
		// Some Code Here
		break;
   }
```
3. [Singleton](https://refactoring.guru/design-patterns/singleton)
```
static MainHUD* instance;
static MainHUD* getInstance(){
        if(!instance)
            instance = new MainHUD();
        return instance;
}
```

##### Features of C++17/20
```
constexpr static int SCREEN_WIDTH = 1024;
constexpr static int SCREEN_HEIGHT = 768;
constexpr static int MAX_PROJECTILES = 3;
```
	
  
