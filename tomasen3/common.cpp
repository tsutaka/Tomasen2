//common.cpp
//全プログラム共通の定数又は関数

#include <windows.h>

#include "common.hpp"

namespace tm2{

//処理時間計測用
DWORD baseTime = 0;
DWORD checkTime[16] = { 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };

/*処理時間計測関数*/
//前回呼び出されてからの時間をcheckTime[num]に返す
void CheckTime(int num) {
	if (num < 0 || num >= 16) {
		return;
	}
	checkTime[num] = timeGetTime() - baseTime;
	baseTime = timeGetTime();
}

/*int以外の定数*/
double PI = 3.1415926535;

/*座標構造体*/
Vec2::Vec2(){
	x = 0.0;
	y = 0.0;
}
Vec2::Vec2(double vecx, double vecy){
	x = vecx;
	y = vecy;
}
Vec2& Vec2::operator+=(const Vec2& pos) {
    this->x += pos.x;
    this->y += pos.y;
    return *this;
}
Vec2& Vec2::operator-=(const Vec2& pos) {
    this->x -= pos.x;
    this->y -= pos.y;
    return *this;
}
const Vec2 Vec2::operator+(const Vec2& pos) const {
    Vec2 result(*this);
    result += pos;
    return result;
}
Vec2& Vec2::operator+(const int val) {
    this->x += val;
    this->y += val;
    return *this;
}
const Vec2 Vec2::operator-(const Vec2& pos) const {
    Vec2 result(*this);
    result -= pos;
    return result;
}
Vec2& Vec2::operator-(const int val) {
    this->x -= val;
    this->y -= val;
    return *this;
}

//待機関数
void await(DWORD ms)
{
	static DWORD prevtime = 0;
	DWORD nowtime;
	LONG sleeptime;
	nowtime = timeGetTime();
	sleeptime = ms - (nowtime-prevtime);
	if ( sleeptime < 0 ) sleeptime = 0;
	Sleep(sleeptime);
	prevtime = timeGetTime();
	
}

//画面外判定関数
bool isIn(int left, int right, int top, int bottom, int x, int y){ //true:画面内
	if(y < top){			//上端越え消滅
		return false;
	}
	else if(y >= bottom){	//下端越え消滅
		return false;
	}
	else if(x < left){		//左端越え消滅
		return false;
	}
	else if(x >= right){	//右端越え消滅
		return false;
	}
	return true;
}

//乱数生成関数
int makeRand(int upper){
	return rand() % upper;
}
//乱数生成関数
int makeRand(int center, int difference){
	return center + rand() % ((difference * 2) + 1) - difference;
}
//乱数生成関数
double makeRand(double center, int difference){
	return center + rand() % ((difference * 2) + 1) - difference;
}
//確率確認関数
bool perCheck(int percent){
	return rand() % 100 < percent;
}

//距離計算関数
double checkDistance(double ox, double oy, double x, double y){
	double t, a;
	t = (ox - x) * (ox - x) + (oy - y) * (oy - y);
	//tの平方根計算
	a = t;
	if ( t <= 0 ) return 0;
	for(int n=1;n<=10;n++){
		t = (t + a / t) / 2;
	}

	return t; 
}

//角度計算関数
double checkDirection(double ox, double oy, double x, double y){
	return atan2(oy - y, ox - x);
}

} //namespace tm2