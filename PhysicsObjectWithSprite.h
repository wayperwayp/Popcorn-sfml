#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "b2GLDraw.h" 
#include<iostream>
#include<conio.h> 
#include<vector>

  const int SCREEN_WIDTH = 1366;
  const int SCREEN_HEIGHT = 768;
static const float SCALE =60.f;
using namespace sf; 
using namespace std;

class PhysicsObjectWithSprite {
	//background process calls this per dt 
public:
	Texture texture;
	bool isPlatform = true; 
	int type = 0; 
	b2Body* body;

	float *player_posX = 0;
	float *player_posY = 0;
	Vector2f pos ;
	Vector2f * player_pos;
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
	 

	/*PhysicsObjectWithSprite( 
		Texture _texture, int _type, int _posX, int _posY, b2World * _world) {
		  
		this->texture = _texture;
		this->type = _type;
		this->world = _world; 
		addToWorld();

	};
	PhysicsObjectWithSprite(
		Texture _texture, int _type, int _posX, int _posY, b2World * _world, float _length, float _width) {
		 
		this->texture = _texture;
		this->type = _type;
		this->world = _world;
		this->length = _length;
		this->width = _width;
		addToWorld();

	};*/

	PhysicsObjectWithSprite(
		b2World * _world,bool _isPlatform,  int _type, int _posX, int _posY, float _length,
		float _width, float *player_posX, float *player_posY, Texture _texture ) {

		 
		this->pos = Vector2f(_posX, _posY);
		this->texture = _texture;
		this->isPlatform = _isPlatform; 
		this->type = _type;
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

	void addToWorld( ) {

		b2BodyDef BodyDef;
		BodyDef.position = b2Vec2(pos.x / SCALE, pos.y/ SCALE);
		BodyDef.type = (type == 0) ? b2_staticBody : b2_dynamicBody;
		body = world->CreateBody(&BodyDef);

		b2PolygonShape Shape;
		Shape.SetAsBox(this->width/ SCALE, this->length/ SCALE);
		b2FixtureDef FixtureDef;
		FixtureDef.density = 1.f;
		FixtureDef.friction = 0.0f;
		FixtureDef.shape = &Shape;
		body->CreateFixture(&FixtureDef);
		//if (!isPlatform) SetLinearVelocity(0.f, 0.f);


	}
	void SetLinearVelocity(float x, float y) {

		b2Vec2 vel = b2Vec2(x, y);
		body->SetLinearVelocity(vel);
	}
	Sprite drawSprite(float dt) {

		sprite.setTexture(texture);
		//sprite.setOrigin(width/2, length/2);
		sprite.setPosition(body->GetPosition().x*SCALE, -body->GetPosition().y*SCALE);
	/*	sprite.setPosition(SCALE * body->GetPosition().x - (type==0)?width*2:-width * 2,
			SCALE * body->GetPosition().y - (type == 0) ? length * 2 : -length * 2);*/
		sprite.setRotation(body->GetAngle() * 180 / b2_pi);
		time += 1;
		if (*player_posX > (float)pos.x + 100) {
			destroy();
		}


		return sprite;
		 
	};


};