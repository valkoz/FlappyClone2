#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include "GameSceneBox.h"
#include "Definitions.h"
class MainMenuScene : public cocos2d::Layer
{
private:
	void GoToGameScene(cocos2d::Ref *sender);
	void GoToGameSceneBox(cocos2d::Ref *sender);
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainMenuScene);
};

#endif // __MAIN_MENU_SCENE_H__
