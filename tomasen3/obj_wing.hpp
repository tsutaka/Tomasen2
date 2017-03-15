#ifndef INCLUDED_OBJ_WING_HPP
#define INCLUDED_OBJ_WING_HPP

#include <cmath>		//math
#include <vector>		//vector
#include <memory>		//shared_ptr

#include "common.hpp"
#include "object.hpp"

// std::tr1:: を std:: と書けるように
namespace std {
	using namespace tr1; 
}

namespace tm2{

/*ウィングクラス（機体）*/
class Wing : public Object{
protected:
	/*固定パラメータ*/
	int shotInterval;	//射撃間隔
	
public:
	/*更新関数*/
	virtual void update(Tomasen& game) = 0;
	virtual void draw(Tomasen& game) = 0;

};

/*自機クラス*/
class Friend : public Wing{
protected:
	/*変動パラメータ*/

	int energy;			//エネルギー
	int man;			//人員
	int fire;			//火災箇所数
	int chargeEnergy;	//回復エネルギー
	int requireMan;		//必要人員
	int burnFire;		//発火値

	int startHp;		//ステージ初期HP
	int startEnergy;	//ステージ初期EN
	int startMan;		//ステージ初期人
	int startFire;		//ステージ初期炎

	int kaihi;			//回避用パラメータ(0-100)

	/*固定パラメータ*/
	int maxEnergy;	//最大エネルギー
	int maxMan;		//必要人員
	int maxFire;	//発火火勢

	int partsANum;	//現時点パーツA数
	int partsALost;	//累積喪失パーツA数
	int partsBNum;	//現時点パーツB数
	int partsBLost;	//累積喪失パーツB数

public:
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);
	/*getter関数*/
	int getStartHp(){return startHp;}
	int getEnergy(){return energy;}
	int getMaxEnergy(){return maxEnergy;}
	int getChargeEnergy(){return chargeEnergy;}
	int getStartEnergy(){return startEnergy;}
	int getMan(){return man;}
	int getRequireMan(){return requireMan;}
	int getMaxMan(){return maxMan;}
	int getStartMan(){return startMan;}
	int getFire(){return fire;}
	int getBurnFire(){return burnFire;}
	int getMaxFire(){return maxFire;}
	int getStartFire(){return startFire;}
	int getPartsANum(){return partsANum;}
	int getPartsALost(){return partsALost;}
	int getPartsBNum(){return partsBNum;}
	int getPartsBLost(){return partsBLost;}
	int getKaihi(){return kaihi;}

	/*setter関数*/
	void setKaihi(int kaihi){Friend::kaihi = kaihi;}

	/*カウントアップ回数*/
	void addKaihi(int kaihi);

};
/*グローバルリソース宣言*/
typedef weak_ptr< Friend > FriendWptr;		//自機のweakポインタ
typedef shared_ptr< Friend > FriendSptr;	//自機のsharedポインタ
typedef vector< FriendSptr > FriendVsptr;	//自機のsharedポインタの配列
extern FriendVsptr friendList;				//自機リスト
FriendWptr friendFactory(FriendSptr friendw, Vec2 pos);	//自機ファクトリ関数

/*敵機クラス*/
class Enemy : public Wing{//当たり判定インタフェースを実装
protected:
	int pattern;		//行動パターン
	Vec2 targetPos;		//移動目的座標
	int phase;			//行動フェーズ
	int canShot;		//射撃許可
	int lockOn;			//ロックオン　ロックオン:1～
	int waitTime;		//パラメータ1
	int boss;		//ボスフラグ



public:
	/*コンストラクタ*/
	Enemy();
	/*更新関数*/
	void update(Tomasen& game);
	/*更新関数*/
	void draw(Tomasen& game);
	virtual void action(Object obj) = 0;

	/*setter関数*/
	void setPattern(int pattern){ Enemy::pattern = pattern; }
	void setTargetPos(Vec2 targetPos){ Enemy::targetPos = targetPos; }
	void setLockOn(int lockOn){ Enemy::lockOn = lockOn; }
	void setWaitTime(int waitTime){ Enemy::waitTime = waitTime; }
	int getBoss(void){ return boss; }
	
};
/*グローバルリソース宣言*/
typedef weak_ptr< Enemy > EnemyWptr;		//敵機のweakポインタ
typedef shared_ptr< Enemy > EnemySptr;		//敵機のsharedポインタ
typedef vector< EnemySptr > EnemyVsptr;		//敵機のsharedポインタの配列
extern EnemyVsptr enemyList;				//敵機リスト
void enemyFactory(EnemySptr enemy, Vec2 pos, int pattern);//敵機ファクトリ関数


} //namespace tm2
#endif//INCLUDED_OBJ_WING_HPP