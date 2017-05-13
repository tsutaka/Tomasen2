#include <cmath>

#include "tomasen.hpp"
#include "obj_bullet.hpp"

namespace tm2{

/*�O���[�o�����\�[�X��`*/
FriendBulletVsptr friendBulletList;					//���e���X�g
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos){		//�w��ʒu�̓Z���^�[
		friendBulletList.push_back( friendBullet );						//���X�g�ɃI�u�W�F�N�g�ǉ�
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(pos);				//���e���w��ʒu�Ɉړ�
}
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos, double dir){//�w��ʒu�̓Z���^�[
		friendBulletList.push_back( friendBullet );						//���X�g�ɃI�u�W�F�N�g�ǉ�
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(pos);				//���e���w��ʒu�Ɉړ�
		(*it)->setDir(dir);												//�w��p�x�Ŕ���
}
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY){		//�w��ʒu�̓Z���^�[
		friendBulletList.push_back( friendBullet );						//���X�g�ɃI�u�W�F�N�g�ǉ�
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//���e���w��ʒu�Ɉړ�
}
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY, double dir){//�w��ʒu�̓Z���^�[
		friendBulletList.push_back( friendBullet );						//���X�g�ɃI�u�W�F�N�g�ǉ�
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//���e���w��ʒu�Ɉړ�
		(*it)->setDir(dir);												//�w��p�x�Ŕ���
}
EnemyBulletVsptr enemyBulletList;					//�G�e���X�g
void enemyBulletFactory(EnemyBulletSptr enemyBullet, Vec2 pos){			//�w��ʒu�̓Z���^�[
		enemyBulletList.push_back( enemyBullet );						//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(pos);				//���e���w��ʒu�Ɉړ�
}
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY){			//�w��ʒu�̓Z���^�[
		enemyBulletList.push_back( enemyBullet );						//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//���e���w��ʒu�Ɉړ�
}
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY, double dir){			//�w��ʒu�̓Z���^�[
		enemyBulletList.push_back( enemyBullet );						//���X�g�ɃI�u�W�F�N�g�ǉ�
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//���e���w��ʒu�Ɉړ�
		(*it)->setDir(dir);												//�w��p�x�Ŕ���
}

Bullet::Bullet(){
	//�f�t�H���g�l
	pos = Vec2(0.0, 0.0);	//���݈ʒu
	move = Vec2(0.0, 0.0);	//�ړ���
	dis = 0.0;				//�ړ���
	dir = 0.0;				//�p�x
	frameCnt = 0;			//�o�߃t���[����
	animeCnt = makeRand(4);	//�A�j���t���[��
	updateCheck = true;		//�X�V��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
	size = 2;

	fire = 1;				//�Η�
}
void FriendBullet::update(Tomasen& game){
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
	/*�e�̈ʒu���X�V*/
	pos.x += cos(dir) * dis;
	pos.y += sin(dir) * dis;
}
void FriendBullet::draw(Tomasen& game){
	/*game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH() );*/
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}


NormalBullet::NormalBullet(){
	name = TEXT("�ʏ�e");		//���O
	maxHp = 1;					//�ő�ϋv�x
	imageX = 0;					//�摜x���W
	imageY = 14;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;								//HP
	dis = 20.0 + makeRand(0.0, 2);								//�ړ���
	dir = -PI/2 + 0.01 * makeRand(0.0, 3);	//�p�x
}
BlueBullet::BlueBullet(){
	name = TEXT("�e");		//���O
	maxHp = 1;					//�ő�ϋv�x
	imageX = 8;					//�摜x���W
	imageY = 8;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;								//HP
	dis = 20.0 + makeRand(0.0, 2);								//�ړ���
	dir = -PI/2 + 0.01 * makeRand(0.0, 3);	//�p�x
}
HadoBeam::HadoBeam(){
	name = TEXT("�g���C");
	maxHp = 10;					//�ő�ϋv�x
	imageX = 20;					//�摜x���W
	imageY = 8;					//�摜y���W
	imageW = 2;					//�摜��
	imageH = 2;					//�摜��
	outputW = 4;			//�o�͕�
	outputH = 4;			//�o�͍�
	animeMax = 4;				//�A�j������
	animeWait = 8;				//�P������̃t���[��
	size = tipSize*outputW;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 15.5;								//�ړ���
	dir = -PI/2;	//�p�x
}
void HadoBeam::draw(Tomasen &game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							40);

}
MissBullet::MissBullet(){
	name = TEXT("�~�T�C��");
	maxHp = 3;					//�ő�ϋv�x
	imageX = 28;					//�摜x���W
	imageY = 10;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 7.9;								//�ړ���
	dir = -PI/2;	//�p�x
}
MissileRBullet::MissileRBullet(){
	name = TEXT("�~�T�C��");
	maxHp = 5;					//�ő�ϋv�x
	imageX = 32;					//�摜x���W
	imageY = 10;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.9;								//�ړ���
	dir = -PI/2;	//�p�x
}
MissileRBullet::~MissileRBullet(){
	//�~�`����
	for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 8){
		effectFactory(EffectSptr(new Explosion()), 
			getPos(), 
			Vec2( getPos().x + sin(cnt) * 100.0, 
				getPos().y + cos(cnt) * 100.0 )
			);
	}
}
void MissileRBullet::update(Tomasen& game){
	//�e�X�V�֐��̎g�p
	FriendBullet::update(game);
	//�����̏o��
	if(frameCnt % 150){
		effectFactory( EffectSptr(new Smoke2()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x, getCenterPos().y ) );
		EffectVsptr::iterator it = effectList.end() - 1;
		(*it)->setTimeOfLife(20);
	}
	//��]�p�x�̏C��
	dir += PI / 2.0 / 200.0;
}
MissileLBullet::MissileLBullet(){
	name = TEXT("�~�T�C��");
	maxHp = 5;					//�ő�ϋv�x
	imageX = 32;					//�摜x���W
	imageY = 10;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.9;								//�ړ���
	dir = -PI/2;	//�p�x
}
MissileLBullet::~MissileLBullet(){
	//�~�`����
	for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 8){
		effectFactory(EffectSptr(new Explosion()), 
			getPos(), 
			Vec2( getPos().x + sin(cnt) * 100.0, 
				getPos().y + cos(cnt) * 100.0 )
			);
	}
}
void MissileLBullet::update(Tomasen& game){
	//�e�X�V�֐��̎g�p
	FriendBullet::update(game);
	//�����̏o��
	if(frameCnt % 150){
		effectFactory( EffectSptr(new Smoke2()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x, getCenterPos().y ) );
		EffectVsptr::iterator it = effectList.end() - 1;
		(*it)->setTimeOfLife(20);
	}
	//��]�p�x�̏C��
	dir -= PI / 2.0 / 200.0;
}




void EnemyBullet::update(Tomasen& game){
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
	/*�e�̈ʒu���X�V*/
	pos.x += cos(dir) * dis;
	pos.y += sin(dir) * dis;
}
void EnemyBullet::draw(Tomasen& game){
	game.IMAGE->drawTip( getPos().x, getPos().y, 
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputW(), 
					game.IMAGE->tipNo(	getImageX(), 
									getImageY() ) );
}
WeakBullet::WeakBullet(){
	name = TEXT("��e");
	maxHp = 1;					//�ő�ϋv�x
	imageX = 4;					//�摜x���W
	imageY = 14;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	outputW = 2;				//�o�͕�
	outputH = 2;				//�o����
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 6.0;								//�ړ���
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//�p�x
}
void WeakBullet::action(const Object &obj){
}
WideBullet::WideBullet(){
	name = TEXT("����");
	maxHp = 10;				//�ő�ϋv�x
	imageX = 0;					//�摜x���W
	imageY = 8;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	outputW = 2;				//�o�͕�
	outputH = 2;				//�o����
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//virtual void Process
	
	hp = maxHp;					//HP
	dis = 1.0;								//�ړ���
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//�p�x
}
void WideBullet::action(const Object &obj){
	dir += 0.01;
	dis += 0.01;
}
SprinklerBullet::SprinklerBullet(){
	name = TEXT("�X�v�����N���[");
	maxHp = 2;					//�ő�ϋv�x
	imageX = 8;					//�摜x���W
	imageY = 14;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	outputW = 2;				//�o�͕�
	outputH = 2;				//�o����
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.2;								//�ړ���
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//�p�x
}
void SprinklerBullet::action(const Object &obj){
}
GreenBullet::GreenBullet(){
	name = TEXT("�Βe");
	maxHp = 2;					//�ő�ϋv�x
	imageX = 4;					//�摜x���W
	imageY = 9;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	outputW = 2;				//�o�͕�
	outputH = 2;				//�o����
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 6;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 1.5;								//�ړ���
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//�p�x
}
void GreenBullet::action(const Object &obj){
	if(frameCnt % 71 == 0){
		if(frameCnt % 2 == 0) dir -= PI / 4;
		else dir += PI / 8;
		dis += 0.2;
	}
}
Ene1Bullet::Ene1Bullet(){
	name = TEXT("�G�l�P�e");
	maxHp = 3;					//�ő�ϋv�x
	imageX = 8;					//�摜x���W
	imageY = 9;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.3 + makeRand(0.0, 10) * 0.1;								//�ړ���
	dir = +PI/2;	//�p�x
}
void Ene1Bullet::action(const Object &obj){
}
Ene2Bullet::Ene2Bullet(){
	name = TEXT("�G�l�Q�e");
	maxHp = 3;					//�ő�ϋv�x
	imageX = 8;					//�摜x���W
	imageY = 10;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 1.3;								//�ړ���
	dir = +PI/2;	//�p�x
}
void Ene2Bullet::action(const Object &obj){
}
Ene3Bullet::Ene3Bullet(){
	name = TEXT("�G�l�R�e");
	maxHp = 3;					//�ő�ϋv�x
	imageX = 8;					//�摜x���W
	imageY = 11;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 0.9;								//�ړ���
	dir = +PI/2;	//�p�x
}
void Ene3Bullet::action(const Object &obj){
}
RedKunaiBullet::RedKunaiBullet(){
	name = TEXT("�ԃN�i�C");
	maxHp = 1;					//�ő�ϋv�x
	imageX = 12;					//�摜x���W
	imageY = 10;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.9;								//�ړ���
	dir = +PI/2;	//�p�x
}
void RedKunaiBullet::action(const Object &obj){

	if(frameCnt % 100 == 0 && frameCnt < 200){
		dir += 0.5 * PI / 2.0;
		dis += 0.1;
	}
}
void RedKunaiBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}
YellowKunaiBullet::YellowKunaiBullet(){
	name = TEXT("���N�i�C");
	maxHp = 1;					//�ő�ϋv�x
	imageX = 12;					//�摜x���W
	imageY = 11;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.5;								//�ړ���
	dir = +PI/2;	//�p�x
}
void YellowKunaiBullet::action(const Object &obj){
}
void YellowKunaiBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}
RaserBullet::RaserBullet(){
	name = TEXT("���[�U�[");
	maxHp = 1;					//�ő�ϋv�x
	imageX = 40;					//�摜x���W
	imageY = 18;				//�摜y���W
	imageW = 2;					//�摜��
	imageH = 4;					//�摜��
	outputW = 2;				//�o�͕�
	outputH = 4;				//�o����
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.5;								//�ړ���
	dir = +PI/2;	//�p�x
}
void RaserBullet::action(const Object &obj){
}
void RaserBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}

RedMBullet::RedMBullet(){
	name = TEXT("�ԃ~�T�C��");
	maxHp = 1;					//�ő�ϋv�x
	imageX = 32;					//�摜x���W
	imageY = 10;				//�摜y���W
	imageW = 1;					//�摜��
	imageH = 2;					//�摜��
	outputW = 1;				//�o�͕�
	outputH = 2;				//�o����
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.5;								//�ړ���
	dir = +PI/2;	//�p�x
}
void RedMBullet::action(const Object &obj){
}
void RedMBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}

} //namespace tm2