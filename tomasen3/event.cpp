#include <cmath>

#include "event.hpp"
#include "drawtext.hpp"

#include "localcommon.hpp"
#include "obj_effect.hpp"
#include "obj_wing_enemy.hpp"

namespace tm2{

/*�O���[�o�����\�[�X��`*/
EventVsptr eventList;		//�C�x���g���X�g
void eventFactory(EventSptr event){
		eventList.push_back( event );			//���X�g�ɃI�u�W�F�N�g�ǉ�
}

/*�R���X�g���N�^*/
Event::Event(){
	pos = Vec2(0.0, 0.0);	//���݈ʒu
	dis = 0.0;				//�ړ���
	dir = 0.0;				//�p�x
	frameCnt = 0;			//�t���[���J�E���g
	phase = 0;				//�t�F�[�Y
	next = 0;			//�C�x���g�I���t���O
}

/*�X�V�֐�*/
void Event::update(Tomasen& game){
	/*�J�E���g�A�b�v*/
	frameCnt++;
	/*�C�x���g�̈ʒu���X�V*/
	pos.x += cos(dir) * dis;
	pos.y += sin(dir) * dis;
}


/*�A�N�V�����֐��i�ʁj*/
void GameTitle::action(Tomasen& game){

	/*���͎�t*/
	if(GetAsyncKeyState(VK_SPACE) && phase >= 1) {//SPACE
		next = 1;	//�I������t���O
		effectList.clear();
	}
	if(GetAsyncKeyState(VK_ESCAPE) && phase >= 1) {//VK_ESCAPE
		next = 999;	//�I������t���O
	}
	if(frameCnt >= 1000 && game.mode != -1) {//�f���J�n
		next = 1000;	//�f�����[�h��
	}
	/*�^�C���X�P�W���[��*/
	if(phase == 0){
		phase++;
		effectFactory( EffectSptr(new DarkR()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new DarkY()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new DarkG()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new DarkB()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightB()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightG()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightY()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightR()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleTo()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleMa()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleSe()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleNi()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�

		effectFactory( EffectSptr(new Earth()), 
			Vec2(SCREEN_WIDTH/2 - 10*tipSize/2, -100), //10 = outputW
			Vec2(SCREEN_WIDTH/2 - 10*tipSize/2, SCREEN_HEIGHT-200) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it)->setMoveMode(0);										//�G�t�F�N�g���w��ʒu�Ɉړ�
	}
	else if(phase == 1 && frameCnt == 100){
		phase++;
		effectFactory( EffectSptr(new PushSpace()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�

	}
	else if(phase == 2 && frameCnt == 500){
		phase++;
		//effectFactory( EffectSptr(new TextScreen()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�

	}
}

/*�R���X�g���N�^*/
Stage1::Stage1(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//�����ʒu
}
/*�A�N�V�����֐��i�ʁj*/
void Stage1::action(Tomasen& game){
	/*STAGE1�̓G�L��������*/
	
	if(phase == 0 && frameCnt == 0 ){
		effectFactory( EffectSptr(new DarkR()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it)->setTargetPos(Vec2(50.0, 150.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�

		effectFactory( EffectSptr(new DarkY()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it2 = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setTargetPos(Vec2(50.0, 200.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�

		effectFactory( EffectSptr(new DarkG()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it3 = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it3)->setTargetPos(Vec2(50.0, 250.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�

		effectFactory( EffectSptr(new DarkB()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it4 = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it4)->setTargetPos(Vec2(50.0, 300.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�

		effectFactory( EffectSptr(new TitleTo()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it5 = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it5)->setTargetPos(Vec2(50.0, 150.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�

		effectFactory( EffectSptr(new TitleMa()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it6 = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it6)->setTargetPos(Vec2(50.0, 200.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�

		effectFactory( EffectSptr(new TitleSe()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it7 = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it7)->setTargetPos(Vec2(50.0, 250.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�

		effectFactory( EffectSptr(new TitleNi()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it8 = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it8)->setTargetPos(Vec2(50.0, 300.0));						//�G�t�F�N�g���w��ʒu�Ɉړ�
	}
	/*�f��*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Earth()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�

	}


	/*1�ʂ̔w�i*/
	
	if(frameCnt % 5 == 0){
		effectFactory( EffectSptr(new Star1()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.6));								//�������Ɉړ�
	}
	if(frameCnt % 7 == 0){
		effectFactory( EffectSptr(new Star2()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.6));								//�������Ɉړ�
	}


	/*1-1*/
	//�Z���^�[�o���^
	if(phase == 0 && frameCnt < 200 && frameCnt % 50 == 0){

		if(frameCnt % 100 == 0){
			enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
			EnemyVsptr::iterator it3 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it3)->setPos(Vec2(SCREEN_WIDTH / 2.0 - 60, -40.0));			//�G�@���C�x���g�ʒu�Ɉړ�
			(*it3)->setMove(Vec2(0.0, 1.6));								//�G�@���C�x���g�ʒu�Ɉړ�
			(*it3)->setPattern(6);										//�G�@�̍s���p�^�[���̎w��
			(*it3)->setWaitTime(300 - frameCnt);									//�ҋ@����

			enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
			EnemyVsptr::iterator it4 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it4)->setPos(Vec2(SCREEN_WIDTH / 2.0, -40.0));			//�G�@���C�x���g�ʒu�Ɉړ�
			(*it4)->setMove(Vec2(0.0, 1.6));								//�G�@���C�x���g�ʒu�Ɉړ�
			(*it4)->setPattern(6);										//�G�@�̍s���p�^�[���̎w��
			(*it4)->setWaitTime(300 - frameCnt);									//�ҋ@����

			enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
			EnemyVsptr::iterator it5 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it5)->setPos(Vec2(SCREEN_WIDTH / 2.0 + 60, -40.0));			//�G�@���C�x���g�ʒu�Ɉړ�
			(*it5)->setMove(Vec2(0.0, 1.6));								//�G�@���C�x���g�ʒu�Ɉړ�
			(*it5)->setPattern(6);										//�G�@�̍s���p�^�[���̎w��
			(*it5)->setWaitTime(300 - frameCnt);									//�ҋ@����
		}
		else{
			enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
			EnemyVsptr::iterator it1 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it1)->setPos(Vec2(SCREEN_WIDTH / 2.0 - 30, -40.0));			//�G�@���C�x���g�ʒu�Ɉړ�
			(*it1)->setMove(Vec2(0.0, 1.6));								//�G�@���C�x���g�ʒu�Ɉړ�
			(*it1)->setPattern(6);										//�G�@�̍s���p�^�[���̎w��
			(*it1)->setWaitTime(300 - frameCnt);									//�ҋ@����

			enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
			EnemyVsptr::iterator it2 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it2)->setPos(Vec2(SCREEN_WIDTH / 2.0 + 30, -40.0));			//�G�@���C�x���g�ʒu�Ɉړ�
			(*it2)->setMove(Vec2(0.0, 1.6));								//�G�@���C�x���g�ʒu�Ɉړ�
			(*it2)->setPattern(6);										//�G�@�̍s���p�^�[���̎w��
			(*it2)->setWaitTime(300 - frameCnt);									//�ҋ@����
		}


	}
	if(phase == 0 && frameCnt > 250){
		phase++;
		frameCnt = 0;
	}
	/*1-2*/
	//���ォ��o��
	if(phase == 1 && frameCnt < 250 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT - 50, -50));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(2);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 1 && frameCnt > 500){
		phase++;
		frameCnt = 0;
	}
	/*1-3*/
	//��납��o��
	if(phase == 2 && frameCnt > 350){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyB()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 3 && frameCnt < 400 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT + 80, SCREEN_HEIGHT + 50));	//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(2);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 3 && frameCnt < 400 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH-SCREEN_INDENT-80, SCREEN_HEIGHT + 50));	//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(3);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 3 && frameCnt > 600){
		phase++;
		frameCnt = 0;
	}
	/*1-4*/
	//�O����܌��J
	if(phase == 4){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyB()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT +50, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(1);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 5 && frameCnt % 30 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2,  -50));	//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(4);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 5 && frameCnt > 400){
		phase++;
		frameCnt = 0;
	}
	/*1-5*/
	//�Z���^�[�ɃC���J����
	if(phase == 6){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyC()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if (phase ==7 && frameCnt > 1100){
		next = 2;
	}

}
/*�A�N�V�����֐��i�ʁj*/

Stage2::Stage2(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//�����ʒu
}
/*�A�N�V�����֐��i�ʁj*/
void Stage2::action(Tomasen& game){
	/*STAGE2�̓G�L��������*/
	
	/*2�ʂ̔w�i*/
	
	if(frameCnt % 14 == 0){
		effectFactory( EffectSptr(new Star1()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.5));								//�������Ɉړ�
	}
	if(frameCnt % 12 == 0){
		effectFactory( EffectSptr(new Star2()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.5));								//�������Ɉړ�
	}

	/*�f��*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Mars()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
	}
	
	/*2-1*/
	//�E�ォ��f��
	if(phase == 0 && frameCnt < 200 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyD()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(makeRand(pos.x, 7), pos.y));			//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);
	}
	if(phase == 0 && frameCnt > 250){
		phase++;
		frameCnt = 0;
	}
	/*2-2*/
	//���[�v�o��
	if(phase == 1 && frameCnt < 1500 && frameCnt % 100 == 0){
		effectList.push_back( EffectSptr(new Marker()) );
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(
			SCREEN_WIDTH/2 + makeRand(0.0, 200), 
			SCREEN_HEIGHT/2 - 200 + makeRand(0.0, 100)));				//�G�t�F�N�g���C�x���g�ʒu�Ɉړ�
	}
	if(phase == 1 && frameCnt > 1600){
		phase++;
		frameCnt = 0;
	}
	/*2-3*/
	//�������{�X
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyF()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 3 && frameCnt > 900){
		phase++;
	}
	if (phase == 4 && frameCnt > 1200){
		next = 3;
	}
}
/*�A�N�V�����֐��i�ʁj*/
Stage3::Stage3(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//�����ʒu
}
/*�A�N�V�����֐��i�ʁj*/
void Stage3::action(Tomasen& game){
	/*STAGE3�̓G�L��������*/
		
	/*3�ʂ̔w�i*/
	
	if(frameCnt % 4 == 0){
		effectFactory( EffectSptr(new Star1()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.4));								//�������Ɉړ�
	}
	if(frameCnt % 6 == 0){
		effectFactory( EffectSptr(new Star2()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.4));								//�������Ɉړ�
	}

	/*�f��*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Jupiter()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
	}
		
	/*3-1*/
	//�C���J
	if(phase == 0 && frameCnt < 200 && frameCnt == 10){
		enemyList.push_back( EnemySptr(new EnemyC()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT +200.0 + makeRand(0.0, 7), -50));			//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(1);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 0 && frameCnt > 250){
		phase++;
		frameCnt = 0;
	}
	/*3-2*/
	//�^�R
	if(phase == 1 && frameCnt < 600 && frameCnt % 150 == 0){
		enemyList.push_back( EnemySptr(new EnemyH()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2 + makeRand(0.0, 100), -100));//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 1 && frameCnt > 800){
		phase++;
		frameCnt = 0;
	}
	/*3-3*/
	//���[�t�H�[
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyI()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 3 && frameCnt > 300){
		phase++;
	}
	if (phase == 4 && frameCnt > 700){
		next = 4;
	}
}
/*�A�N�V�����֐��i�ʁj*/
Stage4::Stage4(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//�����ʒu
}
/*�A�N�V�����֐��i�ʁj*/
void Stage4::action(Tomasen& game){
	/*STAGE4�̓G�L��������*/
	
	
	/*4�ʂ̔w�i*/
	if(frameCnt % 30 == 0){
		effectFactory( EffectSptr(new Star1()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.3));								//�������Ɉړ�
	}
	if(frameCnt % 28 == 0){
		effectFactory( EffectSptr(new Star2()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.3));								//�������Ɉړ�		//�C�x���g�ʒu�Ɉړ�
	}	

	/*�f��*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Saturn()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
	}
	if(phase == 0){					
		phase = 2;//test
	}
	/*4-1*/
	//���P�b�g����
	if(phase == 0 && frameCnt < 200 && frameCnt == 10){
		enemyList.push_back( EnemySptr(new EnemyJ()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH/2,  + 10));			//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 0 && frameCnt > 800){
		frameCnt = 0;
		phase++;
	}
	/*4-2*/
	//������
	if(phase == 1 && frameCnt < 350 && frameCnt % 80 == 0){
		enemyList.push_back( EnemySptr(new EnemyK()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT - 50, SCREEN_HEIGHT - 50));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(1);										//�G�@�̍s���p�^�[���̎w��

		enemyList.push_back( EnemySptr(new EnemyK()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it2 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT - 50));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it2)->setPattern(2);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 1 && frameCnt > 600){
		frameCnt = 0;
		phase++;
	}
	/*4-3*/
	//�T�e���C�g�A���e�i
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyL()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 3 && frameCnt > 900){
		phase++;
	}
	if (phase ==4 && frameCnt > 1100){
		next = 5;
	}
}
/*�A�N�V�����֐��i�ʁj*/
Stage5::Stage5(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//�����ʒu
}
/*�A�N�V�����֐��i�ʁj*/
void Stage5::action(Tomasen& game){
	/*STAGE5�̓G�L��������*/
	
	/*3�ʂ̔w�i*/
	if(frameCnt % 51 == 0){
		effectFactory( EffectSptr(new Star1()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.1));								//�������Ɉړ�
	}
	if(frameCnt % 38 == 0){
		effectFactory( EffectSptr(new Star2()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//�C�x���g�ʒu�Ɉړ�
		(*it)->setMove(Vec2(0.0, 1.1));								//�������Ɉړ�		//�C�x���g�ʒu�Ɉړ�
	}

	/*�f��*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Uranus()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
	}
	
	/*5-1*/
	if(phase == 0 && frameCnt < 200 && frameCnt % 20 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(makeRand(pos.x, 7), pos.y));			//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 0 && frameCnt > 650){
		phase++;
		frameCnt = 0;
	}
	/*5-2*/
	if(phase == 1 && frameCnt < 450 && frameCnt % 50 == 0){
		enemyList.push_back( EnemySptr(new EnemyN()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT + 300, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(1);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 1 && frameCnt < 450 && frameCnt % 50 == 25){
		enemyList.push_back( EnemySptr(new EnemyN()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT + 50, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(2);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 1 && frameCnt > 600){
		phase++;
		frameCnt = 0;
	}
	/*5-3*/
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyO()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��

		enemyList.push_back( EnemySptr(new EnemyO()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it2 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setPos(Vec2(SCREEN_WIDTH / 2 - 90, -100));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it2)->setPattern(0);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 3 && frameCnt > 600){
		phase++;
		frameCnt = 0;
	}
	if(phase == 4 && frameCnt < 400 && frameCnt % 30 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT + 80, SCREEN_HEIGHT + 50));	//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(2);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 4 && frameCnt < 400 && frameCnt % 30 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_WIDTH-SCREEN_INDENT-80, SCREEN_HEIGHT + 50));	//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(3);										//�G�@�̍s���p�^�[���̎w��
	}
	if(phase == 4 && frameCnt > 900){
		phase++;
		frameCnt = 0;
	}
	if(phase == 5 && frameCnt < 350 && frameCnt % 90 == 0){
		enemyList.push_back( EnemySptr(new EnemyK()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(SCREEN_INDENT - 50, SCREEN_HEIGHT - 50));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(1);										//�G�@�̍s���p�^�[���̎w��

		enemyList.push_back( EnemySptr(new EnemyK()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it2 = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT - 50));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it2)->setPattern(2);										//�G�@�̍s���p�^�[���̎w��
	}
	if(game.bossFlag >= 2){
		phase = 6;
		frameCnt = 0;
	}
	/*�f��*/
	if(phase == 6 && frameCnt == 0 ){
		effectFactory( EffectSptr(new Neptune()) );	//���X�g�ɃI�u�W�F�N�g�ǉ�
		next = 6;
	}
}
/*�A�N�V�����֐��i�ʁj*/
void GameOver::action(Tomasen& game){


	//���U���g�̏o���ɂ��Ă�gameResult���Q�Ƃ���tomasen�Ŏ��s���Ă���
	//�Q�[���I�[�o�[�C�x���g�ɂ��Ă����̏�ō쐬�����
	
	/*�^�C���X�P�W���[��*/
	if(phase == 0 && frameCnt > 100){
		/*������*/
		next = 998;
	}

}
/*�A�N�V�����֐��i�ʁj*/
void GameClear::action(Tomasen& game){

	/*�^�C���X�P�W���[��*/
	
	if(phase == 0 && frameCnt == 10){
		/*���@HP�{�[�i�X*/
		if(FriendSptr tmp = game.kosenWing.lock()){
			game.score += tmp->getHp() * 100;
		}
		/*�Q�[���N���A�̕\��*/
		effectFactory( EffectSptr(new DarkR()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new DarkY()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new DarkG()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new DarkB()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightB()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightG()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightY()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new LightR()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleTo()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleMa()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleSe()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		effectFactory( EffectSptr(new TitleNi()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�

		phase++;

	}


	/*���U���g*/
	

	/*�G���f�B���O�̕\��*/

	/*�X�^�b�t���[��*/

	/*�X�^�b�t���[����*/
	if(phase == 1 && frameCnt > 500){
		/*�X�^�b�t���[��*/
		next = 1001;
	}
}

/*�A�N�V�����֐��i�ʁj*/
void StaffRoll::action(Tomasen& game){

	/*�^�C���X�P�W���[��*/
	
	if(phase == 0 && frameCnt == 300){
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it)->setName("���O���t�B�b�N��");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 - 10));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 10));

		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it2 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setName("�Ɓ[��");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 + 10));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10));
		phase++;
		frameCnt = 0;
	}
	else if(phase == 1 && frameCnt == 300){
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it)->setName("���a�f�l�^�r�d��");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 10));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it2 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setName("�������[");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10));

		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it3 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it3)->setName("�Ɓ[���");
		(*it3)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it3)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30));

		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it4 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it4)->setName("�݂����");
		(*it4)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it4)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50));

		phase++;
		frameCnt = 0;
	}
	else if(phase == 2 && frameCnt == 300){
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it)->setName("�����^�v���O���~���O��");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 - 10));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 10));

		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it2 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setName("�Ӂ[�݂�");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 + 10));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10));
		phase++;
		frameCnt = 0;
	}
	else if(phase == 3 && frameCnt == 300){
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it)->setName("���X�y�V�����T���N�X��");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it2 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setName("���݂�");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it3 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it3)->setName("�ɂ��");
		(*it3)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it3)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it4 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it4)->setName("���񂱂�");
		(*it4)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it4)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it5 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it5)->setName("���Ƃ���");
		(*it5)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it5)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it6 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it6)->setName("����[����");
		(*it6)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it6)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40));
		
		phase++;
		frameCnt = 0;
	}
	else if(phase == 4 && frameCnt == 300){
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it)->setName("�����쁡");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 80));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it2 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setName("�r");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it3 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it3)->setName("�s");
		(*it3)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it3)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it4 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it4)->setName("�f");
		(*it4)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it4)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it5 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it5)->setName("��");
		(*it5)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it5)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it6 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it6)->setName("��");
		(*it6)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it6)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it7 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it7)->setName("��");
		(*it7)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it7)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40));
		
		effectFactory( EffectSptr(new TextBox()) );		//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it8 = effectList.end() - 1;			//���O�̃I�u�W�F�N�g���Q��
		(*it8)->setName("��");
		(*it8)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it8)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60));
		
		phase++;
		frameCnt = 0;
	}
	else if(phase == 5 && frameCnt == 1000){/*�Q�[���N���A�̕\��*/
		next = 998;
	}


}

} //namespace tm2