#ifndef __SCORES_H__
#define __SCORES_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Box2D/Box2D.h"


class Scores: public cocos2d::Layer
{
private:
	int highscore = 0;

	int score = 0;

	cocos2d::UserDefault *def;

	cocos2d::Label *scorelabel;

public:
	void initScores();
	void updateScores();
};

#endif // __SCORES_H__


