#ifndef INCLUDED_LOCALCOMMOM_HPP
#define INCLUDED_LOCALCOMMOM_HPP

#include "common.hpp"
/*このゲーム共通な宣言*/

namespace tm2{

/*楽曲ID*/
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

/***列挙型の宣言***/
/*土台接続状態*/
enum jointOK {jointNG = -1, jointEmp, jointUpExist, jointDownExist};
/*兵装接続状態*/
enum weaponOK {weaponNG = -1, weaponEmp, weaponExist};
/*土台接続位置*/
enum jointIndex {upJoint, rightJoint, downJoint, leftJoint, jointIndexEnd};
/*兵装接続位置*/
enum weaponIndex {mainWeapon, subWeapon, weaponIndexEnd};

/***構造体宣言***/
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

/*固定パラメータ*/
extern const int startMode;		//初期画面
extern const int startStage;	//初期ステージ
extern const int startPosX;		//初期自機X座標
extern const int startPosY;		//初期自機Y座標
extern const double moveAmount;	//加速度（１フレーム分）
extern const int wideArea;		//画面外領域の広さ

} //namespace tm2
#endif//INCLUDED_LOCALCOMMOM_HPP