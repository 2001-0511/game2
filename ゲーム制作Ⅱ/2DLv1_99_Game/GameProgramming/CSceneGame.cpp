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
	//�V�[���̐ݒ�
	mScene = EGAME;

	Texture.Load("Image.tga");
	//�����摜�̓ǂݍ���
	CText::mFont.Load("font.tga");

	//�N���X�̃����o�ϐ��ւ̑��
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
			//map�̗v�f��1�̎��A�l�p�`�z�u
			if (map[j][i] == 1) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
				Map->mEnabled = true;
				Map->x = i * 100 - 350;
				Map->y = j * -100 + 250;
				Map->w = 50;
				Map->h = 50;
			}
			if (map[j][i] == 2) {
				CMap *Map = new CMap();
				//�l�p�`�ɒl��ݒ�
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
				//���ֈړ�
				Enemy->mFx = -2;
			}
			if (map[j][i] == 5){
				CEnemy *Enemy = new CEnemy();
				Enemy->x = i * 100 - 350;
				Enemy->y = j * -100 + 250;
				//�E�ֈړ�
				Enemy->mFx = 3;
			}
			
			
		}
	}
}

void CSceneGame::Update() {
	/*
	�z��̗v�f���J��Ԃ�
	�z��.size()
	�z��̗v�f�����擾����
	*/
	for (int i = 0; i < VectorRect.size(); i++) {
		/*
		�z��̎Q��
		�z��[�Y����]
		�ʏ�̔z�񓯗l�ɓY�����ŗv�f�ɃA�N�Z�X�ł���
		*/
		//�X�V����
		VectorRect[i]->Update();
	}
	for (int i = 0; i < VectorRect.size() - 1; i++) {
		//�Փˏ���
		for (int j = i + 1; j < VectorRect.size(); j++) {
			VectorRect[i]->Collision(VectorRect[i], VectorRect[j]);
			VectorRect[j]->Collision(VectorRect[j], VectorRect[i]);
		}
	}

	//���X�g����폜����
	//�C�e���[�^�̐���
	std::vector<CRectangle*>::iterator itr;
	//�C�e���[�^��擪
	itr = VectorRect.begin();
	//�Ō�܂ŌJ��Ԃ�
	while (itr != VectorRect.end()) {
		if ((*itr)->mEnabled) {
			//����
			itr++;
		}
		else {
			//false�̃C���X�^���X���폜
			delete *itr;
			//���X�g������폜
			itr = VectorRect.erase(itr);
		}
	}

	

	//�`��͈͕ϐ��̍쐬�@�͈͍� :-300 �͈͉E : 300 �Œ�
	double mTop, mBottom, mLeft = -300.0, mRight = 300;
	//��ʔ͈͉��̐ݒ�
	mTop = CPlayer::spInstance->y + 400.0;
	//��ʔ͈͏�̐ݒ�
	mBottom = mTop - 800.0f;
	//��ʓ��e�͈͂̕ύX
	//�s����v���W�F�N�V�������[�h�ɕύX
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   //�s���������
	//2D�̉�ʂ�ݒ�
	gluOrtho2D(mLeft, mRight, mBottom, mTop);
	//�s������f���r���[���[�h�֕ύX
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();    //�s���������

	for (int i = 0; i < VectorRect.size(); i++) {
		//�`�揈��
		VectorRect[i]->Render();
	}

	//��ʓ��e�͈͂̕ύX
	//�s����v���W�F�N�V�������[�h�ɕύX
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   //�s���������
	//2D�̉�ʂ�ݒ�
	gluOrtho2D(-400, 400, -600, 0);
	//�s������f���r���[���[�h�֕ύX
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();    //�s���������


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


//���̃V�[���̎擾
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
//�f�X�g���N�^
CSceneGame::~CSceneGame() {
	//�S�ẴC���X�^���X���폜���܂�
	for (int i = 0; i < VectorRect.size(); i++) {
		//�C���X�^���X�̍폜
		delete VectorRect[i];
	}
	//�ϒ��z��̃N���A
	VectorRect.clear();
}
