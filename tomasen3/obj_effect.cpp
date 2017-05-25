#include "obj_effect.hpp"

#include "localcommon.hpp"
#include "tomasen.hpp"

namespace tm2{

/*グローバルリソース定義*/
EffectVsptr effectList;				//エフェクトリスト
void effectFactory(EffectSptr effect){
		effectList.push_back( effect );							//リストにオブジェクト追加
}
void effectFactory(EffectSptr effect, Vec2 pos, Vec2 targetPos){
		effectList.push_back( effect );							//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it)->setPos(pos);										//エフェクトを指定位置に移動
		(*it)->setTargetPos(targetPos);							//エフェクト目標位置を指定
}
void effectFactory(EffectSptr effect, double centerX, double centerY, Vec2 targetCenterPos){
		effectList.push_back( effect );							//リストにオブジェクト追加
		EffectVsptr::iterator it = effectList.end() - 1;		//直前のオブジェクトを参照
		(*it)->setPos(Vec2(centerX - (*it)->getOutputW()*tipSize/2, 
						   centerY - (*it)->getOutputH()*tipSize/2));	//エフェクトを指定位置に移動
		(*it)->setTargetPos(Vec2(targetCenterPos.x - (*it)->getOutputW()*tipSize/2, 
						   targetCenterPos.y - (*it)->getOutputH()*tipSize/2));							//エフェクト目標位置を指定
}

Effect::Effect(){
	hp = 1;						//耐久度
	pos = Vec2(0.0, 0.0);		//位置
	targetPos = Vec2(0.0, 0.0);	//位置
	dis = 0.0;					//移動量
	dir = 0.0;					//角度
	size = 1;
	frameCnt = 0;				//生成後の経過フレーム数
	animeCnt = 0;				//現在のアニメフレーム
	updateCheck = 0;			//更新可否
	outputW = 1;				//出力幅
	outputH = 1;				//出力高
	moveMode = 0;				//0:基本エフェクト
	animeMax = 4;				//アニメーション枚数
	animeWait = 12;			//アニメーション１枚のフレーム数
}

void Effect::update(Tomasen& game){
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

	/*オブジェクト移動*/
	switch(moveMode){
	case 0://ターゲット移動モード(加速→減速)
		pos.x += (targetPos.x - pos.x) / 50;
		pos.y += (targetPos.y - pos.y) / 50;
		break;
	case 1://方向移動モード
		pos.x += cos(dir) * dis;
		pos.y += sin(dir) * dis;
		break;
	case 2://方向移動モード
		pos.x += move.x;
		pos.y += move.y;
		break;
	case 3://ターゲット移動モード(減速→加速)
		move.x += 1;
		if(move.x >= 20){
			move.x = 20;
		}
		pos.x += move.x * (((targetPos.x - pos.x) < 0)?-1:1);
		if((targetPos.x - pos.x) <= 20 && (targetPos.x - pos.x) >= -20 ){
			pos.x = targetPos.x;
		}

		move.y += 0.01;
		if(move.y >= 5){
			move.y = 5;
		}
		pos.y += move.y * (((targetPos.y - pos.y) < 0)?-1:1);
		if((targetPos.y - pos.y) <= 5 && (targetPos.y - pos.y) >= -5 ){
			pos.y = targetPos.y;
		}
		break;
	}
	/*カウントダウン*/
	timeOfLife--;
	if(timeOfLife < 0) timeOfLife = 0;
}

void Effect::draw(Tomasen& game){
	/*エフェクト描画*/
	game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					100);
}

Earth::Earth(){
	maxHp = 1;				//最大耐久度
	imageX = 0;				//画像x座標
	imageY = 26;			//画像y座標
	imageW = 4;				//画像幅
	imageH = 4;				//画像高
	outputW = 10;			//出力幅
	outputH = 10;			//出力高
	animeMax = 3;			//アニメーション枚数
	animeWait = 16;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	dir = PI / 2;				//方向
	dis = 0.5;				//移動量
	moveMode = 1;				//1:惑星エフェクト
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT-200);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT-100);		//目標位置
}

Mars::Mars(){
	maxHp = 1;				//最大耐久度
	imageX = 16;			//画像x座標
	imageY = 26;			//画像y座標
	imageW = 4;				//画像幅
	imageH = 4;				//画像高
	outputW = 10;			//出力幅
	outputH = 10;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 16;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	dir = PI / 2;				//方向
	dis = 1.5;				//移動量
	moveMode = 1;				//1:惑星エフェクト
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//目標位置
}

Jupiter::Jupiter(){
	maxHp = 1;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 26;			//画像y座標
	imageW = 4;				//画像幅
	imageH = 4;				//画像高
	outputW = 14;			//出力幅
	outputH = 14;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 16;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	dir = PI / 2;				//方向
	dis = 1.5;				//移動量
	moveMode = 1;				//1:惑星エフェクト
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//目標位置
}

Saturn::Saturn(){
	maxHp = 1;				//最大耐久度
	imageX = 0;			//画像x座標
	imageY = 30;			//画像y座標
	imageW = 4;				//画像幅
	imageH = 6;				//画像高
	outputW = 14;			//出力幅
	outputH = 21;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 16;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	dir = PI / 2;				//方向
	dis = 1.5;				//移動量
	moveMode = 1;				//1:惑星エフェクト
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//目標位置
}

Uranus::Uranus(){
	maxHp = 1;				//最大耐久度
	imageX = 16;			//画像x座標
	imageY = 30;			//画像y座標
	imageW = 4;				//画像幅
	imageH = 6;				//画像高
	outputW = 12;			//出力幅
	outputH = 18;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 16;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	dir = PI / 2;				//方向
	dis = 1.5;				//移動量
	moveMode = 1;				//1:惑星エフェクト
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//目標位置
}

Neptune::Neptune(){
	maxHp = 1;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 30;			//画像y座標
	imageW = 4;				//画像幅
	imageH = 4;				//画像高
	outputW = 12;			//出力幅
	outputH = 12;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 16;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	dir = PI / 2;				//方向
	dis = 1.5;				//移動量
	moveMode = 1;				//1:惑星エフェクト
	pos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, -100);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2 - outputW*tipSize/2, SCREEN_HEIGHT/2+100);		//目標位置
}

LockOnAlart::LockOnAlart(){
	maxHp = 1;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 20;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 4;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 10;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);		//目標位置
}

Explosion::Explosion(){
	maxHp = 1;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 18;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 50;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);		//目標位置
}

Smoke::Smoke(){
	maxHp = 1;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 22;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 50;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2);					//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2+100);		//目標位置
}

TitleTo::TitleTo(){
	maxHp = 1;				//最大耐久度
	imageX = 0;				//画像x座標
	imageY = 18;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH+wideArea/2, 10*tipSize);					//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, 10*tipSize);		//目標位置
}

TitleMa::TitleMa(){
	maxHp = 1;				//最大耐久度
	imageX = 8;				//画像x座標
	imageY = 18;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, SCREEN_HEIGHT+wideArea/2);	//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, 10*tipSize);			//目標位置
}

TitleSe::TitleSe(){
	maxHp = 1;				//最大耐久度
	imageX = 16;			//画像x座標
	imageY = 18;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(-wideArea/2, 14*tipSize);							//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, 10*tipSize);	//目標位置
}

TitleNi::TitleNi(){
	maxHp = 1;				//最大耐久度
	imageX = 24;			//画像x座標
	imageY = 18;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, -wideArea/2);		//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, 10*tipSize);	//目標位置
}


DarkR::DarkR(){
	maxHp = 1;				//最大耐久度
	imageX = 0;				//画像x座標
	imageY = 22;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, SCREEN_HEIGHT+wideArea/2);	//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, 10*tipSize);			//目標位置
}

LightR::LightR(){
	maxHp = 1;				//最大耐久度
	imageX = 8;				//画像x座標
	imageY = 22;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH+wideArea/2, SCREEN_HEIGHT+wideArea/2);		//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+0*tipSize*4, 10*tipSize);		//目標位置
}

DarkY::DarkY(){
	maxHp = 1;				//最大耐久度
	imageX = 0;				//画像x座標
	imageY = 20;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(-wideArea/2, SCREEN_HEIGHT+wideArea/2);				//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, 10*tipSize);	//目標位置
}

LightY::LightY(){
	maxHp = 1;				//最大耐久度
	imageX = 8;				//画像x座標
	imageY = 20;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH+wideArea/2, -wideArea/2);				//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+1*tipSize*4, 10*tipSize);	//目標位置
}

DarkG::DarkG(){
	maxHp = 1;				//最大耐久度
	imageX = 16;			//画像x座標
	imageY = 22;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(-wideArea/2, -wideArea/2);							//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, 10*tipSize);	//目標位置
}

LightG::LightG(){
	maxHp = 1;				//最大耐久度
	imageX = 24;			//画像x座標
	imageY = 22;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH+wideArea/2, 10*tipSize);							//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, 10*tipSize);	//目標位置
}

DarkB::DarkB(){
	maxHp = 1;				//最大耐久度
	imageX = 16;			//画像x座標
	imageY = 20;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_INDENT+72.0+2*tipSize*4, -wideArea/2);		//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, 10*tipSize);	//目標位置
}

LightB::LightB(){
	maxHp = 1;				//最大耐久度
	imageX = 24;			//画像x座標
	imageY = 20;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 4;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(-wideArea/2, 10*tipSize);							//初期位置
	targetPos = Vec2(SCREEN_INDENT+72.0+3*tipSize*4, 10*tipSize);	//目標位置
}

PushSpace::PushSpace(){
	maxHp = 1;				//最大耐久度
	imageX = 0;				//画像x座標
	imageY = 24;			//画像y座標
	imageW = 8;				//画像幅
	imageH = 2;				//画像高
	outputW = 16;			//出力幅
	outputH = 4;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 2;				//サイズ
	timeOfLife = 3000;		//生存フレーム
	pos = Vec2(SCREEN_WIDTH/2-4*tipSize*2, SCREEN_HEIGHT+wideArea/2);	//初期位置
	targetPos = Vec2(SCREEN_WIDTH/2-4*tipSize*2, 20*tipSize);	//目標位置
}

Wakka::Wakka(){
	maxHp = 1;				//最大耐久度
	imageX = 40;				//画像x座標
	imageY = 22;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 100;		//生存フレーム
}
void Wakka::draw(Tomasen &game){
	/*エフェクト描画*/
	game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					timeOfLife * 150 / 100);

}
Star1::Star1(){
	maxHp = 1;				//最大耐久度
	imageX = 42;			//画像x座標
	imageY = 23;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
	animeMax = 1;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	moveMode = 2;			//2:XY移動量移動
}
void Star1::draw(Tomasen &game){
	/*エフェクト描画*/
	//デフォルト
	Effect::draw(game);
	//減色なし
	/*game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					255);*/

}
Star2::Star2(){
	maxHp = 1;				//最大耐久度
	imageX = 43;			//画像x座標
	imageY = 23;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
	animeMax = 1;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
	moveMode = 2;			//2:XY移動量移動
}
void Star2::draw(Tomasen &game){
	/*エフェクト描画*/
	//デフォルト
	Effect::draw(game);
	//減色なし
	/*game.IMAGE->drawAlphaBlendTile(getPos(), 
					getOutputW(), 
					getOutputH(), 
					getImageX(), getImageY(), 
					getImageW(), getImageH(),
					255);*/
}
Dust1::Dust1(){
	maxHp = 1;				//最大耐久度
	imageX = 45;			//画像x座標
	imageY = 22;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
	animeMax = 1;			//アニメーション枚数
	animeWait = 6;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 100;		//生存フレーム
	moveMode = 0;			//2:XY移動量移動
}
TextScreen::TextScreen(){
	
	timeOfLife = 1000;		//生存フレーム

	//テキスト描画クラスの初期化
	TEXT = new DrawTextImage();
	/*テキストの準備*/
	TEXT->addText("昔むかし　遥か銀河系の彼方で・・・");
	TEXT->addText("銀河大航海時代の地球に残された人類に危機が迫っていた。");
	TEXT->addText("大気汚染で荒廃しきった地球は資源も枯渇し既に生活できる環境ではなかった。");
	TEXT->addText("人類が星間飛行に成功してから１００年、");
	TEXT->addText("地球上の最後の人類は地球を捨てることを決断した。");
	TEXT->addText("そして異星人が蠢く宇宙へ、安息の地を求め飛び立ったのだった。");
}
void TextScreen::update(Tomasen &game){
	/*親クラスの更新*/
	Effect::update(game);


}
void TextScreen::draw(Tomasen &game){
	/*エフェクト描画*/
	TEXT->draw(*(game.IMAGE));
}

TextBox::TextBox(){
	maxHp = 1;				//最大耐久度
	timeOfLife = 999;		//生存フレーム
	size = 1;				//サイズ
	moveMode = 3;

	pos = Vec2(SCREEN_WIDTH - SCREEN_INDENT + 50, 
			SCREEN_HEIGHT / 2);
	targetPos = Vec2(SCREEN_WIDTH / 2,
			SCREEN_HEIGHT / 2);
}
void TextBox::draw(Tomasen &game){
	/*エフェクト描画*/
	game.IMAGE->printText(pos.x, pos.y, name.c_str());
	game.IMAGE->printText(pos.x, pos.y+10, name2.c_str());
}

void TextBox::update(Tomasen& game){
	/*親クラスの更新を呼び出す*/
	Effect::update(game);
	
	//中央部分から枠外への移動
	if(frameCnt == 250){
		move = Vec2(0.0, 0.0);
		targetPos = Vec2(0,
		SCREEN_HEIGHT / 2);
	}
}
void TextBox::setName2(string name2){
	TextBox::name2 = name2;
}
Marker::Marker(){
	maxHp = 1;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 20;			//画像y座標
	imageW = 2;				//画像幅
	imageH = 2;				//画像高
	outputW = 2;			//出力幅
	outputH = 2;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 12;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 100;		//生存フレーム
	moveMode = 1;			//1:XY移動量移動
}
void Marker::update(Tomasen& game){
	/*親の更新メソッド*/
	Effect::update(game);
	timeOfLife -= 2;
	if(timeOfLife < 0) timeOfLife = 0;

	//敵の生成
	if(timeOfLife <= 0){
		enemyList.push_back( EnemySptr(new EnemyE()) );				//リストにオブジェクト追加
		EnemyVsptr::iterator it = enemyList.end() - 1;				//直前のオブジェクトを参照
		(*it)->setPos(Vec2(makeRand(pos.x, 7), pos.y));				//敵機をイベント位置に移動
		(*it)->setPattern(1);										//敵機の行動パターンの指定
		game.MUSIC->Play(musicWarp);
	}
}
void Marker::draw(Tomasen& game){
	/*エフェクト描画*/
	game.IMAGE->drawAlphaBlendTile(
		Vec2(
			getCenterPos().x - (double)timeOfLife/2,
			getCenterPos().y - (double)timeOfLife/2),
		(double)timeOfLife,
		(double)timeOfLife,
		getImageX(),
		getImageY(),
		2,
		2,
		255);
}
Smoke2::Smoke2() {
	maxHp = 1;				//最大耐久度
	imageX = 32;			//画像x座標
	imageY = 8;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
	animeMax = 4;			//アニメーション枚数
	animeWait = 12;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 50;		//生存フレーム
	moveMode = 0;			//1:ターゲット移動
}
Chara::Chara() {
	charOffset = 0;
	imageX = 0;			//画像x座標
	imageY = 1;			//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	animeMax = 1;			//アニメーション枚数
	animeWait = 12;			//アニメーション１枚のフレーム数
	size = 1;				//サイズ
	timeOfLife = 999;		//生存フレーム
}
void Chara::draw(Tomasen& game) {
	/*エフェクト描画*/
	game.IMAGE->drawAlphaBlendTile(getPos(),
		getOutputW(),
		getOutputH(),
		getImageX() + charOffset, getImageY(),
		getImageW(), getImageH(),
		100);
}


} //namespace tm2