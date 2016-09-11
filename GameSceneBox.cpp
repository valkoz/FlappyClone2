#include "GameSceneBox.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
#define SCALE_RATIO 32

Scene* GameSceneBox::createScene()
{
    auto scene = Scene::create();
    auto layer = GameSceneBox::create();
    scene->addChild(layer);
    return scene;
}


bool GameSceneBox::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("background.png"); 
    backgroundSprite->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild ( backgroundSprite );
	
	this->initPhysics();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GameSceneBox::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	this->scheduleUpdate();

    return true;
}

void GameSceneBox::initPhysics() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	world = new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	contactListener = new MyContactListener();
  	world->SetContactListener(contactListener);

//Earth init

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0,origin.y/(2*SCALE_RATIO));
 
	b2Body *groundBody = world->CreateBody(&groundBodyDef);
	b2EdgeShape groundEdge;
	b2FixtureDef boxShapeDef;
	boxShapeDef.filter.groupIndex = 1;
	boxShapeDef.shape = &groundEdge;
	groundEdge.Set(b2Vec2(0,origin.y/(2*SCALE_RATIO)), b2Vec2((visibleSize.width+origin.x)/SCALE_RATIO, origin.y/(2*SCALE_RATIO)));
	groundBody->CreateFixture(&boxShapeDef);

//Sky init

	b2BodyDef skyBodyDef;
	skyBodyDef.position.Set(0,(visibleSize.height+origin.y)/(2*SCALE_RATIO));
 
	b2Body *skyBody = world->CreateBody(&skyBodyDef);
	b2EdgeShape skyEdge;
	b2FixtureDef boxShapeDef2;
		boxShapeDef2.filter.groupIndex = 1;
	boxShapeDef2.shape = &skyEdge;
	skyEdge.Set(b2Vec2(0,(visibleSize.height+origin.y)/(2*SCALE_RATIO)), b2Vec2(visibleSize.width/SCALE_RATIO, (visibleSize.height+origin.y)/(2*SCALE_RATIO)));
	skyBody->CreateFixture(&boxShapeDef2);

	bird = Bird::createWithPhysics(this->world);
	this->addChild ( bird,100 );
	this->initScores();
	this->schedule( schedule_selector( GameSceneBox::SpawnPipe), PIPE_SPAWN_FREQUENCY*visibleSize.width);


}


void GameSceneBox::update(float dt)
{
auto visibleSize = Director::getInstance()->getVisibleSize();
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
    	if (b->GetUserData() != NULL) {
        	Sprite* sprActor = (Sprite*) b->GetUserData();
        	sprActor->setPosition(b->GetPosition().x * SCALE_RATIO, b->GetPosition().y * SCALE_RATIO);
        	sprActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		b2Fixture* f = b->GetFixtureList();
		if(f->GetFilterData().groupIndex == -3){
			this->updateScores();
			world->DestroyBody(b);
			this->removeChild(sprActor, true);
		}
    	
		if ( b->GetPosition().x * SCALE_RATIO < (-visibleSize.width/20 ) ){
			world->DestroyBody(b);
			this->removeChild(sprActor, true);
		}
	}
	} 
	world->Step(dt, 8, 1);
	 

if (contactListener->isContact){
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		world->DestroyBody(b);
	}
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
}

bool GameSceneBox::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
	bird->Fly();
	return true;
}

void GameSceneBox::SpawnPipe(float dt){
	auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto random = CCRANDOM_0_1();	
	auto topPipePosition = visibleSize.height- visibleSize.height*random/2;
	auto PipeWidth = visibleSize.width/20;
	auto topPipePositionWidth = visibleSize.width + PipeWidth;

	Rect a(topPipePositionWidth, topPipePosition, PipeWidth, visibleSize.height +origin.y - topPipePosition);
	auto pipe = Pipe::createWithPhysics(world, a);
	this->addChild ( pipe );

	Rect b(topPipePositionWidth, 0, PipeWidth, topPipePosition - visibleSize.height/3);
	auto pipe2 = Pipe::createWithPhysics(world, b);
	this->addChild ( pipe2 );

	Rect c(topPipePositionWidth, topPipePosition - visibleSize.height/3, PipeWidth, visibleSize.height/3);
	auto empty = Empty::createWithPhysics(world, c);
	this->addChild ( empty );
}

bool GameSceneBox::onContactBegin(){
	return true;
}

GameSceneBox::~GameSceneBox()
{
CC_SAFE_DELETE(world);
}

