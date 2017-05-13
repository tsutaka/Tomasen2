#include "obj_parts_B.hpp"

#include "obj_effect.hpp"

namespace tm2{

CoreA::CoreA(){
	name = TEXT("�R�AA");	//���O
	maxHp = 30;				//�ő�ϋv�x
	hp = maxHp;				//���ݑϋv�x
	imageX = 0;				//�摜x���W
	imageY = 4;				//�摜y���W
	imageW = 1;				//�摜��
	imageH = 1;				//�摜��
	animeMax = 4;			//�A�j������
	animeWait = 4;			//�P������̃t���[��
	size = tipSize;			//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;

}

Base2B::Base2B(){
	name = TEXT("�x�[�X2B");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 28;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base1A::Base1A(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X1A");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 0;					//�摜x���W
	imageY = 5;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointNG;
}

Base4::Base4(){
	name = TEXT("�x�[�X4");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 4;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base3A::Base3A(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X3�`");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 8;					//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base3B::Base3B(){//�E�����Ȃ�
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X3B");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 12;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}
/*�X�V�֐�*/
void Base3B::update(Tomasen& game){
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
				//���U����
				tmp->setPos(Vec2( 
					pos.x + jointPosX[cnt] + kaihi, 
					pos.y + jointPosY[cnt] ));//���ʂ̃p�[�c�̈ʒu���Z�b�g
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
void Base3B::draw(Tomasen& game){
	//�e�̕`��֐��Ăяo��
	PartsB::draw(game);
	//�т�т�\��
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				if(kaihi > 0){
					//���S�_�\��
					game.IMAGE->drawLine(getCenterPos(), 
						tmp->getCenterPos(), 
						game.IMAGE->tipNo(42+animeCnt, 24),
						220);
					//�т�т艹
					game.MUSIC->Play(musicBiribiri);
				}
			}
		}
	}
}


Base3C::Base3C(){//�������Ȃ�
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X3C");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 16;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointNG;
}

/*�X�V�֐�*/
void Base3C::update(Tomasen& game){
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
				//���U����
				tmp->setPos(Vec2( 
					pos.x + jointPosX[cnt] - kaihi, 
					pos.y + jointPosY[cnt] ));//���ʂ̃p�[�c�̈ʒu���Z�b�g
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
void Base3C::draw(Tomasen& game){
	//�e�̕`��֐��Ăяo��
	PartsB::draw(game);
	//�т�т�\��
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				if(kaihi > 0){
					//���S�_�\��
					game.IMAGE->drawLine(getCenterPos(), 
						tmp->getCenterPos(), 
						game.IMAGE->tipNo(42+animeCnt, 24),
						220);
				}
			}
		}
	}

}
Base3D::Base3D(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X3D");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 20;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base2A::Base2A(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X2A");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 24;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base2C::Base2C(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X2C");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 32;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base2D::Base2D(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X2D");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 36;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointNG;
}

Base2E::Base2E(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X2E");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 40;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base2F::Base2F(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X2F");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 44;				//�摜x���W
	imageY = 4;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointNG;
}

Base1B::Base1B(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X1B");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 4;					//�摜x���W
	imageY = 5;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base1C::Base1C(){
	/*�I�u�W�F�N�g�p�����[�^*/
	name = TEXT("�x�[�X1C");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 8;					//�摜x���W
	imageY = 5;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	/*����*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*�W���C���g*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointNG;
}

Base1D::Base1D(){
	name = TEXT("�x�[�X1D");	//���O
	maxHp = 10;					//�ő�ϋv�x
	hp = maxHp;					//���ݑϋv�x
	imageX = 12;				//�摜x���W
	imageY = 5;					//�摜y���W
	imageW = 1;					//�摜��
	imageH = 1;					//�摜��
	animeMax = 4;				//�A�j������
	animeWait = 4;				//�P������̃t���[��
	size = tipSize;				//�����蔻�蒼�a

	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointNG;
}

} //namespace tm2