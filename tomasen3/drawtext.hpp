/************

	DrawText{
�N���X
		�iTipTile(image.hpp)�N���X�̃��b�p�[�j

	�`�b�v�P�ʂł̕`��]������

************/

#ifndef INCLUDED_DRAWTEXT_HPP
#define INCLUDED_DRAWTEXT_HPP


/*************
���P
�Einline�֐��̓w�b�_�t�@�C���ɒ�`�������Ȃ��Ă͂Ȃ�Ȃ��B
�E���̊֐��͐錾�̂݃w�b�_�t�@�C���ɏ����B
*************/
#include <windows.h>
#include "common.hpp"
#include "tiptile.hpp"

namespace tm2{

/*TipTile�̃��b�p�[�N���X*/
class DrawTextImage{

private:
	//������s��
	vector<string> listText;

public:
	/*���̓Z�b�g�֐��Q*/
	inline void addText(string str);
	inline void clearText();
	
	/*���͕`��֐��Q*/
	inline void draw(TipTile &IMAGE);

	/*�X�V�֐�*/
	

};
void DrawTextImage::addText(string str){
	listText.push_back(str);
}
void DrawTextImage::clearText(){
	listText.clear();
}
void DrawTextImage::draw(TipTile &IMAGE){
	//���[�N�̈�ɕ�����`��
	IMAGE.printText(400,100, "test");
	IMAGE.drawTile(Vec2(400.0,200.0),100, IMAGE.getWhite(),1);

	//���z�������ɑ�`�������]��
}

} //namespace tm2
#endif//INCLUDED_DRAWTEXT_HPP