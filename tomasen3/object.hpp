#ifndef INCLUDED_OBJECT_HPP
#define INCLUDED_OBJECT_HPP


#include "common.hpp"

namespace tm2{
	
/*Tomasenの不完全型を定義*/
class Tomasen;

/*オブジェクトクラス*/
class Object {
protected:
	/*変動パラメータ*/
	int hp;					//耐久度
	Vec2 pos;				//位置
	Vec2 move;				//移動量
	double dis;				//移動量
	double dir;				//角度		0.0=水平右向き +方向=時計回り
	long frameCnt;			//生成後の経過フレーム数
	int animeCnt;			//現在のアニメフレーム
	string name;			//名称
	bool updateCheck;		//更新可否


	/*固定パラメータconst static */
	int maxHp;				//最大耐久度
	int imageX;				//画像x座標
	int imageY;				//画像y座標
	int imageW;				//画像幅
	int imageH;				//画像高
	int outputW;			//出力幅
	int outputH;			//出力高
	int animeMax;			//アニメーション枚数
	int animeWait;			//アニメーション１枚のフレーム数
	int size;				//virtual void Process
	int drawPriority;		//描画優先順位（0から先に描画）

	

public:
	/*getter関数*/
	int getHp(){ return hp; }
	Vec2 getPos(){ return pos; }
	Vec2 getMove(){ return move; }
	double getDis(){ return dis; }
	double getDir(){ return dir; }
	string getName(){ return name; }
	long getAnimeCnt(){ return animeCnt; }
	long getFrameCnt(){ return frameCnt; }
	int getMaxHp(){ return maxHp; }
	int getImageX(){ return imageX + animeCnt * imageW; }
	int getImageY(){ return imageY; }
	int getImageW(){ return imageW; }
	int getImageH(){ return imageH; }
	int getOutputW(){ return outputW; }
	int getOutputH(){ return outputH; }
	int getSize(){ return size; }
	int getDrawPriority(){ return drawPriority; }

	/*setter関数*/
	void setHp(int hp){ Object::hp = hp; }
	void setPos(Vec2 pos){ Object::pos = pos; }
	void setMove(Vec2 move){ Object::move = move; }
	void setDis(double dis){ Object::dis = dis; }
	void setDir(double dir){ Object::dir = dir; }
	void setName(string name){ Object::name = name; }
	void setFrameCnt(int frameCnt){ Object::frameCnt = frameCnt; }
	
	/*更新関数（仮想メソッド）*/
	virtual void update(Tomasen& game);
	/*更新関数（描画メソッド）*/
	virtual void draw(Tomasen& game);

	/*ダメージ関数*/
	void damageHp(int);
	/*中心取得*/
	Vec2 getCenterPos();
private:
};

} //namespace tm2
#endif//INCLUDED_OBJECT_HPP