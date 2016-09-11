#ifndef __GAME_SCENE_BOX_H__
#define __GAME_SCENE_BOX_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Bird.h"
#include "PipeBox.h"
#include "MyContactListener.h"
#include "MainMenuScene.h"
#include "Scores.h"

class GameSceneBox : public Scores
{
public:
    static cocos2d::Scene* createScene();
	
    virtual bool init();

	void initPhysics();
	float deltaTime;
    void update(float dt);
    CREATE_FUNC(GameSceneBox);
	b2World* world;
	virtual ~GameSceneBox();

private:
	void SpawnPipe(float dt);
	Bird *bird;
	MyContactListener *contactListener;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onContactBegin();
};

#endif // __GAME_SCENE_BOX_H__
