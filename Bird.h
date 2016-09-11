#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Box2D/Box2D.h"

class Bird : public cocos2d::Sprite
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	b2Body *birdbody = NULL;
	bool isFalling;
	float acceleration_index = 1;
	float up_index = 1;
	Bird();
	Bird(b2World *world);
	virtual bool init(){};
	
public:
	void Move ();
	void Fly();
    	static Bird* create();	
	static Bird* createWithPhysics(b2World *world);
	virtual ~Bird(){};

};

#endif // __BIRD_H__
