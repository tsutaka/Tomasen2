#ifndef INCLUDED_OBJ_ITEM_HPP
#define INCLUDED_OBJ_ITEM_HPP

#include "common.hpp"
#include "object.hpp"
#include "obj_parts.hpp"

namespace tm2{

class Item : public Object{
	/*�ϓ��p�����[�^*/
	Parts *parts;		//�p�[�c��
	
public:
	void update(Tomasen& game);		//�X�V�֐�
};



} //namespace tm2
#endif//INCLUDED_OBJ_ITEM_HPP