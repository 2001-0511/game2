#include "CSceneGame.h"
#include "CTexture.h"
#include "CMap.h"
#include "CKey.h"
#include "CRectangle.h"
#include "CBullet.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CText.h"
#include <stdio.h>

int Time = 60*80;



void CSceneGame::Init() {
	//シーンの設定
	mScene = EGAME;

	Texture.Load("Image.tga");
	//文字画像の読み込み
	CText::mFont.Load("font.tga");

	//クラスのメンバ変数への代入
	CPlayer *Player = new CPlayer();
	Player->x = 0;
	Player->y = -175;
	Player->w = 20;
	Player->h = 25;
	Player->mEnabled = true;

	int map[32][8] =
	{
		{  1, 2, 2, 0, 2, 2, 2, 1 },
		{  1, 4, 0, 2, 0, 5, 0, 1 },
		{  1, 0, 2, 0, 0, 2, 0, 1 },
		{  1, 2, 0, 5, 2, 0, 2, 1 },
		{  1, 0, 0, 2, 0, 0, 0, 1 },
		{  1, 2, 0, 5, 0, 2, 0, 1 },
		{  1, 0, 2, 0, 0, 0, 0, 1 },
		{  1, 0, 4, 2, 2, 0, 0, 1 },
		{  1, 2, 0, 0, 0, 0, 2, 1 },
		{  1, 0, 2, 0, 2, 4, 0, 1 },
		{  1, 0, 0, 0, 0, 2, 0, 1 },
		{  1, 0, 5, 0, 2, 0, 2, 1 },
		{  1, 0, 2, 0, 0, 0, 0, 1 },
		{  1, 2, 5, 0, 0, 2, 0, 1 },
		{  1, 0, 2, 0, 0, 5, 0, 1 },
		{  1, 0, 0, 2, 0, 0, 0, 1 },
		{  1, 2, 0, 0, 5, 2, 0, 1 },
		{  1, 0, 2, 0, 0, 0, 2, 1 },
		{  1, 0, 4, 2, 0, 2, 0, 1 },
		{  1, 0, 2, 0, 2, 0, 0, 1 },
		{  1, 0, 0, 2, 0, 0, 2, 1 },
		{  1, 2, 0, 4, 2, 0, 0, 1 },
		{  1, 0, 2, 0, 5, 0, 0, 1 },
		{  1, 0, 0, 2, 0, 2, 0, 1 },
		{  1, 2, 0, 4, 2, 0, 2, 1 },
		{  1, 0, 0, 2, 0, 4, 0, 1 },
		{  1, 2, 0, 0, 2, 0, 2, 1 },
		{  1, 0, 2, 3, 0, 2, 0, 1 },
		{  1, 1, 1, 1, 1, 1, 1, 1 },
	};

	for (int j = 0; j < 32 ; j++) {
		for (int i = 0; i < 8; i++) {
			//mapの要素が1の時、四角形配置
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
			}
			if (map[j][i] == 2) {
				CMap *Map = new CMap();
				//四角形に値を設定
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 40;
				Map->h = 10;
			}
			if (map[j][i] == 3){
				Player->y = j *-100 + 250;

			}
			if (map[j][i] == 4){
				CEnemy *Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//左へ移動
				Enemy->mFx = -2;
			}
			if (map[j][i] == 5){
				CEnemy *Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//右へ移動
				Enemy->mFx = 3;
			}
			
			
		}
	}
}

void CSceneGame::Update() {
	/*
	配列の要素分繰り返す
	配列名.size()
	配列の要素数を取得する
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		配列の参照
		配列名[添え字]
		通常の配列同様に添え字で要素にアクセスできる
		*/
		//更新処理
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//衝突処理
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//リストから削除する
	//イテレータの生成
	std::vector<CRectangle*>::iterator itr;
	//イテレータを先頭
	itr = VectorRect.begin();
	//最後まで繰り返し
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//次へ
			itr++;
		}
		else {
			//falseのインスタンスを削除
			delete *itr;
			//リストからも削除
			itr = VectorRect.erase(itr);
		}
	}

	

	//描画範囲変数の作成　範囲左 :-300 範囲右 : 300 固定
	double mTop, mBottom, mLeft = -300.0, mRight = 300;
	//画面範囲下の設定
	mTop = CPlayer::spInstance->y + 400.0;
	//画面範囲上の設定
	mBottom = mTop - 800.0f;
	//画面投影範囲の変更
	//行列をプロジェクションモードに変更
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   //行列を初期化
	//2Dの画面を設定
	gluOrtho2D(mLeft, mRight, mBottom, mTop);
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();    //行列を初期化

	for (int i = 0; i < VectorRect.size(); i++) {
		//描画処理
		VectorRect[i]->Render();
	}

	//画面投影範囲の変更
	//行列をプロジェクションモードに変更
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   //行列を初期化
	//2Dの画面を設定
	gluOrtho2D(-400, 400, -600, 0);
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();    //行列を初期化


	char buf[10];
	sprintf(buf, "%d", Time / 60);
	CText::DrawString(buf, 320, -50, 16, 16);

	CText::DrawString("Time", 170, -50, 16, 16);
	if (Time > 0){
		Time--;
	}
	
	if (Time == 0){
		CText::DrawString("GAME OVER", -250, -300, 32, 32);
		CPlayer::Gameover = 0;
	}

	if (CPlayer::Gameclear = 0){
		CText::DrawString("GAME CLEAY", -280, -300, 32, 32);
		Time++;
	}
}


//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//デストラクタ
CSceneGame::~CSceneGame() {
	//全てのインスタンスを削除します
	for (int i = 0; i < VectorRect.size(); i++) {
		//インスタンスの削除
		delete VectorRect[i];
	}
	//可変長配列のクリア
	VectorRect.clear();
}
