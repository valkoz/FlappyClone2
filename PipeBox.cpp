#include "PipeBox.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;


Pipe* Pipe::createWithPhysics(b2World *world, Rect rect)
{
   Pipe* tmp = new Pipe(world, rect);
   if (tmp->init())
   {
     tmp->autorelease();
     return tmp;
   }
   CC_SAFE_DELETE(tmp);
   return NULL;
}

Empty* Empty::createWithPhysics(b2World *world, Rect rect)
{
   Empty* tmp = new Empty(world, rect);
   if (tmp->init())
   {
     tmp->autorelease();
     return tmp;
   }
   CC_SAFE_DELETE(tmp);
   return NULL;
}


Pipe::Pipe(b2World *world, Rect rect)
{
	this->initWithFile("pipe2.png", rect);
	this->setPosition(rect.getMidX(),rect.getMidY());
	
	b2BodyDef PipeBodyDef;
	PipeBodyDef.type = b2_kinematicBody;	
	PipeBodyDef.position.Set(rect.getMidX()/SCALE_RATIO, rect.getMidY()/SCALE_RATIO);
	PipeBodyDef.userData = this;

	PipeBody = world->CreateBody(&PipeBodyDef);

	
	float a = this->getContentSize().width;
	float b = this->getContentSize().height;
	float sizeX = a/(2*SCALE_RATIO);
	float sizeY = b/(2*SCALE_RATIO);

	b2PolygonShape polygon;
	polygon.SetAsBox(sizeX, sizeY); 

	b2FixtureDef PipeShapeDef;
	PipeShapeDef.filter.groupIndex = 1;
	PipeShapeDef.shape = &polygon;

	PipeShapeDef.density = 0;

	PipeShapeDef.friction = 0;

	PipeShapeDef.restitution = 0;

	PipeBody->CreateFixture(&PipeShapeDef);

	PipeBody->SetLinearVelocity( b2Vec2(-5,0));

}

Empty::Empty(b2World *world, Rect rect)
{
	this->init();
	this->setContentSize(Size(rect.getMaxX()-rect.getMinX(),rect.getMaxY()-rect.getMinY()));
	this->setPosition(rect.getMidX(),rect.getMidY());
		
	
	b2BodyDef EmptyBodyDef;
	EmptyBodyDef.type = b2_kinematicBody;	
	EmptyBodyDef.position.Set(rect.getMidX()/SCALE_RATIO, rect.getMidY()/SCALE_RATIO);
	EmptyBodyDef.userData = this;

	EmptyBody = world->CreateBody(&EmptyBodyDef);

	
	float a = this->getContentSize().width;
	float b = this->getContentSize().height;
	float sizeX = a/(2*SCALE_RATIO);
	float sizeY = b/(2*SCALE_RATIO);

	b2PolygonShape polygon;
	polygon.SetAsBox(sizeX, sizeY); 
	b2FixtureDef EmptyShapeDef;
	EmptyShapeDef.filter.groupIndex = -1;
	EmptyShapeDef.shape = &polygon;

	EmptyShapeDef.density = 0;

	EmptyShapeDef.friction = 0;

	EmptyShapeDef.restitution = 0;

	EmptyBody->CreateFixture(&EmptyShapeDef);

	EmptyBody->SetLinearVelocity( b2Vec2(-5,0));

}
