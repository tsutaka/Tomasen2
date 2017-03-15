#ifndef INCLUDED_OBJ_WING_FRIEND_HPP
#define INCLUDED_OBJ_WING_FRIEND_HPP


#include "common.hpp"
#include "object.hpp"
#include "event.hpp"


#include "obj_parts_A.hpp"
#include "obj_parts_B.hpp"
#include "obj_wing.hpp"

namespace tm2{

class KosenWing : public Friend{
public:
	/*変動パラメータ*/
	string name;	//名前　※初期化はコンストラクタ
	double maxMove;	//最大移動量　※初期化はコンストラクタ
	double subMove;	//減少移動量倍率　※初期化はコンストラクタ


public:

	/*リソースリスト*/
	PartsBWptr core;								//自機のコアパーツ

	/*コンストラクタ*/
	KosenWing(Tomasen& game);


	/*更新関数*/
	void update(Tomasen& game);



};



} //namespace tm2
#endif//INCLUDED_OBJ_WING_FRIEND_HPP