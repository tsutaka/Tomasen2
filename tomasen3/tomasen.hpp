#ifndef INCLUDED_TOMASEN_HPP
#define INCLUDED_TOMASEN_HPP

#include <windows.h>				//HWND

#include "tiptile.hpp"				//�摜�`��
#include "drawtext.hpp"				//�摜�`��
#include "music.hpp"				//�y�ȍĐ�
#include "common.hpp"				//����
#include "localcommon.hpp"			//���[�J������
#include "object.hpp"				//�I�u�W�F�N�g�S��

#include "obj_wing.hpp"				//�@��
#include "obj_parts.hpp"			//�p�[�c
#include "obj_item.hpp"				//�A�C�e��
#include "obj_effect.hpp"			//�G�t�F�N�g
#include "obj_bullet.hpp"			//�e
#include "obj_print.hpp"			//�e
#include "event.hpp"				//�C�x���g�S��

#include "obj_parts_A.hpp"			//����
#include "obj_parts_B.hpp"			//�y��
#include "obj_wing_friend.hpp"		//���@
#include "obj_wing_enemy.hpp"		//�G�@

namespace tm2{

class Tomasen{
public:
	/*��Ɨp�N���X*/
	TipTile *IMAGE;
	Music *MUSIC;
	HWND hWnd;
	
public:
	/*�ϓ��p�����[�^*/
	int mode;							//���݂̉��
	int stage;							//���݃X�e�[�W
	int gold;							//GOLD
	int score;							//SCORE
	int hiscore;						//HISCORE
	char checktext[256];				//�ėp������
	bool canInput;						//���͉�
	int prevShot;						//�ˌ���ԋL��
	int shotPerm;						//�ˌ�����
	char inputLog[90000];					//�L�[���͎擾
	int bossFlag;						//�{�X�폜�t���O
	
	typedef vector< string > StringV;	//������z��
	
public:
	/*���\�[�X*/
	FriendWptr kosenWing;			//���@�ւ̎Q��
	BarWptr hpBar;					//HP�Q�[�W
	BarWptr energyBar;				//EN�Q�[�W
	BarWptr manBar;					//�l���Q�[�W
	BarWptr fireBar;				//���Q�[�W
	LabelWptr goldLabel;			//�S�[���h���x��
	LabelWptr scoreLabel;			//�X�R�A���x��
	LabelWptr hiscoreLabel;			//�X�R�A���x��
	LabelWptr resultManLabel;			//�����҃��x��
	LabelWptr resultScoreLabel;			//�g�[�^���X�R�A���x��
	
	int gameResult;					//�Q�[�����U���g�\�����F�P�A���U���g���F�Q
	int gameClear;					//�Q�[���N���A���F�P
	int gameRestart;				//�Q�[�����X�^�[�g���ɂP
	int gameEnd;					//�Q�[���I�����ɂP

	StringV stringV;				//�f�o�b�O�p������
		
	/*�R���X�g���N�^*/
	Tomasen();
	/*�f�X�g���N�^*/
	~Tomasen();

	/*�Q�[���{��*/
	void runGame(HWND);				//���C�����[�v
	
	

private:
	/*�������֐�*/
	void initGame();			//����������
	/*���͊֐�*/	
	void inputGame();			//���[�U���͎�t
	/*���`�B�֐�*/
	void communicationGame();	//�I�u�W�F�N�g�Ԃ̏�����
	/*�X�V�֐�*/
	void updateGame();			//�I�u�W�F�N�g�̍X�V
	/*�폜�֐�*/
	void deleteGame();			//�����蔻�蓙
	/*�\���֐�*/
	void printGame();			//��ʕ`�揈��


	/*���[�_�[�`��*/
	void drawRader();			//���[�_�[
};


} //namespace tm2
#endif//INCLUDED_TOMASEN_HPP