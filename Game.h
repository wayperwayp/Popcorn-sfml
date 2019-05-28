#pragma once
#include "PhysicsObjectWithSprite.h"


using namespace std;
using namespace sf;
class Game {
public:
	vector <PhysicsObjectWithSprite> objectList = {};
	bool paused = false;
	bool game_over = false;
	int score = 0;
	RenderWindow *Window;

	int high_score = 0;
	b2Vec2 Gravity = b2Vec2(0.f, 9.8f);
	b2World World = b2World(Gravity);
	Game * self;
	Game() {

	};
	Game(RenderWindow *_window) {
		Window = _window;
		Window->setFramerateLimit(60);
		b2GLDraw fooDrawInstance;
		World.SetDebugDraw(&fooDrawInstance);
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		flags += b2Draw::e_jointBit;
		flags += b2Draw::e_aabbBit;
		flags += b2Draw::e_pairBit;
		flags += b2Draw::e_centerOfMassBit;
		fooDrawInstance.SetFlags(flags);

		gameLoop();



	};
	Game(RenderWindow *_window, int _high_score) {
		high_score = _high_score;
		//copy code but added highscore ofcourse

	};
	void addPlayer() {
		int MouseX = Mouse::getPosition(*Window).x;
		int MouseY = Mouse::getPosition(*Window).y;
		Texture BoxTexture;
		BoxTexture.loadFromFile("box.png");
		PhysicsObjectWithSprite p(BoxTexture, 1, MouseX, MouseY, &World);
		objectList.push_back(p);

	};
	void addObstacle() {
		int MouseX = Mouse::getPosition(*Window).x;
		int MouseY = Mouse::getPosition(*Window).y;
		Texture BoxTexture;
		BoxTexture.loadFromFile("box.png");
		PhysicsObjectWithSprite p(BoxTexture, 0, MouseX, MouseY, &World, 100, 200);
		objectList.push_back(p);
	};
	void addGround() { 
		Texture BoxTexture;
		BoxTexture.loadFromFile("box.png");
		PhysicsObjectWithSprite p(BoxTexture, 0, 0, 1000, &World, 10, 1920);
		objectList.push_back(p);

	}
	void gameLoop() {
		Event event;
		while (Window->isOpen())
		{	
			 cout << "Numbsssadffafadfaszdser of Physics elements: " << objectList.size() << endl;

			while (Window->pollEvent(event)) {
				if (event.type == Event::Closed) Window->close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				Window->close();
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				addPlayer();
				addGround();
			}

			if (Mouse::isButtonPressed(Mouse::Right)) {
				addObstacle();
			}

			drawWorldObjectsOnFrame();


		}



	}
	void drawWorldObjectsOnFrame() {
		World.Step(1 / 60.f, 8, 3);
		Window->clear(sf::Color::White);
		vector <int> deleteList = {};
		int oLp = 0; 
			for (auto i = objectList.begin(); i != objectList.end(); i++) {

				if (!i->active) {
					deleteList.push_back(oLp);
				}
				else Window->draw(i->drawSprite());
				oLp++;
			}  
			int z = 0;
				for (auto i = deleteList.begin(); i != deleteList.end(); i++) {
					 objectList.erase(objectList.begin() + *i-z);   
					 z++;
					
				}  
			deleteList.clear();
			World.DrawDebugData();
		Window->display();

	}






};