#ifndef INCLUDED_OBJ_ITEM_HPP
#define INCLUDED_OBJ_ITEM_HPP

#include "common.hpp"
#include "object.hpp"
#include "obj_parts.hpp"

namespace tm2{

class Item : public Object{
	/*変動パラメータ*/
	Parts *parts;		//パーツ名
	
public:
	void update(Tomasen& game);		//更新関数
};



} //namespace tm2
#endif//INCLUDED_OBJ_ITEM_HPP