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
	/*�ϓ��p�����[�^*/
	string name;	//���O�@���������̓R���X�g���N�^
	double maxMove;	//�ő�ړ��ʁ@���������̓R���X�g���N�^
	double subMove;	//�����ړ��ʔ{���@���������̓R���X�g���N�^


public:

	/*���\�[�X���X�g*/
	PartsBWptr core;								//���@�̃R�A�p�[�c

	/*�R���X�g���N�^*/
	KosenWing(Tomasen& game);


	/*�X�V�֐�*/
	void update(Tomasen& game);



};



} //namespace tm2
#endif//INCLUDED_OBJ_WING_FRIEND_HPP