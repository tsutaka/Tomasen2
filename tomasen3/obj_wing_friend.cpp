#include <cmath>

#include "obj_wing_friend.hpp"
#include "tomasen.hpp"

namespace tm2{

/*�O���[�o�����\�[�X��`*/
FriendVsptr friendList;			//���@���X�g
FriendWptr friendFactory(FriendSptr friendw, Vec2 pos){
		friendList.push_back( friendw );					//���X�g�ɃI�u�W�F�N�g�ǉ�
		FriendVsptr::iterator it = friendList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		(*it)->setPos(pos);
		return (*it);
}

KosenWing::KosenWing(Tomasen& game){
	/*������*/
	name = TEXT("�R�[�Z���E�B���O");				//���̂̐ݒ�
	maxMove = 4.0;									//�ő�ړ���
	subMove = 0.90;									//�����ړ��ʔ{��
	maxHp = 10;										//�ő�ϋv�x
	imageX = 0;										//�摜x���W
	imageY = 0;										//�摜y���W
	imageW = 1;										//�摜��
	imageH = 1;										//�摜��
	size = tipSize;									//�����蔻�蒼�a
	frameCnt = 0;									//�o�߃t���[����
	
	partsANum = 0;	//�����_�p�[�cA��
	partsALost = 0;	//�ݐϑr���p�[�cA��
	partsBNum = 0;	//�����_�p�[�cB��
	partsBLost = 0;	//�ݐϑr���p�[�cB��


	/*���@����*/	
	core = partsBFactory( PartsBSptr(new CoreA()) );			//�ア�X�}�|�Őe�q�֌W
	if(PartsBSptr coreSptr = core.lock()){						//�R�A�Ƀp�[�c��ǉ�����B
		/*�e�L�X�g�R�s�[��������*/
		coreSptr->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new EngineA()) )
			);					//�R�A�ɃG���W���ǉ�

		PartsBSptr base4_E18 = partsSetFactory(coreSptr, PartsBSptr(new Base4()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base1C_D18 = partsSetFactory(base4_E18, PartsBSptr(new Base1C()), PartsASptr(new SubCanonA()), leftJoint).lock();

		PartsBSptr base1B_F18 = partsSetFactory(base4_E18, PartsBSptr(new Base1B()), PartsASptr(new SubCanonA()), rightJoint).lock();

		PartsBSptr base4_E20 = partsSetFactory(base4_E18, PartsBSptr(new Base4()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base1C_D20 = partsSetFactory(base4_E20, PartsBSptr(new Base1C()), PartsASptr(new EngineA()), leftJoint).lock();

		PartsBSptr base1B_F20 = partsSetFactory(base4_E20, PartsBSptr(new Base1B()), PartsASptr(new EngineA()), rightJoint).lock();

		PartsBSptr base2B_E22 = partsSetFactory(base4_E20, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E24 = partsSetFactory(base2B_E22, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E26 = partsSetFactory(base2B_E24, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E28 = partsSetFactory(base2B_E26, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E30 = partsSetFactory(base2B_E28, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E32 = partsSetFactory(base2B_E30, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E34 = partsSetFactory(base2B_E32, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base1D_E36 = partsSetFactory(base2B_E34, PartsBSptr(new Base1D()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E14 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		coreSptr->setPartsB(upJoint, base2B_E14);					//�R�A�Ƀx�[�X�P�`�ǉ�
		base2B_E14->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//�R�A�ɃR�b�N�s�b�g�ǉ�

		PartsBSptr base2B_E12 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		base2B_E14->setPartsB(upJoint, base2B_E12);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2B_E12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�
		
		PartsBSptr base4_E10 = partsBFactory( PartsBSptr(new Base4()) ).lock();//lock���s�̃G���[�����ȗ�
		base2B_E12->setPartsB(upJoint, base4_E10);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base4_E10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2B_E8 = partsSetFactory(base4_E10, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base2B_E6 = partsSetFactory(base2B_E8, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base1A_E4 = partsSetFactory(base2B_E8, PartsBSptr(new Base1A()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base2F_D10 = partsBFactory( PartsBSptr(new Base2F()) ).lock();//lock���s�̃G���[�����ȗ�
		base4_E10->setPartsB(leftJoint, base2F_D10);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2F_D10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2C_D12 = partsBFactory( PartsBSptr(new Base2C()) ).lock();//lock���s�̃G���[�����ȗ�
		base2F_D10->setPartsB(downJoint, base2C_D12);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2C_D12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base3C_C12 = partsBFactory( PartsBSptr(new Base3C()) ).lock();//lock���s�̃G���[�����ȗ�
		base2C_D12->setPartsB(leftJoint, base3C_C12);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base3C_C12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2B_C10 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		base3C_C12->setPartsB(upJoint, base2B_C10);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2B_C10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2B_C8 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		base2B_C10->setPartsB(upJoint, base2B_C8);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2B_C8->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2B_C6 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		base2B_C8->setPartsB(upJoint, base2B_C6);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2B_C6->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new LuncherR()) )
			);				//�x�[�X�Q�a�Ƀ}�V���K���`�ǉ�


		PartsBSptr base2B_C4 = partsSetFactory(base2B_C6, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base1A_C2 = partsSetFactory(base2B_C4, PartsBSptr(new Base2B()), PartsASptr(new HadohoA()), upJoint).lock();
		
		PartsBSptr base2B_C14 = partsSetFactory(base3C_C12, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();
		
		PartsBSptr base2C_C16 = partsSetFactory(base2B_C14, PartsBSptr(new Base2C()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base2F_B16 = partsSetFactory(base2C_C16, PartsBSptr(new Base2F()), PartsASptr(new HadohoA()), leftJoint).lock();

		PartsBSptr base2B_B18 = partsSetFactory(base2F_B16, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base3B_B20 = partsSetFactory(base2B_B18, PartsBSptr(new Base3B()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base1D_B22 = partsSetFactory(base3B_B20, PartsBSptr(new Base1D()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2F_A20 = partsSetFactory(base3B_B20, PartsBSptr(new Base2F()), PartsASptr(new MachineGunA()), leftJoint).lock();

		PartsBSptr base1D_A22 = partsSetFactory(base2F_A20, PartsBSptr(new Base1D()), PartsASptr(new SubCanonA()), downJoint).lock();


		PartsBSptr base2E_F10 = partsBFactory( PartsBSptr(new Base2E()) ).lock();//lock���s�̃G���[�����ȗ�
		base4_E10->setPartsB(rightJoint, base2E_F10);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2E_F10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2D_F12 = partsBFactory( PartsBSptr(new Base2D()) ).lock();//lock���s�̃G���[�����ȗ�
		base2E_F10->setPartsB(downJoint, base2D_F12);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2D_F12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base3B_G12 = partsBFactory( PartsBSptr(new Base3B()) ).lock();//lock���s�̃G���[�����ȗ�
		base2D_F12->setPartsB(rightJoint, base3B_G12);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base3B_G12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2B_G10 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		base3B_G12->setPartsB(upJoint, base2B_G10);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2B_G10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2B_G8 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		base2B_G10->setPartsB(upJoint, base2B_G8);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2B_G8->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�

		PartsBSptr base2B_G6 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock���s�̃G���[�����ȗ�
		base2B_G8->setPartsB(upJoint, base2B_G6);					//�x�[�X�Q�e�Ƀx�[�X�PD�ǉ�
		base2B_G6->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new LuncherL()) )
			);				//�x�[�X�P�c�Ƀ}�V���K���`�ǉ�


		PartsBSptr base2B_G4 = partsSetFactory(base2B_G6, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base1A_G2 = partsSetFactory(base2B_G4, PartsBSptr(new Base2B()), PartsASptr(new HadohoA()), upJoint).lock();
		
		PartsBSptr base2B_G14 = partsSetFactory(base3B_G12, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();
		
		PartsBSptr base2D_G16 = partsSetFactory(base2B_G14, PartsBSptr(new Base2D()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base2E_H16 = partsSetFactory(base2D_G16, PartsBSptr(new Base2E()), PartsASptr(new HadohoA()), rightJoint).lock();

		PartsBSptr base2B_H18 = partsSetFactory(base2E_H16, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base3C_H20 = partsSetFactory(base2B_H18, PartsBSptr(new Base3C()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base1D_H22 = partsSetFactory(base3C_H20, PartsBSptr(new Base1D()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2E_I20 = partsSetFactory(base3C_H20, PartsBSptr(new Base2E()), PartsASptr(new MachineGunA()), rightJoint).lock();

		PartsBSptr base1D_I22 = partsSetFactory(base2E_I20, PartsBSptr(new Base1D()), PartsASptr(new SubCanonA()), downJoint).lock();
		
		/*�e�L�X�g�R�s�[�����܂�*/

		this->update(game);			//���@�X�V�i�T���؁j
		startHp = maxHp;			//����HP�̋L�^
		startEnergy = maxEnergy;	//����EN�̋L�^
		startMan = maxMan;			//�����l�̋L�^
	}
	
}


/*�X�V�֐�*/
void KosenWing::update(Tomasen& game){
	/*�e�p�����[�^���X�V����*/
	frameCnt++;										//�t���[���J�E���g�̍X�V
	if(frameCnt > 50000) frameCnt = 0;

	/*�p�[�c�֌W�̍X�V*/
	if(PartsBSptr tmp = core.lock()){
		/*�p�[�c����̏����W*/
		TellUpBox box = {
			0,0,		//hp, maxHp
			0,0,0,		//energy,maxEnergy,chargeEnergy
			0,0,0,		//man,requireMan,maxMan
			0,0,0,		//fire,burnFire,maxFire
			0,0,1,0};	//A,lostA,B,lostB				
		tmp->tellUp(box);
		hp = box.hp;
		maxHp = box.maxHp;
		energy = box.energy;
		chargeEnergy = box.chargeEnergy;
		maxEnergy = box.maxEnergy;
		man = box.man;
		requireMan = box.requireMan;
		maxMan = box.maxMan;
		fire = box.fire;
		burnFire = box.burnFire;
		maxFire = box.maxFire;
		partsANum = box.pertsANum;
		partsALost += box.pertsALost;
		partsBNum = box.pertsBNum;
		partsBLost += box.pertsBLost;

		/*���l�̍X�V*/
		tmp->setKaihi(kaihi);
	}
	else{//�R�A������Ă�
		hp = 50;
		if(game.gameResult == 0){
			game.gameResult = 1;
		}
	}
	
	/*���@�ړ�*/
	dir = atan2(move.y, move.x);					//���݂̐i�s�p�Z�o
	dis = sqrt(move.x * move.x + move.y * move.y);	//�ړ��ʎZ�o
	if(dis > maxMove){
		dis = maxMove;						//�ړ��ʗ}�~
	}
	else{
		dis *= subMove;
	}
	move.x = cos(dir) * dis;				//�ړ��ʗ}�~
	move.y = sin(dir) * dis;				//�ړ��ʗ}�~
	pos.x = pos.x + cos(dir) * dis;			//���@�ړ�
	pos.y = pos.y + sin(dir) * dis;			//���@�ړ�
	/*�ړ�������*/
	if(pos.x < SCREEN_INDENT){
		pos.x = SCREEN_INDENT;
	}
	if(pos.y < 0){
		pos.y = 0;
	}
	if(pos.x > SCREEN_WIDTH - SCREEN_INDENT - size){
		pos.x = SCREEN_WIDTH - SCREEN_INDENT - size;
	}
	if(pos.y > SCREEN_HEIGHT - size){
		pos.y = SCREEN_HEIGHT - size;
	}

	/*�R�A�̍X�V*/
	if(PartsBSptr tmp = core.lock()){
		tmp->setPos(Vec2(pos.x, pos.y));
		tmp->update(game);	//�R�A�X�V�i�T���؁j
	}

	/*���l�̍X�V*/
	addKaihi(-4);
		
}

} //namespace tm2