#ifndef INCLUDED_OBJ_BULLET_HPP
#define INCLUDED_OBJ_BULLET_HPP

#include <vector>		//vector
#include <memory>		//shared_ptr

#include "common.hpp"
#include "object.hpp"

// std::tr1:: �� std:: �Ə�����悤��
namespace std {
	using namespace tr1; 
}

namespace tm2{

class Bullet : public Object{
private:
	int fire;				//�Η�

public:
	/*�R���X�g���N�^*/
	Bullet();
	/*�X�V�֐�*/
	virtual void update(Tomasen& game) = 0;
	/*�`��֐�*/
	virtual void draw(Tomasen& game) = 0;

	/*getter�֐�*/
	int getFire(){return fire;}
};

class FriendBullet : public Bullet{
public:
	/*�X�V�֐�*/
	void update(Tomasen& game);
	/*�`��֐�*/
	void draw(Tomasen& game);
};
/*�O���[�o�����\�[�X�錾*/
typedef weak_ptr< FriendBullet > FriendBulletWptr;			//���e��weak�|�C���^
typedef shared_ptr< FriendBullet > FriendBulletSptr;		//���e��shared�|�C���^
typedef vector< FriendBulletSptr > FriendBulletVsptr;		//���e��shared�|�C���^�̔z��
extern FriendBulletVsptr friendBulletList;					//���e���X�g
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos);	//���e�t�@�N�g���֐�
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos, double dir);	//���e�t�@�N�g���֐�
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY);	//���e�t�@�N�g���֐�
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY, double dir);	//���e�t�@�N�g���֐�


class NormalBullet : public FriendBullet{
public:
	/*�R���X�g���N�^*/
	NormalBullet();	
};
class BlueBullet : public FriendBullet{
public:
	/*�R���X�g���N�^*/
	BlueBullet();	
};
class HadoBeam : public FriendBullet{
public:
	/*�R���X�g���N�^*/
	HadoBeam();
	/*�`��֐�*/
	void draw(Tomasen& game);
};
class MissBullet : public FriendBullet{
public:
	/*�R���X�g���N�^*/
	MissBullet();
};
class MissileRBullet : public FriendBullet{
public:
	/*�R���X�g���N�^*/
	MissileRBullet();
	/*�f�X�g���N�^*/
	~MissileRBullet();
	/*�X�V�֐�*/
	void update(Tomasen& game);
};
class MissileLBullet : public FriendBullet{
public:
	/*�R���X�g���N�^*/
	MissileLBullet();
	/*�f�X�g���N�^*/
	~MissileLBullet();
	/*�X�V�֐�*/
	void update(Tomasen& game);
};


class EnemyBullet : public Bullet{
public:
	int phase;
	
	/*�X�V�֐�*/
	void update(Tomasen& game);
	/*�X�V�֐�*/
	void draw(Tomasen& game);
	/*�s���֐�*/
	virtual void action(const Object &obj) = 0;
};
/*�O���[�o�����\�[�X�錾*/
typedef weak_ptr< EnemyBullet > EnemyBulletWptr;		//�G�e��weak�|�C���^
typedef shared_ptr< EnemyBullet > EnemyBulletSptr;		//�G�e��shared�|�C���^
typedef vector< EnemyBulletSptr > EnemyBulletVsptr;		//�G�e��shared�|�C���^�̔z��
extern EnemyBulletVsptr enemyBulletList;				//�G�e���X�g
void enemyBulletFactory(EnemyBulletSptr enemyBullet, Vec2 pos);
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY);
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY, double dir);

class WeakBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	WeakBullet();
	/*�s���֐�*/
	void action(const Object &obj);
};
class WideBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	WideBullet();
	/*�s���֐�*/
	void action(const Object &obj);
};
class SprinklerBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	SprinklerBullet();
	/*�s���֐�*/
	void action(const Object &obj);
};
class GreenBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	GreenBullet();
	/*�s���֐�*/
	void action(const Object &obj);
};
class Ene1Bullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	Ene1Bullet();
	/*�s���֐�*/
	void action(const Object &obj);
};
class Ene2Bullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	Ene2Bullet();
	/*�s���֐�*/
	void action(const Object &obj);
};
class Ene3Bullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	Ene3Bullet();
	/*�s���֐�*/
	void action(const Object &obj);
};
class RedKunaiBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	RedKunaiBullet();
	/*�`��֐�*/
	void draw(Tomasen& game);
	/*�s���֐�*/
	void action(const Object &obj);
};
class YellowKunaiBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	YellowKunaiBullet();
	/*�`��֐�*/
	void draw(Tomasen& game);
	/*�s���֐�*/
	void action(const Object &obj);
};

class RaserBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	RaserBullet();
	/*�`��֐�*/
	void draw(Tomasen& game);
	/*�s���֐�*/
	void action(const Object &obj);
};

class RedMBullet : public EnemyBullet{
public:
	/*�R���X�g���N�^*/
	RedMBullet();
	/*�`��֐�*/
	void draw(Tomasen& game);
	/*�s���֐�*/
	void action(const Object &obj);
};

} //namespace tm2
#endif//INCLUDED_OBJ_BULLET_HPP