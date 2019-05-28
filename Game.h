#pragma once
#include "PhysicsObjectWithSprite.h"
//#include "Platform.h" 

using namespace std;
using namespace sf;
class Game {
public:
	vector <PhysicsObjectWithSprite> objectList = {};
	bool paused = false;
	bool game_over = false;
	int score = 0;
	float player_posX = 0;
	float player_posY = 0;
	RenderWindow *Window;
	int platform_ctr = 0;
	View view;
	int high_score = 0;
	b2Vec2 Gravity = b2Vec2(0.f, 9.8f);
	b2World World = b2World(Gravity);
	Game * self;
	PhysicsObjectWithSprite player;
	Game() {

	};
	Game(RenderWindow *_window) {
		Window = _window;
		view.setSize((float) SCREEN_WIDTH * 2, (float)SCREEN_HEIGHT * 2);
		Window->setView(view);
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
		//int MouseX = Mouse::getPosition(*Window).x/*;
		//int MouseY = Mouse::getPosition(*Window).y;*/
		
		Texture BoxTexture;
		BoxTexture.loadFromFile("box3.png");
		player = PhysicsObjectWithSprite(&World, false, 1, 700, 300, 20 ,5,
			&player_posX, &player_posY, BoxTexture);
		/*PhysicsObjectWithSprite(
		b2World * _world, bool _isPlatform, int _type, int _posX, int _posY, float _length,
		float _width, float *player_posX, float *player_posY, Texture _texture) {*/
		objectList.push_back(player);

	};
	void addObstacle() {
		/*int MouseX = Mouse::getPosition(*Window).x;
		int MouseY = Mouse::getPosition(*Window).y;
		Texture BoxTexture;
		BoxTexture.loadFromFile("box.png");
		PhysicsObjectWithSprite p(BoxTexture, 0, MouseX, MouseY, &World, 100, 200);
		objectList.push_back(p);*/
	};
	void addGround() { 
		/*Texture BoxTexture;
		BoxTexture.loadFromFile("box.png");
		PhysicsObjectWithSprite p(BoxTexture, 0, 0, 1000, &World, 10, SCREEN_WIDTH);
		objectList.push_back(p);*/

	}
	void addPlatform() {

		/*Platform(
			b2World * _world, Texture _texture, int _type, int _posX, int _posY, float _length,
			float _width, float *player_posX, float *player_posY)*/

		Texture BoxTexture;
		BoxTexture.loadFromFile("box.png");
		PhysicsObjectWithSprite p(	&World, true, 0,  platform_ctr * 600, 700, 100.f, SCREEN_WIDTH/6,
			 &player_posX, &player_posY, BoxTexture);
		/*PhysicsObjectWithSprite(
			b2World * _world, bool _isPlatform, int _type, int _posX, int _posY, float _length,
			float _width, float *player_posX, float *player_posY, Texture _texture) {*/

		/*Platform p(&World, BoxTexture, 0, platform_ctr*500, 700, SCREEN_WIDTH / 2,
		800, &player_posX, &player_posY);*/
		objectList.push_back(p);
		platform_ctr++;

	}
	void gameLoop() {
		Event event;
		addPlayer();
		while (Window->isOpen())
		{	
			 cout << "Number of Physics elements: " << objectList.size() << endl;

			while (Window->pollEvent(event)) {
				if (event.type == Event::Closed) Window->close();
			}

			if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) {
				Window->close();
			}

			if (Mouse::isButtonPressed(Mouse::Left)) {
				addPlatform();
			/*	addPlayer();
				addGround();*/
			}

			if (Mouse::isButtonPressed(Mouse::Right)) {
				//addPlayer();
				//addObstacle();
			}
			player_posX = player.body->GetPosition().x; 
			player_posY = player.body->GetPosition().y;
			cout << player_posX << "pos"<<endl;
			view.setCenter(player_posX, player_posY); 
			Window->setView(view);
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