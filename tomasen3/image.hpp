//D2Image�N���Xver1.1 2012/8/20
#ifndef INCLUDED_IMAGE_HPP
#define INCLUDED_IMAGE_HPP

#include <windows.h>
#include "common.hpp"
#include <string.h>


namespace tm2{

class D2Image
{
private:
	/*�f�B�X�v���C�T�C�Y*/
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	/*�]����f�B�X�v���C*/
	HWND hWnd;
	HDC hdc;
	/*�摜�p*/
	int bmpw, bmph;
	BITMAP bmp_info;
	HDC hdc_bmp;
	HBITMAP hBmp;
	/*�}�X�N�摜�p*/
	HDC hdc_msk;
	HBITMAP hMsk;
	/*�}�X�N���]�p*/
	HDC hdc_tmp;
	HBITMAP hTmp;
	/*���z���*/
	HDC hdc_mem;
	HBITMAP hMem;
	/*��Ɖ�ʂP*/
	HDC hdc_wk1;
	HBITMAP hWk1;
	/*��Ɖ�ʂQ*/
	HDC hdc_wk2;
	HBITMAP hWk2;
public:

	/*�萔*/
	static const int xBMP = 0;
	static const int xMEM = 1;
	static const int xMSK = 2;
	static const int xTMP = 3;
	static const int xWK1 = 4;
	static const int xWK2 = 5;
	static const int xCOPY = -1;
	static const int xTRANS = -2;
	static const int xAND = -3;
	static const int xOR = -4;
	/*�R���X�g���N�^*/
	D2Image();
	/*�f�X�g���N�^*/
	~D2Image();
	/*�w��r�b�g�}�b�v��ǂݍ���*/
	void init(HWND, string imagePath, int w, int h);				//�E�B���h�E�n���h��, �摜�p�X,WindowW,WindowH
	/*��������\��������*/
	void memToDis(void);							
	/*�r�b�g�}�b�v�S�̂�]��*/
	void bmpToMem();								
	/*�g��Ȃ��]��*/
	void bmpToMem(int,int,int,int,int,int);			//�]���悘,�]���悙,�摜��,�摜��,�]������,�]������
	/*�g�傠��]��*/
	void bmpToMem(int,int,int,int,int,int,int,int);	//�]���悘,�]���悙,�]����摜��,�]����摜��,�]������,�]������,�]�����摜��,�]����摜��
	/*��]�g�傠��]��*/
	void bmpToMem(int,int,int,int,int,int,int,int,int,int,double);	//�]���悘,�]���悙,�]����摜��,�]����摜��,�]������,�]������,�]�����摜��,�]����摜��,�]�������S��,�]�������Sy,��]�p�x
	/*���ߊg�傠��]��*/
	void bmpToMem(int,int,int,int,int,int,int,int,int);	//�]���悘,�]���悙,�]����摜��,�]����摜��,�]������,�]������,�]�����摜��,�]����摜��,�A���t�@�u�����h
	/*�����o��*/
	void textToMem(int, int, const char[], COLORREF);//�����o��
	/*�ʎw�蓧�ߊg�傠��]��*/
	void mem2Mem(int,int,int,int,int,int,int,int,int,int,int);	//�]����ʔԍ�,�]���悘,�]���悙,�]����摜��,�]����摜��,�]�����ʔԍ�,�]������,�]������,�]�����摜��,�]�����摜��,���ߓx
	/*�ʎw��g���]����]��*/
	void mem2Mem(int,int,int,int,int,int,int,int,int,int,int,int,double); //�]����ʔԍ�,�]���悘,�]���悙,�]����摜��,�]����摜��,�]�����ʔԍ�,�]������,�]������,�]�����摜��,�]�����摜��,�]�������S��,�]�������Sy,��]�p�x
private:
};




} //namespace tm2
#endif//INCLUDED_IMAGE_HPP