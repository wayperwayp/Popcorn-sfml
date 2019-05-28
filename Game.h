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
	Vector2f player_pos;
	Clock clock;
	RenderWindow *Window;
	int platform_ctr = -2;
	View view;
	int high_score = 0;
	b2Vec2 Gravity = b2Vec2(0.f, 0.f);
	b2World World = b2World(Gravity);
	Game * self;
	PhysicsObjectWithSprite player;
	Game() {

	};
	Game(RenderWindow *_window) {
		Window = _window;
		player_pos = Vector2f(0.f, 0.f);
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
		if (paused) return;
		paused = true;
		int MouseX = Mouse::getPosition(*Window).x ;
		int MouseY = Mouse::getPosition(*Window).y; 
		
		Texture BoxTexture;
		BoxTexture.loadFromFile("player.png");
		player = PhysicsObjectWithSprite(&World, false, 1, MouseX, MouseY, 70 ,70,
			&player_pos.x, &player_pos.y, BoxTexture);
		/*PhysicsObjectWithSprite(
		b2World * _world, bool _isPlatform, int _type, int _posX, int _posY, float _length,
		float _width, float *player_posX, float *player_posY, Texture _texture) {*/
		objectList.push_back(player);

	};
	 
	void addPlatform() {
		 
		Texture BoxTexture;
		BoxTexture.loadFromFile("tube.png");
		PhysicsObjectWithSprite p(	&World, true, 0,  platform_ctr * (400+ rand()%800), 1800, 1000.f, 70,
			 &player_pos.x, &player_pos.y, BoxTexture);
		/*PhysicsObjectWithSprite(
			b2World * _world, bool _isPlatform, int _type, int _posX, int _posY, float _length,
			float _width, float *player_posX, float *player_posY, Texture _texture) {*/
		 
		objectList.push_back(p);
		platform_ctr++;

	}
	void gameLoop() {
		Event event;
		//addPlayer();
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
				addPlayer();
				//addObstacle();
			}
			//player_pos.x = (float)player.body->GetPosition().x;
			//player_pos.y = (float)player.body->GetPosition().y;

			//cout << player_posX << "pos"<<endl;
			view.setCenter(player_pos*SCALE); 
			//Window->setView(view);
			drawWorldObjectsOnFrame();
			//if ((int)player_pos.x % 100 == 0) addPlatform();


		}



	}
	void drawWorldObjectsOnFrame() {

		World.Step(1 / 60.f, 8, 3); 
		float dt = clock.restart().asSeconds();
		Window->clear(sf::Color::White);
		vector <int> deleteList = {};
		int oLp = 0; 
			for (auto i = objectList.begin(); i != objectList.end(); i++) {

				if (!i->active) {
					deleteList.push_back(oLp);
				}
				else Window->draw(i->drawSprite(dt));
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