#ifndef INCLUDED_LOCALCOMMOM_HPP
#define INCLUDED_LOCALCOMMOM_HPP

#include "common.hpp"
/*���̃Q�[�����ʂȐ錾*/

namespace tm2{

/*�y��ID*/
extern int musicBGM_1;
extern int musicBGM_2;
extern int musicBGM_3;
extern int musicBGM_4;
extern int musicBGM_5;
extern int musicShot;
extern int musicEnemyDown;
extern int musicFriendHit;
extern int musicDead1;
extern int musicDead2;
extern int musicDead3;
extern int musicDead4;
extern int musicHadou;
extern int musicSakebi;
extern int musicKaiten;
extern int musicAlarm;
extern int musicBakuhatsu;
extern int musicHaretsu;
extern int musicHidan;
extern int musicKikanho;
extern int musicFami;
extern int musicWarp;
extern int musicBiribiri;
extern int musicMissile;

/***�񋓌^�̐錾***/
/*�y��ڑ����*/
enum jointOK {jointNG = -1, jointEmp, jointUpExist, jointDownExist};
/*�����ڑ����*/
enum weaponOK {weaponNG = -1, weaponEmp, weaponExist};
/*�y��ڑ��ʒu*/
enum jointIndex {upJoint, rightJoint, downJoint, leftJoint, jointIndexEnd};
/*�����ڑ��ʒu*/
enum weaponIndex {mainWeapon, subWeapon, weaponIndexEnd};

/***�\���̐錾***/
struct TellUpBox{
	int hp;
	int maxHp;
	int energy;
	int maxEnergy;
	int chargeEnergy;
	int man;
	int requireMan;
	int maxMan;
	int fire;
	int burnFire;
	int maxFire;
	int pertsANum;
	int pertsALost;
	int pertsBNum;
	int pertsBLost;
};

/*�Œ�p�����[�^*/
extern const int startMode;		//�������
extern const int startStage;	//�����X�e�[�W
extern const int startPosX;		//�������@X���W
extern const int startPosY;		//�������@Y���W
extern const double moveAmount;	//�����x�i�P�t���[�����j
extern const int wideArea;		//��ʊO�̈�̍L��

} //namespace tm2
#endif//INCLUDED_LOCALCOMMOM_HPP