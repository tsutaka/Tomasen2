
#include "tomasen.hpp"

#include "obj_print.hpp"

namespace tm2{

/*�O���[�o�����\�[�X��`*/
BarVsptr barList;					//�o�[���X�g
BarWptr barFactory(BarSptr bar){
		barList.push_back( bar );							//���X�g�ɃI�u�W�F�N�g�ǉ�
		BarVsptr::iterator it = barList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		return (*it);
}
LabelVsptr labelList;				//���x�����X�g
LabelWptr labelFactory(LabelSptr label){
		labelList.push_back( label );							//���X�g�ɃI�u�W�F�N�g�ǉ�
		LabelVsptr::iterator it = labelList.end() - 1;	//���O�̃I�u�W�F�N�g���Q��
		return (*it);
}

Print::Print(){
	value = 0;						//���ݒl	//���邢�\��
	printValue = 0;					//�\���l
	maxValue = 0;					//�ő�l	//���Â��\��
	startValue = 0;					//�����l	//�o�[�̉E�[
	frameCnt = 0;					//������̌o�߃t���[����
	animeCnt = 0;					//���݂̃A�j���t���[��
	animeMax = 4;					//�A�j���[�V��������
	animeWait = 4;					//�A�j���[�V�����P���̃t���[����
	maxImageW = 1;					//�摜�Qx���W
	maxImageH = 1;					//�摜�Qy���W
	underImageW = 1;				//���n�摜��
	underImageH = 1;				//���n�摜��
	overImageW = 1;					//��g�摜��
	overImageH = 1;					//��g�摜��
	imageW = 1;						//�摜��
	imageH = 1;						//�摜��
	outputW = 1;			//�o�͕�
	outputH = 1;			//�o�͍�
}

void Bar::update(Tomasen& game){
	/*���ݒl�̍X�V*/
	if(printValue - value > 10 || printValue - value < -10){
		printValue += (value - printValue) / 10;
	}
	else if(printValue < value){
		printValue++;
	}
	else if(printValue > value){
		printValue--;
	}
	/*�J�E���g�A�b�v*/
	frameCnt++;
	if(frameCnt > 50000) frameCnt = 0;
	if(frameCnt % animeWait == 0) animeCnt++;
	if(animeCnt >= animeMax) animeCnt = 0;
}
void Bar::draw(Tomasen& game){
	game.IMAGE->printText((int)getPos().x/tipSize - 2, 
		(int)getPos().y/tipSize, getName().c_str());
	game.IMAGE->drawFillTip(getPos(), 
		getSize(), 1, 
	game.IMAGE->tipNo(getUnderImageX(), getUnderImageY()) );		//���n
	if(getStartValue() > 0){											//�돜�Z�̉��
		game.IMAGE->drawTip(getPos().x, getPos().y, 
			(double)getSize() * tipSize * getMaxValue() / getStartValue(), 
			(double)1 * tipSize, 
			game.IMAGE->tipNo(getMaxImageX(), getMaxImageY()));	//���ő�o�[
		game.IMAGE->drawTip(getPos().x, getPos().y, 
			(double)getSize() * tipSize * getPrintValue() / getStartValue(), 
			(double)1 * tipSize, 
			game.IMAGE->tipNo(getImageX(), getImageY()));			//���ݒl�̃o�[
	}
	else{
		//mb("�ő�l���떔�͕��̐�");
	}
	game.IMAGE->drawFillTip(getPos(), 
		getSize(), 1, 
		game.IMAGE->tipNo(getOverImageX(), getOverImageY()) );		//��g
}

void Label::update(Tomasen& game){
	/*���ݒl�̍X�V*/
	if(printValue - value > 10 || printValue - value < -10){
		printValue += (value - printValue) / 10;
	}
	if(printValue  > value){
		printValue--;
	}
	else if(printValue < value){
		printValue++;
	}
}
void Label::draw(Tomasen& game){
	char checktext[256] = "";
	game.IMAGE->printText((int)getPos().x/tipSize, 
		(int)getPos().y/tipSize, 
		getName().c_str());
	sprintf_s(checktext, sizeof(checktext), "%08d", getPrintValue());
	game.IMAGE->printText((int)getPos().x/tipSize + 7, 
		(int)getPos().y/tipSize, 
		checktext);
}

HpBar::HpBar(){
	/*������*/
	pos = Vec2(40.0*tipSize, 5.0*tipSize);		//�ʒu
	name = "��";			//���O
	//�����l�ɂ��Ă͎��@�̃R���X�g���N�^�Őݒ�
	size = 10;				//�o�[�̕��i�����͂P�Œ�j
	imageX = 28;			//�摜x���W
	imageY = 16;			//�摜y���W
	maxImageX = 1;			//�摜�Qx���W
	maxImageY = 16;			//�摜�Qy���W
	underImageX = 24;		//���n�摜x���W
	underImageY = 17;		//���n�摜y���W
	overImageX = 24;		//��g�摜x���W
	overImageY = 16;		//��g�摜y���W
}

EnergyBar::EnergyBar(){
	/*������*/
	pos = Vec2(40.0*tipSize, 7.0*tipSize);		//�ʒu
	name = "�e";			//���O
	//�����l�ɂ��Ă͎��@�̃R���X�g���N�^�Őݒ�
	size = 10;				//�o�[�̕��i�����͂P�Œ�j
	imageX = 28;			//�摜x���W
	imageY = 17;			//�摜y���W
	maxImageX = 2;			//�摜�Qx���W
	maxImageY = 16;			//�摜�Qy���W
	underImageX = 24;		//���n�摜x���W
	underImageY = 17;		//���n�摜y���W
	overImageX = 24;		//��g�摜x���W
	overImageY = 16;		//��g�摜y���W
}
ManBar::ManBar(){
	/*������*/
	pos = Vec2(40.0*tipSize, 9.0*tipSize);		//�ʒu
	name = "�l";			//���O
	//�����l�ɂ��Ă͎��@�̃R���X�g���N�^�Őݒ�
	size = 10;				//�o�[�̕��i�����͂P�Œ�j
	imageX = 32;			//�摜x���W
	imageY = 17;			//�摜y���W
	maxImageX = 4;			//�摜�Qx���W
	maxImageY = 16;			//�摜�Qy���W
	underImageX = 24;		//���n�摜x���W
	underImageY = 17;		//���n�摜y���W
	overImageX = 24;		//��g�摜x���W
	overImageY = 16;		//��g�摜y���W
}
FireBar::FireBar(){
	/*������*/
	pos = Vec2(40.0*tipSize, 11.0*tipSize);		//�ʒu
	name = "��";			//���O
	//�����l�ɂ��Ă͎��@�̃R���X�g���N�^�Őݒ�
	size = 10;				//�o�[�̕��i�����͂P�Œ�j
	imageX = 32;			//�摜x���W
	imageY = 16;			//�摜y���W
	maxImageX = 3;			//�摜�Qx���W
	maxImageY = 16;			//�摜�Qy���W
	underImageX = 24;		//���n�摜x���W
	underImageY = 17;		//���n�摜y���W
	overImageX = 24;		//��g�摜x���W
	overImageY = 16;		//��g�摜y���W
}

GoldLabel::GoldLabel(){
	/*������*/
	pos = Vec2(38.0*tipSize, 28.0*tipSize);		//�ʒu
	name = "�f�n�k�c�@";			//���O
}
ScoreLabel::ScoreLabel(){
	/*������*/
	pos = Vec2(38.0*tipSize, 30.0*tipSize);		//�ʒu
	name = "�r�b�n�q�d";			//���O
}
HiScoreLabel::HiScoreLabel(){
	/*������*/
	pos = Vec2(38.0*tipSize, 32.0*tipSize);		//�ʒu
	name = "�g�h�r�b�n�q�d";			//���O
}

ResultManLabel::ResultManLabel(){
	/*������*/
	pos = Vec2(SCREEN_WIDTH/2 - 10.0*tipSize, SCREEN_WIDTH/2 - 10.0*tipSize);		//�ʒu
	name = "�����l���F";			//���O
}

void ResultManLabel::draw(Tomasen& game){
	char checktext[256] = "";
	game.IMAGE->printText((int)getPos().x/tipSize, 
		(int)getPos().y/tipSize, 
		getName().c_str());
	sprintf_s(checktext, sizeof(checktext), "%8d", getPrintValue());
	game.IMAGE->printText((int)getPos().x/tipSize + 7, 
		(int)getPos().y/tipSize, 
		checktext);
	game.IMAGE->printText((int)getPos().x/tipSize + 11, 
		(int)getPos().y/tipSize, 
		"�l");
}
ResultScoreLabel::ResultScoreLabel(){
	/*������*/
	pos = Vec2(SCREEN_WIDTH/2 - 10.0*tipSize, SCREEN_WIDTH/2 - 8.0*tipSize);		//�ʒu
	name = "�r�b�n�q�d�F";			//���O
}

} //namespace tm2