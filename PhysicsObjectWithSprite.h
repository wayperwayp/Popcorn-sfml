#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "b2GLDraw.h"
//#include "Game.h"
#include<iostream>
#include<conio.h> 
#include<vector>

static const float SCALE = 30.f;
using namespace sf; 
using namespace std;

class PhysicsObjectWithSprite {
	//background process calls this per dt 
public:
	Texture texture;
	int type = 0;
	int posX = 0, posY = 0;
	b2Body* body;
bool active = true;
	Sprite sprite;
	b2World* world;
	int objectNum  = 0;
	int time = 0; 
	float length = 16.f;
	float width = 16.f;
public:
	PhysicsObjectWithSprite( 
		Texture _texture, int _type, b2World * _world) {
		texture = _texture;
		type = _type;
		world = _world;  
		addToWorld();

	};
	PhysicsObjectWithSprite() {

	};
	 

	PhysicsObjectWithSprite( 
		Texture _texture, int _type, int _posX, int _posY, b2World * _world) {
		 
		this->posX = _posX;
		this->posY = _posY;
		this->texture = _texture;
		this->type = _type;
		this->world = _world; 
		addToWorld();

	};
	PhysicsObjectWithSprite(
		Texture _texture, int _type, int _posX, int _posY, b2World * _world, float _length, float _width) {

		this->posX = _posX;
		this->posY = _posY;
		this->texture = _texture;
		this->type = _type;
		this->world = _world;
		this->length = _length;
		this->width = _width;
		addToWorld();

	};

	void destroy() { 

		world->DestroyBody(body);
		active = false;
		//delete this;

	}

	void addToWorld( ) {

		b2BodyDef BodyDef;
		BodyDef.position = b2Vec2(posX / SCALE, posY / SCALE);
		BodyDef.type = (type == 0) ? b2_staticBody : b2_dynamicBody;
		body = world->CreateBody(&BodyDef);

		b2PolygonShape Shape;
		Shape.SetAsBox(this->width/ SCALE, this->length/ SCALE);
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
		time += 1;
		if (time == 100) {
			destroy();
		}


		return sprite;
		 
	};


};