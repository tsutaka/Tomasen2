#include "obj_parts_A.hpp"
#include "obj_bullet.hpp"
#include "obj_wing_enemy.hpp"

#include "tomasen.hpp"

namespace tm2{

EngineA::EngineA(){
	name = TEXT("�G���W���`");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 0;					//�摜x���W
	imageY = 0;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 10;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
}

void EngineA::action(Tomasen& game){
}

CockpitA::CockpitA(){
	name = TEXT("�R�b�N�s�b�g�`");	//���O
	maxHp = 10;						//�ő�ϋv�x
	hp = maxHp;						//���ݑϋv�x
	imageX = 4;						//�摜x���W
	imageY = 0;						//�摜y���W
	imageW = 1;						//�摜��
	imageH = 1;						//�摜��
	animeMax = 1;					//�A�j������
	animeWait = 10;					//�P������̃t���[��
	size = tipSize;					//�����蔻�蒼�a
}

void CockpitA::action(Tomasen& game){
}

MachineGunA::MachineGunA(){
	name = TEXT("�@�֏e�`");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 8;					//�摜x���W
	imageY = 0;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 100;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 20;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//
}  

void MachineGunA::action(Tomasen& game){
	/*�ˌ�����*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new MissBullet()), 
			getCenterPos().x, getCenterPos().y );
		//�ˌ���
		game.MUSIC->Play(musicKikanho);
		energy -= 1;
	}
	else if(energy <= 0){			//�ˌ��s��
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//�ˌ��ĊJ
		stopShot = 1;
	}
}
MachineGunB::MachineGunB(){
	name = TEXT("�@�֏e�a");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 12;					//�摜x���W
	imageY = 0;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 100;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 20;			//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//
}  
void MachineGunB::action(Tomasen& game){
	/*�ˌ�����*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y ,
			0.0);
		//�ˌ���
		energy -= 1;
	}
	else if(energy <= 0){			//�ˌ��s��
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//�ˌ��ĊJ
		stopShot = 1;
	}
}
MachineGunC::MachineGunC(){
	name = TEXT("�@�֏e�b");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 16;					//�摜x���W
	imageY = 0;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 100;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 20;			//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//
}  
void MachineGunC::action(Tomasen& game){
	/*�ˌ�����*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y, 
			PI / 2);
		//�ˌ���
		energy -= 1;
	}
	else if(energy <= 0){			//�ˌ��s��
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//�ˌ��ĊJ
		stopShot = 1;
	}
}
MachineGunD::MachineGunD(){
	name = TEXT("�@�֏e�c");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 20;				//�摜x���W
	imageY = 0;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 100;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 20;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//
}  
void MachineGunD::action(Tomasen& game){
	/*�ˌ�����*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y, 
			PI);
		//�ˌ���
		energy -= 1;
	}
	else if(energy <= 0){			//�ˌ��s��
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//�ˌ��ĊJ
		stopShot = 1;
	}
}
SprinklerA::SprinklerA(){
	name = TEXT("�X�v�����N���[�`");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 28;				//�摜x���W
	imageY = 0;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 100;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 20;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//
}  
void SprinklerA::action(Tomasen& game){
	/*�ˌ�����*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y, 
			PI);
		//�ˌ���
		energy -= 1;
	}
	else if(energy <= 0){			//�ˌ��s��
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//�ˌ��ĊJ
		stopShot = 1;
	}
}

SubCanonA::SubCanonA(){
	name = TEXT("���C�`");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 0;					//�摜x���W
	imageY = 2;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 2;					//�摜��
	outputW = 1;				//�o�͕�
	outputH = 2;				//�o�͍�
	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	drawPriority = 1;			//�`��D�揇��
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 150;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 20;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//�ˌ��w��
	targetShot = 0;				//�^�[�Q�b�g��ߑ�
	targetDir = 0.0;			//�^�[�Q�b�g�p�x
}  

void SubCanonA::update(Tomasen& game){
	/*��{�X�V�֐��̌Ăяo��*/
	PartsA::update(game);

	/*���C�ɒ��߂̓G�@�̈ʒu��`�B*/
	double distance, minDistance = 1000.0;	//�G����, �ŏ������@���C���ǔ�����
	double eneX = 0.0, eneY = 0.0;			//�GX���W,�GY���W
	int targetLockOn = 0;					//�G��ߑ�:1
	//�ŏ������̓G��T��
	for(EnemyVsptr::iterator itEnemy = enemyList.begin(); itEnemy != enemyList.end(); itEnemy++){
		distance = checkDistance( (*itEnemy)->getCenterPos().x, (*itEnemy)->getCenterPos().y,
			getCenterPos().x, getCenterPos().y );
		if( minDistance > distance ){
				(*itEnemy)->setLockOn(100);
				minDistance = distance;
				eneX = (*itEnemy)->getCenterPos().x;
				eneY = (*itEnemy)->getCenterPos().y;
				targetLockOn = 1;	//���b�N�I���@�C����]
		}
	}
	if(targetLockOn){/*�Ώۃ��b�N�I��*/
		setTargetShot(targetLockOn);
		setTargetX(eneX);
		setTargetY(eneY);
		setTargetDistance(minDistance);
	}
	else {/*�Ώۖ����̏ꍇ�͑O������*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	
	/*�^�[�Q�b�g�p�x�̎Z�o*/
	targetDir = checkDirection(targetX, targetY, getCenterPos().x, getCenterPos().y) + PI/2.0;
	targetDir += 8*PI;
	while(targetDir > dir + PI){
		targetDir -= 2*PI;
	}
	/*�C���̉�]*/
	if(targetDir+2*PI > dir+2*PI + PI / 30.0){
		dir += PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	else if(targetDir+2*PI < dir+2*PI - PI / 30.0){
		dir -= PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	/*�ˌ�����*/
	if(energy > 0 && man >= requireMan && targetShot == 1 && targetDistance < 300){//�ˌ��J�n����
		friendBulletFactory( 
			FriendBulletSptr( new BlueBullet()), 
			getCenterPos().x, getCenterPos().y, dir - PI/2
			);
		game.MUSIC->Play(musicFami);

	}
}

/*�`��֐�*/
void SubCanonA::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//�p�[�c�̕`��i��]����j
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}

HadohoA::HadohoA(){
	name = TEXT("�g���C�`");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 32;					//�摜x���W
	imageY = 0;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 300;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 2;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//
}  

void HadohoA::action(Tomasen& game){
	/*�ˌ�����*/
	if( game.shotPerm == 2 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new HadoBeam()), 
			getCenterPos().x, getCenterPos().y );
		//�ˌ���
		game.MUSIC->Play(musicHadou);
		energy /= 2;
	}
	else if(energy <= 0){			//�ˌ��s��
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//�ˌ��ĊJ
		stopShot = 1;
	}
}

void HadohoA::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//�p�[�c�̕`��i��]����j
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}


HadohoB::HadohoB(){
	name = TEXT("�g���C�a");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 4;					//�摜x���W
	imageY = 2;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 2;					//�摜��
	outputW = 1;					//�摜��
	outputH = 2;					//�摜��

	animeMax = 4;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 300;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 2;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�
	
	stopShot = 1;				//
}  

void HadohoB::action(Tomasen& game){
	/*�ˌ�����*/
	if( game.shotPerm == 2 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new HadoBeam()), 
			getCenterPos().x, getCenterPos().y );
		//�ˌ���
		game.MUSIC->Play(musicHadou);
		energy /= 2;
	}
	else if(energy <= 0){			//�ˌ��s��
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//�ˌ��ĊJ
		stopShot = 1;
	}
}

void HadohoB::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//�p�[�c�̕`��i��]����j
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}


LuncherR::LuncherR(){
	name = TEXT("�~�T�C�������`���[");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 8;					//�摜x���W
	imageY = 2;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 2;					//�摜��
	outputW = 1;				//�摜��
	outputH = 2;				//�摜��

	animeMax = 1;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 300;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 2;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�

	stopShot = 0;
	
}  

void LuncherR::update(Tomasen& game){
	/*��{�X�V�֐��̌Ăяo��*/
	PartsA::update(game);

	/*���C�ɒ��߂̓G�@�̈ʒu��`�B*/
	double distance, minDistance = 500.0;	//�G����, �ŏ������@���C���ǔ�����
	double eneX = 0.0, eneY = 0.0;			//�GX���W,�GY���W
	int targetLockOn = 0;					//�G��ߑ�:1
	//�ŏ������̓G��T��
	for(EnemyVsptr::iterator itEnemy = enemyList.begin(); itEnemy != enemyList.end(); itEnemy++){
		distance = checkDistance( (*itEnemy)->getCenterPos().x, (*itEnemy)->getCenterPos().y,
			getCenterPos().x, getCenterPos().y );
		if( minDistance > distance ){
				(*itEnemy)->setLockOn(100);
				minDistance = distance;
				eneX = (*itEnemy)->getCenterPos().x;
				eneY = (*itEnemy)->getCenterPos().y;
				targetLockOn = 1;	//���b�N�I���@�C����]
		}
	}
	if(targetLockOn){/*�Ώۃ��b�N�I��*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x - 3.0);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	else {/*�Ώۖ����̏ꍇ�͑O������*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	
	/*�^�[�Q�b�g�p�x�̎Z�o*/
	targetDir = checkDirection(targetX, targetY, getCenterPos().x, getCenterPos().y) + PI/2.0;
	targetDir += 8*PI;
	while(targetDir > dir + PI){
		targetDir -= 2*PI;
	}
	/*�C���̉�]*/
	if(targetDir+2*PI > dir+2*PI + PI / 30.0){
		dir += PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	else if(targetDir+2*PI < dir+2*PI - PI / 30.0){
		dir -= PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	if(energy > 0 && man >= requireMan && targetShot == 1 && 
		targetDistance < 300 && frameCnt % 20 == 0){//�ˌ��J�n����300
		kaiten += 1;
		if(kaiten > 4) kaiten = 0;
		friendBulletFactory( 
			FriendBulletSptr( new MissileRBullet()), 
			getCenterPos().x, getCenterPos().y, dir - PI/2.0
			);
		game.MUSIC->Play(musicMissile);

	}
}
void LuncherR::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//�p�[�c�̕`��i��]����j
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}
LuncherL::LuncherL(){
	name = TEXT("�~�T�C�������`���[");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 8;					//�摜x���W
	imageY = 2;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 2;					//�摜��
	outputW = 1;				//�摜��
	outputH = 2;				//�摜��

	animeMax = 1;				//�A�j������
	animeWait  = 4;		        //�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a
	
	maxEnergy = 100;			//�ő�̒e��
	energy = maxEnergy;			//���݂̒e��
	chargeEnergy = 1;			//���e����e��
	maxMan = 300;				//�ő�̐l��
	man = maxMan;				//���݂̐l��
	requireMan = 2;				//�K�v�Ȑl��
	fire = 0;					//���݂̉ΐ�
	burnFire = 30;				//���΂���ΐ�
	maxFire = 80;				//�ő�̉ΐ�

	stopShot = 0;
	
}  

void LuncherL::update(Tomasen& game){
	/*��{�X�V�֐��̌Ăяo��*/
	PartsA::update(game);

	/*���C�ɒ��߂̓G�@�̈ʒu��`�B*/
	double distance, minDistance = 500.0;	//�G����, �ŏ������@���C���ǔ�����
	double eneX = 0.0, eneY = 0.0;			//�GX���W,�GY���W
	int targetLockOn = 0;					//�G��ߑ�:1
	//�ŏ������̓G��T��
	for(EnemyVsptr::iterator itEnemy = enemyList.begin(); itEnemy != enemyList.end(); itEnemy++){
		distance = checkDistance( (*itEnemy)->getCenterPos().x, (*itEnemy)->getCenterPos().y,
			getCenterPos().x, getCenterPos().y );
		if( minDistance > distance ){
				(*itEnemy)->setLockOn(100);
				minDistance = distance;
				eneX = (*itEnemy)->getCenterPos().x;
				eneY = (*itEnemy)->getCenterPos().y;
				targetLockOn = 1;	//���b�N�I���@�C����]
		}
	}
	if(targetLockOn){/*�Ώۃ��b�N�I��*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x + 3.0);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	else {/*�Ώۖ����̏ꍇ�͑O������*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	
	/*�^�[�Q�b�g�p�x�̎Z�o*/
	targetDir = checkDirection(targetX, targetY, getCenterPos().x, getCenterPos().y) + PI/2.0;
	targetDir += 8*PI;
	while(targetDir > dir + PI){
		targetDir -= 2*PI;
	}
	/*�C���̉�]*/
	if(targetDir+2*PI > dir+2*PI + PI / 30.0){
		dir += PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	else if(targetDir+2*PI < dir+2*PI - PI / 30.0){
		dir -= PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	/*�ˌ�����*/
	if(energy > 0 && man >= requireMan && targetShot == 1 && 
		targetDistance < 300 && frameCnt % 20 == 0){//�ˌ��J�n����300
		kaiten += 1;
		if(kaiten > 4) kaiten = 0;
		friendBulletFactory( 
			FriendBulletSptr( new MissileLBullet()), 
			getCenterPos().x, getCenterPos().y, dir - PI/2.0
			);

		game.MUSIC->Play(musicMissile);

	}
}

void LuncherL::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//�p�[�c�̕`��i��]����j
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}


} //namespace tm2