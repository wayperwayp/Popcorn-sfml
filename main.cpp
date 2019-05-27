#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "b2GLDraw.h"
#include<iostream>
#include<conio.h> 
#include<vector>
#include "PhysicsObjectWithSprite.h"

 
using namespace std;
using namespace sf;   
void drawWorldObjectsOnFrame(b2World& World, RenderWindow& Window, vector<PhysicsObjectWithSprite> objectList);

int main()
{
	/** Prepare the window */
	RenderWindow Window(sf::VideoMode(1920, 1080, 20), "Test");
	Window.setFramerateLimit(60);

	//PhysicsObjectWithSprite objectList[1000] ;
	vector<PhysicsObjectWithSprite> objectList;
	/** Prepare the world */
	b2Vec2 acc(0.f, 2.f);
	b2Vec2 Gravity(0.f, 19.8f);
	b2World World(Gravity); 

	b2GLDraw fooDrawInstance;
	World.SetDebugDraw(&fooDrawInstance);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	fooDrawInstance.SetFlags(flags);
	 
	sf::Texture GroundTexture;
	sf::Texture BoxTexture; 
	GroundTexture.loadFromFile("ground.png");
	BoxTexture.loadFromFile("box.png");
	Event event;
	while (Window.isOpen())
	{

		while (Window.pollEvent(event)) {
			if (event.type == Event::Closed) Window.close();
		}
		 
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) { 
			Window.close();
		}  

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			int MouseX = sf::Mouse::getPosition(Window).x;
			int MouseY = sf::Mouse::getPosition(Window).y;
			Texture BoxTexture;
			BoxTexture.loadFromFile("box.png");
			PhysicsObjectWithSprite p(BoxTexture, 1, MouseX, MouseY);
			p.addToWorld(World);
			objectList.push_back(p);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			int MouseX = sf::Mouse::getPosition(Window).x;
			int MouseY = sf::Mouse::getPosition(Window).y;
			Texture BoxTexture;
			BoxTexture.loadFromFile("box.png");
			PhysicsObjectWithSprite p(BoxTexture, 0, MouseX, MouseY);
			p.addToWorld(World);
			objectList.push_back(p);
		}

		drawWorldObjectsOnFrame(World, Window, objectList);

		
	}

	return 0;
} 

void drawWorldObjectsOnFrame(b2World& World, RenderWindow& Window, vector<PhysicsObjectWithSprite> objectList){
	World.Step(1 / 60.f, 8, 3); 
	Window.clear(sf::Color::White);

	for (auto i = objectList.begin(); i!=objectList.end()  ; i++) {
		Window.draw(i->drawSprite());
		 
	}
	//for (b2Body* BodyIterator = objectList.begin(); BodyIterator != 0;
	//	BodyIterator = BodyIterator->GetNext())
	//World.DrawDebugData();

	Window.display();

}

