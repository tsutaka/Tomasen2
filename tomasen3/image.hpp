//D2Imageクラスver1.1 2012/8/20
#ifndef INCLUDED_IMAGE_HPP
#define INCLUDED_IMAGE_HPP

#include <windows.h>
#include "common.hpp"
#include <string.h>


namespace tm2{

class D2Image
{
private:
	/*ディスプレイサイズ*/
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	/*転送先ディスプレイ*/
	HWND hWnd;
	HDC hdc;
	/*画像用*/
	int bmpw, bmph;
	BITMAP bmp_info;
	HDC hdc_bmp;
	HBITMAP hBmp;
	/*マスク画像用*/
	HDC hdc_msk;
	HBITMAP hMsk;
	/*マスク反転用*/
	HDC hdc_tmp;
	HBITMAP hTmp;
	/*仮想画面*/
	HDC hdc_mem;
	HBITMAP hMem;
	/*作業画面１*/
	HDC hdc_wk1;
	HBITMAP hWk1;
	/*作業画面２*/
	HDC hdc_wk2;
	HBITMAP hWk2;
public:

	/*定数*/
	static const int xBMP = 0;
	static const int xMEM = 1;
	static const int xMSK = 2;
	static const int xTMP = 3;
	static const int xWK1 = 4;
	static const int xWK2 = 5;
	static const int xCOPY = -1;
	static const int xTRANS = -2;
	static const int xAND = -3;
	static const int xOR = -4;
	/*コンストラクタ*/
	D2Image();
	/*デストラクタ*/
	~D2Image();
	/*指定ビットマップを読み込み*/
	void init(HWND, string imagePath, int w, int h);				//ウィンドウハンドル, 画像パス,WindowW,WindowH
	/*メモリを表示させる*/
	void memToDis(void);							
	/*ビットマップ全体を転送*/
	void bmpToMem();								
	/*拡大なし転送*/
	void bmpToMem(int,int,int,int,int,int);			//転送先ｘ,転送先ｙ,画像幅,画像高,転送元ｘ,転送元ｙ
	/*拡大あり転送*/
	void bmpToMem(int,int,int,int,int,int,int,int);	//転送先ｘ,転送先ｙ,転送先画像幅,転送先画像高,転送元ｘ,転送元ｙ,転送元画像幅,転送先画像高
	/*回転拡大あり転送*/
	void bmpToMem(int,int,int,int,int,int,int,int,int,int,double);	//転送先ｘ,転送先ｙ,転送先画像幅,転送先画像高,転送元ｘ,転送元ｙ,転送元画像幅,転送先画像高,転送元中心ｘ,転送元中心y,回転角度
	/*透過拡大あり転送*/
	void bmpToMem(int,int,int,int,int,int,int,int,int);	//転送先ｘ,転送先ｙ,転送先画像幅,転送先画像高,転送元ｘ,転送元ｙ,転送元画像幅,転送先画像高,アルファブレンド
	/*文字出力*/
	void textToMem(int, int, const char[], COLORREF);//文字出力
	/*面指定透過拡大あり転送*/
	void mem2Mem(int,int,int,int,int,int,int,int,int,int,int);	//転送先面番号,転送先ｘ,転送先ｙ,転送先画像幅,転送先画像高,転送元面番号,転送元ｘ,転送元ｙ,転送元画像幅,転送元画像高,透過度
	/*面指定拡大回転あり転送*/
	void mem2Mem(int,int,int,int,int,int,int,int,int,int,int,int,double); //転送先面番号,転送先ｘ,転送先ｙ,転送先画像幅,転送先画像高,転送元面番号,転送元ｘ,転送元ｙ,転送元画像幅,転送元画像高,転送元中心ｘ,転送元中心y,回転角度
private:
};




} //namespace tm2
#endif//INCLUDED_IMAGE_HPP