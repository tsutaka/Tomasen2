#include "obj_wing_enemy.hpp"

#include <cmath>

#include "tomasen.hpp"
#include "obj_bullet.hpp"

namespace tm2{

/*グローバルリソース定義*/
EnemyVsptr enemyList;				//敵機リスト
void enemyFactory(EnemySptr enemy, Vec2 pos, int pattern){
		enemyList.push_back( enemy );					//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;	//直前のオブジェクトを参照
		(*it)->setPos(pos);								//敵機を指定位置に移動
		(*it)->setPattern(pattern);						//敵機の行動パターンの指定
}

EnemyA::EnemyA(){
	/*初期化*/
	name = TEXT("トリ");	//名前
	maxHp = 30;				//最大耐久度
	imageX = 0;				//画像x座標
	imageY = 12;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	size = tipSize;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	dis = 3.0;				//移動量
	move = Vec2(0.0, 7.0);	//移動量
	hp = maxHp;				//HP
}
void EnemyA::update(Tomasen& game){
	//親クラスの更新関数を実行
	Enemy::update(game);
	//自機をターゲットに設定
	if(FriendSptr jiki = game.kosenWing.lock()){
		targetPos = jiki->getCenterPos();
	}
}

void EnemyA::action(Object obj){
	/*弾の発射*/
	if(perCheck(1) && canShot > 0){
		enemyBulletFactory(EnemyBulletSptr( new RedKunaiBullet()), 
			makeRand(getCenterPos().x, 5), getCenterPos().y);
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//A1
		if(phase == 0 && pos.y > makeRand(100.0, 20)){
			phase++;
			move = Vec2(-2.5, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && pos.x < SCREEN_INDENT + 50){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -5.0);	//移動量
		}
		break;
	case 1: //A2
		/*目標への移動*/
		dis = 5.0;
		if(pos.x < targetPos.x - dis) move.x = dis;
		if(pos.y < targetPos.y - dis) move.y = dis;
		if(pos.x > targetPos.x + dis) move.x = -dis;
		if(pos.y > targetPos.y + dis) move.y = -dis;
		if(phase == 0){
			canShot = 1;
			targetPos = Vec2(SCREEN_WIDTH / 2, 150);
		}
		if(phase == 0 && frameCnt >= 500){
			phase++;
			frameCnt = 0; 
		}
		if(phase == 1 && pos.x > SCREEN_WIDTH / 2){
			phase++;
			targetPos = Vec2(SCREEN_WIDTH - SCREEN_INDENT + 500, -500);
		}
		break;
	case 2: //A3
		if(phase == 0){
			phase++;
			move = Vec2(0.0, -6.0);	//移動量
		}
		else if(phase == 1 && pos.y < 100){
			phase++;
			move = Vec2(3.0, 1.5);	//移動量
			canShot = 1;
		}
		break;
	case 3: //A4
		if(phase == 0){
			phase++;
			move = Vec2(0.0, -6.0);	//移動量
		}
		else if(phase == 1 && pos.y < 100){
			phase++;
			move = Vec2(-3.0, 1.5);	//移動量
			canShot = 1;
		}
		break;
	case 4: //A5
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 6.0);	//移動量
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			dir = PI/2 + 0.1 * makeRand(0.0, 5);	//角度
			dis = 5.0;
			move.x = cos(dir) * dis;
			move.y = sin(dir) * dis;
		}
		break;
	case 5: //放物線
		//setMoveであらかじめ初期移動量を設定する
		move = move + Vec2(-0.0016, 0.0);	//加速度を加算
		break;
	case 6: //1-1の動き
		//setMoveであらかじめ初期移動量を設定する
		if(phase == 0 && frameCnt > waitTime){
			move = Vec2(0.0, 0.0);	//移動量変更
			phase++;
		}
		if(phase == 1 && frameCnt > waitTime + 100){
			//自機方向に旋回
			
			/*ターゲット角度の算出*/
			dir = checkDirection(
				targetPos.x, targetPos.y, 
				getCenterPos().x, getCenterPos().y
				);// + PI/2.0;
			dis = 5.0;
			move.x = cos(dir) * dis;
			move.y = sin(dir) * dis;

		}
		if(phase == 2 && frameCnt > waitTime + 300){
			move = Vec2(0.0, -0.6);	//移動量変更
		}

		break;

	}

}

EnemyB::EnemyB(){
	/*初期化*/
	name = TEXT("マイン");	//名前
	maxHp = 50;				//最大耐久度
	imageX = 4;				//画像x座標
	imageY = 12;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	size = tipSize;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}
void EnemyB::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 20 == 0){
		shotCnt += 0.3;
		enemyBulletFactory(EnemyBulletSptr( new SprinklerBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//移動量
		}
		break;
	case 1:	//B2
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 3.0);	//移動量
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			move = Vec2(2.0, 0.0);	//移動量
		}
		else if(phase == 2 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//移動量
		}
		break;
	}
	
}

EnemyC::EnemyC(){
	/*初期化*/
	name = TEXT("イルカ");	//名前
	maxHp = 300;				//最大耐久度
	imageX = 8;				//画像x座標
	imageY = 12;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	size = tipSize;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	hp = maxHp;				//HP
}

void EnemyC::action(Object obj){
	/*弾の発射*/
	if(canShot > 0 && frameCnt % 60 == 0){
		for(shotCnt = 0.0; shotCnt < 2 * PI; shotCnt += 2 * PI / 10){
			enemyBulletFactory(EnemyBulletSptr( new WeakBullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
	}
	if(canShot > 0 && frameCnt % 120 < 7 && frameCnt % 3 == 0){
		for(shotCnt = -makeRand(4); shotCnt < 2 * PI; shotCnt += 2 * PI / 7){
			enemyBulletFactory(EnemyBulletSptr( new Ene2Bullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//C1
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 4.0);	//移動量
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			move = Vec2(0.0, 0.0);	//移動量
		}
		else if(phase == 2 && frameCnt > 300){
			phase++;
			canShot = 1;
			move = Vec2(1.0, 0.0);	//移動量
		}
		else if(phase == 3 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			phase++;
			canShot = 1;
			move = Vec2(-1.0, 0.0);	//移動量
		}
		else if(phase == 4 && pos.x < SCREEN_INDENT + 50){
			phase++;
			canShot = 1;
			move = Vec2(0.0, -4.0);	//移動量
		}
		break;
	case 1:	//3-1
		if(phase == 0){
			phase++;
			move = Vec2(0.0, 4.0);	//移動量
		}
		else if(phase == 1 && pos.y > 100){
			phase++;
			canShot = 1;
			move = Vec2(0.0, 0.0);	//移動量
		}
		else if(phase == 2 && frameCnt > 300){
			phase++;
			canShot = 1;
			move = Vec2(1.0, 0.0);	//移動量
		}
		else if(phase == 3 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			phase++;
			canShot = 1;
			move = Vec2(-1.0, 0.0);	//移動量
		}
		else if(phase == 4 && pos.x < SCREEN_INDENT + 50){
			phase++;
			canShot = 1;
			move = Vec2(0.0, -4.0);	//移動量
		}
		break;
	}
	
}

EnemyD::EnemyD(){
	/*初期化*/
	name = TEXT("ロック");	//名前
	maxHp = 50;				//最大耐久度
	imageX = 40;			//画像x座標
	imageY = 12;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力幅
	size = tipSize;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	hp = maxHp;				//HP
}

void EnemyD::action(Object obj){

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//D1
		move += Vec2(makeRand(0.0, 4) * 0.1, makeRand(1.0, 4) * 0.1);	//移動量
		break;
	}
	
}

EnemyE::EnemyE(){
	/*初期化*/
	name = TEXT("ラージロック");	//名前
	maxHp = 50;				//最大耐久度
	imageX = 40;			//画像x座標
	imageY = 12;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力幅
	size = tipSize*5;		//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度

	pattern = 1;
}
void EnemyE::update(Tomasen& game){
	//親クラスの更新関数を実行
	Enemy::update(game);
	//自機をターゲットに設定
	if(FriendSptr jiki = game.kosenWing.lock()){
		targetPos = jiki->getPos();
	}
}
void EnemyE::action(Object obj){



	/*移動方向の決定*/
	switch(pattern){
	case 0:	//E1
		move += Vec2(makeRand(0.0, 4) * 0.01, makeRand(1.0, 4) * 0.01);	//移動量
		break;
	case 1: //自機追尾
		
		
		//自機角度の算出
		dir = checkDirection(
			targetPos.x, targetPos.y, 
			getCenterPos().x, getCenterPos().y
			);
			
		//自機方向に旋回
		dis = 0.7;
		move.x = cos(dir) * dis;
		move.y = sin(dir) * dis;
		//move.x = 0;
		//move.y = 1.0;
		break;
	}

	//3Way
	if(frameCnt > 100 && frameCnt % 300 == 1){
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setDir(dir);											//角度
		(*it)->setDis(2);											//距離
	}
	if(frameCnt > 100 && frameCnt % 300 == 5){
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setDir(dir);											//角度
		(*it)->setDis(2.3);											//距離
	}
	if(frameCnt > 100 && frameCnt % 300 == 9){
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setDir(dir);											//角度
		(*it)->setDis(2.6);											//距離
	}

	//死亡時ばらまき
	if(hp < 7){
		for(shotCnt = makeRand(0.0, 7) * 0.05; shotCnt < 2 * PI; shotCnt += 2 * PI / 5){
			enemyBulletFactory(EnemyBulletSptr( new Ene3Bullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
			EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
			(*it)->setDis(hp*5);										//敵機をイベント位置に移動
		}
		hp = 0;
	}
}

EnemyF::EnemyF(){
	/*初期化*/
	name = TEXT("タコス");	//名前
	maxHp = 1000;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 14;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	size = tipSize*2;		//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	dis = 3.0;				//移動量
	move = Vec2(0.0, 1.2);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyF::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 100 == 0){
		for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 10){
			enemyBulletFactory(EnemyBulletSptr( new RedKunaiBullet()), 
				getCenterPos().x, getCenterPos().y);
			EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
			(*it)->setDir(cnt);										//敵機をイベント位置に移動
		}
	} 
	if(canShot > 0 && frameCnt % 150 == 0){
		for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 15){
			enemyBulletFactory(EnemyBulletSptr( new YellowKunaiBullet()), 
				getCenterPos().x, getCenterPos().y);
			EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
			(*it)->setDir(cnt);										//敵機をイベント位置に移動
		}
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0){
			canShot = 1;
			if(frameCnt > 300){
				move = Vec2(0.0, -0.4);	//移動量
				phase++;
				frameCnt = 0;
			}
		}
		else if(phase == 1){
			canShot = 1;
		}
		break;
	}
	
}

EnemyG::EnemyG(){
	/*初期化*/
	name = TEXT("ボール");	//名前
	maxHp = 15;				//最大耐久度
	imageX = 0;				//画像x座標
	imageY = 13;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	size = tipSize;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyG::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 5 == 0){
		shotCnt += 0.5;
		enemyBulletFactory(EnemyBulletSptr( new WeakBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//G1
		phase++;
		move = Vec2(0.0, 0.0);	//移動量
		canShot = 1;
		break;
	}
	
}

EnemyH::EnemyH(){
	/*初期化*/
	name = TEXT("タコ");	//名前
	maxHp = 70;				//最大耐久度
	imageX = 4;				//画像x座標
	imageY = 13;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	size = tipSize;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間

	dis = 3.0;				//移動量
	move = Vec2(0.0 + makeRand(0.0, 1) * 0.1, 3.0 + makeRand(0.0, 2));	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyH::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 5 == 0){
		shotCnt += 0.5;
		enemyBulletFactory(EnemyBulletSptr( new GreenBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//H1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, -0.2);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//移動量
		}
		break;
	}
	
}

EnemyI::EnemyI(){
	/*初期化*/
	name = TEXT("UFO");	//名前
	maxHp = 150;			//最大耐久度
	imageX = 16;			//画像x座標
	imageY = 12;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	size = tipSize*2;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 10;			//フレーム待ち時間
	
	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyI::action(Object obj){
	/*弾の発射*/
	


	/*移動方向の決定*/
	switch(pattern){
	case 0:	//I1
		if(canShot > 0 && frameCnt % 5 == 0){
			shotCnt += PI / 15.0;
			if(shotCnt > PI / 2 ) shotCnt = - PI / 2; 
			enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
		phase++;
		move = Vec2(0.56, 1.043);	//移動量
		canShot = 1;
		if(phase > 120) {
			shotCnt = PI / 2; 
			phase = 0;
			pattern = 1;
		}
		break;
	case 1:	//I1
		if(canShot > 0 && frameCnt % 5 == 0){
			shotCnt -= PI / 15.0;
			if(shotCnt < PI / 2 ) shotCnt = PI * 3 / 2; 
			enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
				getCenterPos().x, getCenterPos().y, shotCnt);
		}
		phase++;
		move = Vec2(-0.56, 1.443);	//移動量
		canShot = 1;
		if(phase > 120) {
			shotCnt = PI / 2; 
			phase = 0;
			pattern = 0;
		}
		break;
	}
	
}

EnemyJ::EnemyJ(){
	/*初期化*/
	name = TEXT("ラミ");	//名前
	maxHp = 300;				//最大耐久度
	imageX = 40;			//画像x座標
	imageY = 14;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	size = tipSize*2;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間
	
	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyJ::update(Tomasen& game){
	//親クラスの更新関数を実行
	Enemy::update(game);
	//自機をターゲットに設定
	if(FriendSptr jiki = game.kosenWing.lock()){
		targetPos = jiki->getCenterPos();
	}
}
void EnemyJ::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 20 == 0){
		shotCnt += 0.5;
		enemyBulletFactory(EnemyBulletSptr( new Ene2Bullet()), 
			getCenterPos().x-13, getCenterPos().y+10, shotCnt);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setDis(4.5);
	}
	//下向き3way
	if(canShot > 0 && frameCnt % 50 == 0){
		enemyBulletFactory(EnemyBulletSptr( new RedMBullet()), 
			getCenterPos().x-13, getCenterPos().y+10);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setDir(PI/2.0);
		enemyBulletFactory(EnemyBulletSptr( new RedMBullet()), 
			getCenterPos().x-13, getCenterPos().y+10);
		EnemyBulletVsptr::iterator it2 = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it2)->setDir(PI/2.0 - 0.3);
		enemyBulletFactory(EnemyBulletSptr( new RedMBullet()), 
			getCenterPos().x-13, getCenterPos().y+10);
		EnemyBulletVsptr::iterator it3 = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it3)->setDir(PI/2.0 + 0.3);
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//移動量
		}
		break;
	}
	
}

EnemyK::EnemyK(){
	/*初期化*/
	name = TEXT("クロノトリ");//名前
	maxHp = 60;				//最大耐久度
	imageX = 8;				//画像x座標
	imageY = 13;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	size = tipSize;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間
	
	dis = 3.0;				//移動量
	move = Vec2(0.0, -4.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyK::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 2 == 0){
		shotCnt += 0.2;
		enemyBulletFactory(EnemyBulletSptr( new WeakBullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//移動量
		}
		break;
	case 1:	//左スタート
		if(phase == 0){
			move = Vec2(1.6, -10.0);
			phase++;
		}
		move += Vec2(0.0, 0.1);	//移動量
		
		break;
	case 2:	//右スタート
		if(phase == 0){
			move = Vec2(-1.6, -10.0);
			phase++;
		}
		move += Vec2(0.0, 0.1);	//移動量
		
		break;
	}
	
}

EnemyL::EnemyL(){
	/*初期化*/
	name = TEXT("サテライト");	//名前
	maxHp = 600;				//最大耐久度
	imageX = 16;				//画像x座標
	imageY = 14;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	size = tipSize*2;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間
	
	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyL::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 5 == 0){
		shotCnt += 0.2;
		enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
			getCenterPos().x + makeRand(0.0, 10)*0.1, getCenterPos().y);
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setDis(7.3);			//敵機をイベント位置に移動
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(1.0, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && pos.x > SCREEN_WIDTH - SCREEN_INDENT - 50){
			move = Vec2(-1.0, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && pos.x < SCREEN_INDENT + 50){
			move = Vec2(1.0, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//移動量
		}
		break;
	}
	
}

EnemyN::EnemyN(){
	/*初期化*/
	name = TEXT("特攻機");	//名前
	maxHp = 150;				//最大耐久度
	imageX = 24;				//画像x座標
	imageY = 12;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	size = tipSize*2;			//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間
	
	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度
}

void EnemyN::action(Object obj){
	/*弾の発射*/
	if(shotCnt > 10000.0) shotCnt = 0; 
	if(canShot > 0 && frameCnt % 10 == 0){
		shotCnt += 0.6;
		enemyBulletFactory(EnemyBulletSptr( new Ene1Bullet()), 
			getCenterPos().x, getCenterPos().y, shotCnt);
	}

	/*移動方向の決定*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//移動量
			canShot = 1;
		}
		else if(phase == 1 && frameCnt > 600){
			phase++;
			canShot = 0;
			move = Vec2(0.0, -1.0);	//移動量
		}
		break;
	case 1:	//5-2右
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			move += Vec2(-0.1, 0.1);	//移動量
			canShot = 1;
		}
		break;
	case 2:	//5-2左
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			move += Vec2(0.1, 0.1);	//移動量
			canShot = 1;
		}
		break;
	}
	
}

EnemyO::EnemyO(){
	/*初期化*/
	name = TEXT("ボス");	//名前
	maxHp = 3000;			//最大耐久度
	imageX = 24;			//画像x座標
	imageY = 14;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	size = tipSize*2;		//当たり判定直径
	animeMax = 4;			//フレーム数
	animeWait = 4;			//フレーム待ち時間
	
	dis = 3.0;				//移動量
	move = Vec2(0.0, 2.0);	//移動量
	hp = maxHp;				//HP
	shotCnt = 0.0;			//射撃角度

	boss = 1;				//ボスフラグ
}

void EnemyO::action(Object obj){
	/*移動方向の決定*/
	switch(pattern){
	case 0:	//B1
		if(phase == 0 && pos.y > makeRand(200.0, 20)){
			phase++;
			move = Vec2(0.0, 0.0);	//移動量
			canShot = 1;
		}
		if(phase == 1){
			if(canShot > 0 && frameCnt % 20 == 0){
				enemyBulletFactory(EnemyBulletSptr( new RaserBullet()), 
					getCenterPos().x, getCenterPos().y);
				EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
				(*it)->setDis(7.3);			//敵機をイベント位置に移動
			}
		}
		if(phase == 1 && frameCnt > 600){
			phase++;
			frameCnt = 0;
		}
		if(phase == 2){ 
			if(canShot > 0 && frameCnt % 200 == 0){
				for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 8){
					enemyBulletFactory(EnemyBulletSptr( new RedKunaiBullet()), 
						getCenterPos().x, getCenterPos().y);
					EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
					(*it)->setDir(cnt);										//敵機をイベント位置に移動
				}
			} 
			if(canShot > 0 && frameCnt % 350 == 0){
				for(double cnt = 0.0; cnt < 2.0 * PI; cnt += 2.0 * PI / 9){
					enemyBulletFactory(EnemyBulletSptr( new YellowKunaiBullet()), 
						getCenterPos().x, getCenterPos().y);
					EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;				//直前のオブジェクトを参照
					(*it)->setDir(cnt);										//敵機をイベント位置に移動
				}
			}
		}
		if(phase == 2 && frameCnt > 600){
			phase = 1;
			frameCnt = 0;
		}
		break;
	}
	
}

} //namespace tm2