#include <cmath>

#include "tomasen.hpp"
#include "obj_bullet.hpp"

namespace tm2{

/*グローバルリソース定義*/
FriendBulletVsptr friendBulletList;					//自弾リスト
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos){		//指定位置はセンター
		friendBulletList.push_back( friendBullet );						//リストにオブジェクト追加
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//直前のオブジェクトを参照
		(*it)->setPos(pos);				//自弾を指定位置に移動
}
void friendBulletFactory(FriendBulletSptr friendBullet, Vec2 pos, double dir){//指定位置はセンター
		friendBulletList.push_back( friendBullet );						//リストにオブジェクト追加
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//直前のオブジェクトを参照
		(*it)->setPos(pos);				//自弾を指定位置に移動
		(*it)->setDir(dir);												//指定角度で発射
}
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY){		//指定位置はセンター
		friendBulletList.push_back( friendBullet );						//リストにオブジェクト追加
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//直前のオブジェクトを参照
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//自弾を指定位置に移動
}
void friendBulletFactory(FriendBulletSptr friendBullet, double centerX, double centerY, double dir){//指定位置はセンター
		friendBulletList.push_back( friendBullet );						//リストにオブジェクト追加
		FriendBulletVsptr::iterator it = friendBulletList.end() - 1;	//直前のオブジェクトを参照
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//自弾を指定位置に移動
		(*it)->setDir(dir);												//指定角度で発射
}
EnemyBulletVsptr enemyBulletList;					//敵弾リスト
void enemyBulletFactory(EnemyBulletSptr enemyBullet, Vec2 pos){			//指定位置はセンター
		enemyBulletList.push_back( enemyBullet );						//リストにオブジェクト追加
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;		//直前のオブジェクトを参照
		(*it)->setPos(pos);				//自弾を指定位置に移動
}
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY){			//指定位置はセンター
		enemyBulletList.push_back( enemyBullet );						//リストにオブジェクト追加
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;		//直前のオブジェクトを参照
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//自弾を指定位置に移動
}
void enemyBulletFactory(EnemyBulletSptr enemyBullet, double centerX, double centerY, double dir){			//指定位置はセンター
		enemyBulletList.push_back( enemyBullet );						//リストにオブジェクト追加
		EnemyBulletVsptr::iterator it = enemyBulletList.end() - 1;		//直前のオブジェクトを参照
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2) );				//自弾を指定位置に移動
		(*it)->setDir(dir);												//指定角度で発射
}

Bullet::Bullet(){
	//デフォルト値
	pos = Vec2(0.0, 0.0);	//現在位置
	move = Vec2(0.0, 0.0);	//移動量
	dis = 0.0;				//移動量
	dir = 0.0;				//角度
	frameCnt = 0;			//経過フレーム数
	animeCnt = makeRand(4);	//アニメフレーム
	updateCheck = true;		//更新可否
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
	size = 2;

	fire = 1;				//火力
}
void FriendBullet::update(Tomasen& game){
	/*カウントアップ*/
	frameCnt++;
	if(frameCnt > 10000) frameCnt = 0;
	/*アニメーション処理*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt % animeMax == 0){
			animeCnt = 0;
		}
	}
	/*弾の位置を更新*/
	pos.x += cos(dir) * dis;
	pos.y += sin(dir) * dis;
}
void FriendBullet::draw(Tomasen& game){
	/*game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH() );*/
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}


NormalBullet::NormalBullet(){
	name = TEXT("通常弾");		//名前
	maxHp = 1;					//最大耐久度
	imageX = 0;					//画像x座標
	imageY = 14;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;								//HP
	dis = 20.0 + makeRand(0.0, 2);								//移動量
	dir = -PI/2 + 0.01 * makeRand(0.0, 3);	//角度
}
BlueBullet::BlueBullet(){
	name = TEXT("青弾");		//名前
	maxHp = 1;					//最大耐久度
	imageX = 8;					//画像x座標
	imageY = 8;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;								//HP
	dis = 20.0 + makeRand(0.0, 2);								//移動量
	dir = -PI/2 + 0.01 * makeRand(0.0, 3);	//角度
}
HadoBeam::HadoBeam(){
	name = TEXT("波動砲");
	maxHp = 10;					//最大耐久度
	imageX = 20;					//画像x座標
	imageY = 8;					//画像y座標
	imageW = 2;					//画像幅
	imageH = 2;					//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;				//アニメ枚数
	animeWait = 8;				//１枚当りのフレーム
	size = tipSize*outputW;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 15.5;								//移動量
	dir = -PI/2;	//角度
}
void HadoBeam::draw(Tomasen &game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							40);

}
MissBullet::MissBullet(){
	name = TEXT("ミサイル");
	maxHp = 3;					//最大耐久度
	imageX = 28;					//画像x座標
	imageY = 10;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 7.9;								//移動量
	dir = -PI/2;	//角度
}
MissileRBullet::MissileRBullet(){
	name = TEXT("ミサイル");
	maxHp = 5;					//最大耐久度
	imageX = 32;					//画像x座標
	imageY = 10;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.9;								//移動量
	dir = -PI/2;	//角度
}
MissileRBullet::~MissileRBullet(){
	//円形爆炎
	for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 8){
		effectFactory(EffectSptr(new Explosion()), 
			getPos(), 
			Vec2( getPos().x + sin(cnt) * 100.0, 
				getPos().y + cos(cnt) * 100.0 )
			);
	}
}
void MissileRBullet::update(Tomasen& game){
	//親更新関数の使用
	FriendBullet::update(game);
	//爆炎の出力
	if(frameCnt % 150){
		effectFactory( EffectSptr(new Smoke2()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x, getCenterPos().y ) );
		EffectVsptr::iterator it = effectList.end() - 1;
		(*it)->setTimeOfLife(20);
	}
	//回転角度の修正
	dir += PI / 2.0 / 200.0;
}
MissileLBullet::MissileLBullet(){
	name = TEXT("ミサイル");
	maxHp = 5;					//最大耐久度
	imageX = 32;					//画像x座標
	imageY = 10;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.9;								//移動量
	dir = -PI/2;	//角度
}
MissileLBullet::~MissileLBullet(){
	//円形爆炎
	for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 8){
		effectFactory(EffectSptr(new Explosion()), 
			getPos(), 
			Vec2( getPos().x + sin(cnt) * 100.0, 
				getPos().y + cos(cnt) * 100.0 )
			);
	}
}
void MissileLBullet::update(Tomasen& game){
	//親更新関数の使用
	FriendBullet::update(game);
	//爆炎の出力
	if(frameCnt % 150){
		effectFactory( EffectSptr(new Smoke2()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x, getCenterPos().y ) );
		EffectVsptr::iterator it = effectList.end() - 1;
		(*it)->setTimeOfLife(20);
	}
	//回転角度の修正
	dir -= PI / 2.0 / 200.0;
}




void EnemyBullet::update(Tomasen& game){
	/*カウントアップ*/
	frameCnt++;
	if(frameCnt > 10000) frameCnt = 0;
	/*アニメーション処理*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt % animeMax == 0){
			animeCnt = 0;
		}
	}
	/*弾の位置を更新*/
	pos.x += cos(dir) * dis;
	pos.y += sin(dir) * dis;
}
void EnemyBullet::draw(Tomasen& game){
	game.IMAGE->drawTip( getPos().x, getPos().y, 
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputW(), 
					game.IMAGE->tipNo(	getImageX(), 
									getImageY() ) );
}
WeakBullet::WeakBullet(){
	name = TEXT("弱弾");
	maxHp = 1;					//最大耐久度
	imageX = 4;					//画像x座標
	imageY = 14;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	outputW = 2;				//出力幅
	outputH = 2;				//出力髙
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 4;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 6.0;								//移動量
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//角度
}
void WeakBullet::action(const Object &obj){
}
WideBullet::WideBullet(){
	name = TEXT("水球");
	maxHp = 10;				//最大耐久度
	imageX = 0;					//画像x座標
	imageY = 8;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	outputW = 2;				//出力幅
	outputH = 2;				//出力髙
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//virtual void Process
	
	hp = maxHp;					//HP
	dis = 1.0;								//移動量
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//角度
}
void WideBullet::action(const Object &obj){
	dir += 0.01;
	dis += 0.01;
}
SprinklerBullet::SprinklerBullet(){
	name = TEXT("スプリンクラー");
	maxHp = 2;					//最大耐久度
	imageX = 8;					//画像x座標
	imageY = 14;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	outputW = 2;				//出力幅
	outputH = 2;				//出力髙
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.2;								//移動量
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//角度
}
void SprinklerBullet::action(const Object &obj){
}
GreenBullet::GreenBullet(){
	name = TEXT("緑弾");
	maxHp = 2;					//最大耐久度
	imageX = 4;					//画像x座標
	imageY = 9;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	outputW = 2;				//出力幅
	outputH = 2;				//出力髙
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 6;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 1.5;								//移動量
	dir = +PI/2 + 0.01 * makeRand(0.0, 2);	//角度
}
void GreenBullet::action(const Object &obj){
	if(frameCnt % 71 == 0){
		if(frameCnt % 2 == 0) dir -= PI / 4;
		else dir += PI / 8;
		dis += 0.2;
	}
}
Ene1Bullet::Ene1Bullet(){
	name = TEXT("エネ１弾");
	maxHp = 3;					//最大耐久度
	imageX = 8;					//画像x座標
	imageY = 9;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.3 + makeRand(0.0, 10) * 0.1;								//移動量
	dir = +PI/2;	//角度
}
void Ene1Bullet::action(const Object &obj){
}
Ene2Bullet::Ene2Bullet(){
	name = TEXT("エネ２弾");
	maxHp = 3;					//最大耐久度
	imageX = 8;					//画像x座標
	imageY = 10;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 1.3;								//移動量
	dir = +PI/2;	//角度
}
void Ene2Bullet::action(const Object &obj){
}
Ene3Bullet::Ene3Bullet(){
	name = TEXT("エネ３弾");
	maxHp = 3;					//最大耐久度
	imageX = 8;					//画像x座標
	imageY = 11;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 0.9;								//移動量
	dir = +PI/2;	//角度
}
void Ene3Bullet::action(const Object &obj){
}
RedKunaiBullet::RedKunaiBullet(){
	name = TEXT("赤クナイ");
	maxHp = 1;					//最大耐久度
	imageX = 12;					//画像x座標
	imageY = 10;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.9;								//移動量
	dir = +PI/2;	//角度
}
void RedKunaiBullet::action(const Object &obj){

	if(frameCnt % 100 == 0 && frameCnt < 200){
		dir += 0.5 * PI / 2.0;
		dis += 0.1;
	}
}
void RedKunaiBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}
YellowKunaiBullet::YellowKunaiBullet(){
	name = TEXT("黄クナイ");
	maxHp = 1;					//最大耐久度
	imageX = 12;					//画像x座標
	imageY = 11;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.5;								//移動量
	dir = +PI/2;	//角度
}
void YellowKunaiBullet::action(const Object &obj){
}
void YellowKunaiBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}
RaserBullet::RaserBullet(){
	name = TEXT("レーザー");
	maxHp = 1;					//最大耐久度
	imageX = 40;					//画像x座標
	imageY = 18;				//画像y座標
	imageW = 2;					//画像幅
	imageH = 4;					//画像高
	outputW = 2;				//出力幅
	outputH = 4;				//出力髙
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.5;								//移動量
	dir = +PI/2;	//角度
}
void RaserBullet::action(const Object &obj){
}
void RaserBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}

RedMBullet::RedMBullet(){
	name = TEXT("赤ミサイル");
	maxHp = 1;					//最大耐久度
	imageX = 32;					//画像x座標
	imageY = 10;				//画像y座標
	imageW = 1;					//画像幅
	imageH = 2;					//画像高
	outputW = 1;				//出力幅
	outputH = 2;				//出力髙
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = 2;					//virtual void Process
	
	hp = maxHp;					//HP
	dis = 2.5;								//移動量
	dir = +PI/2;	//角度
}
void RedMBullet::action(const Object &obj){
}
void RedMBullet::draw(Tomasen& game){
	game.IMAGE->drawRotateTile(getOutputW(), getOutputH(), getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir() + PI/2,
							getImageX(), getImageY(), getImageW(), getImageH(), 
							150);
}

} //namespace tm2