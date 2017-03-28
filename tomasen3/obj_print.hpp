#ifndef INCLUDED_OBJ_PRINT_HPP
#define INCLUDED_OBJ_PRINT_HPP

#include <vector>		//vector
#include <memory>		//shared_ptr

#include "common.hpp"
#include "object.hpp"

// std::tr1:: を std:: と書けるように
namespace std {
	using namespace tr1; 
}



namespace tm2{

class Print : public Object{
protected:
	/*変動パラメータ*/
	int value;				//現在値
	int printValue;			//表示値

	/*固定パラメータ*/
	int maxValue;			//最大値
	int startValue;			//初期値

	int maxImageX;			//バー２画像x座標
	int maxImageY;			//バー２画像y座標
	int maxImageW;			//バー２画像幅
	int maxImageH;			//バー２画像高
	int underImageX;		//下地画像x座標
	int underImageY;		//下地画像y座標
	int underImageW;		//下地画像幅
	int underImageH;		//下地画像高
	int overImageX;			//上枠画像x座標
	int overImageY;			//上枠画像y座標
	int overImageW;			//上枠画像幅
	int overImageH;			//上枠画像高

public:
	/*コンストラクタ*/
	Print();
	/*setter関数*/
	void setValue(int value){ Print::value = value; }
	void setPrintValue(int printValue){ Print::printValue = printValue; }
	void setMaxValue(int maxValue){ Print::maxValue = maxValue; }
	void setStartValue(int startValue){ Print::startValue = startValue; }
	/*getter関数*/
	int getValue(){ return value; }
	int getPrintValue(){ return printValue; }
	int getMaxValue(){ return maxValue; }
	int getStartValue(){ return startValue; }
	int getMaxImageX(){ return maxImageX; }
	int getMaxImageY(){ return maxImageY; }
	int getMaxImageW(){ return maxImageW; }
	int getMaxImageH(){ return maxImageH; }
	int getUnderImageX(){ return underImageX + animeCnt * imageW; }
	int getUnderImageY(){ return underImageY; }
	int getUnderImageW(){ return underImageW; }
	int getUnderImageH(){ return underImageH; }
	int getOverImageX(){ return overImageX + animeCnt * imageW; }
	int getOverImageY(){ return overImageY; }
	int getOverImageW(){ return overImageW; }
	int getOverImageH(){ return overImageH; }
	
	/*更新関数*/
	virtual void update(Tomasen& game) = 0;
	/*描画関数*/
	virtual void draw(Tomasen& game) = 0;

};

class Bar : public Print{
public:
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);
};
/*グローバルリソース宣言*/
typedef weak_ptr< Bar > BarWptr;		//バーのweakポインタ
typedef shared_ptr< Bar > BarSptr;		//バーのsharedポインタ
typedef vector< BarSptr > BarVsptr;		//バーのsharedポインタの配列
extern BarVsptr barList;				//バーリスト
BarWptr barFactory(BarSptr barList);	//バーファクトリ関数

class Label : public Print{
public:
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);
};
/*グローバルリソース宣言*/
typedef weak_ptr< Label > LabelWptr;			//ラベルのweakポインタ
typedef shared_ptr< Label > LabelSptr;			//ラベルのsharedポインタ
typedef vector< LabelSptr > LabelVsptr;			//ラベルのsharedポインタの配列
extern LabelVsptr labelList;					//ラベルリスト
LabelWptr labelFactory(LabelSptr labelList);	//ラベルファクトリ関数


class HpBar : public Bar{
public:
	/*コンストラクタ*/
	HpBar();
};

class EnergyBar : public Bar{
public:
	/*コンストラクタ*/
	EnergyBar();
};

class ManBar : public Bar{
public:
	/*コンストラクタ*/
	ManBar();
};

class FireBar : public Bar{
public:
	/*コンストラクタ*/
	FireBar();
};

class GoldLabel : public Label{
public:
	/*コンストラクタ*/
	GoldLabel();
};

class ScoreLabel : public Label{
public:
	/*コンストラクタ*/
	ScoreLabel();
};

class HiScoreLabel : public Label{
public:
	/*コンストラクタ*/
	HiScoreLabel();
};

class ResultManLabel : public Label{
public:
	/*コンストラクタ*/
	ResultManLabel();

	void draw(Tomasen& game);
};

class ResultScoreLabel : public Label{
public:
	/*コンストラクタ*/
	ResultScoreLabel();
};

} //namespace tm2
#endif//INCLUDED_OBJ_PRINT_HPP