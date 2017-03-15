#ifndef INCLUDED_OBJ_EFFECT_HPP
#define INCLUDED_OBJ_EFFECT_HPP

#include <vector>		//vector
#include <memory>		//shared_ptr

#include "tomasen.hpp"

// std::tr1:: �� std:: �Ə�����悤��
namespace std {
	using namespace tr1; 
}

namespace tm2{

class Effect : public Object{
protected:
	int timeOfLife;		//�����t���[��
	Vec2 targetPos;		//�ړ��ړI���W
	int moveMode;			//�G�t�F�N�g���[�h�@0:�^�[�Q�b�g�ړ��A1:���W�A���w��ړ��A2:xy�w��ړ�

public:
	/*�R���X�g���N�^*/
	Effect();
	/*getter�֐�*/
	int getTimeOfLife(){return timeOfLife;}
	Vec2 getTargetPos(){return targetPos;}
	/*setter�֐�*/
	void setTimeOfLife(int timeOfLife){Effect::timeOfLife = timeOfLife;}
	void setTargetPos(Vec2 targetPos){Effect::targetPos = targetPos;}
	void setMoveMode(int moveMode){Effect::moveMode = moveMode;}
	/*�X�V�֐�*/
	void update(Tomasen& game);
	/*�`��֐�*/
	void draw(Tomasen& game);
};
/*�O���[�o�����\�[�X�錾*/
typedef weak_ptr< Effect > EffectWptr;		//�G�t�F�N�g��weak�|�C���^
typedef shared_ptr< Effect > EffectSptr;	//�G�t�F�N�g��shared�|�C���^
typedef vector< EffectSptr > EffectVsptr;	//�G�t�F�N�g��shared�|�C���^�̔z��
extern EffectVsptr effectList;				//�G�t�F�N�g���X�g
void effectFactory(EffectSptr effectList);	//�G�t�F�N�g�t�@�N�g���֐�
void effectFactory(EffectSptr effectList, Vec2 pos, Vec2 targetPos);	//�G�t�F�N�g�t�@�N�g���֐�
void effectFactory(EffectSptr effectList, double centerX, double centerY, Vec2 targetCenterPos);	//�G�t�F�N�g�t�@�N�g���֐�

class Earth : public Effect {
public:
	Earth();
};
class Mars : public Effect {
public:
	Mars();
};
class Jupiter : public Effect {
public:
	Jupiter();
};
class Saturn : public Effect {
public:
	Saturn();
};
class Uranus : public Effect {
public:
	Uranus();
};
class Neptune : public Effect {
public:
	Neptune();
};
class LockOnAlart : public Effect {
public:
	LockOnAlart();
};
class Explosion : public Effect {
public:
	Explosion();
};
class Smoke : public Effect {
public:
	Smoke();
};
class TitleTo : public Effect {
public:
	TitleTo();
};
class TitleMa : public Effect {
public:
	TitleMa();
};
class TitleSe : public Effect {
public:
	TitleSe();
};
class TitleNi : public Effect {
public:
	TitleNi();
};

class DarkR : public Effect {
public:
	DarkR();
};
class LightR : public Effect {
public:
	LightR();
};
class DarkY : public Effect {
public:
	DarkY();
};
class LightY : public Effect {
public:
	LightY();
};
class DarkG : public Effect {
public:
	DarkG();
};
class LightG : public Effect {
public:
	LightG();
};
class DarkB : public Effect {
public:
	DarkB();
};
class LightB : public Effect {
public:
	LightB();
};
class PushSpace : public Effect {
public:
	PushSpace();
};
class Wakka : public Effect {
public:
	Wakka();
	void draw(Tomasen &game);
};
class Star1 : public Effect {
public:
	Star1();
	void draw(Tomasen &game);
};
class Star2 : public Effect {
public:
	Star2();
	void draw(Tomasen &game);
};
class Dust1 : public Effect {
public:
	Dust1();
};
class TextScreen : public Effect {
public:
	DrawTextImage *TEXT;

	TextScreen();
	void update(Tomasen &game);
	void draw(Tomasen &game);
};
class TextBox : public Effect {
public:
	TextBox();
	void update(Tomasen &game);
	void draw(Tomasen &game);
	void setName2(string name2);
private:
	string name2;
};
class Marker : public Effect {
public:
	Marker();
	void update(Tomasen &game);
	void draw(Tomasen &game);
};
class Smoke2 : public Effect {
public:
	Smoke2();
};

} //namespace tm2
#endif//INCLUDED_OBJ_EFFECT_HPP