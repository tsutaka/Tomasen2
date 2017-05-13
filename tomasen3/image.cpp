#include "image.hpp"

namespace tm2{

D2Image::D2Image()
{
}
D2Image::~D2Image()
{
	DeleteObject(hMem);
	DeleteDC(hdc_mem);
	DeleteObject(hTmp);
	DeleteDC(hdc_tmp);
	DeleteObject(hWk1);
	DeleteDC(hdc_wk1);
	DeleteObject(hWk2);
	DeleteDC(hdc_wk2);
	DeleteObject(hMsk);
	DeleteDC(hdc_msk);
	DeleteObject(hBmp);
	DeleteDC(hdc_bmp);
	PostQuitMessage(0);
}
void D2Image::init(HWND _hWnd, string imagePath, int x, int y){
	/*�f�B�X�v���C�T�C�Y*/
	SCREEN_WIDTH = x;
	SCREEN_HEIGHT = y;
	/*�摜�̓ǂݍ���*/
	hWnd = _hWnd;
	hdc = GetDC(hWnd);
	hBmp = (HBITMAP)LoadImage(
		NULL,//�C���X�^���X�n���h��
		TEXT(imagePath.c_str()),//�C���[�W�̖��O
		IMAGE_BITMAP,//�C���[�W�^�C�v
		0,//��
		0,//����
		LR_LOADFROMFILE);//���[�h�I�v�V����
	if( hBmp == NULL )
	{
		MessageBox(
			NULL, TEXT("�r�b�g�}�b�v�̃��[�h�Ɏ��s���܂���"), TEXT("�G���["),
			MB_OK | MB_ICONWARNING
		);
	}
	GetObject(hBmp, (int)sizeof(bmp_info), &bmp_info);
	bmpw = bmp_info.bmWidth;
	bmph = bmp_info.bmHeight;
	hdc_bmp = CreateCompatibleDC(hdc);//�݊����̂���DC���擾
	SelectObject(hdc_bmp, hBmp);//MDC�Ƀr�b�g�}�b�v���Z�b�g
	SetBkColor(hdc_bmp, (COLORREF)RGB(255, 0, 255));//�w�i�F��ݒ�
	SetTextColor(hdc_bmp , (COLORREF)RGB(0, 0, 0));//�����F�����ɐݒ�

	/*���z�f�o�C�X�R���e�L�X�g*/
	hdc_mem = CreateCompatibleDC(hdc);//�݊����̂���DC���擾
	hMem = CreateCompatibleBitmap(hdc_bmp, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//�r�b�g�}�b�v���쐬
	SelectObject(hdc_mem, hMem);//MDC�Ƀr�b�g�}�b�v���Z�b�g
	SetBkColor(hdc_mem, (COLORREF)RGB(255, 0, 255));//�w�i�F��ݒ�
	SetTextColor(hdc_mem , (COLORREF)RGB(0, 0, 0));//�����F�����ɐݒ�

	/*�}�X�N�摜*/
	hdc_msk = CreateCompatibleDC(hdc);//�݊����̂���DC���擾
	hMsk = CreateCompatibleBitmap(hdc_msk, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//�r�b�g�}�b�v���쐬
	SelectObject(hdc_msk, hMsk);//MDC�Ƀr�b�g�}�b�v���Z�b�g
	SetBkColor(hdc_msk, (COLORREF)RGB(255, 0, 255));//�w�i�F��ݒ�
	SetTextColor(hdc_msk, (COLORREF)RGB(0, 0, 0));//�����F�����ɐݒ�
	/*�����r�b�g�}�b�v�ɂ���@���ߕ���:��*/
	BitBlt(hdc_msk, //�]����
		0, 0, //�]������W
		bmpw, bmph, //���ƍ���
		hdc_bmp, //�]����
		0, 0, //�]�������W
		SRCCOPY);//���X�^�I�y���[�V����

	/*��Ɨp�摜*/
	hdc_tmp = CreateCompatibleDC(hdc);//�݊����̂���DC���擾
	hTmp = CreateCompatibleBitmap(hdc_tmp, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//�r�b�g�}�b�v���쐬
	SelectObject(hdc_tmp, hTmp);//MDC�Ƀr�b�g�}�b�v���Z�b�g
	SetBkColor(hdc_tmp, (COLORREF)RGB(255, 0, 255));//�w�i�F��ݒ�
	SetTextColor(hdc_tmp , (COLORREF)RGB(0, 0, 0));//�����F�����ɐݒ�
	/*�}�X�N�摜�̔������]���쐬*/
	BitBlt(hdc_tmp, //�]����
		0, 0, //�]������W
		bmpw, bmph, //���ƍ���
		hdc_msk, //�]����
		0, 0, //�]�������W
		NOTSRCCOPY);//���X�^�I�y���[�V����
	
	/*��Ɨp�摜1*/
	hdc_wk1 = CreateCompatibleDC(hdc);//�݊����̂���DC���擾
	hWk1 = CreateCompatibleBitmap(hdc, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//�r�b�g�}�b�v���쐬
	SelectObject(hdc_wk1, hWk1);//MDC�Ƀr�b�g�}�b�v���Z�b�g
	SetBkColor(hdc_wk1, (COLORREF)RGB(255, 0, 255));//�w�i�F��ݒ�
	SetTextColor(hdc_wk1, (COLORREF)RGB(0, 0, 0));//�����F�����ɐݒ�
	
	/*��Ɨp�摜2*/
	hdc_wk2 = CreateCompatibleDC(hdc);//�݊����̂���DC���擾
	hWk2 = CreateCompatibleBitmap(hdc, 
		SCREEN_WIDTH, SCREEN_HEIGHT);//�r�b�g�}�b�v���쐬
	SelectObject(hdc_wk2, hWk2);//MDC�Ƀr�b�g�}�b�v���Z�b�g
	SetBkColor(hdc_wk2, (COLORREF)RGB(255, 0, 255));//�w�i�F��ݒ�
	SetTextColor(hdc_wk2, (COLORREF)RGB(0, 0, 0));//�����F�����ɐݒ�


	SetBkColor(hdc_bmp, (COLORREF)RGB(0xff, 0xff, 0xff));//�w�i�F��ݒ�
	SetBkColor(hdc_msk, (COLORREF)RGB(0xff, 0xff, 0xff));//�w�i�F��ݒ�
	SetBkColor(hdc_tmp, (COLORREF)RGB(0xff, 0xff, 0xff));//�w�i�F��ݒ�
	SetBkColor(hdc_mem, (COLORREF)RGB(0xff, 0xff, 0xff));//�w�i�F��ݒ�
	SetBkColor(hdc_wk1, (COLORREF)RGB(0xff, 0xff, 0xff));//�w�i�F��ݒ�
	SetBkColor(hdc_wk2, (COLORREF)RGB(0xff, 0xff, 0xff));//�w�i�F��ݒ�
	SetTextColor(hdc_bmp, (COLORREF)RGB(0, 0, 0));//�e�L�X�g�F��ݒ�
	SetTextColor(hdc_msk, (COLORREF)RGB(0, 0, 0));//�e�L�X�g�F��ݒ�
	SetTextColor(hdc_tmp, (COLORREF)RGB(0, 0, 0));//�e�L�X�g�F��ݒ�
	SetTextColor(hdc_mem, (COLORREF)RGB(0, 0, 0));//�e�L�X�g�F��ݒ�
	SetTextColor(hdc_wk1, (COLORREF)RGB(0, 0, 0));//�e�L�X�g�F��ݒ�
	SetTextColor(hdc_wk2, (COLORREF)RGB(0, 0, 0));//�e�L�X�g�F��ݒ�

	/*���摜�̉��H�@���ߕ����F��*/
	BitBlt(hdc_bmp, //�]����
		0, 0, //�]������W
		bmpw, bmph, //���ƍ���
		hdc_tmp, //�]����
		0, 0, //�]�������W
		SRCAND);//���X�^�I�y���[�V����


	ReleaseDC(hWnd, hdc);

}
void D2Image::memToDis(){
	hdc = GetDC(hWnd);
	/*���z��ʂ��f�B�X�v���C�֓]��*/
	BitBlt(hdc, //�]����
		0, 0, //�]������W
		bmpw, bmph, //���ƍ���
		hdc_mem, //�]����
		0, 0, //�]�������W
		SRCCOPY);//���X�^�I�y���[�V����
	ReleaseDC(hWnd, hdc);
}
void D2Image::bmpToMem(){//�g��Ȃ�

	/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
	BitBlt(hdc_mem, //�]����
		0, 0, //�]������W
		bmpw, bmph, //���ƍ���
		hdc_msk, //�]����
		0, 0, //�]�������W
		SRCAND);//���X�^�I�y���[�V����
	
	/*���摜�Ɖ��z��ʂ�OR*/
	BitBlt(hdc_mem, //�]����
		0, 0, //�]������W
		bmpw, bmph, //�]���敝�ƍ���
		hdc_bmp, //�]����
		0, 0, //�]�������W
		SRCPAINT);//���X�^�I�y���[�V����
}
void D2Image::bmpToMem(int tox, int toy, int tow, int toh, int fromx, int fromy){//�g��Ȃ�

	/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
	BitBlt(hdc_mem, //�]����
		tox, toy, //�]������W
		tow, toh, //���ƍ���
		hdc_msk, //�]����
		fromx, fromy, //�]�������W
		SRCAND);//���X�^�I�y���[�V����
	
	/*���摜�Ɖ��z��ʂ�OR*/
	BitBlt(hdc_mem, //�]����
		tox, toy, //�]������W
		tow, toh, //�]���敝�ƍ���
		hdc_bmp, //�]����
		fromx, fromy, //�]�������W
		SRCPAINT);//���X�^�I�y���[�V����
}
void D2Image::bmpToMem(int tox, int toy, int tow, int toh, 
					   int fromx, int fromy, int fromw, int fromh){//�g�傠��R�s�[

	/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
	StretchBlt(hdc_mem, //�]����
		tox, toy, //�]������W
		tow, toh, //���ƍ���
		hdc_msk, //�]����
		fromx, fromy, //�]�������W
		fromw, fromh,//�]�������ƍ���
		SRCAND);//���X�^�I�y���[�V����
	
	/*���摜�Ɖ��z��ʂ�OR*/
	StretchBlt(hdc_mem, //�]����
		tox, toy, //�]������W
		tow, toh, //�]���敝�ƍ���
		hdc_bmp, //�]����
		fromx, fromy, //�]�������W
		fromw, fromh,//�]�������ƍ���
		SRCPAINT);//���X�^�I�y���[�V����
}
void D2Image::bmpToMem(int tocenterx, int tocentery, int tow, int toh, 
					   int fromx, int fromy, int fromw, int fromh,
					   int fromcenterx, int fromcentery, double angle){//��]�g�傠��R�s�[

	/*��]�Ȃ��̏ꍇ���̂܂܏o��*/
	if(angle <= 2.0*PI/80.0 && angle >= -2.0*PI/80.0){
		bmpToMem(
			tocenterx - tow/2, 
			tocentery - toh/2, 
			tow, toh, 
			fromx, fromy, fromw, fromh
			);
		return;
	}

	/*��]�O���_�̎Z�o*/
	POINT pt[3];
	POINT pt2[3];
	int offsetx, offsety;
	pt[0].x = fromcenterx - fromw/2;//����x 
	pt[0].y = fromcentery - fromh/2;//����y
	pt[1].x = fromcenterx - fromw/2 + fromw;//�E��x
	pt[1].y = fromcentery - fromh/2;//�E��y
	pt[2].x = fromcenterx - fromw/2;//����x 
	pt[2].y = fromcentery - fromh/2 + fromh;//����y
	/*���_�փI�t�Z�b�g�ړ�*/
	offsetx = pt[0].x;
	offsety = pt[0].y;
	pt[0].x -= offsetx;//����x 
	pt[0].y -= offsety;//����y
	pt[1].x -= offsetx;//�E��x
	pt[1].y -= offsety;//�E��y
	pt[2].x -= offsetx;//����x 
	pt[2].y -= offsety;//����y
	/*�g��*/
	pt[1].x *= (LONG)((double)tow / (double)fromw);//�E��x
	pt[2].y *= (LONG)((double)toh / (double)fromh);//����y
	//�k���Ȃǂ̍ۂɂ��܂��o�͂ł��Ȃ��o�O����H
	/*�I�t�Z�b�g�߂�*/
	offsetx = tocenterx - tow/2;
	offsety = tocentery - toh/2;
	pt[0].x += offsetx;//����x 
	pt[0].y += offsety;//����y
	pt[1].x += offsetx;//�E��x
	pt[1].y += offsety;//�E��y
	pt[2].x += offsetx;//����x 
	pt[2].y += offsety;//����y
	/*���_�փI�t�Z�b�g�ړ�*/
	pt[0].x -= tocenterx;
	pt[0].y -= tocentery;
	pt[1].x -= tocenterx;
	pt[1].y -= tocentery;
	pt[2].x -= tocenterx;
	pt[2].y -= tocentery;
	/*��]�s��̓K�p*/
	pt2[0].x = (LONG)(pt[0].x * cos(angle) - pt[0].y * sin(angle));
	pt2[0].y = (LONG)(pt[0].x * sin(angle) + pt[0].y * cos(angle));
	pt2[1].x = (LONG)(pt[1].x * cos(angle) - pt[1].y * sin(angle));
	pt2[1].y = (LONG)(pt[1].x * sin(angle) + pt[1].y * cos(angle));
	pt2[2].x = (LONG)(pt[2].x * cos(angle) - pt[2].y * sin(angle));
	pt2[2].y = (LONG)(pt[2].x * sin(angle) + pt[2].y * cos(angle));
	/*���_����I�t�Z�b�g�ړ�*/
	pt2[0].x += tocenterx;
	pt2[0].y += tocentery;
	pt2[1].x += tocenterx;
	pt2[1].y += tocentery;
	pt2[2].x += tocenterx;
	pt2[2].y += tocentery;

	/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
	PlgBlt(hdc_mem, //�]����
		pt2,//�]����R���_���
		hdc_bmp, //�]����
		fromx, fromy, //�]�������W
		fromw, fromh,//�]�������ƍ���
		hTmp, //�]����
		fromx, fromy //�]�������W
		);
	
}
void D2Image::bmpToMem(int tox, int toy, int tow, int toh, 
					   int fromx, int fromy, int fromw, int fromh,
					   int alpha){//���ߊg�傠��R�s�[

	/*�A���t�@�����\���̍쐬*/
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;		//�Œ�
	bf.BlendFlags = 0;				//�Œ�
	bf.SourceConstantAlpha = alpha;	//�A���t�@�u�����h�l
	bf.AlphaFormat = 0;				//�Œ�

	/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
	AlphaBlend(hdc_mem, //�]����
		tox, toy, tow, toh, //�]����x, �]����y, �]����, �]����, 
		hdc_bmp, //�]����
		fromx, fromy, //�]�������W
		fromw, fromh,//�]�������ƍ���
		bf);
	
}
void D2Image::textToMem(int x, int y, const char* text,COLORREF color){
	SetTextColor(hdc_mem, color);//�e�L�X�g�F��ݒ�
	SetBkMode(hdc_mem, TRANSPARENT); //�w�i����
	TextOut(hdc_mem, 
		x,
		y,
		(LPCTSTR)text,
		strlen(text));
	SetTextColor(hdc_mem, (COLORREF)RGB(0, 0, 0));//�e�L�X�g�F��ݒ�


}
void D2Image::mem2Mem(int tono, int tox, int toy, int tow, int toh, 
					   int fromno, int fromx, int fromy, int fromw, int fromh, int alpha){//�g�傠��R�s�[�i�ʎw��j
	
	/*�o�͖ʂ̑I��*/
	HDC hdc_to;
	switch(tono){
	case xBMP://�r�b�g�}�b�v
		hdc_to = hdc_bmp;
		break;
	case xMEM://���z���
		hdc_to = hdc_mem;
		break;
	case xMSK://�}�X�N�摜�i���ߕ����F���j
		hdc_to = hdc_msk;
		break;
	case xTMP://�}�X�N�摜�i���ߕ����F���j
		hdc_to = hdc_tmp;
		break;
	case xWK1://��Ɖ�ʂP
		hdc_to = hdc_wk1;
		break;
	case xWK2://��Ɖ�ʂQ
		hdc_to = hdc_wk2;
		break;
	default:
		hdc_to = hdc_mem;
		break;
	}

	/*���͖ʂ̑I��*/
	HDC hdc_from;
	switch(fromno){
	case xBMP://�r�b�g�}�b�v
		hdc_from = hdc_bmp;
		break;
	case xMEM://���z���
		hdc_from = hdc_mem;
		break;
	case xMSK://�}�X�N�摜�i���ߕ����F���j
		hdc_from = hdc_msk;
		break;
	case xTMP://�}�X�N�摜�i���ߕ����F���j
		hdc_from = hdc_tmp;
		break;
	case xWK1://��Ɖ�ʂP
		hdc_from = hdc_wk1;
		break;
	case xWK2://��Ɖ�ʂQ
		hdc_from = hdc_wk2;
		break;
	default:
		hdc_from = hdc_bmp;
		break;
	}

	//���ߓ]���̂�
	if(alpha >= 255){
		
		TransparentBlt(hdc_to, //�]����
			tox, toy, //�]������W
			tow, toh, //�]���敝�ƍ���
			hdc_from, //�]����
			fromx, fromy, //�]�������W
			fromw, fromh,//�]�������ƍ���
			RGB(0,0,0));//���ߐF

	}
	//�������]���@�i���ߐF�Ȃ��j
	else if(alpha > 0){
		/*�A���t�@�����\���̍쐬*/
		BLENDFUNCTION bf;
		bf.BlendOp = AC_SRC_OVER;		//�Œ�
		bf.BlendFlags = 0;				//�Œ�
		bf.SourceConstantAlpha = alpha;	//�A���t�@�u�����h�l
		bf.AlphaFormat = 0;				//�Œ�

		/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
		AlphaBlend(hdc_to, //�]����
			tox, toy, tow, toh, //�]����x, �]����y, �]����, �]����, 
			hdc_from, //�]����
			fromx, fromy, //�]�������W
			fromw, fromh,//�]�������ƍ���
			bf);
	}
	else if(alpha == 0){
		//�]������
	}
	else if(alpha == xCOPY){//�R�s�[
		StretchBlt(hdc_to, //�]����
			tox, toy, //�]������W
			tow, toh, //���ƍ���
			hdc_from, //�]����
			fromx, fromy, //�]�������W
			fromw, fromh,//�]�������ƍ���
			SRCCOPY);//���X�^�I�y���[�V����
	}
	else if(alpha == xTRANS){//���߃R�s�[
		/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
		StretchBlt(hdc_to, //�]����
			tox, toy, //�]������W
			tow, toh, //���ƍ���
			hdc_msk, //�]����
			fromx, fromy, //�]�������W
			fromw, fromh,//�]�������ƍ���
			SRCAND);//���X�^�I�y���[�V����
	
		/*���摜�Ɖ��z��ʂ�OR*/
		StretchBlt(hdc_to, //�]����
			tox, toy, //�]������W
			tow, toh, //�]���敝�ƍ���
			hdc_from, //�]����
			fromx, fromy, //�]�������W
			fromw, fromh,//�]�������ƍ���
			SRCPAINT);//���X�^�I�y���[�V����
	}
	else if(alpha == xAND){//AND�]��
		/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
		StretchBlt(hdc_to, //�]����
			tox, toy, //�]������W
			tow, toh, //���ƍ���
			hdc_from, //�]����
			fromx, fromy, //�]�������W
			fromw, fromh,//�]�������ƍ���
			SRCAND);//���X�^�I�y���[�V����
	}
	else if(alpha == xOR){//AND�]��
		/*���摜�Ɖ��z��ʂ�OR*/
		StretchBlt(hdc_to, //�]����
			tox, toy, //�]������W
			tow, toh, //�]���敝�ƍ���
			hdc_from, //�]����
			fromx, fromy, //�]�������W
			fromw, fromh,//�]�������ƍ���
			SRCPAINT);//���X�^�I�y���[�V����
	}
}
void D2Image::mem2Mem(int tono, int tocenterx, int tocentery, int tow, int toh, 
					   int fromno, int fromx, int fromy, int fromw, int fromh,
					   int fromcenterx, int fromcentery, double angle){//��]�g�傠��R�s�[

	/*�o�͖ʂ̑I��*/
	HDC hdc_to;
	switch(tono){
	case xBMP://�r�b�g�}�b�v
		hdc_to = hdc_bmp;
		break;
	case xMEM://���z���
		hdc_to = hdc_mem;
		break;
	case xMSK://�}�X�N�摜�i���ߕ����F���j
		hdc_to = hdc_msk;
		break;
	case xTMP://�}�X�N�摜�i���ߕ����F���j
		hdc_to = hdc_tmp;
		break;
	case xWK1://��Ɖ�ʂP
		hdc_to = hdc_wk1;
		break;
	case xWK2://��Ɖ�ʂQ
		hdc_to = hdc_wk2;
		break;
	default:
		hdc_to = hdc_mem;
		break;
	}

	/*���͖ʂ̑I��*/
	HDC hdc_from;
	switch(fromno){
	case xBMP://�r�b�g�}�b�v
		hdc_from = hdc_bmp;
		break;
	case xMEM://���z���
		hdc_from = hdc_mem;
		break;
	case xMSK://�}�X�N�摜�i���ߕ����F���j
		hdc_from = hdc_msk;
		break;
	case xTMP://�}�X�N�摜�i���ߕ����F���j
		hdc_from = hdc_tmp;
		break;
	case xWK1://��Ɖ�ʂP
		hdc_from = hdc_wk1;
		break;
	case xWK2://��Ɖ�ʂQ
		hdc_from = hdc_wk2;
		break;
	default:
		hdc_from = hdc_bmp;
		break;
	}
	/*��]�Ȃ��̏ꍇ���̂܂܏o��*/
	if(angle <= 2.0*PI/80.0 && angle >= -2.0*PI/80.0){
		mem2Mem(
			tono,tocenterx - tow/2, 
			tocentery - toh/2, 
			tow, toh, 
			fromno, fromx, fromy, fromw, fromh,
			xTRANS
			);
		return;
	}

	/*��]�O���_�̎Z�o*/
	POINT pt[3];
	POINT pt2[3];
	int offsetx, offsety;
	pt[0].x = fromcenterx - fromw/2;//����x 
	pt[0].y = fromcentery - fromh/2;//����y
	pt[1].x = fromcenterx - fromw/2 + fromw;//�E��x
	pt[1].y = fromcentery - fromh/2;//�E��y
	pt[2].x = fromcenterx - fromw/2;//����x 
	pt[2].y = fromcentery - fromh/2 + fromh;//����y
	/*���_�փI�t�Z�b�g�ړ�*/
	offsetx = pt[0].x;
	offsety = pt[0].y;
	pt[0].x -= offsetx;//����x 
	pt[0].y -= offsety;//����y
	pt[1].x -= offsetx;//�E��x
	pt[1].y -= offsety;//�E��y
	pt[2].x -= offsetx;//����x 
	pt[2].y -= offsety;//����y
	/*�g��*/
	pt[1].x *= (LONG)((double)tow / (double)fromw);//�E��x
	pt[2].y *= (LONG)((double)toh / (double)fromh);//����y
	/*�I�t�Z�b�g�߂�*/
	offsetx = tocenterx - tow/2;
	offsety = tocentery - toh/2;
	pt[0].x += offsetx;//����x 
	pt[0].y += offsety;//����y
	pt[1].x += offsetx;//�E��x
	pt[1].y += offsety;//�E��y
	pt[2].x += offsetx;//����x 
	pt[2].y += offsety;//����y
	/*���_�փI�t�Z�b�g�ړ�*/
	pt[0].x -= tocenterx;
	pt[0].y -= tocentery;
	pt[1].x -= tocenterx;
	pt[1].y -= tocentery;
	pt[2].x -= tocenterx;
	pt[2].y -= tocentery;
	/*��]�s��̓K�p*/
	pt2[0].x = (LONG)(pt[0].x * cos(angle) - pt[0].y * sin(angle));
	pt2[0].y = (LONG)(pt[0].x * sin(angle) + pt[0].y * cos(angle));
	pt2[1].x = (LONG)(pt[1].x * cos(angle) - pt[1].y * sin(angle));
	pt2[1].y = (LONG)(pt[1].x * sin(angle) + pt[1].y * cos(angle));
	pt2[2].x = (LONG)(pt[2].x * cos(angle) - pt[2].y * sin(angle));
	pt2[2].y = (LONG)(pt[2].x * sin(angle) + pt[2].y * cos(angle));
	/*���_����I�t�Z�b�g�ړ�*/
	pt2[0].x += tocenterx;
	pt2[0].y += tocentery;
	pt2[1].x += tocenterx;
	pt2[1].y += tocentery;
	pt2[2].x += tocenterx;
	pt2[2].y += tocentery;

	/*�}�X�N�摜�Ɖ��z��ʂ�AND�@�]���������摜�����F��*/
	PlgBlt(hdc_to, //�]����
		pt2,//�]����R���_���
		hdc_from, //�]�����@�I�������Œ�I
		fromx, fromy, //�]�������W
		fromw, fromh,//�]�������ƍ���
		hTmp, //�]�����}�X�N�@�I�Œ�I
		fromx, fromy //�]�������W
		);
	
}

} //namespace tm2