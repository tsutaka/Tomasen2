#include "obj_parts_A.hpp"
#include "obj_bullet.hpp"
#include "obj_wing_enemy.hpp"

#include "tomasen.hpp"

namespace tm2{

EngineA::EngineA(){
	name = TEXT("エンジンＡ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 0;					//画像x座標
	imageY = 0;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 10;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径
}

void EngineA::action(Tomasen& game){
}

CockpitA::CockpitA(){
	name = TEXT("コックピットＡ");	//名前
	maxHp = 10;						//最大耐久度
	hp = maxHp;						//現在耐久度
	imageX = 4;						//画像x座標
	imageY = 0;						//画像y座標
	imageW = 1;						//画像幅
	imageH = 1;						//画像高
	animeMax = 1;					//アニメ枚数
	animeWait = 10;					//１枚当りのフレーム
	size = tipSize;					//当たり判定直径
}

void CockpitA::action(Tomasen& game){
}

MachineGunA::MachineGunA(){
	name = TEXT("機関銃Ａ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 8;					//画像x座標
	imageY = 0;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 100;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 20;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//
}  

void MachineGunA::action(Tomasen& game){
	/*射撃処理*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new MissBullet()), 
			getCenterPos().x, getCenterPos().y );
		//射撃音
		game.MUSIC->Play(musicKikanho);
		energy -= 1;
	}
	else if(energy <= 0){			//射撃不可
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//射撃再開
		stopShot = 1;
	}
}
MachineGunB::MachineGunB(){
	name = TEXT("機関銃Ｂ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 12;					//画像x座標
	imageY = 0;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 100;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 20;			//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//
}  
void MachineGunB::action(Tomasen& game){
	/*射撃処理*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y ,
			0.0);
		//射撃音
		energy -= 1;
	}
	else if(energy <= 0){			//射撃不可
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//射撃再開
		stopShot = 1;
	}
}
MachineGunC::MachineGunC(){
	name = TEXT("機関銃Ｃ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 16;					//画像x座標
	imageY = 0;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 100;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 20;			//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//
}  
void MachineGunC::action(Tomasen& game){
	/*射撃処理*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y, 
			PI / 2);
		//射撃音
		energy -= 1;
	}
	else if(energy <= 0){			//射撃不可
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//射撃再開
		stopShot = 1;
	}
}
MachineGunD::MachineGunD(){
	name = TEXT("機関銃Ｄ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 20;				//画像x座標
	imageY = 0;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 100;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 20;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//
}  
void MachineGunD::action(Tomasen& game){
	/*射撃処理*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y, 
			PI);
		//射撃音
		energy -= 1;
	}
	else if(energy <= 0){			//射撃不可
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//射撃再開
		stopShot = 1;
	}
}
SprinklerA::SprinklerA(){
	name = TEXT("スプリンクラーＡ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 28;				//画像x座標
	imageY = 0;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 100;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 20;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//
}  
void SprinklerA::action(Tomasen& game){
	/*射撃処理*/
	if(game.shotPerm == 1 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new NormalBullet()), 
			getCenterPos().x, getCenterPos().y, 
			PI);
		//射撃音
		energy -= 1;
	}
	else if(energy <= 0){			//射撃不可
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//射撃再開
		stopShot = 1;
	}
}

SubCanonA::SubCanonA(){
	name = TEXT("副砲Ａ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 0;					//画像x座標
	imageY = 2;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 2;					//画像高
	outputW = 1;				//出力幅
	outputH = 2;				//出力高
	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	drawPriority = 1;			//描画優先順位
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 150;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 20;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//射撃指示
	targetShot = 0;				//ターゲットを捕捉
	targetDir = 0.0;			//ターゲット角度
}  

void SubCanonA::update(Tomasen& game){
	/*基本更新関数の呼び出し*/
	PartsA::update(game);

	/*副砲に直近の敵機の位置を伝達*/
	double distance, minDistance = 1000.0;	//敵距離, 最小距離　＝砲塔追尾距離
	double eneX = 0.0, eneY = 0.0;			//敵X座標,敵Y座標
	int targetLockOn = 0;					//敵を捕捉:1
	//最小距離の敵を探索
	for(EnemyVsptr::iterator itEnemy = enemyList.begin(); itEnemy != enemyList.end(); itEnemy++){
		distance = checkDistance( (*itEnemy)->getCenterPos().x, (*itEnemy)->getCenterPos().y,
			getCenterPos().x, getCenterPos().y );
		if( minDistance > distance ){
				(*itEnemy)->setLockOn(100);
				minDistance = distance;
				eneX = (*itEnemy)->getCenterPos().x;
				eneY = (*itEnemy)->getCenterPos().y;
				targetLockOn = 1;	//ロックオン　砲塔回転
		}
	}
	if(targetLockOn){/*対象ロックオン*/
		setTargetShot(targetLockOn);
		setTargetX(eneX);
		setTargetY(eneY);
		setTargetDistance(minDistance);
	}
	else {/*対象無しの場合は前を向く*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	
	/*ターゲット角度の算出*/
	targetDir = checkDirection(targetX, targetY, getCenterPos().x, getCenterPos().y) + PI/2.0;
	targetDir += 8*PI;
	while(targetDir > dir + PI){
		targetDir -= 2*PI;
	}
	/*砲塔の回転*/
	if(targetDir+2*PI > dir+2*PI + PI / 30.0){
		dir += PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	else if(targetDir+2*PI < dir+2*PI - PI / 30.0){
		dir -= PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	/*射撃処理*/
	if(energy > 0 && man >= requireMan && targetShot == 1 && targetDistance < 300){//射撃開始距離
		friendBulletFactory( 
			FriendBulletSptr( new BlueBullet()), 
			getCenterPos().x, getCenterPos().y, dir - PI/2
			);
		game.MUSIC->Play(musicFami);

	}
}

/*描画関数*/
void SubCanonA::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//パーツの描画（回転あり）
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}

HadohoA::HadohoA(){
	name = TEXT("波動砲Ａ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 32;					//画像x座標
	imageY = 0;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 300;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 2;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//
}  

void HadohoA::action(Tomasen& game){
	/*射撃処理*/
	if( game.shotPerm == 2 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new HadoBeam()), 
			getCenterPos().x, getCenterPos().y );
		//射撃音
		game.MUSIC->Play(musicHadou);
		energy /= 2;
	}
	else if(energy <= 0){			//射撃不可
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//射撃再開
		stopShot = 1;
	}
}

void HadohoA::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//パーツの描画（回転あり）
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}


HadohoB::HadohoB(){
	name = TEXT("波動砲Ｂ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 4;					//画像x座標
	imageY = 2;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 2;					//画像高
	outputW = 1;					//画像幅
	outputH = 2;					//画像高

	animeMax = 4;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 300;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 2;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢
	
	stopShot = 1;				//
}  

void HadohoB::action(Tomasen& game){
	/*射撃処理*/
	if( game.shotPerm == 2 && energy > 0 && man >= requireMan && stopShot == 1 && kaihi == 0){
		friendBulletFactory( FriendBulletSptr( new HadoBeam()), 
			getCenterPos().x, getCenterPos().y );
		//射撃音
		game.MUSIC->Play(musicHadou);
		energy /= 2;
	}
	else if(energy <= 0){			//射撃不可
		stopShot = 0;
	}
	else if(energy == maxEnergy){	//射撃再開
		stopShot = 1;
	}
}

void HadohoB::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//パーツの描画（回転あり）
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}


LuncherR::LuncherR(){
	name = TEXT("ミサイルランチャー");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 8;					//画像x座標
	imageY = 2;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 2;					//画像高
	outputW = 1;				//画像幅
	outputH = 2;				//画像高

	animeMax = 1;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 300;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 2;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢

	stopShot = 0;
	
}  

void LuncherR::update(Tomasen& game){
	/*基本更新関数の呼び出し*/
	PartsA::update(game);

	/*副砲に直近の敵機の位置を伝達*/
	double distance, minDistance = 500.0;	//敵距離, 最小距離　＝砲塔追尾距離
	double eneX = 0.0, eneY = 0.0;			//敵X座標,敵Y座標
	int targetLockOn = 0;					//敵を捕捉:1
	//最小距離の敵を探索
	for(EnemyVsptr::iterator itEnemy = enemyList.begin(); itEnemy != enemyList.end(); itEnemy++){
		distance = checkDistance( (*itEnemy)->getCenterPos().x, (*itEnemy)->getCenterPos().y,
			getCenterPos().x, getCenterPos().y );
		if( minDistance > distance ){
				(*itEnemy)->setLockOn(100);
				minDistance = distance;
				eneX = (*itEnemy)->getCenterPos().x;
				eneY = (*itEnemy)->getCenterPos().y;
				targetLockOn = 1;	//ロックオン　砲塔回転
		}
	}
	if(targetLockOn){/*対象ロックオン*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x - 3.0);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	else {/*対象無しの場合は前を向く*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	
	/*ターゲット角度の算出*/
	targetDir = checkDirection(targetX, targetY, getCenterPos().x, getCenterPos().y) + PI/2.0;
	targetDir += 8*PI;
	while(targetDir > dir + PI){
		targetDir -= 2*PI;
	}
	/*砲塔の回転*/
	if(targetDir+2*PI > dir+2*PI + PI / 30.0){
		dir += PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	else if(targetDir+2*PI < dir+2*PI - PI / 30.0){
		dir -= PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	if(energy > 0 && man >= requireMan && targetShot == 1 && 
		targetDistance < 300 && frameCnt % 20 == 0){//射撃開始距離300
		kaiten += 1;
		if(kaiten > 4) kaiten = 0;
		friendBulletFactory( 
			FriendBulletSptr( new MissileRBullet()), 
			getCenterPos().x, getCenterPos().y, dir - PI/2.0
			);
		game.MUSIC->Play(musicMissile);

	}
}
void LuncherR::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//パーツの描画（回転あり）
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}
LuncherL::LuncherL(){
	name = TEXT("ミサイルランチャー");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 8;					//画像x座標
	imageY = 2;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 2;					//画像高
	outputW = 1;				//画像幅
	outputH = 2;				//画像高

	animeMax = 1;				//アニメ枚数
	animeWait  = 4;		        //１枚当りのフレーム
	size = tipSize;				//当たり判定直径
	
	maxEnergy = 100;			//最大の弾数
	energy = maxEnergy;			//現在の弾数
	chargeEnergy = 1;			//給弾する弾数
	maxMan = 300;				//最大の人員
	man = maxMan;				//現在の人員
	requireMan = 2;				//必要な人員
	fire = 0;					//現在の火勢
	burnFire = 30;				//発火する火勢
	maxFire = 80;				//最大の火勢

	stopShot = 0;
	
}  

void LuncherL::update(Tomasen& game){
	/*基本更新関数の呼び出し*/
	PartsA::update(game);

	/*副砲に直近の敵機の位置を伝達*/
	double distance, minDistance = 500.0;	//敵距離, 最小距離　＝砲塔追尾距離
	double eneX = 0.0, eneY = 0.0;			//敵X座標,敵Y座標
	int targetLockOn = 0;					//敵を捕捉:1
	//最小距離の敵を探索
	for(EnemyVsptr::iterator itEnemy = enemyList.begin(); itEnemy != enemyList.end(); itEnemy++){
		distance = checkDistance( (*itEnemy)->getCenterPos().x, (*itEnemy)->getCenterPos().y,
			getCenterPos().x, getCenterPos().y );
		if( minDistance > distance ){
				(*itEnemy)->setLockOn(100);
				minDistance = distance;
				eneX = (*itEnemy)->getCenterPos().x;
				eneY = (*itEnemy)->getCenterPos().y;
				targetLockOn = 1;	//ロックオン　砲塔回転
		}
	}
	if(targetLockOn){/*対象ロックオン*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x + 3.0);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	else {/*対象無しの場合は前を向く*/
		setTargetShot(targetLockOn);
		setTargetX(getCenterPos().x);
		setTargetY(getCenterPos().y - 5.0);
		setTargetDistance(minDistance);
	}
	
	/*ターゲット角度の算出*/
	targetDir = checkDirection(targetX, targetY, getCenterPos().x, getCenterPos().y) + PI/2.0;
	targetDir += 8*PI;
	while(targetDir > dir + PI){
		targetDir -= 2*PI;
	}
	/*砲塔の回転*/
	if(targetDir+2*PI > dir+2*PI + PI / 30.0){
		dir += PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	else if(targetDir+2*PI < dir+2*PI - PI / 30.0){
		dir -= PI / 30.0;
		game.MUSIC->Play(musicKaiten);
	}
	/*射撃処理*/
	if(energy > 0 && man >= requireMan && targetShot == 1 && 
		targetDistance < 300 && frameCnt % 20 == 0){//射撃開始距離300
		kaiten += 1;
		if(kaiten > 4) kaiten = 0;
		friendBulletFactory( 
			FriendBulletSptr( new MissileLBullet()), 
			getCenterPos().x, getCenterPos().y, dir - PI/2.0
			);

		game.MUSIC->Play(musicMissile);

	}
}

void LuncherL::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(	//パーツの描画（回転あり）
							getOutputW(),
							getOutputH(),
							getCenterPos().x,
							getCenterPos().y,
							getDir(),
							getImageX(),
							getImageY(),
							getImageW(),
							getImageH() );
}


} //namespace tm2