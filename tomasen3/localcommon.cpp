#include "localcommon.hpp"

namespace tm2{

/*変動パラメータ*/
int musicBGM_1;
int musicBGM_2;
int musicBGM_3;
int musicBGM_4;
int musicBGM_5;
int musicShot;
int musicEnemyDown;
int musicFriendHit;
int musicDead1;
int musicDead2;
int musicDead3;
int musicDead4;
int musicHadou;
int musicSakebi;
int musicKaiten;
int musicAlarm;
int musicBakuhatsu;
int musicHaretsu;
int musicHidan;
int musicKikanho;
int musicFami;
int musicWarp;
int musicBiribiri;
int musicMissile;

/*固定パラメータ */
const int startMode = 0;					//初期画面
const int startStage = 1;					//初期ステージ
const int startPosX = SCREEN_WIDTH / 2;		//初期自機X座標
const int startPosY = SCREEN_HEIGHT - 50;	//初期自機Y座標
const double moveAmount = 0.3;				//移動量定義
const int wideArea = 100;					//画面外の広さ

}//namespace tm2