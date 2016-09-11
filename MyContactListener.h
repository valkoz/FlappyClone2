#include "Box2D/Box2D.h"

class MyContactListener : public b2ContactListener /*Отслеживает столкновения птицы с препятствиями*/
  {
	void BeginContact(b2Contact* contact) {
  
	int filterA = contact->GetFixtureA()->GetFilterData().groupIndex;
	int filterB = contact->GetFixtureB()->GetFilterData().groupIndex;

	if ((filterA>0)||(filterB>0)){
		isContact = 1;
		return;
	}
	if((filterA == -1) || (filterB == -1)){	/*-1 - индекс пространства между препятствиями*/
		b2Filter newfilter;
		newfilter.groupIndex = -3;	/*-3 - индекс, по которому удаляется объект*/
		if(filterA == -1)
			contact->GetFixtureA()->SetFilterData(newfilter);
		else
			contact->GetFixtureB()->SetFilterData(newfilter);
		contact->GetFixtureA()->GetBody()->SetLinearVelocity( b2Vec2(0,contact->GetFixtureA()->GetBody()->GetLinearVelocity().y));
		contact->GetFixtureB()->GetBody()->SetLinearVelocity( b2Vec2(0,contact->GetFixtureB()->GetBody()->GetLinearVelocity().y));
		score++;
	}
    }
public:
	bool isContact = 0;
	int score = 0;
};
