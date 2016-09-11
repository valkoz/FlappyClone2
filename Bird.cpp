#include "Bird.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Bird::Bird()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->initWithFile("ball.png");
   	this->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	birdbody = NULL;
	isFalling = true;
}

Bird::Bird(b2World *world){
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	this->initWithFile("ball.png");
   	this->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	b2BodyDef ballBodyDef;
	ballBodyDef.type = b2_dynamicBody;
	ballBodyDef.position.Set((visibleSize.width/2 + origin.x)/SCALE_RATIO, (visibleSize.height/2 + origin.y)/SCALE_RATIO);
	ballBodyDef.userData = this;

	birdbody = world->CreateBody(&ballBodyDef);

	b2CircleShape circle;
	circle.m_radius = 12.5/SCALE_RATIO;	

	b2FixtureDef ballShapeDef;
	ballShapeDef.filter.groupIndex = -2;
	ballShapeDef.shape = &circle;
	ballShapeDef.density = 1.0f;
	ballShapeDef.friction = 0.2f;
	ballShapeDef.restitution = 40.0f;

	birdbody->CreateFixture(&ballShapeDef);
}


Bird* Bird::create()
{
   Bird* tmp = new Bird();
   if (tmp->init())
   {
     tmp->autorelease();
     return tmp;
   }
   CC_SAFE_DELETE(tmp);
   return NULL;
}

Bird* Bird::createWithPhysics(b2World *world)
{
   Bird* tmp = new Bird(world);
   if (tmp->init())
   {
     tmp->autorelease();
     return tmp;
   }
   CC_SAFE_DELETE(tmp);
   return NULL;
}


void Bird::Move(){
	if (true == isFalling)
		{
			this->setPositionX(visibleSize.width/2 + origin.x);
			this->setPositionY(this->getPositionY()-(acceleration_index*BIRD_FALLING_SPEED* visibleSize.height));
			acceleration_index = acceleration_index*1.05;
	}
	else
		{
			
			up_index = 20/(acceleration_index);
			if ( up_index <5)
				{
				isFalling = true;
				acceleration_index = 1;
				}
			else{
			this->setPositionX(visibleSize.width/2 + origin.x);
			this->setPositionY(this->getPositionY()+(up_index*BIRD_FALLING_SPEED* visibleSize.height));
			acceleration_index = acceleration_index*1.2;
			}
			
		}
}

void Bird::Fly(){
	if (birdbody!=NULL)
		birdbody->ApplyLinearImpulse( b2Vec2(0,3), birdbody->GetPosition(), true );	
	else
		isFalling = false;
}


