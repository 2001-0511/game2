#include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"

//extern：他のソースファイルの外部変数にアクセスする宣言
extern CTexture Texture;

#define G 1      //重力
#define VJ0 18   //ジャンプ力

CPlayer* CPlayer::spInstance;

CPlayer::CPlayer()
: mFx(1.0f), mFy(0.0f)
, FireCount(0), mVj(0), mJump(0)   //0はジャンプ可能
{
	mTag = EPLAYER;
	spInstance = this;
}

void CPlayer::Update() {

	//staticメソッドはどこからでも呼べる
	if (CKey::Push('A')) {
		x -= 3;
		mFx = -1;
		mFy = 0;
		if (x - w < -300) {
			x = -300 + w;
		}
	}
	if (CKey::Push('D')) {
		x += 3;
		mFx = 1;
		mFy = 0;
		if (x + w > 300) {
			x = 300 - w;
		}
	}
	//if (CKey::Push('W')) {
	//	y += 3;
	//	mFx = 0;
	//	mFy = 1;
	//^}
	//if (CKey::Push('S')) {
	//	y -= 3;
	//	mFx = 0;
	//	mFy = -1;
	//	if (y - h < -300){
	//		y = -300 + h;
	//	}
	//}

	//ジャンプ可能か
	if (mJump == 0 && CKey::Once(' ')){
		//ジャンプ力を速度に設定
		mVj = VJ0;
		//フラグに1加算
		mJump++;
	}
	//速度に重力加速度加算
	mVj -= G;
	//速度分移動
	y += mVj;
	
}

void CPlayer::Render() {
	CRectangle::Render(Texture, 146 - 16, 146 + 16, 146 + 16, 146 - 16);
}

void CPlayer::Collision(CRectangle *ri, CRectangle *ry) {
	if (ry->mTag == EBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) xの絶対値を求める
			//移動量が少ない方向だけ移動させる
			if (abs(mx) < abs(my)) {
				//Rectをxだけ移動する
				x += mx;
			}
			else {
				//Rectをyだけ移動する
				y += my;
				//着地
				mVj = 0; //ジャンプ速度0
				if (my>0)
				{
					//ジャンプ可能
					mJump = 0;
				}
			}
		}
	}
	if (ry->mTag == EENEMY){
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)){
			if (abs(mx) < abs(my)) {
				x += mx;
			}
			else {
				y += my;
				 
			}
		}
	}
}
