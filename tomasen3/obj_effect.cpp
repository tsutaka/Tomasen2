#include "obj_effect.hpp"

#include "localcommon.hpp"
#include "tomasen.hpp"

namespace tm2{

/*�O���[�o�����\�[�X��`*/
EffectVsptr effectList;				//�G�t�F�N�g���X�g
void effectFactory(EffectSptr effect){
		effectList.push_back( effect );							//���X�g�ɃI�u�W�F�N�g�ǉ�
}
void effectFactory(EffectSptr effect, Vec2 pos, Vec2 targetPos){
		effectList.push_back( effect );							//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(pos);										//�G�t�F�N�g���w��ʒu�Ɉړ�
		(*it)->setTargetPos(targetPos);							//�G�t�F�N�g�ڕW�ʒu���w��
}
void effectFactory(EffectSptr effect, double centerX, double centerY, Vec2 targetCenterPos){
		effectList.push_back( effect );							//���X�g�ɃI�u�W�F�N�g�ǉ�
		EffectVsptr::iterator it = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2));	//�G�t�F�N�g���w��ʒu�Ɉړ�
		(*it)->setTargetPos(Vec2(targetCenterPos.x - (*it)->getOutputW()*tipSize/2, 
						   targetCenterPos.y - (*it)->getOutputH()*tipSize/2));							//�G�t�F�N�g�ڕW�ʒu���w��
}

Effect::Effect(){
	hp = 1;						//�ϋv�x
	pos = Vec2(0.0, 0.0);		//�ʒu
	targetPos = Vec2(0.0, 0.0);	//�ʒu
	dis = 0.0;					//�ړ���
	dir = 0.0;					//�p�x
	size = 1;
	frameCnt = 0;				//������̌o�߃t���[����
	animeCnt = 0;				//���݂̃A�j���t���[��
	updateCheck = 0;			//�X�V��
	outputW = 1;				//�o�͕�
	outputH = 1;				//�o�͍�
	moveMode = 0;				//0:��{�G�t�F�N�g
	animeMax = 4;				//�A�j���[�V��������
	animeWait = 12;			//�A�j���[�V�����P���̃t���[����
}

void Effect::update(Tomasen& game){
	/*�J�E���g�A�b�v*/
	frameCnt++;
	if(frameCnt > 10000) frameCnt = 0;
	/*�A�j���[�V��������*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt % animeMax == 0){
			animeCnt = 0;
		}
	}

	/*�I�u�W�F�N�g�ړ�*/
	switch(moveMode){
	case 0://�^�[�Q�b�g�ړ����[�h(����������)
		pos.x += (targetPos.x - pos.x) / 50;
		pos.y += (targetPos.y - pos.y) / 50;
		break;
	case 1://�����ړ����[�h
		pos.x += cos(dir) * dis;
		pos.y += sin(dir) * dis;
		break;
	case 2://�����ړ����[�h
		pos.x += move.x;
		pos.y += move.y;
		break;
	case 3://�^�[�Q�b�g�ړ����[�h(����������)
		move.x += 1;
		if(move.x >= 20){
			move.x = 20;
		}
		pos.x += move.x * (((targetPos.x - pos.x) < 0)?-1:1);
		if((targetPos.x - pos.x) <= 20 && (targetPos.x - pos.x) >= -20 ){
			pos.x = targetPos.x;
		}

		move.y += 0.01;
		if(move.y >= 5){
			move.y = 5;
		}
		pos.y += move.y * (((targetPos.y - pos.y) < 0)?-1:1);
		if((targetPos.y - pos.y) <= 5 && (targetPos.y - pos.y) >= -5 ){
			pos.y = targetPos.y;
		}
		break;
	}
	/*�J�E���g�_�E��*/
	timeOfLife--;
	if(timeOfLife < 0) timeOfLife = 0;
}

void Effect::draw(Tomasen& game){
	/*�G�t�F�N�g�`��*/
	game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					100);
}

Earth::Earth(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 0;				//�摜x���W
	imageY = 26;			//�摜y���W
	imageW = 4;				//�摜��
	imageH = 4;				//�摜��
	outputW = 10;			//�o�͕�
	outputH = 10;			//�o�͍�
	animeMax = 3;			//�A�j���[�V��������
	animeWait = 16;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	dir = PI / 2;				//����
	dis = 0.5;				//�ړ���
	moveMode = 1;				//1:�f���G�t�F�N�g
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT-200);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT-100);		//�ڕW�ʒu
}

Mars::Mars(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 16;			//�摜x���W
	imageY = 26;			//�摜y���W
	imageW = 4;				//�摜��
	imageH = 4;				//�摜��
	outputW = 10;			//�o�͕�
	outputH = 10;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 16;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	dir = PI / 2;				//����
	dis = 1.5;				//�ړ���
	moveMode = 1;				//1:�f���G�t�F�N�g
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

Jupiter::Jupiter(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 26;			//�摜y���W
	imageW = 4;				//�摜��
	imageH = 4;				//�摜��
	outputW = 14;			//�o�͕�
	outputH = 14;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 16;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	dir = PI / 2;				//����
	dis = 1.5;				//�ړ���
	moveMode = 1;				//1:�f���G�t�F�N�g
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

Saturn::Saturn(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 0;			//�摜x���W
	imageY = 30;			//�摜y���W
	imageW = 4;				//�摜��
	imageH = 6;				//�摜��
	outputW = 14;			//�o�͕�
	outputH = 21;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 16;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	dir = PI / 2;				//����
	dis = 1.5;				//�ړ���
	moveMode = 1;				//1:�f���G�t�F�N�g
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

Uranus::Uranus(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 16;			//�摜x���W
	imageY = 30;			//�摜y���W
	imageW = 4;				//�摜��
	imageH = 6;				//�摜��
	outputW = 12;			//�o�͕�
	outputH = 18;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 16;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	dir = PI / 2;				//����
	dis = 1.5;				//�ړ���
	moveMode = 1;				//1:�f���G�t�F�N�g
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

Neptune::Neptune(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 30;			//�摜y���W
	imageW = 4;				//�摜��
	imageH = 4;				//�摜��
	outputW = 12;			//�o�͕�
	outputH = 12;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 16;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	dir = PI / 2;				//����
	dis = 1.5;				//�ړ���
	moveMode = 1;				//1:�f���G�t�F�N�g
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

LockOnAlart::LockOnAlart(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 20;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 4;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 10;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

Explosion::Explosion(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 18;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 50;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

Smoke::Smoke(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 22;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 50;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);					//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);		//�ڕW�ʒu
}

TitleTo::TitleTo(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 0;				//�摜x���W
	imageY = 18;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH+wideArea/2, 10*tipSize);					//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, 10*tipSize);		//�ڕW�ʒu
}

TitleMa::TitleMa(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 8;				//�摜x���W
	imageY = 18;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, SCREEN_HEIGHT+wideArea/2);	//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, 10*tipSize);			//�ڕW�ʒu
}

TitleSe::TitleSe(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 16;			//�摜x���W
	imageY = 18;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(-wideArea/2, 14*tipSize);							//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}

TitleNi::TitleNi(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 24;			//�摜x���W
	imageY = 18;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, -wideArea/2);		//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}


DarkR::DarkR(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 0;				//�摜x���W
	imageY = 22;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, SCREEN_HEIGHT+wideArea/2);	//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, 10*tipSize);			//�ڕW�ʒu
}

LightR::LightR(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 8;				//�摜x���W
	imageY = 22;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH+wideArea/2, SCREEN_HEIGHT+wideArea/2);		//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, 10*tipSize);		//�ڕW�ʒu
}

DarkY::DarkY(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 0;				//�摜x���W
	imageY = 20;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(-wideArea/2, SCREEN_HEIGHT+wideArea/2);				//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}

LightY::LightY(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 8;				//�摜x���W
	imageY = 20;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH+wideArea/2, -wideArea/2);				//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}

DarkG::DarkG(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 16;			//�摜x���W
	imageY = 22;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(-wideArea/2, -wideArea/2);							//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}

LightG::LightG(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 24;			//�摜x���W
	imageY = 22;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH+wideArea/2, 10*tipSize);							//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}

DarkB::DarkB(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 16;			//�摜x���W
	imageY = 20;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, -wideArea/2);		//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}

LightB::LightB(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 24;			//�摜x���W
	imageY = 20;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(-wideArea/2, 10*tipSize);							//�����ʒu
	targetPos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, 10*tipSize);	//�ڕW�ʒu
}

PushSpace::PushSpace(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 0;				//�摜x���W
	imageY = 24;			//�摜y���W
	imageW = 8;				//�摜��
	imageH = 2;				//�摜��
	outputW = 16;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 2;				//�T�C�Y
	timeOfLife = 3000;		//�����t���[��
	pos = Vec2(SCREEN_WIDTH/2-4*tipSize*2, SCREEN_HEIGHT+wideArea/2);	//�����ʒu
	targetPos = Vec2(SCREEN_WIDTH/2-4*tipSize*2, 20*tipSize);	//�ڕW�ʒu
}

Wakka::Wakka(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 40;				//�摜x���W
	imageY = 22;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 100;		//�����t���[��
}
void Wakka::draw(Tomasen &game){
	/*�G�t�F�N�g�`��*/
	game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					timeOfLife * 150 / 100);

}
Star1::Star1(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 42;			//�摜x���W
	imageY = 23;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
	animeMax = 1;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	moveMode = 2;			//2:XY�ړ��ʈړ�
}
void Star1::draw(Tomasen &game){
	/*�G�t�F�N�g�`��*/
	//�f�t�H���g
	Effect::draw(game);
	//���F�Ȃ�
	/*game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					255);*/

}
Star2::Star2(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 43;			//�摜x���W
	imageY = 23;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
	animeMax = 1;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
	moveMode = 2;			//2:XY�ړ��ʈړ�
}
void Star2::draw(Tomasen &game){
	/*�G�t�F�N�g�`��*/
	//�f�t�H���g
	Effect::draw(game);
	//���F�Ȃ�
	/*game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					255);*/
}
Dust1::Dust1(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 45;			//�摜x���W
	imageY = 22;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
	animeMax = 1;			//�A�j���[�V��������
	animeWait = 6;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 100;		//�����t���[��
	moveMode = 0;			//2:XY�ړ��ʈړ�
}
TextScreen::TextScreen(){
	
	timeOfLife = 1000;		//�����t���[��

	//�e�L�X�g�`��N���X�̏�����
	TEXT = new DrawTextImage();
	/*�e�L�X�g�̏���*/
	TEXT->addText("�̂ނ����@�y����͌n�̔ޕ��ŁE�E�E");
	TEXT->addText("��͑�q�C����̒n���Ɏc���ꂽ�l�ނɊ�@�������Ă����B");
	TEXT->addText("��C�����ōr�p���������n���͎������͊������ɐ����ł�����ł͂Ȃ������B");
	TEXT->addText("�l�ނ����Ԕ�s�ɐ������Ă���P�O�O�N�A");
	TEXT->addText("�n����̍Ō�̐l�ނ͒n�����̂Ă邱�Ƃ����f�����B");
	TEXT->addText("�����Ĉِ��l��忂��F���ցA�����̒n�����ߔ�ї������̂������B");
}
void TextScreen::update(Tomasen &game){
	/*�e�N���X�̍X�V*/
	Effect::update(game);


}
void TextScreen::draw(Tomasen &game){
	/*�G�t�F�N�g�`��*/
	TEXT->draw(*(game.IMAGE));
}

TextBox::TextBox(){
	maxHp = 1;				//�ő�ϋv�x
	timeOfLife = 999;		//�����t���[��
	size = 1;				//�T�C�Y
	moveMode = 3;

	pos = Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, 
			SCREEN_HEIGHT / 2);
	targetPos = Vec2(SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2);
}
void TextBox::draw(Tomasen &game){
	/*�G�t�F�N�g�`��*/
	game.IMAGE->printText(pos.x, pos.y, name.c_str());
	game.IMAGE->printText(pos.x, pos.y+10, name2.c_str());
}

void TextBox::update(Tomasen& game){
	/*�e�N���X�̍X�V���Ăяo��*/
	Effect::update(game);
	
	//������������g�O�ւ̈ړ�
	if(frameCnt == 250){
		move = Vec2(0.0, 0.0);
		targetPos = Vec2(0,
		SCREEN_HEIGHT / 2);
	}
}
void TextBox::setName2(string name2){
	TextBox::name2 = name2;
}
Marker::Marker(){
	maxHp = 1;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 20;			//�摜y���W
	imageW = 2;				//�摜��
	imageH = 2;				//�摜��
	outputW = 2;			//�o�͕�
	outputH = 2;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 12;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 100;		//�����t���[��
	moveMode = 1;			//1:XY�ړ��ʈړ�
}
void Marker::update(Tomasen& game){
	/*�e�̍X�V���\�b�h*/
	Effect::update(game);
	timeOfLife -= 2;
	if(timeOfLife < 0) timeOfLife = 0;

	//�G�̐���
	if(timeOfLife <= 0){
		enemyList.push_back( EnemySptr(new EnemyE()) );				//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyVsptr::iterator it = enemyList.end() - 1;				//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(makeRand(pos.x, 7), pos.y));				//�G�@���C�x���g�ʒu�Ɉړ�
		(*it)->setPattern(1);										//�G�@�̍s���p�^�[���̎w��
		game.MUSIC->Play(musicWarp);
	}
}
void Marker::draw(Tomasen& game){
	/*�G�t�F�N�g�`��*/
	game.IMAGE->drawAlphaBlendTile(
		Vec2(
			getCenterPos().x - (double)timeOfLife/2,
			getCenterPos().y - (double)timeOfLife/2),
		(double)timeOfLife,
		(double)timeOfLife,
		getImageX(),
		getImageY(),
		2,
		2,
		255);
}
Smoke2::Smoke2() {
	maxHp = 1;				//�ő�ϋv�x
	imageX = 32;			//�摜x���W
	imageY = 8;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
	animeMax = 4;			//�A�j���[�V��������
	animeWait = 12;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 50;		//�����t���[��
	moveMode = 0;			//1:�^�[�Q�b�g�ړ�
}
Chara::Chara() {
	charOffset = 0;
	imageX = 0;			//�摜x���W
	imageY = 1;			//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	animeMax = 1;			//�A�j���[�V��������
	animeWait = 12;			//�A�j���[�V�����P���̃t���[����
	size = 1;				//�T�C�Y
	timeOfLife = 999;		//�����t���[��
}
void Chara::draw(Tomasen& game) {
	/*�G�t�F�N�g�`��*/
	game.IMAGE->drawAlphaBlendTile(getPos(),
		getOutputW(),
		getOutputH(),
		getImageX() + charOffset, getImageY(),
		getImageW(), getImageH(),
		100);
}


} //namespace tm2