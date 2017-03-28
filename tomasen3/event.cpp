#include <cmath>

#include "event.hpp"
#include "drawtext.hpp"

#include "localcommon.hpp"
#include "obj_effect.hpp"
#include "obj_wing_enemy.hpp"

namespace tm2{

/*グローバルリソース定義*/
EventVsptr eventList;		//イベントリスト
void eventFactory(EventSptr event){
		eventList.push_back( event );			//リストにオブジェクト追加
}

/*コンストラクタ*/
Event::Event(){
	pos = Vec2(0.0, 0.0);	//現在位置
	dis = 0.0;				//移動量
	dir = 0.0;				//角度
	frameCnt = 0;			//フレームカウント
	phase = 0;				//フェーズ
	next = 0;			//イベント終了フラグ
}

/*更新関数*/
void Event::update(Tomasen& game){
	/*カウントアップ*/
	frameCnt++;
	/*イベントの位置を更新*/
	pos.x += cos(dir) * dis;
	pos.y += sin(dir) * dis;
}


/*アクション関数（個別）*/
void GameTitle::action(Tomasen& game){

	/*入力受付*/
	if(GetAsyncKeyState(VK_SPACE) && phase >= 1) {//SPACE
		next = 1;	//終了判定フラグ
		effectList.clear();
	}
	if(GetAsyncKeyState(VK_ESCAPE) && phase >= 1) {//VK_ESCAPE
		next = 999;	//終了判定フラグ
	}
	if(frameCnt >= 1000 && game.mode != -1) {//デモ開始
		next = 1000;	//デモモードへ
	}
	/*タイムスケジュール*/
	if(phase == 0){
		phase++;
		effectFactory( EffectSptr(new DarkR()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new DarkY()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new DarkG()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new DarkB()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightB()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightG()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightY()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightR()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleTo()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleMa()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleSe()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleNi()) );		//リストにオブジェクト追加

		effectFactory( EffectSptr(new Earth()), 
			Vec2(SCREEN_WIDTH/2 - 10*tipSize/2, -100), //10 = outputW
			Vec2(SCREEN_WIDTH/2 - 10*tipSize/2, SCREEN_HEIGHT-200) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it)->setMoveMode(0);										//エフェクトを指定位置に移動
	}
	else if(phase == 1 && frameCnt == 100){
		phase++;
		effectFactory( EffectSptr(new PushSpace()) );	//リストにオブジェクト追加

	}
	else if(phase == 2 && frameCnt == 500){
		phase++;
		//effectFactory( EffectSptr(new TextScreen()) );	//リストにオブジェクト追加

	}
}

/*コンストラクタ*/
Stage1::Stage1(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//初期位置
}
/*アクション関数（個別）*/
void Stage1::action(Tomasen& game){
	/*STAGE1の敵キャラ生成*/
	
	if(phase == 0 && frameCnt == 0 ){
		effectFactory( EffectSptr(new DarkR()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it)->setTargetPos(Vec2(50.0, 150.0));						//エフェクトを指定位置に移動

		effectFactory( EffectSptr(new DarkY()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it2 = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it2)->setTargetPos(Vec2(50.0, 200.0));						//エフェクトを指定位置に移動

		effectFactory( EffectSptr(new DarkG()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it3 = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it3)->setTargetPos(Vec2(50.0, 250.0));						//エフェクトを指定位置に移動

		effectFactory( EffectSptr(new DarkB()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it4 = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it4)->setTargetPos(Vec2(50.0, 300.0));						//エフェクトを指定位置に移動

		effectFactory( EffectSptr(new TitleTo()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it5 = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it5)->setTargetPos(Vec2(50.0, 150.0));						//エフェクトを指定位置に移動

		effectFactory( EffectSptr(new TitleMa()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it6 = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it6)->setTargetPos(Vec2(50.0, 200.0));						//エフェクトを指定位置に移動

		effectFactory( EffectSptr(new TitleSe()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it7 = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it7)->setTargetPos(Vec2(50.0, 250.0));						//エフェクトを指定位置に移動

		effectFactory( EffectSptr(new TitleNi()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it8 = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it8)->setTargetPos(Vec2(50.0, 300.0));						//エフェクトを指定位置に移動
	}
	/*惑星*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Earth()) );	//リストにオブジェクト追加

	}


	/*1面の背景*/
	
	if(frameCnt % 5 == 0){
		effectFactory( EffectSptr(new Star1()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.6));								//下方向に移動
	}
	if(frameCnt % 7 == 0){
		effectFactory( EffectSptr(new Star2()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.6));								//下方向に移動
	}


	/*1-1*/
	//センター出現型
	if(phase == 0 && frameCnt < 200 && frameCnt % 50 == 0){

		if(frameCnt % 100 == 0){
			enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
			EnemyVsptr::iterator it3 = enemyList.end() - 1;				//直前のオブジェクトを参照
			(*it3)->setPos(Vec2(SCREEN_WIDTH / 2.0 - 60, -40.0));			//敵機をイベント位置に移動
			(*it3)->setMove(Vec2(0.0, 1.6));								//敵機をイベント位置に移動
			(*it3)->setPattern(6);										//敵機の行動パターンの指定
			(*it3)->setWaitTime(300 - frameCnt);									//待機時間

			enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
			EnemyVsptr::iterator it4 = enemyList.end() - 1;				//直前のオブジェクトを参照
			(*it4)->setPos(Vec2(SCREEN_WIDTH / 2.0, -40.0));			//敵機をイベント位置に移動
			(*it4)->setMove(Vec2(0.0, 1.6));								//敵機をイベント位置に移動
			(*it4)->setPattern(6);										//敵機の行動パターンの指定
			(*it4)->setWaitTime(300 - frameCnt);									//待機時間

			enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
			EnemyVsptr::iterator it5 = enemyList.end() - 1;				//直前のオブジェクトを参照
			(*it5)->setPos(Vec2(SCREEN_WIDTH / 2.0 + 60, -40.0));			//敵機をイベント位置に移動
			(*it5)->setMove(Vec2(0.0, 1.6));								//敵機をイベント位置に移動
			(*it5)->setPattern(6);										//敵機の行動パターンの指定
			(*it5)->setWaitTime(300 - frameCnt);									//待機時間
		}
		else{
			enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
			EnemyVsptr::iterator it1 = enemyList.end() - 1;				//直前のオブジェクトを参照
			(*it1)->setPos(Vec2(SCREEN_WIDTH / 2.0 - 30, -40.0));			//敵機をイベント位置に移動
			(*it1)->setMove(Vec2(0.0, 1.6));								//敵機をイベント位置に移動
			(*it1)->setPattern(6);										//敵機の行動パターンの指定
			(*it1)->setWaitTime(300 - frameCnt);									//待機時間

			enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
			EnemyVsptr::iterator it2 = enemyList.end() - 1;				//直前のオブジェクトを参照
			(*it2)->setPos(Vec2(SCREEN_WIDTH / 2.0 + 30, -40.0));			//敵機をイベント位置に移動
			(*it2)->setMove(Vec2(0.0, 1.6));								//敵機をイベント位置に移動
			(*it2)->setPattern(6);										//敵機の行動パターンの指定
			(*it2)->setWaitTime(300 - frameCnt);									//待機時間
		}


	}
	if(phase == 0 && frameCnt > 250){
		phase++;
		frameCnt = 0;
	}
	/*1-2*/
	//左上から出現
	if(phase == 1 && frameCnt < 250 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT - 50, -50));				//敵機をイベント位置に移動
		(*it)->setPattern(2);										//敵機の行動パターンの指定
	}
	if(phase == 1 && frameCnt > 500){
		phase++;
		frameCnt = 0;
	}
	/*1-3*/
	//後ろから出現
	if(phase == 2 && frameCnt > 350){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyB()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 3 && frameCnt < 400 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT + 80, SCREEN_HEIGHT + 50));	//敵機をイベント位置に移動
		(*it)->setPattern(2);										//敵機の行動パターンの指定
	}
	if(phase == 3 && frameCnt < 400 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH-SCREEN_INDENT-80, SCREEN_HEIGHT + 50));	//敵機をイベント位置に移動
		(*it)->setPattern(3);										//敵機の行動パターンの指定
	}
	if(phase == 3 && frameCnt > 600){
		phase++;
		frameCnt = 0;
	}
	/*1-4*/
	//前から五月雨
	if(phase == 4){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyB()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT +50, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(1);										//敵機の行動パターンの指定
	}
	if(phase == 5 && frameCnt % 30 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2,  -50));	//敵機をイベント位置に移動
		(*it)->setPattern(4);										//敵機の行動パターンの指定
	}
	if(phase == 5 && frameCnt > 400){
		phase++;
		frameCnt = 0;
	}
	/*1-5*/
	//センターにイルカさん
	if(phase == 6){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyC()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if (phase ==7 && frameCnt > 1100){
		next = 2;
	}

}
/*アクション関数（個別）*/

Stage2::Stage2(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//初期位置
}
/*アクション関数（個別）*/
void Stage2::action(Tomasen& game){
	/*STAGE2の敵キャラ生成*/
	
	/*2面の背景*/
	
	if(frameCnt % 14 == 0){
		effectFactory( EffectSptr(new Star1()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.5));								//下方向に移動
	}
	if(frameCnt % 12 == 0){
		effectFactory( EffectSptr(new Star2()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.5));								//下方向に移動
	}

	/*惑星*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Mars()) );	//リストにオブジェクト追加
	}
	
	/*2-1*/
	//右上から惑星
	if(phase == 0 && frameCnt < 200 && frameCnt % 10 == 0){
		enemyList.push_back( EnemySptr(new EnemyD()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(makeRand(pos.x, 7), pos.y));			//敵機をイベント位置に移動
		(*it)->setPattern(0);
	}
	if(phase == 0 && frameCnt > 250){
		phase++;
		frameCnt = 0;
	}
	/*2-2*/
	//ワープ出現
	if(phase == 1 && frameCnt < 1500 && frameCnt % 100 == 0){
		effectList.push_back( EffectSptr(new Marker()) );
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(
			SCREEN_WIDTH/2 + makeRand(0.0, 200), 
			SCREEN_HEIGHT/2 - 200 + makeRand(0.0, 100)));				//エフェクトをイベント位置に移動
	}
	if(phase == 1 && frameCnt > 1600){
		phase++;
		frameCnt = 0;
	}
	/*2-3*/
	//堅い中ボス
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyF()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 3 && frameCnt > 900){
		phase++;
	}
	if (phase == 4 && frameCnt > 1200){
		next = 3;
	}
}
/*アクション関数（個別）*/
Stage3::Stage3(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//初期位置
}
/*アクション関数（個別）*/
void Stage3::action(Tomasen& game){
	/*STAGE3の敵キャラ生成*/
		
	/*3面の背景*/
	
	if(frameCnt % 4 == 0){
		effectFactory( EffectSptr(new Star1()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.4));								//下方向に移動
	}
	if(frameCnt % 6 == 0){
		effectFactory( EffectSptr(new Star2()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.4));								//下方向に移動
	}

	/*惑星*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Jupiter()) );	//リストにオブジェクト追加
	}
		
	/*3-1*/
	//イルカ
	if(phase == 0 && frameCnt < 200 && frameCnt == 10){
		enemyList.push_back( EnemySptr(new EnemyC()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT +200.0 + makeRand(0.0, 7), -50));			//敵機をイベント位置に移動
		(*it)->setPattern(1);										//敵機の行動パターンの指定
	}
	if(phase == 0 && frameCnt > 250){
		phase++;
		frameCnt = 0;
	}
	/*3-2*/
	//タコ
	if(phase == 1 && frameCnt < 600 && frameCnt % 150 == 0){
		enemyList.push_back( EnemySptr(new EnemyH()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2 + makeRand(0.0, 100), -100));//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 1 && frameCnt > 800){
		phase++;
		frameCnt = 0;
	}
	/*3-3*/
	//ユーフォー
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyI()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 3 && frameCnt > 300){
		phase++;
	}
	if (phase == 4 && frameCnt > 700){
		next = 4;
	}
}
/*アクション関数（個別）*/
Stage4::Stage4(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//初期位置
}
/*アクション関数（個別）*/
void Stage4::action(Tomasen& game){
	/*STAGE4の敵キャラ生成*/
	
	
	/*4面の背景*/
	if(frameCnt % 30 == 0){
		effectFactory( EffectSptr(new Star1()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.3));								//下方向に移動
	}
	if(frameCnt % 28 == 0){
		effectFactory( EffectSptr(new Star2()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.3));								//下方向に移動		//イベント位置に移動
	}	

	/*惑星*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Saturn()) );	//リストにオブジェクト追加
	}
	if(phase == 0){					
		phase = 2;//test
	}
	/*4-1*/
	//ロケットもち
	if(phase == 0 && frameCnt < 200 && frameCnt == 10){
		enemyList.push_back( EnemySptr(new EnemyJ()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH/2,  + 10));			//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 0 && frameCnt > 800){
		frameCnt = 0;
		phase++;
	}
	/*4-2*/
	//黒い鳥
	if(phase == 1 && frameCnt < 350 && frameCnt % 80 == 0){
		enemyList.push_back( EnemySptr(new EnemyK()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT - 50, SCREEN_HEIGHT - 50));				//敵機をイベント位置に移動
		(*it)->setPattern(1);										//敵機の行動パターンの指定

		enemyList.push_back( EnemySptr(new EnemyK()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it2 = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT - 50));				//敵機をイベント位置に移動
		(*it2)->setPattern(2);										//敵機の行動パターンの指定
	}
	if(phase == 1 && frameCnt > 600){
		frameCnt = 0;
		phase++;
	}
	/*4-3*/
	//サテライトアンテナ
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyL()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 3 && frameCnt > 900){
		phase++;
	}
	if (phase ==4 && frameCnt > 1100){
		next = 5;
	}
}
/*アクション関数（個別）*/
Stage5::Stage5(){
	pos = Vec2(SCREEN_WIDTH-SCREEN_INDENT - 50, -wideArea);	//初期位置
}
/*アクション関数（個別）*/
void Stage5::action(Tomasen& game){
	/*STAGE5の敵キャラ生成*/
	
	/*3面の背景*/
	if(frameCnt % 51 == 0){
		effectFactory( EffectSptr(new Star1()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.1));								//下方向に移動
	}
	if(frameCnt % 38 == 0){
		effectFactory( EffectSptr(new Star2()) );	//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2.0 + makeRand(0.0, SCREEN_WIDTH / 2), 0.0));			//イベント位置に移動
		(*it)->setMove(Vec2(0.0, 1.1));								//下方向に移動		//イベント位置に移動
	}

	/*惑星*/
	if(phase == 0 && frameCnt == 10 ){
		effectFactory( EffectSptr(new Uranus()) );	//リストにオブジェクト追加
	}
	
	/*5-1*/
	if(phase == 0 && frameCnt < 200 && frameCnt % 20 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(makeRand(pos.x, 7), pos.y));			//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 0 && frameCnt > 650){
		phase++;
		frameCnt = 0;
	}
	/*5-2*/
	if(phase == 1 && frameCnt < 450 && frameCnt % 50 == 0){
		enemyList.push_back( EnemySptr(new EnemyN()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT + 300, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(1);										//敵機の行動パターンの指定
	}
	if(phase == 1 && frameCnt < 450 && frameCnt % 50 == 25){
		enemyList.push_back( EnemySptr(new EnemyN()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT + 50, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(2);										//敵機の行動パターンの指定
	}
	if(phase == 1 && frameCnt > 600){
		phase++;
		frameCnt = 0;
	}
	/*5-3*/
	if(phase == 2){
		phase++;
		enemyList.push_back( EnemySptr(new EnemyO()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH / 2, -100));				//敵機をイベント位置に移動
		(*it)->setPattern(0);										//敵機の行動パターンの指定

		enemyList.push_back( EnemySptr(new EnemyO()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it2 = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it2)->setPos(Vec2(SCREEN_WIDTH / 2 - 90, -100));				//敵機をイベント位置に移動
		(*it2)->setPattern(0);										//敵機の行動パターンの指定
	}
	if(phase == 3 && frameCnt > 600){
		phase++;
		frameCnt = 0;
	}
	if(phase == 4 && frameCnt < 400 && frameCnt % 30 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT + 80, SCREEN_HEIGHT + 50));	//敵機をイベント位置に移動
		(*it)->setPattern(2);										//敵機の行動パターンの指定
	}
	if(phase == 4 && frameCnt < 400 && frameCnt % 30 == 0){
		enemyList.push_back( EnemySptr(new EnemyA()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_WIDTH-SCREEN_INDENT-80, SCREEN_HEIGHT + 50));	//敵機をイベント位置に移動
		(*it)->setPattern(3);										//敵機の行動パターンの指定
	}
	if(phase == 4 && frameCnt > 900){
		phase++;
		frameCnt = 0;
	}
	if(phase == 5 && frameCnt < 350 && frameCnt % 90 == 0){
		enemyList.push_back( EnemySptr(new EnemyK()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(SCREEN_INDENT - 50, SCREEN_HEIGHT - 50));				//敵機をイベント位置に移動
		(*it)->setPattern(1);										//敵機の行動パターンの指定

		enemyList.push_back( EnemySptr(new EnemyK()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it2 = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT - 50));				//敵機をイベント位置に移動
		(*it2)->setPattern(2);										//敵機の行動パターンの指定
	}
	if(game.bossFlag >= 2){
		phase = 6;
		frameCnt = 0;
	}
	/*惑星*/
	if(phase == 6 && frameCnt == 0 ){
		effectFactory( EffectSptr(new Neptune()) );	//リストにオブジェクト追加
		next = 6;
	}
}
/*アクション関数（個別）*/
void GameOver::action(Tomasen& game){


	//リザルトの出現についてはgameResultを参照してtomasenで実行している
	//ゲームオーバーイベントについてもその場で作成される
	
	/*タイムスケジュール*/
	if(phase == 0 && frameCnt > 100){
		/*初期化*/
		next = 998;
	}

}
/*アクション関数（個別）*/
void GameClear::action(Tomasen& game){

	/*タイムスケジュール*/
	
	if(phase == 0 && frameCnt == 10){
		/*自機HPボーナス*/
		if(FriendSptr tmp = game.kosenWing.lock()){
			game.score += tmp->getHp() * 100;
		}
		/*ゲームクリアの表示*/
		effectFactory( EffectSptr(new DarkR()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new DarkY()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new DarkG()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new DarkB()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightB()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightG()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightY()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new LightR()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleTo()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleMa()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleSe()) );		//リストにオブジェクト追加
		effectFactory( EffectSptr(new TitleNi()) );		//リストにオブジェクト追加

		phase++;

	}


	/*リザルト*/
	

	/*エンディングの表示*/

	/*スタッフロール*/

	/*スタッフロールへ*/
	if(phase == 1 && frameCnt > 500){
		/*スタッフロール*/
		next = 1001;
	}
}

/*アクション関数（個別）*/
void StaffRoll::action(Tomasen& game){

	/*タイムスケジュール*/
	
	if(phase == 0 && frameCnt == 300){
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it)->setName("■グラフィック■");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 - 10));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 10));

		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it2 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it2)->setName("とーた");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 + 10));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10));
		phase++;
		frameCnt = 0;
	}
	else if(phase == 1 && frameCnt == 300){
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it)->setName("■ＢＧＭ／ＳＥ■");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 10));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it2 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it2)->setName("かっしー");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10));

		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it3 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it3)->setName("とーやま");
		(*it3)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it3)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 30));

		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it4 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it4)->setName("みやもと");
		(*it4)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it4)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50));

		phase++;
		frameCnt = 0;
	}
	else if(phase == 2 && frameCnt == 300){
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it)->setName("■企画／プログラミング■");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 - 10));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 10));

		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it2 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it2)->setName("ふーみん");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2 + 10));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 10));
		phase++;
		frameCnt = 0;
	}
	else if(phase == 3 && frameCnt == 300){
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it)->setName("■スペシャルサンクス■");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it2 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it2)->setName("しみず");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it3 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it3)->setName("にゃは");
		(*it3)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it3)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it4 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it4)->setName("けんこう");
		(*it4)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it4)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it5 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it5)->setName("さとだい");
		(*it5)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it5)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it6 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it6)->setName("しょーだい");
		(*it6)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it6)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40));
		
		phase++;
		frameCnt = 0;
	}
	else if(phase == 4 && frameCnt == 300){
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it)->setName("■製作■");
		(*it)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 80));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it2 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it2)->setName("Ｓ");
		(*it2)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it2)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 60));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it3 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it3)->setName("Ｔ");
		(*it3)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it3)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 40));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it4 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it4)->setName("Ｇ");
		(*it4)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it4)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it5 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it5)->setName("班");
		(*it5)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it5)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it6 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it6)->setName("＠");
		(*it6)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it6)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it7 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it7)->setName("通");
		(*it7)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it7)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 40));
		
		effectFactory( EffectSptr(new TextBox()) );		//リストにオブジェクト追加
		EffectVsptr::iterator it8 = effectList.end() - 1;			//直前のオブジェクトを参照
		(*it8)->setName("メ");
		(*it8)->setPos(Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, SCREEN_HEIGHT / 2));
		(*it8)->setTargetPos(Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60));
		
		phase++;
		frameCnt = 0;
	}
	else if(phase == 5 && frameCnt == 1000){/*ゲームクリアの表示*/
		next = 998;
	}


}

} //namespace tm2