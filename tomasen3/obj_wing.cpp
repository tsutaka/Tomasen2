
#include "tomasen.hpp"

#include "obj_wing.hpp"
#include "obj_effect.hpp"
 
namespace tm2{

void Friend::update(Tomasen& game){

}
void Friend::draw(Tomasen& game){

}


/*�R���X�g���N�^*/
Enemy::Enemy(){
	//�f�t�H���g�l
	pos = Vec2(0.0, 0.0);		//���݈ʒu
	move = Vec2(0.0, 0.0);		//�ړ���
	dis = 5.0;					//�ړ���
	dir = 0.0;					//�p�x
	frameCnt = 0;				//�o�߃t���[����
	animeCnt = 0;				//�A�j���t���[��
	updateCheck = true;			//�X�V��
	pattern = 0;				//�s���p�^�[��
	targetPos = Vec2(0.0,0.0);	//�ړ��ړI���W
	phase = 0;					//�s���t�F�[�Y
	canShot = 0;				//�ˌ�����
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�

	lockOn = 0;				//���b�N�I��
	boss = 0;				//�{�X�t���O
}
void Enemy::update(Tomasen& game){
	/*�e�p�����[�^���X�V����*/
	frameCnt++;										//�t���[���J�E���g�̍X�V
	/*�A�j���[�V��������*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt >= animeMax){
			animeCnt = 0;
		}
	}
	if(lockOn = 100){
		//���b�N�I���A���[�g
		if(frameCnt % 3 == 0){
			effectFactory(EffectSptr(new LockOnAlart()), 
				getCenterPos().x,	getCenterPos().y, 
				Vec2( getPos().x - tipSize/2 + makeRand(0.0, 30), 
					getPos().y - tipSize/2 - makeRand(250.0, 90) )
				);
		}
	}
	/*���b�N�I������*/
	if(lockOn > 0){
		lockOn--;
	}

	/*�G�@�̈ʒu���X�V*/
	pos.x += move.x;
	pos.y += move.y;
}
void Enemy::draw(Tomasen& game){
	game.IMAGE->drawTile( getPos().x, getPos().y,	//x, y,
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputW(), 
					game.IMAGE->tipNo(	getImageX(),		//ino
									getImageY() ), 
					getImageW(), getImageH()	//ix, iy, 
					);
}

/*�J�E���g�A�b�v��*/
void Friend::addKaihi(int kaihi){
	const int kaihiMin = 0;
	const int kaihiMax = 70;

	Friend::kaihi += kaihi;
	if(Friend::kaihi > kaihiMax){
		Friend::kaihi = kaihiMax;
	}else if(Friend::kaihi < kaihiMin){
		Friend::kaihi = kaihiMin;
	}
}

} //namespace tm2