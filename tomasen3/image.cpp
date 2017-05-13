#include "image.hpp"

namespace tm2{

D2Image::D2Image()
{
}
D2Image::~D2Image()
{
	DeleteObject(hMem);
	DeleteDC(hdc_mem);
	DeleteObject(hTmp);
	DeleteDC(hdc_tmp);
	DeleteObject(hWk1);
	DeleteDC(hdc_wk1);
	DeleteObject(hWk2);
	DeleteDC(hdc_wk2);
	DeleteObject(hMsk);
	DeleteDC(hdc_msk);
	DeleteObject(hBmp);
	DeleteDC(hdc_bmp);
	PostQuitMessage(0);
}
void D2Image::init(HWND _hWnd, string imagePath, int x, int y){
	/*ディスプレイサイズ*/
	SCREEN_WIDTH = x;
	SCREEN_HEIGHT = y;
	/*画像の読み込み*/
	hWnd = _hWnd;
	hdc = GetDC(hWnd);
	hBmp = (HBITMAP)LoadImage(
		NULL,//インスタンスハンドル
		TEXT(imagePath.c_str()),//イメージの名前
		IMAGE_BITMAP,//イメージタイプ
		0,//幅
		0,//高さ
		LR_LOADFROMFILE);//ロードオプション
	if( hBmp == NULL )
	{
		MessageBox(
			NULL, TEXT("ビットマップのロードに失敗しました"), TEXT("エラー"),
			MB_OK | MB_ICONWARNING
		);
	}
	GetObject(hBmp, (int)sizeof(bmp_info), &bmp_info);
	bmpw = bmp_info.bmWidth;
	bmph = bmp_info.bmHeight;
	hdc_bmp = CreateCompatibleDC(hdc);//互換性のあるDCを取得
	SelectObject(hdc_bmp, hBmp);//MDCにビットマップをセット
	SetBkColor(hdc_bmp, (COLORREF)RGB(255, 0, 255));//背景色を設定
	SetTextColor(hdc_bmp , (COLORREF)RGB(0, 0, 0));//文字色を黒に設定

	/*仮想デバイスコンテキスト*/
	hdc_mem = CreateCompatibleDC(hdc);//互換性のあるDCを取得
	hMem = CreateCompatibleBitmap(hdc_bmp, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//ビットマップを作成
	SelectObject(hdc_mem, hMem);//MDCにビットマップをセット
	SetBkColor(hdc_mem, (COLORREF)RGB(255, 0, 255));//背景色を設定
	SetTextColor(hdc_mem , (COLORREF)RGB(0, 0, 0));//文字色を黒に設定

	/*マスク画像*/
	hdc_msk = CreateCompatibleDC(hdc);//互換性のあるDCを取得
	hMsk = CreateCompatibleBitmap(hdc_msk, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//ビットマップを作成
	SelectObject(hdc_msk, hMsk);//MDCにビットマップをセット
	SetBkColor(hdc_msk, (COLORREF)RGB(255, 0, 255));//背景色を設定
	SetTextColor(hdc_msk, (COLORREF)RGB(0, 0, 0));//文字色を黒に設定
	/*白黒ビットマップにする　透過部分:白*/
	BitBlt(hdc_msk, //転送先
		0, 0, //転送先座標
		bmpw, bmph, //幅と高さ
		hdc_bmp, //転送元
		0, 0, //転送元座標
		SRCCOPY);//ラスタオペレーション

	/*作業用画像*/
	hdc_tmp = CreateCompatibleDC(hdc);//互換性のあるDCを取得
	hTmp = CreateCompatibleBitmap(hdc_tmp, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//ビットマップを作成
	SelectObject(hdc_tmp, hTmp);//MDCにビットマップをセット
	SetBkColor(hdc_tmp, (COLORREF)RGB(255, 0, 255));//背景色を設定
	SetTextColor(hdc_tmp , (COLORREF)RGB(0, 0, 0));//文字色を黒に設定
	/*マスク画像の白黒反転を作成*/
	BitBlt(hdc_tmp, //転送先
		0, 0, //転送先座標
		bmpw, bmph, //幅と高さ
		hdc_msk, //転送元
		0, 0, //転送元座標
		NOTSRCCOPY);//ラスタオペレーション
	
	/*作業用画像1*/
	hdc_wk1 = CreateCompatibleDC(hdc);//互換性のあるDCを取得
	hWk1 = CreateCompatibleBitmap(hdc, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//ビットマップを作成
	SelectObject(hdc_wk1, hWk1);//MDCにビットマップをセット
	SetBkColor(hdc_wk1, (COLORREF)RGB(255, 0, 255));//背景色を設定
	SetTextColor(hdc_wk1, (COLORREF)RGB(0, 0, 0));//文字色を黒に設定
	
	/*作業用画像2*/
	hdc_wk2 = CreateCompatibleDC(hdc);//互換性のあるDCを取得
	hWk2 = CreateCompatibleBitmap(hdc, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//ビットマップを作成
	SelectObject(hdc_wk2, hWk2);//MDCにビットマップをセット
	SetBkColor(hdc_wk2, (COLORREF)RGB(255, 0, 255));//背景色を設定
	SetTextColor(hdc_wk2, (COLORREF)RGB(0, 0, 0));//文字色を黒に設定


	SetBkColor(hdc_bmp, (COLORREF)RGB(0xff, 0xff, 0xff));//背景色を設定
	SetBkColor(hdc_msk, (COLORREF)RGB(0xff, 0xff, 0xff));//背景色を設定
	SetBkColor(hdc_tmp, (COLORREF)RGB(0xff, 0xff, 0xff));//背景色を設定
	SetBkColor(hdc_mem, (COLORREF)RGB(0xff, 0xff, 0xff));//背景色を設定
	SetBkColor(hdc_wk1, (COLORREF)RGB(0xff, 0xff, 0xff));//背景色を設定
	SetBkColor(hdc_wk2, (COLORREF)RGB(0xff, 0xff, 0xff));//背景色を設定
	SetTextColor(hdc_bmp, (COLORREF)RGB(0, 0, 0));//テキスト色を設定
	SetTextColor(hdc_msk, (COLORREF)RGB(0, 0, 0));//テキスト色を設定
	SetTextColor(hdc_tmp, (COLORREF)RGB(0, 0, 0));//テキスト色を設定
	SetTextColor(hdc_mem, (COLORREF)RGB(0, 0, 0));//テキスト色を設定
	SetTextColor(hdc_wk1, (COLORREF)RGB(0, 0, 0));//テキスト色を設定
	SetTextColor(hdc_wk2, (COLORREF)RGB(0, 0, 0));//テキスト色を設定

	/*元画像の加工　透過部分：黒*/
	BitBlt(hdc_bmp, //転送先
		0, 0, //転送先座標
		bmpw, bmph, //幅と高さ
		hdc_tmp, //転送元
		0, 0, //転送元座標
		SRCAND);//ラスタオペレーション


	ReleaseDC(hWnd, hdc);

}
void D2Image::memToDis(){
	hdc = GetDC(hWnd);
	/*仮想画面をディスプレイへ転送*/
	BitBlt(hdc, //転送先
		0, 0, //転送先座標
		bmpw, bmph, //幅と高さ
		hdc_mem, //転送元
		0, 0, //転送元座標
		SRCCOPY);//ラスタオペレーション
	ReleaseDC(hWnd, hdc);
}
void D2Image::bmpToMem(){//拡大なし

	/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
	BitBlt(hdc_mem, //転送先
		0, 0, //転送先座標
		bmpw, bmph, //幅と高さ
		hdc_msk, //転送元
		0, 0, //転送元座標
		SRCAND);//ラスタオペレーション
	
	/*元画像と仮想画面をOR*/
	BitBlt(hdc_mem, //転送先
		0, 0, //転送先座標
		bmpw, bmph, //転送先幅と高さ
		hdc_bmp, //転送元
		0, 0, //転送元座標
		SRCPAINT);//ラスタオペレーション
}
void D2Image::bmpToMem(int tox, int toy, int tow, int toh, int fromx, int fromy){//拡大なし

	/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
	BitBlt(hdc_mem, //転送先
		tox, toy, //転送先座標
		tow, toh, //幅と高さ
		hdc_msk, //転送元
		fromx, fromy, //転送元座標
		SRCAND);//ラスタオペレーション
	
	/*元画像と仮想画面をOR*/
	BitBlt(hdc_mem, //転送先
		tox, toy, //転送先座標
		tow, toh, //転送先幅と高さ
		hdc_bmp, //転送元
		fromx, fromy, //転送元座標
		SRCPAINT);//ラスタオペレーション
}
void D2Image::bmpToMem(int tox, int toy, int tow, int toh, 
					   int fromx, int fromy, int fromw, int fromh){//拡大ありコピー

	/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
	StretchBlt(hdc_mem, //転送先
		tox, toy, //転送先座標
		tow, toh, //幅と高さ
		hdc_msk, //転送元
		fromx, fromy, //転送元座標
		fromw, fromh,//転送元幅と高さ
		SRCAND);//ラスタオペレーション
	
	/*元画像と仮想画面をOR*/
	StretchBlt(hdc_mem, //転送先
		tox, toy, //転送先座標
		tow, toh, //転送先幅と高さ
		hdc_bmp, //転送元
		fromx, fromy, //転送元座標
		fromw, fromh,//転送元幅と高さ
		SRCPAINT);//ラスタオペレーション
}
void D2Image::bmpToMem(int tocenterx, int tocentery, int tow, int toh, 
					   int fromx, int fromy, int fromw, int fromh,
					   int fromcenterx, int fromcentery, double angle){//回転拡大ありコピー

	/*回転なしの場合そのまま出力*/
	if(angle <= 2.0*PI/80.0 && angle >= -2.0*PI/80.0){
		bmpToMem(
			tocenterx - tow/2, 
			tocentery - toh/2, 
			tow, toh, 
			fromx, fromy, fromw, fromh
			);
		return;
	}

	/*回転前頂点の算出*/
	POINT pt[3];
	POINT pt2[3];
	int offsetx, offsety;
	pt[0].x = fromcenterx - fromw/2;//左上x 
	pt[0].y = fromcentery - fromh/2;//左上y
	pt[1].x = fromcenterx - fromw/2 + fromw;//右上x
	pt[1].y = fromcentery - fromh/2;//右上y
	pt[2].x = fromcenterx - fromw/2;//左下x 
	pt[2].y = fromcentery - fromh/2 + fromh;//左下y
	/*原点へオフセット移動*/
	offsetx = pt[0].x;
	offsety = pt[0].y;
	pt[0].x -= offsetx;//左上x 
	pt[0].y -= offsety;//左上y
	pt[1].x -= offsetx;//右上x
	pt[1].y -= offsety;//右上y
	pt[2].x -= offsetx;//左下x 
	pt[2].y -= offsety;//左下y
	/*拡大*/
	pt[1].x *= (LONG)((double)tow / (double)fromw);//右上x
	pt[2].y *= (LONG)((double)toh / (double)fromh);//左下y
	//縮小などの際にうまく出力できないバグあり？
	/*オフセット戻し*/
	offsetx = tocenterx - tow/2;
	offsety = tocentery - toh/2;
	pt[0].x += offsetx;//左上x 
	pt[0].y += offsety;//左上y
	pt[1].x += offsetx;//右上x
	pt[1].y += offsety;//右上y
	pt[2].x += offsetx;//左下x 
	pt[2].y += offsety;//左下y
	/*原点へオフセット移動*/
	pt[0].x -= tocenterx;
	pt[0].y -= tocentery;
	pt[1].x -= tocenterx;
	pt[1].y -= tocentery;
	pt[2].x -= tocenterx;
	pt[2].y -= tocentery;
	/*回転行列の適用*/
	pt2[0].x = (LONG)(pt[0].x * cos(angle) - pt[0].y * sin(angle));
	pt2[0].y = (LONG)(pt[0].x * sin(angle) + pt[0].y * cos(angle));
	pt2[1].x = (LONG)(pt[1].x * cos(angle) - pt[1].y * sin(angle));
	pt2[1].y = (LONG)(pt[1].x * sin(angle) + pt[1].y * cos(angle));
	pt2[2].x = (LONG)(pt[2].x * cos(angle) - pt[2].y * sin(angle));
	pt2[2].y = (LONG)(pt[2].x * sin(angle) + pt[2].y * cos(angle));
	/*原点からオフセット移動*/
	pt2[0].x += tocenterx;
	pt2[0].y += tocentery;
	pt2[1].x += tocenterx;
	pt2[1].y += tocentery;
	pt2[2].x += tocenterx;
	pt2[2].y += tocentery;

	/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
	PlgBlt(hdc_mem, //転送先
		pt2,//転送先３頂点情報
		hdc_bmp, //転送元
		fromx, fromy, //転送元座標
		fromw, fromh,//転送元幅と高さ
		hTmp, //転送元
		fromx, fromy //転送元座標
		);
	
}
void D2Image::bmpToMem(int tox, int toy, int tow, int toh, 
					   int fromx, int fromy, int fromw, int fromh,
					   int alpha){//透過拡大ありコピー

	/*アルファ合成構造体作成*/
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;		//固定
	bf.BlendFlags = 0;				//固定
	bf.SourceConstantAlpha = alpha;	//アルファブレンド値
	bf.AlphaFormat = 0;				//固定

	/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
	AlphaBlend(hdc_mem, //転送先
		tox, toy, tow, toh, //転送先x, 転送先y, 転送幅, 転送高, 
		hdc_bmp, //転送元
		fromx, fromy, //転送元座標
		fromw, fromh,//転送元幅と高さ
		bf);
	
}
void D2Image::textToMem(int x, int y, const char* text,COLORREF color){
	SetTextColor(hdc_mem, color);//テキスト色を設定
	SetBkMode(hdc_mem, TRANSPARENT); //背景透過
	TextOut(hdc_mem, 
		x,
		y,
		(LPCTSTR)text,
		strlen(text));
	SetTextColor(hdc_mem, (COLORREF)RGB(0, 0, 0));//テキスト色を設定


}
void D2Image::mem2Mem(int tono, int tox, int toy, int tow, int toh, 
					   int fromno, int fromx, int fromy, int fromw, int fromh, int alpha){//拡大ありコピー（面指定）
	
	/*出力面の選択*/
	HDC hdc_to;
	switch(tono){
	case xBMP://ビットマップ
		hdc_to = hdc_bmp;
		break;
	case xMEM://仮想画面
		hdc_to = hdc_mem;
		break;
	case xMSK://マスク画像（透過部分：白）
		hdc_to = hdc_msk;
		break;
	case xTMP://マスク画像（透過部分：黒）
		hdc_to = hdc_tmp;
		break;
	case xWK1://作業画面１
		hdc_to = hdc_wk1;
		break;
	case xWK2://作業画面２
		hdc_to = hdc_wk2;
		break;
	default:
		hdc_to = hdc_mem;
		break;
	}

	/*入力面の選択*/
	HDC hdc_from;
	switch(fromno){
	case xBMP://ビットマップ
		hdc_from = hdc_bmp;
		break;
	case xMEM://仮想画面
		hdc_from = hdc_mem;
		break;
	case xMSK://マスク画像（透過部分：白）
		hdc_from = hdc_msk;
		break;
	case xTMP://マスク画像（透過部分：黒）
		hdc_from = hdc_tmp;
		break;
	case xWK1://作業画面１
		hdc_from = hdc_wk1;
		break;
	case xWK2://作業画面２
		hdc_from = hdc_wk2;
		break;
	default:
		hdc_from = hdc_bmp;
		break;
	}

	//透過転送のみ
	if(alpha >= 255){
		
		TransparentBlt(hdc_to, //転送先
			tox, toy, //転送先座標
			tow, toh, //転送先幅と高さ
			hdc_from, //転送元
			fromx, fromy, //転送元座標
			fromw, fromh,//転送元幅と高さ
			RGB(0,0,0));//透過色

	}
	//半透明転送　（透過色なし）
	else if(alpha > 0){
		/*アルファ合成構造体作成*/
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;		//固定
		bf.BlendFlags = 0;				//固定
		bf.SourceConstantAlpha = alpha;	//アルファブレンド値
		bf.AlphaFormat = 0;				//固定

		/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
		AlphaBlend(hdc_to, //転送先
			tox, toy, tow, toh, //転送先x, 転送先y, 転送幅, 転送高, 
			hdc_from, //転送元
			fromx, fromy, //転送元座標
			fromw, fromh,//転送元幅と高さ
			bf);
	}
	else if(alpha == 0){
		//転送無し
	}
	else if(alpha == xCOPY){//コピー
		StretchBlt(hdc_to, //転送先
			tox, toy, //転送先座標
			tow, toh, //幅と高さ
			hdc_from, //転送元
			fromx, fromy, //転送元座標
			fromw, fromh,//転送元幅と高さ
			SRCCOPY);//ラスタオペレーション
	}
	else if(alpha == xTRANS){//透過コピー
		/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
		StretchBlt(hdc_to, //転送先
			tox, toy, //転送先座標
			tow, toh, //幅と高さ
			hdc_msk, //転送元
			fromx, fromy, //転送元座標
			fromw, fromh,//転送元幅と高さ
			SRCAND);//ラスタオペレーション
	
		/*元画像と仮想画面をOR*/
		StretchBlt(hdc_to, //転送先
			tox, toy, //転送先座標
			tow, toh, //転送先幅と高さ
			hdc_from, //転送元
			fromx, fromy, //転送元座標
			fromw, fromh,//転送元幅と高さ
			SRCPAINT);//ラスタオペレーション
	}
	else if(alpha == xAND){//AND転送
		/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
		StretchBlt(hdc_to, //転送先
			tox, toy, //転送先座標
			tow, toh, //幅と高さ
			hdc_from, //転送元
			fromx, fromy, //転送元座標
			fromw, fromh,//転送元幅と高さ
			SRCAND);//ラスタオペレーション
	}
	else if(alpha == xOR){//AND転送
		/*元画像と仮想画面をOR*/
		StretchBlt(hdc_to, //転送先
			tox, toy, //転送先座標
			tow, toh, //転送先幅と高さ
			hdc_from, //転送元
			fromx, fromy, //転送元座標
			fromw, fromh,//転送元幅と高さ
			SRCPAINT);//ラスタオペレーション
	}
}
void D2Image::mem2Mem(int tono, int tocenterx, int tocentery, int tow, int toh, 
					   int fromno, int fromx, int fromy, int fromw, int fromh,
					   int fromcenterx, int fromcentery, double angle){//回転拡大ありコピー

	/*出力面の選択*/
	HDC hdc_to;
	switch(tono){
	case xBMP://ビットマップ
		hdc_to = hdc_bmp;
		break;
	case xMEM://仮想画面
		hdc_to = hdc_mem;
		break;
	case xMSK://マスク画像（透過部分：白）
		hdc_to = hdc_msk;
		break;
	case xTMP://マスク画像（透過部分：黒）
		hdc_to = hdc_tmp;
		break;
	case xWK1://作業画面１
		hdc_to = hdc_wk1;
		break;
	case xWK2://作業画面２
		hdc_to = hdc_wk2;
		break;
	default:
		hdc_to = hdc_mem;
		break;
	}

	/*入力面の選択*/
	HDC hdc_from;
	switch(fromno){
	case xBMP://ビットマップ
		hdc_from = hdc_bmp;
		break;
	case xMEM://仮想画面
		hdc_from = hdc_mem;
		break;
	case xMSK://マスク画像（透過部分：白）
		hdc_from = hdc_msk;
		break;
	case xTMP://マスク画像（透過部分：黒）
		hdc_from = hdc_tmp;
		break;
	case xWK1://作業画面１
		hdc_from = hdc_wk1;
		break;
	case xWK2://作業画面２
		hdc_from = hdc_wk2;
		break;
	default:
		hdc_from = hdc_bmp;
		break;
	}
	/*回転なしの場合そのまま出力*/
	if(angle <= 2.0*PI/80.0 && angle >= -2.0*PI/80.0){
		mem2Mem(
			tono,tocenterx - tow/2, 
			tocentery - toh/2, 
			tow, toh, 
			fromno, fromx, fromy, fromw, fromh,
			xTRANS
			);
		return;
	}

	/*回転前頂点の算出*/
	POINT pt[3];
	POINT pt2[3];
	int offsetx, offsety;
	pt[0].x = fromcenterx - fromw/2;//左上x 
	pt[0].y = fromcentery - fromh/2;//左上y
	pt[1].x = fromcenterx - fromw/2 + fromw;//右上x
	pt[1].y = fromcentery - fromh/2;//右上y
	pt[2].x = fromcenterx - fromw/2;//左下x 
	pt[2].y = fromcentery - fromh/2 + fromh;//左下y
	/*原点へオフセット移動*/
	offsetx = pt[0].x;
	offsety = pt[0].y;
	pt[0].x -= offsetx;//左上x 
	pt[0].y -= offsety;//左上y
	pt[1].x -= offsetx;//右上x
	pt[1].y -= offsety;//右上y
	pt[2].x -= offsetx;//左下x 
	pt[2].y -= offsety;//左下y
	/*拡大*/
	pt[1].x *= (LONG)((double)tow / (double)fromw);//右上x
	pt[2].y *= (LONG)((double)toh / (double)fromh);//左下y
	/*オフセット戻し*/
	offsetx = tocenterx - tow/2;
	offsety = tocentery - toh/2;
	pt[0].x += offsetx;//左上x 
	pt[0].y += offsety;//左上y
	pt[1].x += offsetx;//右上x
	pt[1].y += offsety;//右上y
	pt[2].x += offsetx;//左下x 
	pt[2].y += offsety;//左下y
	/*原点へオフセット移動*/
	pt[0].x -= tocenterx;
	pt[0].y -= tocentery;
	pt[1].x -= tocenterx;
	pt[1].y -= tocentery;
	pt[2].x -= tocenterx;
	pt[2].y -= tocentery;
	/*回転行列の適用*/
	pt2[0].x = (LONG)(pt[0].x * cos(angle) - pt[0].y * sin(angle));
	pt2[0].y = (LONG)(pt[0].x * sin(angle) + pt[0].y * cos(angle));
	pt2[1].x = (LONG)(pt[1].x * cos(angle) - pt[1].y * sin(angle));
	pt2[1].y = (LONG)(pt[1].x * sin(angle) + pt[1].y * cos(angle));
	pt2[2].x = (LONG)(pt[2].x * cos(angle) - pt[2].y * sin(angle));
	pt2[2].y = (LONG)(pt[2].x * sin(angle) + pt[2].y * cos(angle));
	/*原点からオフセット移動*/
	pt2[0].x += tocenterx;
	pt2[0].y += tocentery;
	pt2[1].x += tocenterx;
	pt2[1].y += tocentery;
	pt2[2].x += tocenterx;
	pt2[2].y += tocentery;

	/*マスク画像と仮想画面をAND　転送したい画像部分：黒*/
	PlgBlt(hdc_to, //転送先
		pt2,//転送先３頂点情報
		hdc_from, //転送元　！ｂｍｐ固定！
		fromx, fromy, //転送元座標
		fromw, fromh,//転送元幅と高さ
		hTmp, //転送元マスク　！固定！
		fromx, fromy //転送元座標
		);
	
}

} //namespace tm2