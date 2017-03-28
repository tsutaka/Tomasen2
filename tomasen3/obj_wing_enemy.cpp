#include "obj_wing_enemy.hpp"

#include <cmath>

#include "tomasen.hpp"
#include "obj_bullet.hpp"

namespace tm2{

/*�O���[�o�����\�[�X��`*/
EnemyVsptr enemyList;				//�G�@���X�g
void enemyFactory(EnemySptr enemy, Vec2 pos, int pattern){
		enemyList.push_back( enemy );					//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(pos);								//�G�@���w��ʒu�Ɉړ�
		(*it)->setPattern(pattern);						//�G�@�̍s���p�^�[���̎w��
}

EnemyA::EnemyA(){
	/*������*/
	name = TEXT("�g��");	//���O
	maxHp = 30;				//�ő�ϋv�x
	imageX = 0;				//�摜x���W
	imageY = 12;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	size = tipSize;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 7.0);	//�ړ���
	hp = maxHp;				//HP
}
void EnemyA::update(Tomasen& game){
	//�e�N���X�̍X�V�֐������s
	Enemy::update(game);
	//���@���^�[�Q�b�g�ɐݒ�
	if(FriendSptr jiki = game.kosenWing.lock()){
		targetPos = jiki->getCenterPos();
	}
}

void EnemyA::action(Object obj){
	/*�e�̔���*/
	if(perCheck(1) && canShot > 0){
		enemyBulletFactory(EnemyBulletSptr( new RedKunaiBullet()), 
			makeRand(getCenterPos().x, 5), getCenterPos().y);
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//A1
		if(phase == 0 && pos.y > makeRand(100.0, 20)){
			phase++;
			move = Vec2(-2.5, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && pos.x < SCREEN_INDENT + 50){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -5.0);	//�ړ���
		}
		break;
	case 1: //A2
		/*�ڕW�ւ̈ړ�*/
		dis = 5.0;
		if(pos.x < targetPos.x - dis) move.x = dis;
		if(pos.y < targetPos.y - dis) move.y = dis;
		if(pos.x > targetPos.x + dis) move.x = -dis;
		if(pos.y > targetPos.y + dis) move.y = -dis;
		if(phase == 0){
			canShot = 1;
			targetPos = Vec2(SCREEN_WIDTH / 2, 150);
		}
		if(phase == 0 && frameCnt >= 500){
			phase++;
			frameCnt = 0; 
		}
		if(phase == 1 && pos.x > SCREEN_WIDTH / 2){
			phase++;
			targetPos = Vec2(SCREEN_WIDTH - SCREEN_INDENT + 500, -500);
		}
		break;
	case 2: //A3
		if(phase == 0){
			phase++;
			move = Vec2(0.0, -6.0);	//�ړ���
		}
		else if(phase == 1 && pos.y < 100){
			phase++;
			move = Vec2(3.0, 1.5);	//�ړ���
			canShot = 1;
		}
		break;
	case 3: //A4
		if(phase == 0){
			phase++;
			move = Vec2(0.0, -6.0);	//�ړ���
		}
		else if(phase == 1 && pos.y < 100){
			phase++;
			move = Vec2(-3.0, 1.5);	//�ړ���
			canShot = 1;
		}
		break;
	case 4: //A5
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 6.0);	//�ړ���
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			dir = PI/2 + 0.1 * makeRand(0.0, 5);	//�p�x
			dis = 5.0;
			move.x = cos(dir) * dis;
			move.y = sin(dir) * dis;
		}
		break;
	case 5: //������
		//setMove�ł��炩���ߏ����ړ��ʂ�ݒ肷��
		move = move + Vec2(-0.0016, 0.0);	//�����x�����Z
		break;
	case 6: //1-1�̓���
		//setMove�ł��炩���ߏ����ړ��ʂ�ݒ肷��
		if(phase == 0 && frameCnt > waitTime){
			move = Vec2(0.0, 0.0);	//�ړ��ʕύX
			phase++;
		}
		if(phase == 1 && frameCnt > waitTime + 100){
			//���@�����ɐ���
			
			/*�^�[�Q�b�g�p�x�̎Z�o*/
			dir = checkDirection(
				targetPos.x, targetPos.y, 
				getCenterPos().x, getCenterPos().y
				);// + PI/2.0;
			dis = 5.0;
			move.x = cos(dir) * dis;
			move.y = sin(dir) * dis;

		}
		if(phase == 2 && frameCnt > waitTime + 300){
			move = Vec2(0.0, -0.6);	//�ړ��ʕύX
		}

		break;

	}

}

EnemyB::EnemyB(){
	/*������*/
	name = TEXT("�}�C��");	//���O
	maxHp = 50;				//�ő�ϋv�x
	imageX = 4;				//�摜x���W
	imageY = 12;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	size = tipSize;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}
void EnemyB::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 20 == 0){
		shotCnt += 0.3;
		enemyBulletFactory(EnemyBulletSptr( new SprinklerBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//�ړ���
		}
		break;
	case 1:	//B2
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 3.0);	//�ړ���
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			move = Vec2(2.0, 0.0);	//�ړ���
		}
		else if(phase == 2 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//�ړ���
		}
		break;
	}
	
}

EnemyC::EnemyC(){
	/*������*/
	name = TEXT("�C���J");	//���O
	maxHp = 300;				//�ő�ϋv�x
	imageX = 8;				//�摜x���W
	imageY = 12;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	size = tipSize;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	hp = maxHp;				//HP
}

void EnemyC::action(Object obj){
	/*�e�̔���*/
	if(canShot > 0 && frameCnt % 60 == 0){
		for(shotCnt = 0.0; shotCnt < 2 * PI; shotCnt += 2 * PI / 10){
			enemyBulletFactory(EnemyBulletSptr( new WeakBullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
	}
	if(canShot > 0 && frameCnt % 120 < 7 && frameCnt % 3 == 0){
		for(shotCnt = -makeRand(4); shotCnt < 2 * PI; shotCnt += 2 * PI / 7){
			enemyBulletFactory(EnemyBulletSptr( new Ene2Bullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//C1
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 4.0);	//�ړ���
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			move = Vec2(0.0, 0.0);	//�ړ���
		}
		else if(phase == 2 && frameCnt > 300){
			phase++;
			canShot = 1;
			move = Vec2(1.0, 0.0);	//�ړ���
		}
		else if(phase == 3 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			phase++;
			canShot = 1;
			move = Vec2(-1.0, 0.0);	//�ړ���
		}
		else if(phase == 4 && pos.x < SCREEN_INDENT + 50){
			phase++;
			canShot = 1;
			move = Vec2(0.0, -4.0);	//�ړ���
		}
		break;
	case 1:	//3-1
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 4.0);	//�ړ���
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			move = Vec2(0.0, 0.0);	//�ړ���
		}
		else if(phase == 2 && frameCnt > 300){
			phase++;
			canShot = 1;
			move = Vec2(1.0, 0.0);	//�ړ���
		}
		else if(phase == 3 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			phase++;
			canShot = 1;
			move = Vec2(-1.0, 0.0);	//�ړ���
		}
		else if(phase == 4 && pos.x < SCREEN_INDENT + 50){
			phase++;
			canShot = 1;
			move = Vec2(0.0, -4.0);	//�ړ���
		}
		break;
	}
	
}

EnemyD::EnemyD(){
	/*������*/
	name = TEXT("���b�N");	//���O
	maxHp = 50;				//�ő�ϋv�x
	imageX = 40;			//�摜x���W
	imageY = 12;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͕�
	size = tipSize;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	hp = maxHp;				//HP
}

void EnemyD::action(Object obj){

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//D1
		move += Vec2(makeRand(0.0, 4) * 0.1, makeRand(1.0, 4) * 0.1);	//�ړ���
		break;
	}
	
}

EnemyE::EnemyE(){
	/*������*/
	name = TEXT("���[�W���b�N");	//���O
	maxHp = 50;				//�ő�ϋv�x
	imageX = 40;			//�摜x���W
	imageY = 12;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͕�
	size = tipSize*5;		//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x

	pattern = 1;
}
void EnemyE::update(Tomasen& game){
	//�e�N���X�̍X�V�֐������s
	Enemy::update(game);
	//���@���^�[�Q�b�g�ɐݒ�
	if(FriendSptr jiki = game.kosenWing.lock()){
		targetPos = jiki->getPos();
	}
}
void EnemyE::action(Object obj){



	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//E1
		move += Vec2(makeRand(0.0, 4) * 0.01, makeRand(1.0, 4) * 0.01);	//�ړ���
		break;
	case 1: //���@�ǔ�
		
		
		//���@�p�x�̎Z�o
		dir = checkDirection(
			targetPos.x, targetPos.y, 
			getCenterPos().x, getCenterPos().y
			);
			
		//���@�����ɐ���
		dis = 0.7;
		move.x = cos(dir) * dis;
		move.y = sin(dir) * dis;
		//move.x = 0;
		//move.y = 1.0;
		break;
	}

	//3Way
	if(frameCnt > 100 && frameCnt % 300 == 1){
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setDir(dir);											//�p�x
		(*it)->setDis(2);											//����
	}
	if(frameCnt > 100 && frameCnt % 300 == 5){
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setDir(dir);											//�p�x
		(*it)->setDis(2.3);											//����
	}
	if(frameCnt > 100 && frameCnt % 300 == 9){
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setDir(dir);											//�p�x
		(*it)->setDis(2.6);											//����
	}

	//���S���΂�܂�
	if(hp < 7){
		for(shotCnt = makeRand(0.0, 7) * 0.05; shotCnt < 2 * PI; shotCnt += 2 * PI / 5){
			enemyBulletFactory(EnemyBulletSptr( new Ene3Bullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
			EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it)->setDis(hp*5);										//�G�@���C�x���g�ʒu�Ɉړ�
		}
		hp = 0;
	}
}

EnemyF::EnemyF(){
	/*������*/
	name = TEXT("�^�R�X");	//���O
	maxHp = 1000;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 14;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	size = tipSize*2;		//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 1.2);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyF::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 100 == 0){
		for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 10){
			enemyBulletFactory(EnemyBulletSptr( new RedKunaiBullet()), 
				getCenterPos().x, getCenterPos().y);
			EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it)->setDir(cnt);										//�G�@���C�x���g�ʒu�Ɉړ�
		}
	} 
	if(canShot > 0 && frameCnt % 150 == 0){
		for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 15){
			enemyBulletFactory(EnemyBulletSptr( new YellowKunaiBullet()), 
				getCenterPos().x, getCenterPos().y);
			EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
			(*it)->setDir(cnt);										//�G�@���C�x���g�ʒu�Ɉړ�
		}
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0){
			canShot = 1;
			if(frameCnt > 300){
				move = Vec2(0.0, -0.4);	//�ړ���
				phase++;
				frameCnt = 0;
			}
		}
		else if(phase == 1){
			canShot = 1;
		}
		break;
	}
	
}

EnemyG::EnemyG(){
	/*������*/
	name = TEXT("�{�[��");	//���O
	maxHp = 15;				//�ő�ϋv�x
	imageX = 0;				//�摜x���W
	imageY = 13;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	size = tipSize;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyG::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 5 == 0){
		shotCnt += 0.5;
		enemyBulletFactory(EnemyBulletSptr( new WeakBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//G1
		phase++;
		move = Vec2(0.0, 0.0);	//�ړ���
		canShot = 1;
		break;
	}
	
}

EnemyH::EnemyH(){
	/*������*/
	name = TEXT("�^�R");	//���O
	maxHp = 70;				//�ő�ϋv�x
	imageX = 4;				//�摜x���W
	imageY = 13;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	size = tipSize;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����

	dis = 3.0;				//�ړ���
	move = Vec2(0.0 + makeRand(0.0, 1) * 0.1, 3.0 + makeRand(0.0, 2));	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyH::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 5 == 0){
		shotCnt += 0.5;
		enemyBulletFactory(EnemyBulletSptr( new GreenBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//H1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, -0.2);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//�ړ���
		}
		break;
	}
	
}

EnemyI::EnemyI(){
	/*������*/
	name = TEXT("UFO");	//���O
	maxHp = 150;			//�ő�ϋv�x
	imageX = 16;			//�摜x���W
	imageY = 12;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	size = tipSize*2;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 10;			//�t���[���҂�����
	
	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyI::action(Object obj){
	/*�e�̔���*/
	


	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//I1
		if(canShot > 0 && frameCnt % 5 == 0){
			shotCnt += PI / 15.0;
			if(shotCnt > PI / 2 ) shotCnt = - PI / 2; 
			enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
		phase++;
		move = Vec2(0.56, 1.043);	//�ړ���
		canShot = 1;
		if(phase > 120) {
			shotCnt = PI / 2; 
			phase = 0;
			pattern = 1;
		}
		break;
	case 1:	//I1
		if(canShot > 0 && frameCnt % 5 == 0){
			shotCnt -= PI / 15.0;
			if(shotCnt < PI / 2 ) shotCnt = PI * 3 / 2; 
			enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
		phase++;
		move = Vec2(-0.56, 1.443);	//�ړ���
		canShot = 1;
		if(phase > 120) {
			shotCnt = PI / 2; 
			phase = 0;
			pattern = 0;
		}
		break;
	}
	
}

EnemyJ::EnemyJ(){
	/*������*/
	name = TEXT("���~");	//���O
	maxHp = 300;				//�ő�ϋv�x
	imageX = 40;			//�摜x���W
	imageY = 14;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	size = tipSize*2;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����
	
	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyJ::update(Tomasen& game){
	//�e�N���X�̍X�V�֐������s
	Enemy::update(game);
	//���@���^�[�Q�b�g�ɐݒ�
	if(FriendSptr jiki = game.kosenWing.lock()){
		targetPos = jiki->getCenterPos();
	}
}
void EnemyJ::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 20 == 0){
		shotCnt += 0.5;
		enemyBulletFactory(EnemyBulletSptr( new Ene2Bullet()), 
			getCenterPos().x-13, getCenterPos().y+10, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setDis(4.5);
	}
	//������3way
	if(canShot > 0 && frameCnt % 50 == 0){
		enemyBulletFactory(EnemyBulletSptr( new RedMBullet()), 
			getCenterPos().x-13, getCenterPos().y+10);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setDir(PI/2.0);
		enemyBulletFactory(EnemyBulletSptr( new RedMBullet()), 
			getCenterPos().x-13, getCenterPos().y+10);
		EnemyBulletVsptr::iterator it2 = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it2)->setDir(PI/2.0 - 0.3);
		enemyBulletFactory(EnemyBulletSptr( new RedMBullet()), 
			getCenterPos().x-13, getCenterPos().y+10);
		EnemyBulletVsptr::iterator it3 = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it3)->setDir(PI/2.0 + 0.3);
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//�ړ���
		}
		break;
	}
	
}

EnemyK::EnemyK(){
	/*������*/
	name = TEXT("�N���m�g��");//���O
	maxHp = 60;				//�ő�ϋv�x
	imageX = 8;				//�摜x���W
	imageY = 13;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	size = tipSize;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����
	
	dis = 3.0;				//�ړ���
	move = Vec2(0.0, -4.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyK::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 2 == 0){
		shotCnt += 0.2;
		enemyBulletFactory(EnemyBulletSptr( new WeakBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//�ړ���
		}
		break;
	case 1:	//���X�^�[�g
		if(phase == 0){
			move = Vec2(1.6, -10.0);
			phase++;
		}
		move += Vec2(0.0, 0.1);	//�ړ���
		
		break;
	case 2:	//�E�X�^�[�g
		if(phase == 0){
			move = Vec2(-1.6, -10.0);
			phase++;
		}
		move += Vec2(0.0, 0.1);	//�ړ���
		
		break;
	}
	
}

EnemyL::EnemyL(){
	/*������*/
	name = TEXT("�T�e���C�g");	//���O
	maxHp = 600;				//�ő�ϋv�x
	imageX = 16;				//�摜x���W
	imageY = 14;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	size = tipSize*2;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����
	
	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyL::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 5 == 0){
		shotCnt += 0.2;
		enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
			getCenterPos().x + makeRand(0.0, 10)*0.1, getCenterPos().y);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setDis(7.3);			//�G�@���C�x���g�ʒu�Ɉړ�
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(1.0, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			move = Vec2(-1.0, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && pos.x < SCREEN_INDENT + 50){
			move = Vec2(1.0, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//�ړ���
		}
		break;
	}
	
}

EnemyN::EnemyN(){
	/*������*/
	name = TEXT("���U�@");	//���O
	maxHp = 150;				//�ő�ϋv�x
	imageX = 24;				//�摜x���W
	imageY = 12;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	size = tipSize*2;			//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����
	
	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x
}

void EnemyN::action(Object obj){
	/*�e�̔���*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 10 == 0){
		shotCnt += 0.6;
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//�ړ���
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//�ړ���
		}
		break;
	case 1:	//5-2�E
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			move += Vec2(-0.1, 0.1);	//�ړ���
			canShot = 1;
		}
		break;
	case 2:	//5-2��
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			move += Vec2(0.1, 0.1);	//�ړ���
			canShot = 1;
		}
		break;
	}
	
}

EnemyO::EnemyO(){
	/*������*/
	name = TEXT("�{�X");	//���O
	maxHp = 3000;			//�ő�ϋv�x
	imageX = 24;			//�摜x���W
	imageY = 14;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	size = tipSize*2;		//�����蔻�蒼�a
	animeMax = 4;			//�t���[����
	animeWait = 4;			//�t���[���҂�����
	
	dis = 3.0;				//�ړ���
	move = Vec2(0.0, 2.0);	//�ړ���
	hp = maxHp;				//HP
	shotCnt = 0.0;			//�ˌ��p�x

	boss = 1;				//�{�X�t���O
}

void EnemyO::action(Object obj){
	/*�ړ������̌���*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//�ړ���
			canShot = 1;
		}
		if(phase == 1){
			if(canShot > 0 && frameCnt % 20 == 0){
				enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
					getCenterPos().x, getCenterPos().y);
				EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
				(*it)->setDis(7.3);			//�G�@���C�x���g�ʒu�Ɉړ�
			}
		}
		if(phase == 1 && frameCnt > 600){
			phase++;
			frameCnt = 0;
		}
		if(phase == 2){ 
			if(canShot > 0 && frameCnt % 200 == 0){
				for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 8){
					enemyBulletFactory(EnemyBulletSptr( new RedKunaiBullet()), 
						getCenterPos().x, getCenterPos().y);
					EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
					(*it)->setDir(cnt);										//�G�@���C�x���g�ʒu�Ɉړ�
				}
			} 
			if(canShot > 0 && frameCnt % 350 == 0){
				for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 9){
					enemyBulletFactory(EnemyBulletSptr( new YellowKunaiBullet()), 
						getCenterPos().x, getCenterPos().y);
					EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
					(*it)->setDir(cnt);										//�G�@���C�x���g�ʒu�Ɉړ�
				}
			}
		}
		if(phase == 2 && frameCnt > 600){
			phase = 1;
			frameCnt = 0;
		}
		break;
	}
	
}

} //namespace tm2