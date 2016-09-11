#include "Scores.h"
USING_NS_CC;


void Scores::initScores(){	
	auto visibleSize = Director::getInstance()->getVisibleSize();
    	auto origin = Director::getInstance()->getVisibleOrigin();
	
	__String *tempScore = __String::createWithFormat("Score: %i",score);

	scorelabel = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 20);
	scorelabel->setColor(Color3B::BLUE);
	scorelabel->setPosition( Point(7*visibleSize.width/8 + origin.x, 6*visibleSize.height/8 + origin.y));
	this->addChild(scorelabel,1000);

	
	def = UserDefault::getInstance();
	highscore = def->getIntegerForKey("HIGHSCORE", 0 );
	__String *tempHighScore = __String::createWithFormat("HighScore: %i",highscore);
	auto highscorelabel = Label::createWithTTF(tempHighScore->getCString(), "fonts/Marker Felt.ttf", 20);
	highscorelabel->setColor(Color3B::RED);
	highscorelabel->setPosition( Point(7*visibleSize.width/8 + origin.x, 7*visibleSize.height/8 + origin.y));
	this->addChild(highscorelabel,1001);
}


void Scores::updateScores(){		
	score++;
	__String *tempScore = __String::createWithFormat("Score: %i",score);
	scorelabel->setString(tempScore->getCString());
	if (score>highscore){
		highscore = score;
		def->setIntegerForKey("HIGHSCORE", highscore );
		}
	def->flush();
}
