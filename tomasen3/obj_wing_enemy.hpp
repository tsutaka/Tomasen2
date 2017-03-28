#ifndef INCLUDED_OBJ_WING_ENEMY_HPP
#define INCLUDED_OBJ_WING_ENEMY_HPP



#include "common.hpp"
#include "obj_wing.hpp"

namespace tm2{

class EnemyA : public Enemy{
public:
	/*�R���X�g���N�^*/
	EnemyA();	
	/*�X�V�֐�*/
	void update(Tomasen& game);
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyB : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyB();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyC : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyC();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyD : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyD();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyE : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyE();
	/*�X�V�֐�*/
	void update(Tomasen& game);	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyF : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyF();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyG : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyG();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyH : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyH();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyI : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyI();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyJ : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyJ();	
	/*�X�V�֐�*/
	void update(Tomasen& game);
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyK : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyK();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyL : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyL();	
	/*�s���֐�*/
	void action(Object obj);
};

class EnemyN : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyN();	
	/*�s���֐�*/
	void action(Object obj);
};


class EnemyO : public Enemy{
public:
	double shotCnt;
public:
	/*�R���X�g���N�^*/
	EnemyO();	
	/*�s���֐�*/
	void action(Object obj);
};

} //namespace tm2
#endif//INCLUDED_OBJ_WING_ENEMY_HPP