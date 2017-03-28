#ifndef INCLUDED_OBJ_PARTS_HPP
#define INCLUDED_OBJ_PARTS_HPP

#include <vector>		//vector
#include <memory>		//shared_ptr

#include "common.hpp"
#include "localcommon.hpp"
#include "object.hpp"

// std::tr1:: を std:: と書けるように
namespace std {
	using namespace tr1; 
}

namespace tm2{

class Parts : public Object{
protected:
	int energy;			//現在の弾数
	int chargeEnergy;	//給弾する弾数
	int maxEnergy;		//最大の弾数
	int man;			//現在の人員
	int requireMan;		//必要な人員
	int maxMan;			//最大の人員
	int fire;			//現在の火勢
	int burnFire;		//発火する火勢
	int maxFire;		//最大の火勢
	int kaihi;			//回避値

public:
	/*コンストラクタ*/
	Parts();
	/*getter関数*/
	int getEnergy(){return energy;}
	int getChargeEnergy(){return chargeEnergy;}
	int getMaxEnergy(){return maxEnergy;}
	int getMan(){return man;}
	int getRequireMan(){return requireMan;}
	int getMaxMan(){return maxMan;}
	int getFire(){return fire;}
	int getBurnFire(){return burnFire;}
	int getMaxFire(){return maxFire;}
	int getKaihi(){return kaihi;}
	/*getter関数*/
	void setKaihi(int kaihi){Parts::kaihi = kaihi;}
	/*add関数*/
	void addEnergy(int energy){Parts::energy += energy;}
	void addChargeEnergy(int chargeEnergy){Parts::chargeEnergy += chargeEnergy;}
	void addMaxEnergy(int maxEnergy){Parts::maxEnergy += maxEnergy;}
	void addMan(int man){Parts::man += man;}
	void addRequireMan(int requireMan){Parts::requireMan += requireMan;}
	void addMaxMan(int maxMan){Parts::maxMan += maxMan;}
	void addFire(int fire){Parts::fire += fire;}
	void addBurnFire(int burnFire){Parts::burnFire += burnFire;}
	void addMaxFire(int maxFire){Parts::maxFire += maxFire;}
	void addKaihi(int kaihi);
	
	/*更新関数*/
	virtual void update(Tomasen& game) = 0;
	/*描画関数*/
	virtual void draw(Tomasen& game) = 0;
	/*報告関数*/
	void tellUp(TellUpBox &box);
	virtual void subTellUp(TellUpBox &box) = 0;

	/*殺傷関数*/
	void killMan(int damage);
};


class PartsA : public Parts{
private:

public:
	/*コンストラクタ*/
	PartsA();
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);
	/*行動関数（各兵装固有処理）*/
	virtual void action(Tomasen& game);
	/*報告関数*/
	virtual void subTellUp(TellUpBox &box);
};

/*グローバルリソース宣言*/
typedef weak_ptr< PartsA > PartsAWptr;			//パーツのweakポインタ
typedef shared_ptr< PartsA > PartsASptr;		//パーツのsharedポインタ
typedef vector< PartsASptr > PartsAVsptr;		//パーツのsharedポインタの配列
extern PartsAVsptr partsAList;					//パーツリスト
PartsAWptr partsAFactory(PartsASptr partsAList);	//パーツファクトリ関数

class PartsB : public Parts{
protected:
	typedef weak_ptr< PartsA > PartsAWptr;		//パーツのweakポインタ
	typedef shared_ptr< PartsA > PartsASptr;	//パーツのsharedポインタ
	typedef vector< PartsASptr > PartsAVsptr;	//パーツのsharedポインタの配列
	weaponOK weapon[2];							//兵装有無
	int weaponPosX[2];							//兵装X座標（親からの相対）
	int weaponPosY[2];							//兵装Y座標（親からの相対）
	PartsAWptr partsA0;							//兵装オブジェクト
	PartsAWptr partsA1;							//兵装オブジェクト

	typedef weak_ptr< PartsB > PartsBWptr;		//パーツのweakポインタ
	typedef shared_ptr< PartsB > PartsBSptr;	//パーツのsharedポインタ
	typedef vector< PartsBSptr > PartsBVsptr;	//パーツのsharedポインタの配列
	jointOK joint[4];							//ジョイント有無
	int jointPosX[4];							//子のジョイントX座標（親からの相対）
	int jointPosY[4];							//子のジョイントY座標（親からの相対）
	PartsBWptr partsB0;							//ジョイントオブジェクト↑
	PartsBWptr partsB1;							//ジョイントオブジェクト→
	PartsBWptr partsB2;							//ジョイントオブジェクト↓
	PartsBWptr partsB3;							//ジョイントオブジェクト←
	int jointParent;							//親とのジョイント状態 1:接続あり

public:
	/*コンストラクタ*/
	PartsB();
	/*デストラクタ*/
	~PartsB();
	/*setter関数*/
	void setPartsA(weaponIndex pos, PartsAWptr partsA);
	void setPartsB(jointIndex pos, PartsBSptr partsB);
	void setWeapon(weaponIndex index, weaponOK val);
	void setJoint(jointIndex index, jointOK val);
	void setJointParent(int jointParent);
	/*getter関数*/
	PartsASptr getPartsA(weaponIndex index);
	PartsBSptr getPartsB(jointIndex index);
	int getJointParent(void);
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);
	/*報告関数*/
	void subTellUp(TellUpBox &box);
};

/*グローバルリソース宣言*/
typedef weak_ptr< PartsB > PartsBWptr;		//パーツのweakポインタ
typedef shared_ptr< PartsB > PartsBSptr;	//パーツのsharedポインタ
typedef vector< PartsBSptr > PartsBVsptr;	//パーツのsharedポインタの配列
extern PartsBVsptr partsBList;				//パーツリスト
PartsBWptr partsBFactory(PartsBSptr partsBList);	//パーツファクトリ関数
PartsBWptr partsSetFactory(PartsBSptr partsB, PartsBSptr newPartsB, PartsASptr newPartsA, jointIndex jointDir);


} //namespace tm2
#endif//INCLUDED_OBJ_PARTS_HPP