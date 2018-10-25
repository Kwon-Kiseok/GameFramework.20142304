#pragma once
#include "SDLGameObject.h"

class Monster : public SDLGameObject
{
public:
	Monster(const LoaderParams* pParams);
	~Monster() {}

	virtual void draw();
	virtual void update();
	virtual void clean();
	void control(int m_x, int m_y, int currentFrame); //몬스터 이동 함수
private:
	bool goR = true;
};