#ifndef INCLUDED_OBJ_PARTS_A_HPP
#define INCLUDED_OBJ_PARTS_A_HPP

#include "common.hpp"
#include "obj_parts.hpp"

namespace tm2{

class EngineA : public PartsA{
private:

public:
	/*コンストラクタ*/
	EngineA();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
};

class CockpitA : public PartsA{
private:

public:
	/*コンストラクタ*/
	CockpitA();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
};

class MachineGunA : public PartsA{//上
private:
	int stopShot;
public:
	/*コンストラクタ*/
	MachineGunA();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
};

class MachineGunB : public PartsA{//右
private:
	int stopShot;
public:
	/*コンストラクタ*/
	MachineGunB();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
};

class MachineGunC : public PartsA{//下
private:
	int stopShot;
public:
	/*コンストラクタ*/
	MachineGunC();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
};

class MachineGunD : public PartsA{//左
private:
	int stopShot;
public:
	/*コンストラクタ*/
	MachineGunD();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
};

class SprinklerA : public PartsA{
private:
	int stopShot;
public:
	/*コンストラクタ*/
	SprinklerA();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
};

class SubCanonA : public PartsA{
private:
	int stopShot;				//射撃指示
	int targetShot;				//ターゲットを捕捉
	double targetX;				//ターゲットX座標
	double targetY;				//ターゲットY座標
	double targetDistance;		//ターゲット距離
	double targetDir;			//ターゲット角度
public:
	/*コンストラクタ*/
	SubCanonA();
	/*行動関数（各兵装固有処理）*/
	void update(Tomasen& game);
	/*描画関数（各兵装固有処理）*/
	void draw(Tomasen& game);
	/*setter関数*/
	void setTargetShot(int targetShot){ SubCanonA::targetShot = targetShot; }
	void setTargetX(double targetX){ SubCanonA::targetX = targetX; }
	void setTargetY(double targetY){ SubCanonA::targetY = targetY; }
	void setTargetDistance(double targetDistance){ SubCanonA::targetDistance = targetDistance; }
	double getTargetDir(void){ return targetDir; }
};

class HadohoA : public PartsA{
private:
	int stopShot;
public:
	/*コンストラクタ*/
	HadohoA();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
	/*描画関数（各兵装固有処理）*/
	void draw(Tomasen& game);
};

class HadohoB : public PartsA{
private:
	int stopShot;
public:
	/*コンストラクタ*/
	HadohoB();
	/*行動関数（各兵装固有処理）*/
	void action(Tomasen& game);
	/*描画関数（各兵装固有処理）*/
	void draw(Tomasen& game);
};
class LuncherR : public PartsA{
private:
	int stopShot;				//射撃指示
	int targetShot;				//ターゲットを捕捉
	double targetX;				//ターゲットX座標
	double targetY;				//ターゲットY座標
	double targetDistance;		//ターゲット距離
	double targetDir;			//ターゲット角度
	int kaiten;
public:
	/*コンストラクタ*/
	LuncherR();
	/*行動関数（各兵装固有処理）*/
	void update(Tomasen& game);
	/*描画関数（各兵装固有処理）*/
	void draw(Tomasen& game);
	/*setter関数*/
	void setTargetShot(int targetShot){ LuncherR::targetShot = targetShot; }
	void setTargetX(double targetX){ LuncherR::targetX = targetX; }
	void setTargetY(double targetY){ LuncherR::targetY = targetY; }
	void setTargetDistance(double targetDistance){ LuncherR::targetDistance = targetDistance; }
	double getTargetDir(void){ return targetDir; }
};
class LuncherL : public PartsA{
private:
	int stopShot;				//射撃指示
	int targetShot;				//ターゲットを捕捉
	double targetX;				//ターゲットX座標
	double targetY;				//ターゲットY座標
	double targetDistance;		//ターゲット距離
	double targetDir;			//ターゲット角度
	int kaiten;
public:
	/*コンストラクタ*/
	LuncherL();
	/*行動関数（各兵装固有処理）*/
	void update(Tomasen& game);
	/*描画関数（各兵装固有処理）*/
	void draw(Tomasen& game);
	/*setter関数*/
	void setTargetShot(int targetShot){ LuncherL::targetShot = targetShot; }
	void setTargetX(double targetX){ LuncherL::targetX = targetX; }
	void setTargetY(double targetY){ LuncherL::targetY = targetY; }
	void setTargetDistance(double targetDistance){ LuncherL::targetDistance = targetDistance; }
	double getTargetDir(void){ return targetDir; }
};

} //namespace tm2
#endif//INCLUDED_OBJ_PARTS_A_HPP