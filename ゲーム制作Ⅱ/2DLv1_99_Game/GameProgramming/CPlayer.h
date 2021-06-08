#ifndef CPLAYER_H
#define CPLAYER_H

#include "CRectangle.h"

class CPlayer : public CRectangle {
public:
	int mFx, mFy;
	int FireCount;
	int mJump;    //ジャンプフラグ
	int mVj;      //ジャンプ用速度
	static CPlayer* spInstance;
	CPlayer();
	void Update();
	void Render();

	void Collision(CRectangle *i, CRectangle *y);
};

#endif
