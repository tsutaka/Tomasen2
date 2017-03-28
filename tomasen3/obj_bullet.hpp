#ifndef INCLUDED_OBJ_BULLET_HPP
#define INCLUDED_OBJ_BULLET_HPP

#include <vector>		//vector
#include <memory>		//shared_ptr

#include "common.hpp"
#include "object.hpp"

// std::tr1:: を std:: と書けるように
namespace std {
	using namespace tr1; 
}

namespace tm2{

class Bullet : public Object{
private:
	int fire;				//火力

public:
	/*コンストラクタ*/
	Bullet();
	/*更新関数*/
	virtual void update(Tomasen& game) = 0;
	/*描画関数*/
	virtual void draw(Tomasen& game) = 0;

	/*getter関数*/
	int getFire(){return fire;}
};

class FriendBullet : public Bullet{
public:
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);
};
/*グローバルリソース宣言*/
typedef weak_ptr< FriendBullet > FriendBulletWptr;			//自弾のweakポインタ
typedef shared_ptr< FriendBullet > FriendBulletSptr;		//自弾のsharedポインタ
typedef vector< FriendBulletSptr > FriendBulletVsptr;		//自弾のsharedポインタの配列
extern FriendBulletVsptr friendBulletList;					//自弾リスト
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos);	//自弾ファクトリ関数
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos, double dir);	//自弾ファクトリ関数
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY);	//自弾ファクトリ関数
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY, double dir);	//自弾ファクトリ関数


class NormalBullet : public FriendBullet{
public:
	/*コンストラクタ*/
	NormalBullet();	
};
class BlueBullet : public FriendBullet{
public:
	/*コンストラクタ*/
	BlueBullet();	
};
class HadoBeam : public FriendBullet{
public:
	/*コンストラクタ*/
	HadoBeam();
	/*描画関数*/
	void draw(Tomasen& game);
};
class MissBullet : public FriendBullet{
public:
	/*コンストラクタ*/
	MissBullet();
};
class MissileRBullet : public FriendBullet{
public:
	/*コンストラクタ*/
	MissileRBullet();
	/*デストラクタ*/
	~MissileRBullet();
	/*更新関数*/
	void update(Tomasen& game);
};
class MissileLBullet : public FriendBullet{
public:
	/*コンストラクタ*/
	MissileLBullet();
	/*デストラクタ*/
	~MissileLBullet();
	/*更新関数*/
	void update(Tomasen& game);
};


class EnemyBullet : public Bullet{
public:
	int phase;
	
	/*更新関数*/
	void update(Tomasen& game);
	/*更新関数*/
	void draw(Tomasen& game);
	/*行動関数*/
	virtual void action(const Object &obj) = 0;
};
/*グローバルリソース宣言*/
typedef weak_ptr< EnemyBullet > EnemyBulletWptr;		//敵弾のweakポインタ
typedef shared_ptr< EnemyBullet > EnemyBulletSptr;		//敵弾のsharedポインタ
typedef vector< EnemyBulletSptr > EnemyBulletVsptr;		//敵弾のsharedポインタの配列
extern EnemyBulletVsptr enemyBulletList;				//敵弾リスト
void enemyBulletFactory(EnemyBulletSptr enemyBullet, Vec2 pos);
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY);
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY, double dir);

class WeakBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	WeakBullet();
	/*行動関数*/
	void action(const Object &obj);
};
class WideBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	WideBullet();
	/*行動関数*/
	void action(const Object &obj);
};
class SprinklerBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	SprinklerBullet();
	/*行動関数*/
	void action(const Object &obj);
};
class GreenBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	GreenBullet();
	/*行動関数*/
	void action(const Object &obj);
};
class Ene1Bullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	Ene1Bullet();
	/*行動関数*/
	void action(const Object &obj);
};
class Ene2Bullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	Ene2Bullet();
	/*行動関数*/
	void action(const Object &obj);
};
class Ene3Bullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	Ene3Bullet();
	/*行動関数*/
	void action(const Object &obj);
};
class RedKunaiBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	RedKunaiBullet();
	/*描画関数*/
	void draw(Tomasen& game);
	/*行動関数*/
	void action(const Object &obj);
};
class YellowKunaiBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	YellowKunaiBullet();
	/*描画関数*/
	void draw(Tomasen& game);
	/*行動関数*/
	void action(const Object &obj);
};

class RaserBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	RaserBullet();
	/*描画関数*/
	void draw(Tomasen& game);
	/*行動関数*/
	void action(const Object &obj);
};

class RedMBullet : public EnemyBullet{
public:
	/*コンストラクタ*/
	RedMBullet();
	/*描画関数*/
	void draw(Tomasen& game);
	/*行動関数*/
	void action(const Object &obj);
};

} //namespace tm2
#endif//INCLUDED_OBJ_BULLET_HPP