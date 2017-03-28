/************

	DrawText{
クラス
		（TipTile(image.hpp)クラスのラッパー）

	チップ単位での描画転送処理

************/

#ifndef INCLUDED_DRAWTEXT_HPP
#define INCLUDED_DRAWTEXT_HPP


/*************
教訓
・inline関数はヘッダファイルに定義も書かなくてはならない。
・他の関数は宣言のみヘッダファイルに書く。
*************/
#include <windows.h>
#include "common.hpp"
#include "tiptile.hpp"

namespace tm2{

/*TipTileのラッパークラス*/
class DrawTextImage{

private:
	//文字列行列
	vector<string> listText;

public:
	/*文章セット関数群*/
	inline void addText(string str);
	inline void clearText();
	
	/*文章描画関数群*/
	inline void draw(TipTile &IMAGE);

	/*更新関数*/
	

};
void DrawTextImage::addText(string str){
	listText.push_back(str);
}
void DrawTextImage::clearText(){
	listText.clear();
}
void DrawTextImage::draw(TipTile &IMAGE){
	//ワーク領域に文字列描画
	IMAGE.printText(400,100, "test");
	IMAGE.drawTile(Vec2(400.0,200.0),100, IMAGE.getWhite(),1);

	//仮想メモリに台形半透明転写
}

} //namespace tm2
#endif//INCLUDED_DRAWTEXT_HPP