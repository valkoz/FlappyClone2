#ifndef __PIPEBOX_H__
#define __PIPEBOX_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class Pipe : public cocos2d::Sprite	/*Задает препятствие */
{
private:
	b2Body *PipeBody = NULL;
	Pipe(b2World *world, Rect rect);
	virtual bool init(){};


public:
	static Pipe* createWithPhysics(b2World *world, Rect rect);
	virtual ~Pipe(){};

};

class Empty: public cocos2d::Sprite	/*Задает пространство между препятствиями (для подсчета очков)*/
{
private:
	b2Body *EmptyBody = NULL;
	Empty(b2World *world, Rect rect);
	virtual bool init(){};

public:	
	static Empty* createWithPhysics(b2World *world, Rect rect);
	virtual ~Empty(){};
};

#endif // __PIPEBOX_H__
