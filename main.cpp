 
//#include "PhysicsObjectWithSprite.h"
#include "Game.h" 
 
using namespace std;
using namespace sf;    
int main()
{ 
	RenderWindow Window(VideoMode(1366, 768, 32), "Game Screen");
	Window.setFramerateLimit(60);
	Game game(&Window);


	return 0;
} 
 