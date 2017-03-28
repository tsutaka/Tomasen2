
#include "tomasen.hpp"

#include "obj_print.hpp"

namespace tm2{

/*グローバルリソース定義*/
BarVsptr barList;					//バーリスト
BarWptr barFactory(BarSptr bar){
		barList.push_back( bar );							//リストにオブジェクト追加
		BarVsptr::iterator it = barList.end() - 1;	//直前のオブジェクトを参照
		return (*it);
}
LabelVsptr labelList;				//ラベルリスト
LabelWptr labelFactory(LabelSptr label){
		labelList.push_back( label );							//リストにオブジェクト追加
		LabelVsptr::iterator it = labelList.end() - 1;	//直前のオブジェクトを参照
		return (*it);
}

Print::Print(){
	value = 0;						//現在値	//明るい表示
	printValue = 0;					//表示値
	maxValue = 0;					//最大値	//薄暗い表示
	startValue = 0;					//初期値	//バーの右端
	frameCnt = 0;					//生成後の経過フレーム数
	animeCnt = 0;					//現在のアニメフレーム
	animeMax = 4;					//アニメーション枚数
	animeWait = 4;					//アニメーション１枚のフレーム数
	maxImageW = 1;					//画像２x座標
	maxImageH = 1;					//画像２y座標
	underImageW = 1;				//下地画像幅
	underImageH = 1;				//下地画像高
	overImageW = 1;					//上枠画像幅
	overImageH = 1;					//上枠画像高
	imageW = 1;						//画像幅
	imageH = 1;						//画像高
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
}

void Bar::update(Tomasen& game){
	/*現在値の更新*/
	if(printValue - value > 10 || printValue - value < -10){
		printValue += (value - printValue) / 10;
	}
	else if(printValue < value){
		printValue++;
	}
	else if(printValue > value){
		printValue--;
	}
	/*カウントアップ*/
	frameCnt++;
	if(frameCnt > 50000) frameCnt = 0;
	if(frameCnt % animeWait == 0) animeCnt++;
	if(animeCnt >= animeMax) animeCnt = 0;
}
void Bar::draw(Tomasen& game){
	game.IMAGE->printText((int)getPos().x/tipSize - 2, 
		(int)getPos().y/tipSize, getName().c_str());
	game.IMAGE->drawFillTip(getPos(), 
		getSize(), 1, 
	game.IMAGE->tipNo(getUnderImageX(), getUnderImageY()) );		//下地
	if(getStartValue() > 0){											//零除算の回避
		game.IMAGE->drawTip(getPos().x, getPos().y, 
			(double)getSize() * tipSize * getMaxValue() / getStartValue(), 
			(double)1 * tipSize, 
			game.IMAGE->tipNo(getMaxImageX(), getMaxImageY()));	//現最大バー
		game.IMAGE->drawTip(getPos().x, getPos().y, 
			(double)getSize() * tipSize * getPrintValue() / getStartValue(), 
			(double)1 * tipSize, 
			game.IMAGE->tipNo(getImageX(), getImageY()));			//現在値のバー
	}
	else{
		//mb("最大値が零又は負の数");
	}
	game.IMAGE->drawFillTip(getPos(), 
		getSize(), 1, 
		game.IMAGE->tipNo(getOverImageX(), getOverImageY()) );		//上枠
}

void Label::update(Tomasen& game){
	/*現在値の更新*/
	if(printValue - value > 10 || printValue - value < -10){
		printValue += (value - printValue) / 10;
	}
	if(printValue  > value){
		printValue--;
	}
	else if(printValue < value){
		printValue++;
	}
}
void Label::draw(Tomasen& game){
	char checktext[256] = "";
	game.IMAGE->printText((int)getPos().x/tipSize, 
		(int)getPos().y/tipSize, 
		getName().c_str());
	sprintf_s(checktext, sizeof(checktext), "%08d", getPrintValue());
	game.IMAGE->printText((int)getPos().x/tipSize + 7, 
		(int)getPos().y/tipSize, 
		checktext);
}

HpBar::HpBar(){
	/*初期化*/
	pos = Vec2(40.0*tipSize, 5.0*tipSize);		//位置
	name = "耐";			//名前
	//初期値については自機のコンストラクタで設定
	size = 10;				//バーの幅（高さは１固定）
	imageX = 28;			//画像x座標
	imageY = 16;			//画像y座標
	maxImageX = 1;			//画像２x座標
	maxImageY = 16;			//画像２y座標
	underImageX = 24;		//下地画像x座標
	underImageY = 17;		//下地画像y座標
	overImageX = 24;		//上枠画像x座標
	overImageY = 16;		//上枠画像y座標
}

EnergyBar::EnergyBar(){
	/*初期化*/
	pos = Vec2(40.0*tipSize, 7.0*tipSize);		//位置
	name = "弾";			//名前
	//初期値については自機のコンストラクタで設定
	size = 10;				//バーの幅（高さは１固定）
	imageX = 28;			//画像x座標
	imageY = 17;			//画像y座標
	maxImageX = 2;			//画像２x座標
	maxImageY = 16;			//画像２y座標
	underImageX = 24;		//下地画像x座標
	underImageY = 17;		//下地画像y座標
	overImageX = 24;		//上枠画像x座標
	overImageY = 16;		//上枠画像y座標
}
ManBar::ManBar(){
	/*初期化*/
	pos = Vec2(40.0*tipSize, 9.0*tipSize);		//位置
	name = "人";			//名前
	//初期値については自機のコンストラクタで設定
	size = 10;				//バーの幅（高さは１固定）
	imageX = 32;			//画像x座標
	imageY = 17;			//画像y座標
	maxImageX = 4;			//画像２x座標
	maxImageY = 16;			//画像２y座標
	underImageX = 24;		//下地画像x座標
	underImageY = 17;		//下地画像y座標
	overImageX = 24;		//上枠画像x座標
	overImageY = 16;		//上枠画像y座標
}
FireBar::FireBar(){
	/*初期化*/
	pos = Vec2(40.0*tipSize, 11.0*tipSize);		//位置
	name = "炎";			//名前
	//初期値については自機のコンストラクタで設定
	size = 10;				//バーの幅（高さは１固定）
	imageX = 32;			//画像x座標
	imageY = 16;			//画像y座標
	maxImageX = 3;			//画像２x座標
	maxImageY = 16;			//画像２y座標
	underImageX = 24;		//下地画像x座標
	underImageY = 17;		//下地画像y座標
	overImageX = 24;		//上枠画像x座標
	overImageY = 16;		//上枠画像y座標
}

GoldLabel::GoldLabel(){
	/*初期化*/
	pos = Vec2(38.0*tipSize, 28.0*tipSize);		//位置
	name = "ＧＯＬＤ　";			//名前
}
ScoreLabel::ScoreLabel(){
	/*初期化*/
	pos = Vec2(38.0*tipSize, 30.0*tipSize);		//位置
	name = "ＳＣＯＲＥ";			//名前
}
HiScoreLabel::HiScoreLabel(){
	/*初期化*/
	pos = Vec2(38.0*tipSize, 32.0*tipSize);		//位置
	name = "ＨＩＳＣＯＲＥ";			//名前
}

ResultManLabel::ResultManLabel(){
	/*初期化*/
	pos = Vec2(SCREEN_WIDTH/2 - 10.0*tipSize, SCREEN_WIDTH/2 - 10.0*tipSize);		//位置
	name = "生存人数：";			//名前
}

void ResultManLabel::draw(Tomasen& game){
	char checktext[256] = "";
	game.IMAGE->printText((int)getPos().x/tipSize, 
		(int)getPos().y/tipSize, 
		getName().c_str());
	sprintf_s(checktext, sizeof(checktext), "%8d", getPrintValue());
	game.IMAGE->printText((int)getPos().x/tipSize + 7, 
		(int)getPos().y/tipSize, 
		checktext);
	game.IMAGE->printText((int)getPos().x/tipSize + 11, 
		(int)getPos().y/tipSize, 
		"人");
}
ResultScoreLabel::ResultScoreLabel(){
	/*初期化*/
	pos = Vec2(SCREEN_WIDTH/2 - 10.0*tipSize, SCREEN_WIDTH/2 - 8.0*tipSize);		//位置
	name = "ＳＣＯＲＥ：";			//名前
}

} //namespace tm2