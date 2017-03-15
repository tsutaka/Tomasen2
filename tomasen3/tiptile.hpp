/************

	TipTileクラス
		（D2Image(image.hpp)クラスのラッパー）

	チップ単位での描画転送処理

************/

#ifndef INCLUDED_TIPTILE_HPP
#define INCLUDED_TIPTILE_HPP

/*************
教訓
・inline関数はヘッダファイルに定義も書かなくてはならない。
・他の関数は宣言のみヘッダファイルに書く。
*************/
#include <windows.h>
#include "common.hpp"
#include "image.hpp"

namespace tm2{

/*D2Imageのラッパークラス*/
class TipTile{

private:
	D2Image *IMG;

public:
	/**************
	描画系関数の引数についてのルール
	double型座標(またはVec2型)	:	詳細座標
	int型座標(またはPOINT型)	:	チップ単位座標

	チップ：基本最小単位の正方形
	タイル：チップ以上のサイズの四角形
	**************/
	inline int tipNo(int x, int y);		//チップ番号算出

	inline void init(HWND hWnd, const char str[], int screenW, int screenH);			//初期化
	inline void set(int width, int height, int tipSize);	//BMPデータの設定

	inline void printText(int posx, int posy, const char str[]);	//テキストの表示

	inline void printText(double posx, double posy, const char str[]);	//テキストの表示
	
	inline void drawDot(double vecx, double vecy, double size, int TipNo);//一ドット描画
	inline void drawLine(Vec2 from, Vec2 to, int TipNo, int alpha);//ライン描画

	inline void drawTip(void);//チップ一覧表示
	inline void drawTip(int posx, int posy, int TipNo);			//チップの描画
	inline void drawTip(double x, double y, int TipNo);			//チップの描画
	inline void drawTip(Vec2 vec, int TipNo);					//チップの描画
	inline void drawTip(Vec2 vec, int TipX, int TipY);			//チップの描画
	inline void drawTip(POINT pos, int TipNo);					//チップの描画
	
	inline void drawRotateTip(double centerx, double centery, double angle, int TipNo);			//チップの回転描画

	inline void drawTip(int posx, int posy, int w, int h, int TipNo);			//チップの拡大描画
	inline void drawTip(double x, double y, double w, double h, int TipNo);		//チップの拡大描画
	
	inline void drawAlphaBlendTip(double x, double y, double w, double h, int TipNo, int alpha);					//チップの半透明拡大描画

	inline void drawTile(int posx, int posy, int TileSize, int TileNo);				//タイルの描画
	inline void drawTile(Vec2 vec, int TileSize, int TileNo);						//タイルの描画
	inline void drawTile(Vec2 vec, int TileSize, double TileX, double TileY);				//タイルの描画
	inline void drawTile(int posx, int posy, int TileNo, int TileW, int TileH);				//タイルの描画
	inline void drawTile(int posx, int posy, int TileX, int TileY, int TileW, int TileH);	//タイルの描画
	
	inline void drawRotateTile(int w, int h, double centerx, double centery, double angle, int TileX, int TileY, int TileW, int TileH);			//タイルの回転描画
	inline void drawRotateTile(int w, int h, double centerx, double centery, double angle, int TileX, int TileY, int TileW, int TileH, int alpha);			//タイルの回転半透明描画

	inline void drawTile(int posx, int posy, int w, int h, int TileNo, int TileW, int TileH);		//タイルの拡大描画
	inline void drawTile(double x, double y, int w, int h, int TileNo, int TileW, int TileH);		//タイルの拡大描画
	inline void drawTile(double x, double y, double w, double h, int TileNo, int TileW, int TileH);	//タイルの拡大描画
	inline void drawTile(Vec2 vec, int w, int h, int TileNo, int TileW, int TileH);					//タイルの拡大描画
	inline void drawTile(Vec2 vec, int w, int h, int TileX, int TileY, int TileW, int TileH);		//タイルの半透明拡大描画
	
	inline void drawAlphaBlendTile(Vec2 vec, int w, int h, int TileX, int TileY, int TileW, int TileH, int alpha);		//タイルの半透明拡大描画
	inline void drawAlphaBlendTile(Vec2 vec, double w, double h, int TileX, int TileY, int TileW, int TileH, int alpha);		//タイルの半透明拡大描画
	
	inline void drawTile(Vec2 vec, int tosize, int TileNo, int fromsize);		//タイルの拡大描画(送り先も元も正方形)
	inline void drawTile(Vec2 vec, double tosize, int TileNo, int fromsize);	//タイルの拡大描画(送り先も元も正方形)

	inline void drawFillTip(int x, int y, int w, int h, int TipNo);		//チップで範囲を埋める
	inline void drawFillTip(Vec2 vec, int w, int h, int TipNo);			//チップで範囲を埋める
	
	inline void drawEnd(void);//メモリの画像を転送

	inline void setBasicColor(int red, int  green, int blue, int black, int white);	//基本色のチップ番号を設定
	inline int getRed();		//赤のチップ番号の取得
	inline int getGreen();		//緑のチップ番号の取得
	inline int getBlue();		//青のチップ番号の取得
	inline int getBlack();		//黒のチップ番号の取得
	inline int getWhite();		//白のチップ番号の取得


private:
	int BMP_WIDTH;		//BMPの幅
	int BMP_HEIGHT;		//BMPウの高さ
	int MapTipSize;		//チップのサイズ
	int MapTipW;		//BMP上の横マップチップの数
	int MapTipH;		//BMP上の縦マップチップの数

	int redTipNo;		//赤チップ番号
	int greenTipNo;		//緑チップ番号
	int blueTipNo;		//青チップ番号
	int blackTipNo;		//黒チップ番号
	int whiteTipNo;		//白チップ番号
};


int TipTile::tipNo(int x, int y){		//チップ番号算出
	return y * MapTipW + x;
}
void TipTile::init(HWND hWnd, const char str[], int screenx, int screeny){
	IMG = new D2Image();
	IMG->init(hWnd, str, screenx, screeny);			//初期化
	BMP_WIDTH = 800;								//BMPの幅
	BMP_HEIGHT = 600;								//BMPの高さ
	MapTipSize = 16;								//チップのサイズ
	MapTipW = BMP_WIDTH / MapTipSize;				//BMP上の横マップチップの数
	MapTipH = BMP_HEIGHT / MapTipSize;				//BMP上の縦マップチップの数
}

void TipTile::set(int width, int height, int tipSize){
	BMP_WIDTH = width;						//ウィンドウの幅
	BMP_HEIGHT = height;					// ウィンドウの高さ
	MapTipSize = 16;						//チップのサイズ
	MapTipW = BMP_WIDTH / MapTipSize;	//BMP上の横マップチップの数
	MapTipH = BMP_HEIGHT / MapTipSize;	//BMP上の縦マップチップの数
}

void TipTile::printText(int posx, int posy, const char str[]){
	IMG->textToMem(
		posx * MapTipSize,	//描画先x
		posy * MapTipSize,	//描画先y
		str,				//描画文字列
		RGB(100,200,50)
		);
}

void TipTile::printText(double posx, double posy, const char str[]){
	IMG->textToMem(
		(int)posx,	//描画先x
		(int)posy,	//描画先y
		str,				//描画文字列
		RGB(100,200,50)
		);
}

void TipTile::drawDot(double vecx, double vecy, double size, int TipNo){//ドットの描画
	IMG->bmpToMem(
		(int)vecx, //描画先x
		(int)vecy, //描画先y
		(int)size, //幅
		(int)size, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize //転送元y
		);
}
void TipTile::drawLine(Vec2 from, Vec2 to, int TipNo, int alpha)//ライン描画
{
	int size = MapTipSize;
	//中央部にチップ
	/*IMG->bmpToMem(
		(int)((from.x + to.x) / 2.0), //描画先x
		(int)((from.y + to.y) / 2.0), //描画先y
		(int)(sqrt(
			(to.x - from.x) * (to.x - from.x) + 
			(to.y - from.y) * (to.y - from.y)
		)), //描画先幅
		(int)size, //描画先高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize, //転送元y
		MapTipSize,//転送元幅
		MapTipSize,//転送元高
		MapTipSize/2,//転送元中心x
		MapTipSize/2,//転送元中心y
		atan2(to.y - from.y, to.x - from.x)
		);*/
	//出力先w,hの準備
	double h = MapTipSize;
	double w = sqrt(
			(to.x - from.x) * (to.x - from.x) + 
			(to.y - from.y) * (to.y - from.y) );
	double centerx = ((from.x + to.x) / 2.0);
	double centery = ((from.y + to.y) / 2.0);
	double angle = atan2(to.y - from.y, to.x - from.x);
	
	//回転と半透明を同時にできないため手数を踏む
	/*画面→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		(int)(1.5 * ((w>h)?w:h)), //幅
		(int)(1.5 * ((w>h)?w:h)), //高
		IMG->xMEM, //描画元：仮想画面
		(int)centerx - (int)(1.5 * ((w>h)?w:h) / 2), //描画元x
		(int)centery - (int)(1.5 * ((w>h)?w:h) / 2), //描画元y
		(int)(1.5 * ((w>h)?w:h)), //幅
		(int)(1.5 * ((w>h)?w:h)), //高
		IMG->xCOPY);
	/*元画像→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		(int)(1.5 * ((w>h)?w:h) / 2), //描画先中心x
		(int)(1.5 * ((w>h)?w:h) / 2), //描画先中心y
		(int)(w), //幅
		(int)(h), //高
		IMG->xBMP, //描画元：ビットマップ画面
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize, //転送元y
		MapTipSize,//転送元幅
		MapTipSize,//転送元高
		MapTipSize/2,//転送元中心x
		MapTipSize/2,//転送元中心y
		angle);
	/*ワーク領域→仮想領域アルファ転送*/
	IMG->mem2Mem(IMG->xMEM, //描画先：仮想画面
		(int)centerx - (int)(1.5 * ((w>h)?w:h) / 2), //描画先x
		(int)centery - (int)(1.5 * ((w>h)?w:h) / 2), //描画先y
		(int)(1.5 * ((w>h)?w:h)), //幅
		(int)(1.5 * ((w>h)?w:h)), //高
		IMG->xWK1, //描画元：ワーク画面
		0, //転送元x
		0, //転送元y
		(int)(1.5 * ((w>h)?w:h)), //幅
		(int)(1.5 * ((w>h)?w:h)), //高
		100);//0～255
}


void TipTile::drawTip(void)
{
	/*マップチップ一覧の表示*/
	IMG->bmpToMem();
	
}
void TipTile::drawTip(int posx, int posy, int TipNo){//チップの描画
	IMG->bmpToMem(
		posx * MapTipSize, //描画先x
		posy * MapTipSize, //描画先y
		MapTipSize, //幅
		MapTipSize, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize //転送元y
		);
}
void TipTile::drawTip(double x, double y, int TipNo){//チップの描画
	IMG->bmpToMem(
		(int)x, //描画先x
		(int)y, //描画先y
		MapTipSize, //幅
		MapTipSize, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize //転送元y
		);
}
void TipTile::drawTip(Vec2 vec, int TipNo){//チップの描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		MapTipSize, //幅
		MapTipSize, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize //転送元y
		);
}
void TipTile::drawTip(Vec2 vec, int TipX, int TipY){//チップの描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		MapTipSize, //幅
		MapTipSize, //高
		TipX * MapTipSize, //転送元x
		TipY * MapTipSize //転送元y
		);
}
void TipTile::drawTip(POINT pos, int TipNo){//チップの描画
	IMG->bmpToMem(
		pos.x * MapTipSize, //描画先x
		pos.y * MapTipSize, //描画先y
		MapTipSize, //幅
		MapTipSize, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize //転送元y
		);
}
void TipTile::drawRotateTip(double centerx, double centery, double angle, int TipNo){//チップの回転描画
	IMG->bmpToMem(
		(int)centerx, //描画先x
		(int)centery, //描画先y
		MapTipSize, //幅
		MapTipSize, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize, //転送元y
		MapTipSize, //幅
		MapTipSize, //高
		MapTipSize/2,//転送元中心x
		MapTipSize/2,//転送元中心y
		angle//回転角度
		);
}
void TipTile::drawTip(int posx, int posy, int w, int h, int TipNo){//チップの拡大描画
	IMG->bmpToMem(
		posx * MapTipSize, //描画先x
		posy * MapTipSize, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize, //転送元y
		MapTipSize, //幅
		MapTipSize //高
		);
}
void TipTile::drawTip(double x, double y, double w, double h, int TipNo){//チップの拡大描画
	IMG->bmpToMem(
		(int)x, //描画先x
		(int)y, //描画先y
		(int)w, //幅
		(int)h, //高
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize, //転送元y
		MapTipSize, //幅
		MapTipSize //高
		);
}
void TipTile::drawAlphaBlendTip(double x, double y, double w, double h, int TipNo, int alpha){//チップの半透明描画
	/*画面→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		(int)w, //幅
		(int)h, //高
		IMG->xMEM, //描画元：ビットマップ画面
		(int)x, //描画元x
		(int)y, //描画元y
		(int)w, //幅
		(int)h, //高
		IMG->xCOPY);
	/*元画像→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		(int)w, //幅
		(int)h, //高
		IMG->xBMP, //描画元：ビットマップ画面
		(TipNo % MapTipW) * MapTipSize, //転送元x
		(TipNo / MapTipW) * MapTipSize, //転送元y
		MapTipSize, //幅
		MapTipSize, //高
		IMG->xTRANS);
	/*ワーク領域→仮想領域アルファ転送*/
	IMG->mem2Mem(IMG->xMEM, //描画先：仮想画面
		(int)x, //描画先x
		(int)y, //描画先y
		(int)w, //幅
		(int)h, //高
		IMG->xWK1, //描画元：ビットマップ画面
		0, //転送元x
		0, //転送元y
		(int)w, //幅
		(int)h, //高
		alpha); //0～255
}
void TipTile::drawTile(int posx, int posy, int TileSize, int TileNo){//タイルの描画
	IMG->bmpToMem(
		posx * MapTipSize, //描画先x
		posy * MapTipSize, //描画先y
		TileSize * MapTipSize, //幅
		TileSize * MapTipSize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		TileSize * MapTipSize, //幅
		TileSize * MapTipSize //高
		);
}
void TipTile::drawTile(Vec2 vec, int TileSize, int TileNo){//タイルの描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		TileSize * MapTipSize, //幅
		TileSize * MapTipSize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		TileSize * MapTipSize, //幅
		TileSize * MapTipSize //高
		);
}
void TipTile::drawTile(Vec2 vec, int TileSize, double TileX, double TileY){//タイルの描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		TileSize * MapTipSize, //幅
		TileSize * MapTipSize, //高
		(int)TileX, //転送元x
		(int)TileY, //転送元y
		TileSize * MapTipSize, //幅
		TileSize * MapTipSize //高
		);
}
void TipTile::drawTile(int posx, int posy, int TileNo, int TileW, int TileH){//タイルの描画
	IMG->bmpToMem(
		posx * MapTipSize, //描画先x
		posy * MapTipSize, //描画先y
		TileW * MapTipSize, //幅
		TileH * MapTipSize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize //高
		);
}
void TipTile::drawTile(int posx, int posy, int TileX, int TileY, int TileW, int TileH){//タイルの描画
	IMG->bmpToMem(
		posx * MapTipSize, //描画先x
		posy * MapTipSize, //描画先y
		TileW * MapTipSize, //幅
		TileH * MapTipSize, //高
		TileX * MapTipSize, //転送元x
		TileY * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize //高
		);
}
void TipTile::drawRotateTile(int w, int h, double centerx, double centery, double angle, int TileX, int TileY, int TileW, int TileH){			//タイルの回転描画
	IMG->bmpToMem(
		(int)centerx, //描画先x
		(int)centery, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		TileX * MapTipSize, //転送元x
		TileY * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize, //高
		TileW * MapTipSize/2,//転送元中心x
		TileH * MapTipSize/2,//転送元中心y
		angle//回転角度
		);
}
void TipTile::drawRotateTile(int w, int h, double centerx, double centery, double angle, int TileX, int TileY, int TileW, int TileH, int alpha){			//タイルの回転描画
	/*画面→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //幅
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //高
		IMG->xMEM, //描画元：仮想画面
		(int)centerx - (int)(1.5 * ((w>h)?w:h) * MapTipSize / 2), //描画元x
		(int)centery - (int)(1.5 * ((w>h)?w:h) * MapTipSize / 2), //描画元y
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //幅
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //高
		IMG->xCOPY);
	/*元画像→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		(int)(1.5 * ((w>h)?w:h) * MapTipSize / 2), //描画先中心x
		(int)(1.5 * ((w>h)?w:h) * MapTipSize / 2), //描画先中心y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		IMG->xBMP, //描画元：ビットマップ画面
		TileX * MapTipSize, //転送元x
		TileY * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize, //高
		TileW * MapTipSize/2,//転送元中心x
		TileH * MapTipSize/2,//転送元中心y
		angle);
	/*ワーク領域→仮想領域アルファ転送*/
	IMG->mem2Mem(IMG->xMEM, //描画先：仮想画面
		(int)centerx - (int)(1.5 * ((w>h)?w:h) * MapTipSize / 2), //描画先x
		(int)centery - (int)(1.5 * ((w>h)?w:h) * MapTipSize / 2), //描画先y
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //幅
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //高
		IMG->xWK1, //描画元：ワーク画面
		0, //転送元x
		0, //転送元y
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //幅
		(int)(1.5 * ((w>h)?w:h) * MapTipSize), //高
		alpha);//0～255
}
void TipTile::drawTile(int posx, int posy, int w, int h, int TileNo, int TileW, int TileH){//タイルの拡大描画
	IMG->bmpToMem(
		posx * MapTipSize, //描画先x
		posy * MapTipSize, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize //高
		);
}
void TipTile::drawTile(double x, double y, double w, double h, int TileNo, int TileW, int TileH){//タイルの拡大描画
	IMG->bmpToMem(
		(int)x, //描画先x
		(int)y, //描画先y
		(int)w, //幅
		(int)h, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize //高
		);
}
void TipTile::drawTile(double x, double y, int w, int h, int TileNo, int TileW, int TileH){//タイルの拡大描画
	IMG->bmpToMem(
		(int)x, //描画先x
		(int)y, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize //高
		);
}
void TipTile::drawTile(Vec2 vec, int w, int h, int TileNo, int TileW, int TileH){//タイルの拡大描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize //高
		);
}
void TipTile::drawTile(Vec2 vec, int w, int h, int TileX, int TileY, int TileW, int TileH){//タイルの拡大描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		TileX * MapTipSize, //転送元x
		TileY * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize //高
		);
}
void TipTile::drawAlphaBlendTile(Vec2 vec, int w, int h, int TileX, int TileY, int TileW, int TileH, int alpha){//タイルの拡大描画
	/*画面→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		IMG->xMEM, //描画元：出力画面
		(int)vec.x, //描画元x
		(int)vec.y, //描画元y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		IMG->xCOPY);
	/*元画像→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		IMG->xBMP, //描画元：ビットマップ画面
		TileX * MapTipSize, //転送元x
		TileY * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize, //高
		IMG->xTRANS);
	/*ワーク領域→仮想領域アルファ転送*/
	IMG->mem2Mem(IMG->xMEM, //描画先：仮想画面
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		IMG->xWK1, //描画元：ワーク画面
		0, //転送元x
		0, //転送元y
		w * MapTipSize, //幅
		h * MapTipSize, //高
		alpha);
}
void TipTile::drawAlphaBlendTile(Vec2 vec, double w, double h, int TileX, int TileY, int TileW, int TileH, int alpha){//タイルの拡大描画
	/*画面→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		(int)w, //幅
		(int)h, //高
		IMG->xMEM, //描画元：出力画面
		(int)vec.x, //描画元x
		(int)vec.y, //描画元y
		(int)w, //幅
		(int)h, //高
		IMG->xCOPY);
	/*元画像→ワーク領域*/
	IMG->mem2Mem(IMG->xWK1, //描画先：作業領域１
		0, //描画先x
		0, //描画先y
		(int)w, //幅
		(int)h, //高
		IMG->xBMP, //描画元：ビットマップ画面
		TileX * MapTipSize, //転送元x
		TileY * MapTipSize, //転送元y
		TileW * MapTipSize, //幅
		TileH * MapTipSize, //高
		IMG->xTRANS);
	/*ワーク領域→仮想領域アルファ転送*/
	IMG->mem2Mem(IMG->xMEM, //描画先：仮想画面
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		(int)w, //幅
		(int)h, //高
		IMG->xWK1, //描画元：ワーク画面
		0, //転送元x
		0, //転送元y
		(int)w, //幅
		(int)h, //高
		alpha);
}
void TipTile::drawTile(Vec2 vec, int tosize, int TileNo, int fromsize){//タイルの拡大描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		tosize * MapTipSize, //幅
		tosize * MapTipSize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		fromsize * MapTipSize, //幅
		fromsize * MapTipSize //高
		);
}
void TipTile::drawTile(Vec2 vec, double tosize, int TileNo, int fromsize){//タイルの拡大描画
	IMG->bmpToMem(
		(int)vec.x, //描画先x
		(int)vec.y, //描画先y
		(int)tosize, //幅
		(int)tosize, //高
		(TileNo % MapTipW) * MapTipSize, //転送元x
		(TileNo / MapTipW) * MapTipSize, //転送元y
		fromsize * MapTipSize, //幅
		fromsize * MapTipSize //高
		);
}

void TipTile::drawFillTip(int x, int y, int w, int h, int TipNo){		//チップで範囲を埋める
	for(int j = y; j < y + h; j++){
		for(int i = x; i < x + w; i++){
			drawTip(i, j, TipNo);
		}
	}
}

void TipTile::drawFillTip(Vec2 vec, int w, int h, int TipNo){		//チップで範囲を埋める
	for(int j = 0; j < h; j++){
		for(int i = 0; i < w; i++){
			drawTip(vec.x + i * MapTipSize, vec.y + j * MapTipSize, TipNo);
		}
	}
}

void TipTile::drawEnd(void){
	IMG->memToDis();
}


void TipTile::setBasicColor(int red, int  green, int blue, int black, int white){	//基本色のチップ番号を設定
	redTipNo = red;
	greenTipNo = green;
	blueTipNo = blue;
	blackTipNo = black;
	whiteTipNo = white;
}
int TipTile::getRed(){			//赤のチップ番号の取得
	return redTipNo;
}
int TipTile::getGreen(){		//緑のチップ番号の取得
	return greenTipNo;
}
int TipTile::getBlue(){			//青のチップ番号の取得
	return blueTipNo;
}
int TipTile::getBlack(){		//黒のチップ番号の取得
	return blackTipNo;
}
int TipTile::getWhite(){		//白のチップ番号の取得
	return whiteTipNo;
}

} //namespace tm2
#endif//INCLUDED_TIPTILE_HPP