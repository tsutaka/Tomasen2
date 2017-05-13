
#include "tomasen.hpp"

#include "obj_wing.hpp"
#include "obj_effect.hpp"
 
namespace tm2{

void Friend::update(Tomasen& game){

}
void Friend::draw(Tomasen& game){

}


/*コンストラクタ*/
Enemy::Enemy(){
	//デフォルト値
	pos = Vec2(0.0, 0.0);		//現在位置
	move = Vec2(0.0, 0.0);		//移動量
	dis = 5.0;					//移動量
	dir = 0.0;					//角度
	frameCnt = 0;				//経過フレーム数
	animeCnt = 0;				//アニメフレーム
	updateCheck = true;			//更新可否
	pattern = 0;				//行動パターン
	targetPos = Vec2(0.0,0.0);	//移動目的座標
	phase = 0;					//行動フェーズ
	canShot = 0;				//射撃許可
	outputW = 1;			//出力幅
	outputH = 1;			//出力高

	lockOn = 0;				//ロックオン
	boss = 0;				//ボスフラグ
}
void Enemy::update(Tomasen& game){
	/*各パラメータを更新する*/
	frameCnt++;										//フレームカウントの更新
	/*アニメーション処理*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt >= animeMax){
			animeCnt = 0;
		}
	}
	if(lockOn = 100){
		//ロックオンアラート
		if(frameCnt % 3 == 0){
			effectFactory(EffectSptr(new LockOnAlart()), 
				getCenterPos().x,	getCenterPos().y, 
				Vec2( getPos().x - tipSize/2 + makeRand(0.0, 30), 
					getPos().y - tipSize/2 - makeRand(250.0, 90) )
				);
		}
	}
	/*ロックオン解除*/
	if(lockOn > 0){
		lockOn--;
	}

	/*敵機の位置を更新*/
	pos.x += move.x;
	pos.y += move.y;
}
void Enemy::draw(Tomasen& game){
	game.IMAGE->drawTile( getPos().x, getPos().y,	//x, y,
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputW(), 
					game.IMAGE->tipNo(	getImageX(),		//ino
									getImageY() ), 
					getImageW(), getImageH()	//ix, iy, 
					);
}

/*カウントアップ回数*/
void Friend::addKaihi(int kaihi){
	const int kaihiMin = 0;
	const int kaihiMax = 70;

	Friend::kaihi += kaihi;
	if(Friend::kaihi > kaihiMax){
		Friend::kaihi = kaihiMax;
	}else if(Friend::kaihi < kaihiMin){
		Friend::kaihi = kaihiMin;
	}
}

} //namespace tm2