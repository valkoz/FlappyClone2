#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Bird.h"
#include "MainMenuScene.h"
#include "Scores.h"

class GameScene : public Scores 
{
private:
	cocos2d::Size visibleSize;

	cocos2d::Vec2 origin;

	void SpawnPipe(float dt);

	void CreatePipe(cocos2d::Rect rect);

	void CreateEmpty(cocos2d::Rect rect);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	
	void update(float dt);

	int pipe_number = 1;

	int score_tag = 100;

	Bird *bird;

	cocos2d::Rect ground;
	
	cocos2d::Rect sky;

public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
