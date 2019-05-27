#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "b2GLDraw.h"
#include<iostream>
#include<conio.h> 
#include<vector>

static const float SCALE = 30.f;
using namespace sf; 
class PhysicsObjectWithSprite {
	//background process calls this per dt 
	Texture texture;
	int type = 0;
	int posX = 0, posY = 0;
	b2Body* body;
	Sprite sprite;
	int objectNum  = (int) objectList.size();
	int time = 0;
public:
	PhysicsObjectWithSprite(Texture _texture, int _type) {
		texture = _texture;
		type = _type;

	};
	PhysicsObjectWithSprite() {

	};
	 
	void destroy() {
		objectList.erase(objectList[objectNum]); 


	}
	PhysicsObjectWithSprite(Texture _texture, int _type, int _posX, int _posY) {
		texture = _texture;
		type = _type;
		posX = _posX;
		posY = _posY;

	};

	void addToWorld(b2World& world) {

		b2BodyDef BodyDef;
		BodyDef.position = b2Vec2(posX / SCALE, posY / SCALE);
		BodyDef.type = (type == 0) ? b2_staticBody : b2_dynamicBody;
		body = world.CreateBody(&BodyDef);

		b2PolygonShape Shape;
		Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
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
		if (time == 300) {
			destroy();
		}


		return sprite;
		 
	};


};