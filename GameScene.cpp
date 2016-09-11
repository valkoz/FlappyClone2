#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}


bool GameScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild ( backgroundSprite );

    this->schedule( schedule_selector( GameScene::SpawnPipe), PIPE_SPAWN_FREQUENCY*visibleSize.width);

	bird = Bird::create();
    this->addChild ( bird,100 );
	ground.setRect(0,0,visibleSize.width+origin.x,origin.y);
	sky.setRect(0,visibleSize.height+origin.y,visibleSize.width+origin.x,0);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->initScores();

	this->scheduleUpdate();

    return true;
}


void GameScene::SpawnPipe(float dt){

	auto random = CCRANDOM_0_1();	
	auto topPipePosition = visibleSize.height- visibleSize.height*random/2;
	float PipeWidth = visibleSize.width/20;
	auto topPipePositionWidth = visibleSize.width + PipeWidth;
	Rect a(topPipePositionWidth, topPipePosition, PipeWidth, visibleSize.height +origin.y - topPipePosition);
	CreatePipe(a);
	Rect b(topPipePositionWidth, 0, PipeWidth, topPipePosition - visibleSize.height/3);	
	CreatePipe(b);
	Rect c(topPipePositionWidth, topPipePosition - visibleSize.height/3, PipeWidth, visibleSize.height/3);
	CreateEmpty(c);

}

void GameScene::CreatePipe(cocos2d::Rect rect){
	auto Pipe = Sprite::create("pipe2.png", rect);
	Pipe->setPosition(rect.getMidX(),rect.getMidY());
	Pipe->setTag(pipe_number++);
	this->addChild(Pipe);
	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED*visibleSize.width, Point(-visibleSize.width*1.5,0));
	Pipe->runAction(topPipeAction);
}

void GameScene::CreateEmpty(cocos2d::Rect rect){
	auto score_hole = Sprite::create();
	score_hole->setContentSize(Size(rect.getMaxX()-rect.getMinX(),rect.getMaxY()-rect.getMinY()));
	score_hole->setPosition(rect.getMidX(),rect.getMidY());
	score_hole->setTag(score_tag++);
	this->addChild(score_hole);
	auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED*visibleSize.width, Point(-visibleSize.width*1.5,0));
	score_hole->runAction(topPipeAction);
}


bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
	bird->Fly();
	return true;
}


	
void GameScene::update(float dt){
	bird->Move();
	float radius = 12.5;
	if ((ground.intersectsCircle(bird->getPosition(), radius))||(sky.intersectsCircle(bird->getPosition(), radius))){ 
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

	for(int counter = 1; counter < this->getChildrenCount(); counter++)
	{
    		Node *child = this->getChildByTag(counter);
    		Sprite* s = dynamic_cast<Sprite*>(child);
    		if(s != 0) {
       			if (s->getBoundingBox().intersectsCircle(bird->getPosition(), radius)){
				auto scene = MainMenuScene::createScene();
				Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
				}
			if(s->getPositionX() < (-visibleSize.width/20)){
				if (s->getTag() == 1)
				pipe_number = 1;
				this->removeChildByTag(s->getTag(), true);
			}
    		}


	child = this->getChildByTag(counter+99);
    	s = dynamic_cast<Sprite*>(child);
    	if(s != 0) {
			if (s->getBoundingBox().intersectsCircle(bird->getPosition(), radius)){
				this->updateScores();
				this->removeChildByTag(s->getTag(), true);
				score_tag = 100;
			}
		}	
	}	
}

