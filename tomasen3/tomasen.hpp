#ifndef INCLUDED_TOMASEN_HPP
#define INCLUDED_TOMASEN_HPP

#include <windows.h>				//HWND

#include "tiptile.hpp"				//画像描画
#include "drawtext.hpp"				//画像描画
#include "music.hpp"				//楽曲再生
#include "common.hpp"				//共通
#include "localcommon.hpp"			//ローカル共通
#include "object.hpp"				//オブジェクト全般

#include "obj_wing.hpp"				//機体
#include "obj_parts.hpp"			//パーツ
#include "obj_item.hpp"				//アイテム
#include "obj_effect.hpp"			//エフェクト
#include "obj_bullet.hpp"			//弾
#include "obj_print.hpp"			//弾
#include "event.hpp"				//イベント全般

#include "obj_parts_A.hpp"			//兵装
#include "obj_parts_B.hpp"			//土台
#include "obj_wing_friend.hpp"		//自機
#include "obj_wing_enemy.hpp"		//敵機

namespace tm2{

class Tomasen{
public:
	/*作業用クラス*/
	TipTile *IMAGE;
	Music *MUSIC;
	HWND hWnd;
	
public:
	/*変動パラメータ*/
	int mode;							//現在の画面
	int stage;							//現在ステージ
	int gold;							//GOLD
	int score;							//SCORE
	int hiscore;						//HISCORE
	char checktext[256];				//汎用文字列
	bool canInput;						//入力可否
	int prevShot;						//射撃状態記憶
	int shotPerm;						//射撃許可
	char inputLog[90000];					//キー入力取得
	int bossFlag;						//ボス削除フラグ
	
	typedef vector< string > StringV;	//文字列配列
	
public:
	/*リソース*/
	FriendWptr kosenWing;			//自機への参照
	BarWptr hpBar;					//HPゲージ
	BarWptr energyBar;				//ENゲージ
	BarWptr manBar;					//人員ゲージ
	BarWptr fireBar;				//炎ゲージ
	LabelWptr goldLabel;			//ゴールドラベル
	LabelWptr scoreLabel;			//スコアラベル
	LabelWptr hiscoreLabel;			//スコアラベル
	LabelWptr resultManLabel;			//生存者ラベル
	LabelWptr resultScoreLabel;			//トータルスコアラベル
	
	int gameResult;					//ゲームリザルト表示時：１、リザルト中：２
	int gameClear;					//ゲームクリア時：１
	int gameRestart;				//ゲームリスタート時に１
	int gameEnd;					//ゲーム終了時に１

	StringV stringV;				//デバッグ用文字列
		
	/*コンストラクタ*/
	Tomasen();
	/*デストラクタ*/
	~Tomasen();

	/*ゲーム本体*/
	void runGame(HWND);				//メインループ
	
	

private:
	/*初期化関数*/
	void initGame();			//初期化処理
	/*入力関数*/	
	void inputGame();			//ユーザ入力受付
	/*情報伝達関数*/
	void communicationGame();	//オブジェクト間の情報交換
	/*更新関数*/
	void updateGame();			//オブジェクトの更新
	/*削除関数*/
	void deleteGame();			//当たり判定等
	/*表示関数*/
	void printGame();			//画面描画処理


	/*レーダー描画*/
	void drawRader();			//レーダー
};


} //namespace tm2
#endif//INCLUDED_TOMASEN_HPP