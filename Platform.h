#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "b2GLDraw.h" 
#include<iostream>
#include<conio.h> 
#include<vector>
  
using namespace sf;
using namespace std;

class Platform { 
public:
	Texture texture; 
	int platform_type = 0;
	int posX = 0, posY = 0;
	float *player_posX = 0;
	float *player_posY = 0;
	b2Body* body;
	bool active = true;
	Sprite sprite;
	b2World* world;
	int objectNum = 0; 
	float length = 16.f;
	float width = 16.f;
public: 
	Platform() {

	};

 
	Platform(
		b2World * _world, Texture _texture, int _type, int _posX, int _posY,  float _length,
		float _width, float *player_posX, float *player_posY) {

		this->posX = _posX;
		this->posY = _posY;
		this->texture = _texture;
		this->platform_type = _type;
		this->world = _world;
		this->length = _length;
		this->width = _width;
		this->player_posX = player_posX;
		this->player_posY = player_posY;
		addToWorld();

	};

	void destroy() {

		world->DestroyBody(body);
		active = false;
		//delete this;

	}

	void addToWorld() {

		b2BodyDef BodyDef;
		BodyDef.position = b2Vec2(posX / SCALE, posY / SCALE);
		BodyDef.type = (platform_type == 0) ? b2_staticBody : b2_dynamicBody;
		body = world->CreateBody(&BodyDef);

		b2PolygonShape Shape;
		Shape.SetAsBox(this->width / SCALE, this->length / SCALE);
		b2FixtureDef FixtureDef;
		FixtureDef.density = 1.f;
		FixtureDef.friction = 0.7f;
		FixtureDef.shape = &Shape;
		body->CreateFixture(&FixtureDef);


	}
	Sprite drawSprite() {

		sprite.setTexture(texture);
		sprite.setOrigin(16.f, 16.f);
		sprite.setPosition(SCALE * body->GetPosition().x,
			SCALE * body->GetPosition().y);
		sprite.setRotation(body->GetAngle() * 180 / b2_pi);

		if (*player_posX > (float) posX + 100) {
			destroy();
		}
		 


		return sprite;

	};


};