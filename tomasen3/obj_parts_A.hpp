#ifndef INCLUDED_OBJ_PARTS_A_HPP
#define INCLUDED_OBJ_PARTS_A_HPP

#include "common.hpp"
#include "obj_parts.hpp"

namespace tm2{

class EngineA : public PartsA{
private:

public:
	/*�R���X�g���N�^*/
	EngineA();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
};

class CockpitA : public PartsA{
private:

public:
	/*�R���X�g���N�^*/
	CockpitA();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
};

class MachineGunA : public PartsA{//��
private:
	int stopShot;
public:
	/*�R���X�g���N�^*/
	MachineGunA();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
};

class MachineGunB : public PartsA{//�E
private:
	int stopShot;
public:
	/*�R���X�g���N�^*/
	MachineGunB();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
};

class MachineGunC : public PartsA{//��
private:
	int stopShot;
public:
	/*�R���X�g���N�^*/
	MachineGunC();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
};

class MachineGunD : public PartsA{//��
private:
	int stopShot;
public:
	/*�R���X�g���N�^*/
	MachineGunD();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
};

class SprinklerA : public PartsA{
private:
	int stopShot;
public:
	/*�R���X�g���N�^*/
	SprinklerA();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
};

class SubCanonA : public PartsA{
private:
	int stopShot;				//�ˌ��w��
	int targetShot;				//�^�[�Q�b�g��ߑ�
	double targetX;				//�^�[�Q�b�gX���W
	double targetY;				//�^�[�Q�b�gY���W
	double targetDistance;		//�^�[�Q�b�g����
	double targetDir;			//�^�[�Q�b�g�p�x
public:
	/*�R���X�g���N�^*/
	SubCanonA();
	/*�s���֐��i�e�����ŗL�����j*/
	void update(Tomasen& game);
	/*�`��֐��i�e�����ŗL�����j*/
	void draw(Tomasen& game);
	/*setter�֐�*/
	void setTargetShot(int targetShot){ SubCanonA::targetShot = targetShot; }
	void setTargetX(double targetX){ SubCanonA::targetX = targetX; }
	void setTargetY(double targetY){ SubCanonA::targetY = targetY; }
	void setTargetDistance(double targetDistance){ SubCanonA::targetDistance = targetDistance; }
	double getTargetDir(void){ return targetDir; }
};

class HadohoA : public PartsA{
private:
	int stopShot;
public:
	/*�R���X�g���N�^*/
	HadohoA();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
	/*�`��֐��i�e�����ŗL�����j*/
	void draw(Tomasen& game);
};

class HadohoB : public PartsA{
private:
	int stopShot;
public:
	/*�R���X�g���N�^*/
	HadohoB();
	/*�s���֐��i�e�����ŗL�����j*/
	void action(Tomasen& game);
	/*�`��֐��i�e�����ŗL�����j*/
	void draw(Tomasen& game);
};
class LuncherR : public PartsA{
private:
	int stopShot;				//�ˌ��w��
	int targetShot;				//�^�[�Q�b�g��ߑ�
	double targetX;				//�^�[�Q�b�gX���W
	double targetY;				//�^�[�Q�b�gY���W
	double targetDistance;		//�^�[�Q�b�g����
	double targetDir;			//�^�[�Q�b�g�p�x
	int kaiten;
public:
	/*�R���X�g���N�^*/
	LuncherR();
	/*�s���֐��i�e�����ŗL�����j*/
	void update(Tomasen& game);
	/*�`��֐��i�e�����ŗL�����j*/
	void draw(Tomasen& game);
	/*setter�֐�*/
	void setTargetShot(int targetShot){ LuncherR::targetShot = targetShot; }
	void setTargetX(double targetX){ LuncherR::targetX = targetX; }
	void setTargetY(double targetY){ LuncherR::targetY = targetY; }
	void setTargetDistance(double targetDistance){ LuncherR::targetDistance = targetDistance; }
	double getTargetDir(void){ return targetDir; }
};
class LuncherL : public PartsA{
private:
	int stopShot;				//�ˌ��w��
	int targetShot;				//�^�[�Q�b�g��ߑ�
	double targetX;				//�^�[�Q�b�gX���W
	double targetY;				//�^�[�Q�b�gY���W
	double targetDistance;		//�^�[�Q�b�g����
	double targetDir;			//�^�[�Q�b�g�p�x
	int kaiten;
public:
	/*�R���X�g���N�^*/
	LuncherL();
	/*�s���֐��i�e�����ŗL�����j*/
	void update(Tomasen& game);
	/*�`��֐��i�e�����ŗL�����j*/
	void draw(Tomasen& game);
	/*setter�֐�*/
	void setTargetShot(int targetShot){ LuncherL::targetShot = targetShot; }
	void setTargetX(double targetX){ LuncherL::targetX = targetX; }
	void setTargetY(double targetY){ LuncherL::targetY = targetY; }
	void setTargetDistance(double targetDistance){ LuncherL::targetDistance = targetDistance; }
	double getTargetDir(void){ return targetDir; }
};

} //namespace tm2
#endif//INCLUDED_OBJ_PARTS_A_HPP