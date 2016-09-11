#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenuScene::create();
    scene->addChild(layer);
    return scene;
}


bool MainMenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("background.jpg");
    backgroundSprite->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild ( backgroundSprite );

    auto label = Label::createWithTTF("Flappy Bird", "fonts/Marker Felt.ttf", 24);
    auto playItem = MenuItemLabel::create(label, CC_CALLBACK_1(MainMenuScene::GoToGameScene,this));
    playItem->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/4 + origin.y));


    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);


    auto labelBox = Label::createWithTTF("Flappy Bird Box 2D", "fonts/Marker Felt.ttf", 24);
    auto playItem2 = MenuItemLabel::create(labelBox, CC_CALLBACK_1(MainMenuScene::GoToGameSceneBox,this));
    playItem2->setPosition( Point(visibleSize.width/2 + origin.x, 3*visibleSize.height/4 + origin.y));


    auto menu2 = Menu::create(playItem2, NULL);
    menu2->setPosition(Point::ZERO);
    this->addChild(menu2);



    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref *sender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::GoToGameSceneBox(cocos2d::Ref *sender)
{
	auto scene = GameSceneBox::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
