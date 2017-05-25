#ifndef INCLUDED_COMMON_HPP
#define INCLUDED_COMMON_HPP

#pragma comment(lib, "winmm.lib") //タイマ

#include <windows.h>
#include <string>
#include <sstream>
#include <cassert>
#include <cmath>
#include <vector>

namespace tm2{

//処理時間計測用
extern DWORD baseTime;
extern DWORD checkTime[16];
void CheckTime(int num);
	
// std:: を省略できるように
using namespace std;

/*****************定数*****************/
const int SCREEN_WIDTH = 800;		// ウィンドウの幅
const int SCREEN_HEIGHT = 600;		// ウィンドウの高さ
const int SCREEN_INDENT = 200;		// 左右余白
const int tipSize = 16;				//チップのサイズ
extern double PI;

/*****************座標構造体*****************/
struct Vec2{
	double x;
	double y;
	Vec2();
	Vec2(double, double);
    const Vec2 operator+(const Vec2&) const;
    const Vec2 operator-(const Vec2&) const;
	Vec2& operator+=(const Vec2&);
    Vec2& operator-=(const Vec2&);
    Vec2& operator+(const int);
    Vec2& operator-(const int);
};


//待機関数
void await(DWORD);

//画面外判定関数
bool isIn(int left, int right, int top, int bottom, int x, int y);

//整数型から文字列型
template<typename T> string valToStr(T val)
{
	ostringstream temp; //書式指定しやすい文字列型
	temp << val;
	return temp.str();
}

//メッセージボクス関数
template<typename T> void mb(T val){
	MessageBox(NULL,valToStr(val).c_str(),"mb",MB_OK);
	return;
}
//メッセージボクス関数
template<typename T, typename T2> void mb(T val, T2 val2){
	MessageBox(NULL,valToStr(val).c_str(),valToStr(val2).c_str(),MB_OK);
	return;
}

//乱数生成関数
int makeRand(int upper);
int makeRand(int center, int difference);
double makeRand(double center, int difference);

//確率確認関数
bool perCheck(int percent);

//距離計算関数
double checkDistance(double ox, double oy, double x, double y);

//角度計算関数
double checkDirection(double ox, double oy, double x, double y);


} //namespace tm2
#endif//INCLUDED_COMMON_HPP