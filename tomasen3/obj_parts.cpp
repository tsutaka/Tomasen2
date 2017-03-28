#include "obj_parts.hpp"

#include "tomasen.hpp"
#include "obj_effect.hpp"

namespace tm2{

/*�O���[�o�����\�[�X��`*/
PartsAVsptr partsAList;			//�p�[�c���X�g
PartsAWptr partsAFactory(PartsASptr partsA){
		partsAList.push_back( partsA );			//���X�g�ɃI�u�W�F�N�g�ǉ�
		PartsAVsptr::iterator it = partsAList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		return (*it);
}
PartsBVsptr partsBList;			//�p�[�c���X�g
PartsBWptr partsBFactory(PartsBSptr partsB){
		partsBList.push_back( partsB );			//���X�g�ɃI�u�W�F�N�g�ǉ�
		PartsBVsptr::iterator it = partsBList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		return (*it);
}
PartsBWptr partsSetFactory(PartsBSptr partsB, PartsBSptr newPartsB, PartsASptr newPartsA, jointIndex jointDir){
		PartsBSptr base = partsBFactory( newPartsB ).lock();//�x�[�X�̍쐬
		partsB->setPartsB(jointDir, base);					//�x�[�X�̐ڑ�
		if(newPartsA != NULL){
			base->setPartsA(mainWeapon,							//�����̍쐬�Ɛڑ�
				partsAFactory( newPartsA )
				);
		}
		return newPartsB;
}
/*�R���X�g���N�^*/
Parts::Parts(){
	//�p�[�c�̃f�t�H���g�l
	pos = Vec2(0.0, 0.0);	//���݈ʒu
	move = Vec2(0.0, 0.0);	//�ړ���
	dis = 0.0;				//�ړ���
	dir = 0.0;				//�p�x
	frameCnt = 0;			//�o�߃t���[����
	animeCnt = 0;			//�A�j���t���[��
	updateCheck = true;		//�X�V��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
	maxEnergy = 50;			//�ő�̒e��
	energy = maxEnergy;		//���݂̒e��
	chargeEnergy = 1;		//���e����e��
	maxMan = 10;			//�ő�̐l��
	man = 50;				//���݂̐l��
	requireMan = 0;			//�K�v�Ȑl��
	fire = 5;				//���݂̉ΐ�
	burnFire = 20;			//���΂���ΐ�
	maxFire = 50;			//�ő�̉ΐ�
	kaihi = 0;				//�ό`�t���O(�ό`�F�P)
	drawPriority = 0;

}
/*add�֐�*/
//���@���̂ɂ����l�̊֐�����
void Parts::addKaihi(int kaihi){
	const int kaihiMin = 0;
	const int kaihiMax = 80;
	Parts::kaihi += kaihi;
	if(Parts::kaihi > kaihiMax){
		Parts::kaihi = kaihiMax;
	}else if(Parts::kaihi < kaihiMin){
		Parts::kaihi = kaihiMin;
	}
}
/*�񍐊֐�*/
void Parts::tellUp(TellUpBox &box){
	box.hp += hp;
	box.maxHp += maxHp;
	box.energy += energy;
	box.chargeEnergy += chargeEnergy;
	box.maxEnergy += maxEnergy;
	box.man += man;
	box.requireMan += requireMan;
	box.maxMan += maxMan;
	box.fire += fire;
	box.burnFire += burnFire;
	box.maxFire += maxFire;
	this->subTellUp(box);
	return;
}
/*�E���֐�*/
void Parts::killMan(int damage){
	if(perCheck(25)){
		man -= damage;
	}
	//�V�q�̂����
	for(int cnt = 0; cnt < damage; cnt++){
		effectFactory( EffectSptr(new Wakka()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 50), 
					getCenterPos().y - tipSize/2 + makeRand(-75.0, 20) )
			);
	}
}

/*�R���X�g���N�^*/
PartsA::PartsA(){
}
/*�X�V�֐�*/
void PartsA::update(Tomasen& game){
	/*�J�E���g�A�b�v*/
	frameCnt++;
	if(frameCnt > 90000) frameCnt = 0;
	/*�A�j���[�V��������*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt % animeMax == 0){
			animeCnt = 0;
		}
	}

	/*���e����*/
	if(frameCnt%2 == 0 && man >= requireMan && fire < burnFire){	//�l���\���A�΍ЂȂ�
		if(energy < maxEnergy) energy += chargeEnergy;
	}
	else if(frameCnt%3 == 0 && man >= requireMan){					//�l���\���A�΍Ђ���
		if(energy < maxEnergy) energy += chargeEnergy;
	}
}
/*�`��֐�*/
void PartsA::draw(Tomasen& game){
	game.IMAGE->drawRotateTip(	getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir(),
							game.IMAGE->tipNo(	getImageX(), 
												getImageY() ) );
}
/*�A�N�V�����֐���*/
void PartsA::action(Tomasen& game){
}
/*�T�u�񍐊֐�*/
void PartsA::subTellUp(TellUpBox &box){
	return;
}

/*�R���X�g���N�^*/
PartsB::PartsB(){
	//�p�[�cB�̃f�t�H���g�l
	weapon[mainWeapon] = weaponEmp;		//�����L��
	weaponPosX[mainWeapon] = 0;			//����X���W�i�e����̑��΁j
	weaponPosY[mainWeapon] = 0;			//����Y���W�i�e����̑��΁j
	weapon[subWeapon] = weaponNG;		//�����L��
	weaponPosX[subWeapon] = 0;			//����X���W�i�e����̑��΁j
	weaponPosY[subWeapon] = 0;			//����Y���W�i�e����̑��΁j
	joint[upJoint] = jointEmp;			//�W���C���g�L��
	jointPosX[upJoint] = 0;				//�W���C���gX���W�i�e����̑��΁j
	jointPosY[upJoint] = -tipSize;		//�W���C���gY���W�i�e����̑��΁j
	joint[rightJoint] = jointEmp;		//�W���C���g�L��
	jointPosX[rightJoint] = tipSize;	//�W���C���gX���W�i�e����̑��΁j
	jointPosY[rightJoint] = 0;			//�W���C���gY���W�i�e����̑��΁j
	joint[downJoint] = jointEmp;		//�W���C���g�L��
	jointPosX[downJoint] = 0;			//�W���C���gX���W�i�e����̑��΁j
	jointPosY[downJoint] = tipSize;		//�W���C���gY���W�i�e����̑��΁j
	joint[leftJoint] = jointEmp;		//�W���C���g�L��
	jointPosX[leftJoint] = -tipSize;	//�W���C���gX���W�i�e����̑��΁j
	jointPosY[leftJoint] = 0;			//�W���C���gY���W�i�e����̑��΁j
	jointParent = 1;					//�e�Ƃ̐ڑ���
}
/*�f�X�g���N�^*/
PartsB::~PartsB(){
	jointParent = 0;					//�e���番��
	/*���ʕ����̕���*/
	for(int cnt = 0; cnt < weaponIndexEnd; cnt++){
		if(weapon[cnt] == (int)weaponExist){
			if(PartsASptr tmp = getPartsA((weaponIndex)cnt)){	
				/*���ʕ����̔j��*/
				tmp->setHp(0);
			}
		}
	}
	/*���ʃW���C���g�̕���*/
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				/*���ʕ����̕���*/
				tmp->setJointParent(0);
			}
		}
	}
}

/*�X�V�֐�*/
void PartsB::update(Tomasen& game){
	/*�J�E���g�A�b�v*/
	frameCnt++;
	if(frameCnt > 90000) frameCnt = 0;
	/*�A�j���[�V��������*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt % animeMax == 0){
			animeCnt = 0;
		}
	}
	/*�e�p�[�c�����Ȃ��ꍇ�̒E��*/
	if(jointParent == 0){
		pos.y += 2;
		if(frameCnt % 2 == 0){
			//����
			effectFactory( EffectSptr(new Explosion()), 
				getCenterPos().x, getCenterPos().y, 
				Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 50), 
					 getCenterPos().y - tipSize/2 + makeRand(-200.0, 60) )
				);
			//��
			effectFactory( EffectSptr(new Smoke()), 
				getCenterPos().x, getCenterPos().y, 
				Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 70), 
					 getCenterPos().y - tipSize/2 + makeRand(-100.0, 60) )
				);
		}
		if(frameCnt % 30 == 0){//�A���[����
			game.MUSIC->Play(musicAlarm);
		}
		if(frameCnt % 50 == makeRand(30)){//�j��
			game.MUSIC->Play(musicHaretsu);
		}
	}
	

	/*���ʕ����̍X�V*/
	for(int cnt = 0; cnt < weaponIndexEnd; cnt++){
		if(weapon[cnt] == (int)weaponExist){
			if(PartsASptr tmp = getPartsA((weaponIndex)cnt)){	
				/*�ʒu�̍X�V*/
				tmp->setPos(Vec2( pos.x + weaponPosX[cnt], pos.y + weaponPosY[cnt]));//���ʂ̃p�[�c�̈ʒu���Z�b�g
				tmp->update(game);		//���ʂ̃p�[�c�̍X�V

				/*���ʂ��畺���̗A��*/
				if(man < maxMan && tmp->getMan() > tmp->getRequireMan()){
					//�l�����ő�łȂ����ʂɗ]�蕺��������Ƃ�
					man += 1;
					tmp->addMan(-1);
				}

				/*��ʂ��畺���̗A��*/
				else if(man > requireMan && tmp->getMan() < tmp->getRequireMan()){
					//�l�����ő�łȂ����ʂɗ]�蕺��������Ƃ�
					man -= 1;
					tmp->addMan(1);
				}

				/*���l�̍X�V*/
				tmp->setKaihi(kaihi);
			}
		}
	}
	/*���ʃW���C���g�̍X�V*/
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				/*�ʒu�̍X�V*/
				//���ʃW���C���g�ʒu�̌���
				//�k������
				tmp->setPos(Vec2( 
					pos.x + jointPosX[cnt] * (100 - kaihi) / 100, 
					pos.y + jointPosY[cnt] * (100 - kaihi) / 100));//���ʂ̃p�[�c�̈ʒu���Z�b�g
				tmp->update(game);		//���ʂ̃p�[�c�̍X�V

				/*���ʂ��畺���̗A��*/
				if(man < maxMan && tmp->getMan() > tmp->getRequireMan()){
					//�l�����ő�łȂ����ʂɗ]�蕺��������Ƃ�
					man += 1;
					tmp->addMan(-1);
				}

				/*��ʂ��畺���̗A��*/
				else if(man > requireMan && tmp->getMan() < tmp->getRequireMan()){
					//�l�����ő�łȂ����ʂɗ]�蕺��������Ƃ�
					man -= 1;
					tmp->addMan(1);
				}

				/*���l�̍X�V*/
				//if(energy > 10){
					tmp->setKaihi(kaihi);
				//}
			}
		}
	}
	/*���*/
	if(kaihi > 0 && energy >= 10){
		energy -= 10;		//��𒆂̓G�l���M�[����
	}
	/*���*/
	if(kaihi > 0){
		//dir += 0.1;			//��𒆂͉�]
	}
}

/*�`��֐�*/
void PartsB::draw(Tomasen& game){
	game.IMAGE->drawTip( getPos().x, getPos().y, 
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputH(), 
					game.IMAGE->tipNo(	getImageX(), 
									getImageY() ) );
	game.IMAGE->drawAlphaBlendTip( getPos().x, getPos().y, //HP�_��
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputH(), 
					game.IMAGE->getRed(),
					(getMaxHp() - getHp() ) * 120 / getMaxHp() );
}

/*������Ԑݒ�֐�*/
void PartsB::setWeapon(weaponIndex index, weaponOK val){
	weapon[index] = val;
}
/*�y���Ԑݒ�֐�*/
void PartsB::setJoint(jointIndex index, jointOK val){
	joint[index] = val;
}
/*�e�ڑ��y���Ԑݒ�֐�*/
void PartsB::setJointParent(int jointParent){
	PartsB::jointParent = jointParent;
}
/*�����擾*/
PartsASptr PartsB::getPartsA(weaponIndex index){
	if(index == mainWeapon){
		return partsA0.lock();
	}
	else{//index = subWeapon
		return partsA1.lock();
	}
}
/*�y��擾*/
PartsBSptr PartsB::getPartsB(jointIndex index){
	if(index == upJoint){
		return partsB0.lock();
	}
	else if(index == rightJoint){
		return partsB1.lock();
	}
	else if(index == downJoint){
		return partsB2.lock();
	}
	else{//index = leftJoint
		return partsB3.lock();
	}
}
/*�e�L���擾*/
int PartsB::getJointParent(void){
	return jointParent;
}
/*�����ǉ��֐�*/
void PartsB::setPartsA(weaponIndex pos, PartsAWptr partsA){
	weapon[pos] = weaponExist;					//����
	switch((int)pos){
	case (int)mainWeapon:
		partsA0 = partsA;			//������ǉ�
		break;
	default://(int)subWeapon
		partsA1 = partsA;			//������ǉ�
		break;
	}
	if(PartsASptr tmp = getPartsA(pos)){	//�����ɏ�ʑw�̏����i�[����ꍇ�͂���
		//tmp->setPartsB(0, 1);				//�����̏�ʂ̐ݒ�
	}
}
/*�y��ǉ��֐�*/
void PartsB::setPartsB(jointIndex pos, PartsBSptr partsB){
	jointIndex jointPos;
	joint[pos] = jointDownExist;					//����
	switch((int)pos){
	case (int)upJoint:
		partsB0 = PartsBWptr(partsB);			//�W���C���g��ǉ�
		jointPos = downJoint;					//�ڑ���̃W���C���g�̎w��
		break;
	case (int)rightJoint:
		partsB1 = PartsBWptr(partsB);			//�W���C���g��ǉ�
		jointPos = leftJoint;					//�ڑ���̃W���C���g�̎w��
		break;
	case (int)downJoint:
		partsB2 = PartsBWptr(partsB);			//�W���C���g��ǉ�
		jointPos = upJoint;						//�ڑ���̃W���C���g�̎w��
		break;
	default://(int)leftJoint
		partsB3 = PartsBWptr(partsB);			//�W���C���g��ǉ�
		jointPos = rightJoint;					//�ڑ���̃W���C���g�̎w��
		break;
	}
}

/*�T�u�񍐊֐�*/
void PartsB::subTellUp(TellUpBox &box){
	/*�p�[�cA�̒T��*/
	for(int pos = (int)mainWeapon; pos < (int)weaponIndexEnd; pos++){
		if(weapon[pos] == weaponExist){	
			if( PartsASptr tmp = getPartsA((weaponIndex)pos) ){
				box.pertsANum++;
				tmp->tellUp(box);
			}
			else{
				box.pertsALost++;
				weapon[(int)pos] = weaponEmp;
			}
		}
	}
	/*�p�[�cB�̒T��*/
	for(int pos = (int)upJoint; pos < (int)jointIndexEnd; pos++){
		if(joint[pos] == jointDownExist){	
			if( PartsBSptr tmp = getPartsB((jointIndex)pos) ){
				box.pertsBNum++;
				tmp->tellUp(box);
			}
			else{
				box.pertsBLost++;
				joint[(int)pos] = jointEmp;
			}
		}
	}
	return;
}

} //namespace tm2